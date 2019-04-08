#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"
#include <immintrin.h>
#define depth 0
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

    if (c == 3){
        h        = atoi(v[1]);
        w        = atoi(v[2]);
        graphics = 0;
        time     = 1000      ;
    }else if (c == 4) {
        h        = atoi(v[1]);
        w        = atoi(v[2]);
        graphics = atoi(v[3]);
        time     = 1000      ;
    }else if (c == 6){
            h        = atoi(v[1]);
            w        = atoi(v[2]);
            graphics = atoi(v[3]);
            time     = atoi(v[4]);
            filename =      v[5] ;
    }else{
        h    = 20;
        w    = 20;
        time = 20;
        graphics = 1;
    }

    game(h,w,time,filename);

    printf("%d %d\n",h,w);
    return 0;

}

////////////////////////////////
///functions
////////////////////////////////

void evolve(int h, int w,int** universe,int** limbo){

    for (int i = 0; i < h+2; ++i) {
        memset(limbo[i],0, (w+2)*sizeof(int));
    }

    for (int i = 1; i < h+1; ++i) {
        for (int j = 1; j < w+1; ++j) {
            limbo[i][j] = universe[i-1][j-1] + universe[i-1][j] + universe[i-1][j+1]
                    + universe[i][j-1] + universe[i][j+1] + universe[i+1][j-1] + universe[i+1][j] + universe[i+1][j+1];
        }

    }

    for (int i = 0; i < h+2; ++i) {
        for (int j = 0; j < w+2; ++j) {
            if (universe[i][j] && limbo[i][j] == 2){
                limbo[i][j] = 1;
            }else if(universe[i][j] && limbo[i][j] == 3){
                limbo[i][j] = 1;
            }else if(limbo[i][j] == 3){
                limbo[i][j] = 1;
            }else{
                limbo[i][j] = 0;
            }
	//universe[i][j]=limbo[i][j];
        }
    }



}


void game(int h, int w, int time,char* filename) {
    ///graphics initializing
    char *error;
    if (graphics) {
        InitializeGraphics(error, 900, 900);
        SetCAxes(0, 1);
    }

    ///filling the universe for this code!
    int **universe;
    if (filename == NULL) {
        ///create new one
        universe = _mm_malloc((h+2)* sizeof(int*),64);
        for (int i = 0; i < h + 2; ++i) {
            universe[i] = _mm_malloc((w+2)* sizeof(int),32);
        }
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                universe[i + 1][j + 1] = rand() < RAND_MAX / ((double)1/density) ? 1 : 0;
            }
        }
    } else {
        ///read from file
        FILE *fp = fopen(filename, "r");
        universe = _mm_malloc((h+2)* sizeof(int*),64);
        for (int i = 0; i < h + 2; ++i) {
            universe[i] = _mm_malloc((w+2)* sizeof(int),32);
        }

        for (int i = 1; i < h + 1; ++i) {
            fread(&universe[i][1], 1, w * sizeof(int), fp);
        }
    }


    int** limbo = _mm_malloc((h+2)* sizeof(int*),64);
    for (int i = 0; i < h + 2; ++i) {
        limbo[i] = _mm_malloc((w+2)* sizeof(int),32);
    }
    for (int iter = 0; iter < time; ++iter) {
        ///graphics
        if (graphics) {
            ClearScreen();
            for (int i = 0; i < h + 2; ++i) {
                for (int j = 0; j < w + 2; ++j) {
                    if (universe[i][j]) {
                        DrawCircle(((float) j) / w + ((float) 1 / w), ((float) i) / h + ((float) 1 / h),
                                   GW + (2 * (float) 1 / w), GH + (2 * (float) 1 / h), 0.002, 0, redColor);
                        //Refresh();
                        usleep(1);
                    } else if (!universe[i][j] && depth) {
                        DrawCircle(((float) j) / w + ((float) 1 / w), ((float) i) / h + ((float) 1 / h),
                                   GW + (2 * (float) 1 / w), GH + (2 * (float) 1 / h), 0.002, 0, greenColor);
                        Refresh();
                        usleep(1);
                    }
                }

            }
            Refresh();
            usleep(50000);
        }



        ///evolve
        evolve(h, w, universe, limbo);
	int** buffer = universe;
	universe = limbo;
 	limbo = buffer;
	


    }

    for (int k = 0; k < h+2; ++k) {
        _mm_free(limbo[k]);
    }
    _mm_free(limbo);

    for (int k = 0; k < h + 2; ++k) {
        _mm_free(universe[k]);
    }
    _mm_free(universe);
}

