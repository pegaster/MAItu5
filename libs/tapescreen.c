#include "tapescreen.h"
#include <stdio.h>

void PrintTape(int tapeLength, int *tape, int alphabetLength, char *alphabet, int cursorIndex, int flag){
     for(int i = 0; i < tapeLength; i++){
        
        if(i == cursorIndex && flag){
            printf("\x1B[42m%c\033[0m", alphabet[tape[i]]);
        }
        else{
            printf("%c", alphabet[tape[i]]);
        }
    }
    printf("\n");
}