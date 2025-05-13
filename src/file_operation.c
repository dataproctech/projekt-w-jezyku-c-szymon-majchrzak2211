#include <stdio.h>
#include "../include/file_operation.h"


int check_saves(){

}

char *get_save_name(){
    printf("\nChoose save slot (1/2/3/4): ");
    char slot;
    scanf(" %c", &slot);
    if(slot!='1' && slot!='2' && slot!='3' && slot!='4'){
        printf("\nError: Make sure to put a number from 1 to 4.\n");
        return NULL;
    }
    char *savefile_name = malloc(16*sizeof(char));
    if (!savefile_name) {
        printf("\nError: Memory allocation failed.\n");
        return NULL;
    }
    strcpy(savefile_name, "saves/save_0.txt");
    savefile_name[11]=slot;

    return savefile_name;
}

int save(Board *board){
    char *save_name = get_save_name();
    if(save_name==NULL) { printf("\nError: Invalid save name\n"); return -1;}
    FILE *savefile = fopen(save_name,"wt");
    if(savefile==NULL){
        printf("\nError: Couldn't open file: %s\n", save_name);
        free(save_name);
        return 1;
    }
    printf("Placeholder");

    free(save_name);
    fclose(savefile);
    return 0;
}