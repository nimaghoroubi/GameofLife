#include <stdio.h>
#include <stdlib.h>

int main(int c, char** v) {

    FILE *output;
    FILE *source;

    int h = atoi(v[1]);
    int w = atoi(v[2]);
    char *name = v[3];
    source = fopen(name,"r+w");
    output = fopen("final.gal","r+w");


    int* output_data = calloc(1,(h+2)*(w+2)* sizeof(int));
    fread(output_data,1,(h+2)*(w+2)* sizeof(int),output);
    fclose(output);


    int* source_data = calloc(1,(h+2)*(w+2)* sizeof(int));
    fread(source_data,1,(h+2)*(w+2)* sizeof(int),source);


    int check = 1 ;
    for (int i = 0; i < (w+2)*(h+2); ++i) {
        if (output_data[i] != source_data[i]){
            check = 0;
        }
    }

    if (check){
        printf("correct results\n");
    }else{
        printf("wrong results\n");
    }



    return 0;
}
