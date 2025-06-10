#include <stdio.h>
#include "../include/file_operation.h"


void check_saves(){
    int available[4]={0,0,0,0};
    FILE *qwerty = fopen("saves/save_1.txt","rt");
    if(qwerty!=NULL){
        available[0]=1;
        fclose(qwerty);
    }
    qwerty = fopen("saves/save_2.txt","rt");
    if(qwerty!=NULL){
        available[1]=1;
        fclose(qwerty);
    }
    qwerty = fopen("saves/save_3.txt","rt");
    if(qwerty!=NULL){
        available[2]=1;
        fclose(qwerty);
    }
    qwerty = fopen("saves/save_4.txt","rt");
    if(qwerty!=NULL){
        available[3]=1;
        fclose(qwerty);
    }
    printf("Save slots in use:");
    for(int i=0;i<4;i++) if(available[i]!=0) printf(" %d", i+1);
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

char *slot_name(int slot){
    if(slot<1 || slot>4){
        printf("\nError: Invalid slot number\n");
        return NULL;
    }
    char *savefile_name = malloc(16*sizeof(char));
    if (!savefile_name) {
        printf("\nError: Memory allocation failed.\n");
        return NULL;
    }
    strcpy(savefile_name, "saves/save_0.txt");
    savefile_name[11] = '0' + slot; // Convert int to char
    return savefile_name;
}

int save(Board *board, char turn, int slot){
    check_saves();
    char *save_name = slot_name(slot);
    if(save_name==NULL) { printf("\nError: Invalid save name\n"); return -1;}
    FILE *savefile = fopen(save_name,"wt");
    if(savefile==NULL){
        printf("\nError: Couldn't open file: %s\n", save_name);
        free(save_name);
        return 1;
    }
    
    fprintf(savefile,"%d %d ", board->score.black_count, board->score.white_count);
    fprintf(savefile, "%c\n", turn);
    fprintf(savefile, "%d ", board->size);
    for(int i=0; i<board->size;i++){
        for(int j=0; j<board->size;j++){
            fprintf(savefile, "%c", board->board[i][j]);
        }
    }

    free(save_name);
    fclose(savefile);
    return 0;
}

int load(Board *board, int slot){
    check_saves();
    char player;
    char *save_name = slot_name(slot);
    if(save_name==NULL) { printf("\nError: Invalid save slot\n"); return -1;}
    FILE *savefile = fopen(save_name,"rt");
    if(savefile==NULL){
        printf("\nError: Couldn't open file: %s\n", save_name);
        free(save_name);
        return -1;
    }

    fscanf(savefile,"%d %d ", &board->score.black_count, &board->score.white_count);
    fscanf(savefile, "%c\n", &player);
    fscanf(savefile, "%d ", &board->size);
    for(int i=0; i<board->size;i++){
        for(int j=0; j<board->size;j++){
            fscanf(savefile, "%c", &board->board[i][j]);
        }
    }

    free(save_name);
    fclose(savefile);
    return player;
}