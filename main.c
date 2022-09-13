#include <stdio.h>
#include <stdlib.h>
#include "libs/myio.h"
#include "libs/structs.h"
#include "libs/parse.h"
#include "libs/logic.h"
#define MOVE_RIGHT 1
#define MOV_LEFT 0
#define DO_NOTHING 2
#define STOP 3
// ghghg
int main(int argc, char **argv){
    if(argc < 2){
        printf("No file to intereptate\n");
        return 0;
    }
    int debug = 0;
    char *fileName, *flag, format[] = ".tu4";
    if(argc == 3){
        if(argv[1][0] == '-'){
            flag = argv[1];
            fileName = argv[2];
        }
        else if(argv[2][0] == '-'){
            flag = argv[2];
            fileName = argv[1];
        }
        else{
            printf("Error\n");
            return 0;
        }
        if(flag[1] == 'd' && flag[2] == 0){
            debug = 1;
        }
        else if(flag[1] == 'b' && flag[2] == 0){
            debug = 2;
        }
        else{
            printf("Unknown flag %s\n", flag);
        }
    }
    else if(argc == 2){
        fileName = argv[1];
    }
    else{
        printf("Wrong use\n");
        return 0;
    }
    
    FILE *filePtr = fopen(fileName, "r");
    if(filePtr == NULL){
        printf("No such file or directory \"%s\"\n", fileName);
        return 0;
    }
    
    
    
    int alphabetLength, tapeLength, cursorIndex, modesQuantity, mode = 0;
    char *alphabet;
    int *tape;
    Instruction **instructions;
    if(!ParseFromFile(filePtr, &alphabetLength, &alphabet, &modesQuantity, &instructions)){
        return 0;
    }
    if(!ParseFromTape(&tapeLength, &tape, alphabetLength, alphabet, &cursorIndex)){
        return 0;
    }
    if(debug){
        printf("cursor index: %d, mode: %d\n", cursorIndex, mode);
        for(int i = 0; i < tapeLength; i++){
            printf("%c", alphabet[tape[i]]);
        }
        printf("\n");
        if(debug == 2){
            int c = getchar();
            printf("%c\n", c);
            if(c == 'd'){
                debug = 1;
            }
            else if(c == 'f'){
                debug = 0;
            }
        }
    }
    while(Execute(tape, tapeLength, &cursorIndex, alphabetLength, alphabet, modesQuantity, instructions, &mode)){
        if(debug){
            printf("cursor index: %d, mode: %d\n", cursorIndex, mode);
            for(int i = 0; i < tapeLength; i++){
                printf("%c", alphabet[tape[i]]);
            }
            printf("\n");
            if(debug == 2){
                int c = getchar();
                if(c == 'd'){
                    debug = 1;
                }
            }
        }
    }
    
    if(debug){
        printf("cursor index: %d, mode: %d\n", cursorIndex, mode);
    }
    for(int i = 0; i < tapeLength; i++){
        printf("%c", alphabet[tape[i]]);
    }
    printf("\n");
    for(int i = 0; i < modesQuantity; i++){
        free(instructions[i]);
    }
    free(instructions);
    free(alphabet);
    free(tape);
    return 0;
}
