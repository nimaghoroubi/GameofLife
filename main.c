#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"

///graphics
const float GW = 1;
const float GH = 1;
const int   redColor    = 0;
const int   greenColor  = 1;
const int   yellowColor = 2;



void create_universe(int h, int w, char* filename);

int main(int c, char** v) {
    printf("Hello, World! oh, wait!\n"
           "I hope you know the syntax of being a god in this universe!\n"
           "it's h w universename.gal\n"
           "have you used it correctly?...\n");

    ///graphics
    InitializeGraphics(v[0],700,700);
    SetCAxes(0,1);


    int h, w;
    char* filename;

    ///initializing values
    if (c == 4){
        printf("First step of creating a universe is correct!\n");
        h = atoi(v[1]);
        w = atoi(v[2]);
        filename = v[3];
    }else{
        printf("Maybe read a book on how to be a god to a microverse?\n"
               "your inputs were wrong, pay attention to syntax\n"
               "it's h w universename.gal\n");
    }


    ///see if user wants to create or see a universe
    printf("Do you want to see a universe you created or make a new one? (see/make)\n");
    char decision[10];
    scanf("%s",decision);

    if(strncmp(decision,"see",3)==0){
        ///see the universe
        FILE* fp = fopen(filename,"r");
        if (fp == NULL){
            printf("No universe exists in that name\n");
            exit(1);
        }
        int d;
        ClearScreen();
        for (int i = 0; i < h+2; ++i) {
            for (int j = 0; j < w+2; ++j) {
               fread(&d,1, sizeof(int),fp);
               if (d){
                   DrawCircle(((float)j)/w, ((float)i)/h, GW, GH, 0.002, 0, redColor);
               }
            }

        }
        Refresh();
        sleep(5);


    } else if(strncmp(decision,"make",4)==0){
        ///create a new one
        create_universe(h,w,filename);
        printf("do you want to see your world? (yes/no)\n");
        char answer[3];
        scanf("%s",answer);
        if (strncmp(answer,"yes",3)==0){
            Refresh();
            sleep(5);
        } else{
            printf("then we are done! bye bye\n");
        }
    }

    return 0;

}



////////////////////////////////////////////////////////////////////////////////////////////
///functions
////////////////////////////////////////////////////////////////////////////////////////////

void create_universe(int h, int w, char* filename){
    FILE* fp = fopen(filename,"w+");
    int** universe = (int**)calloc(1,(h+2)* sizeof(int*));
    for (int i = 0; i < h+2; ++i) {
        universe[i] = (int*)calloc(1,(w+2)* sizeof(int));
    }

    for (int i = 1; i < h+1; ++i) {
        for (int j = 1; j < w+1; ++j) {
            universe[i][j] = rand() < RAND_MAX/300 ? 1 : 0;

        }

    }

    for (int i = 0; i < h+2; ++i) {
        for (int j = 0; j < w+2; ++j) {
            fwrite(&universe[i][j],1, sizeof(int),fp);
            if (universe[i][j]){
                DrawCircle(((float)j)/w, ((float)i)/h, GW, GH, 0.002, 0, redColor);
            }
        }

    }


    for (int i = 0; i < h+2; ++i) {
        free(universe[i]);
    }
    free(universe);

};
