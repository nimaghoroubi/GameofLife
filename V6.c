/////////////////////////////////////////////////////////////////////////////////////////
////for correct usage read the readme.txt file, all syntax and usage is written there.
/////////////////////////////////////////////////////////////
/////////////////////////////////////////
//////////////////////////////
//////Nima Ghoroubi
//////////
///

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "graphics.h"
#include <immintrin.h>
#define depth 0
//universe density is when you choose blind universe creation within this program and not import any files
#define density 0.11 ///(0-1)


///graphics
int graphics;
const float GW = 1;
const float GH = 1;
const int   redColor    = 0;
const int   greenColor  = 1;
const int   yellowColor = 2;



void game(int h, int w, int time,char* filename);




int main(int c, char** v){

    int        h = 0;
    int        w = 0;
    graphics = 0;
    int     time = 0;
    char*   filename = NULL;
    int thread_num = 1;
//understanding the user arguments
    if (c == 3){
        h        = atoi(v[1]);
        w        = atoi(v[2]);
        graphics = 0;
        time     = 1000      ;
    }else if (c == 4) {
        h        = atoi(v[1]);
        w        = atoi(v[2]);
        graphics = atoi(v[3]);
        time     = 10000      ;
    }else if (c == 7){
        h        = atoi(v[1]);
        w        = atoi(v[2]);
        graphics = atoi(v[3]);
        time     = atoi(v[4]);
        filename =      v[5] ;
        thread_num = atoi(v[6]);
    }else{
        h    = 20;
        w    = 20;
        time = 20;
        graphics = 1;
    }
///setting number of threads and launching the computations
    omp_set_num_threads(thread_num);
    game(h,w,time,filename);

    printf("tested for %d %d universe size\n",h,w);
    return 0;

}

////////////////////////////////
///functions
////////////////////////////////



void game(int h, int w, int time,char* filename) {
    ///graphics initializing
    char *error;
    if (graphics) {
        InitializeGraphics(error, 900, 900);
        SetCAxes(0, 1);
    }

    ///filling the universe for this code!
    int *universe;
    if (filename == NULL) {
        ///create new one
        universe = _mm_malloc((w+2)*(h+2)* sizeof(int),32);

        for (int i = 1; i < h+1; ++i) {
            for (int j = 1; j < w+1; ++j) {
                universe[i*(w+2)+j] = rand() < RAND_MAX / ((double)1/density) ? 1 : 0;
            }
        }
    } else {
        ///read from file
        FILE *fp = fopen(filename, "r");
        universe = _mm_malloc((w+2)*(h+2)* sizeof(int),32);

        for (int i = 1; i < h + 1; ++i) {
            fread(&universe[i*(w+2)+1], 1, w * sizeof(int), fp);
        }
    }


    int* limbo = _mm_malloc((w+2)*(h+2)* sizeof(int),32);

    for (int iter = 0; iter < time; ++iter) {
        if(graphics){
            Refresh();
            ClearScreen();
            usleep(90000);
        }
        ///evolve, this used to be a function but now its kind of inlined and is here!
//memset is used to clean the limbo memory block with vector register helps
        memset(limbo,0, (w+2)*(h+2)*sizeof(int));
#pragma omp parallel for schedule(static)
        for (int i = 1; i< h+1; i = i + 1) {
            for (int j1 = 1; j1 < w+1; j1 = j1 + 4) {

                for (int j = j1; j < j1+4; ++j) {
		    /// each node is summed up to neighbor values, and then checked for next life iteration condition
                    limbo[i * (w + 2) + j] = universe[(i - 1) * (w + 2) + (j - 1)] + universe[(i - 1) * (w + 2) + (j)] +
                                             universe[(i - 1) * (w + 2) + (j + 1)]
                                             + universe[(i) * (w + 2) + (j - 1)] + universe[(i) * (w + 2) + (j + 1)]
                                             + universe[(i + 1) * (w + 2) + (j - 1)] + universe[(i + 1) * (w + 2) + (j)] +
                                             universe[(i + 1) * (w + 2) + (j + 1)];

                    if (universe[i * (w + 2) + j] && limbo[i * (w + 2) + j] == 2) {
                        limbo[i * (w + 2) + j] = 1;
                    } else if (universe[i * (w + 2) + j] && limbo[i * (w + 2) + j] == 3) {
                        limbo[i * (w + 2) + j] = 1;
                    } else if (limbo[i * (w + 2) + j] == 3) {
                        limbo[i * (w + 2) + j] = 1;
                    } else {
                        limbo[i * (w + 2) + j] = 0;
                    }
                }

            }
        }


        //// swapping the limbo and the universe to remove need for copying element by element
        int* buffer = universe;
        universe = limbo;
        limbo = buffer;
	// plot the living cells if asked for!
        if(graphics){
            for (int i = 1; i < h+1; ++i) {
                for (int j = 1; j < w+1; ++j) {
                    if (universe[(i) * (w + 2) + (j)]==1){
                        DrawCircle(((float) j) / w + ((float) 1 / w), ((float) i) / h + ((float) 1 / h),
                                   GW + (2 * (float) 1 / w), GH + (2 * (float) 1 / h), 0.002, 0, redColor);
                    }
                }
            }
        }
    }

    FILE *rt;
    rt = fopen("final.gal", "w+");
    fwrite(universe, (w+2)*(h+2)*sizeof(int),1,rt);
    fclose(rt);

//free the allocated memory
    _mm_free(limbo);
    _mm_free(universe);
}

