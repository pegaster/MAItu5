#include <stdio.h>
#include <stdlib.h>
#include "myio.h"
#include "parse.h"

int ParseFromFile(FILE *filePtr, int *alphabetLengthPtr, char **alphabetPtr, int *modesQuantityPtr, Instruction ***instructionsPtr){
    int alphabetLength, modesQuantity, end = 0;
    char *buff = (char *)malloc(sizeof(char) * BUFF_LENGTH);
    char c;

    FGetLine(filePtr, buff, BUFF_LENGTH);
    int result;
    if(!(result = sscanf(buff, "alphabet length: %d", &alphabetLength)) || result == EOF){
        printf("line 1: parsing error, you need write length of alphabet\n");
        return 0;
    }
    char *alphabet = (char *)malloc(sizeof(char) * alphabetLength + 1);
    while ((c = fgetc(filePtr)) != '\n')
    {
        alphabet[end++ + 1] = c;
        if (c == EOF){
            printf("line 2: parsing error, EOF\n");
            return 0;
        }
        if (end > alphabetLength){
            printf("line 2: parsing error, alphabet is longer then length\n");
            return 0;
        }
    }
    if (alphabetLength - end > 1){
        printf("line 2: parsing error, alphabet is shorter then length\n");
        return 0;
    }
    alphabet[0] = '_';
    alphabetLength += 1;

    FGetLine(filePtr, buff, 200);
    if(!(result = sscanf(buff, "modes: %d\n", &modesQuantity)) || result == EOF){
        printf("line 3: parsing error, you need write modes quantity\n");
        return 0;
    }
    if (modesQuantity > 98){
        printf("you can't use more than 98 modes\n");
    }
    Instruction **instructions = (Instruction **)malloc(sizeof(Instruction *) * modesQuantity);
    for(int i = 0; i < modesQuantity; i++){
        instructions[i] = (Instruction *)malloc(sizeof(Instruction) * alphabetLength);
        for(int j = 0; j < alphabetLength; j++){
            Instruction stop;
            stop.symbol = j;
            stop.action = STOP;
            instructions[i][j] = stop;
        }
    }
    int lineCount = 4;
    while(!FGetLine(filePtr, buff, BUFF_LENGTH)){
        int curMode, newMode;
        char curSymbol, newSymbol, action;
        result = sscanf(buff, "%d, %c, %c, %c, %d", &curMode, &curSymbol, &newSymbol, &action, &newMode);
        if(result < 4 || result == 4 && action != '#'){
            
            printf("line %d: \"%s\"parsing error, not enough params\n", lineCount, buff);
            return 0;
        }
        if(curMode < 0 || curMode > 98){
            printf("line %d: error, mode number is more than 98\n", lineCount);
            return 0;
        }
        int flag = 2;
        int curSymbolIndex, newSymbolIndex;
        for(int i = 0; i < alphabetLength; i++){
            if(alphabet[i] == curSymbol){
                flag -= 1;
                curSymbolIndex = i;
            }
            if(alphabet[i] == newSymbol){
                flag -= 1;
                newSymbolIndex = i;
            }
            if(flag == 0){
                break;
            }
        }
        if(flag){
            printf("line %d: error, symbols \'%c\' not in alphabet\n", lineCount, curSymbol);
            return 0;
        }
        instructions[curMode][curSymbolIndex].symbol = newSymbolIndex;
        
        if (result == 5){
            instructions[curMode][curSymbolIndex].mode = newMode;
        }
        switch (action)
        {
        case '>':
            instructions[curMode][curSymbolIndex].action = MOVE_RIGHT;
            break;
        
        case '<':
            instructions[curMode][curSymbolIndex].action = MOVE_LEFT;
            break;

        case '=':
            instructions[curMode][curSymbolIndex].action = DO_NOTHING;
            break;
        
        case '#':
            instructions[curMode][curSymbolIndex].action = STOP;
            break;

        default:
            printf("line %d: error, unknown action \'%c\'\n", lineCount, action);
            return 0;
        }
        lineCount++;
        
    }
    
    fclose(filePtr);
    free(buff);
    *alphabetLengthPtr = alphabetLength;
    *alphabetPtr = alphabet;
    *modesQuantityPtr = modesQuantity;
    *instructionsPtr = instructions;
    return 1;
}

int ParseFromTape(int *tapeLengthPtr, int **tapePtr, int alphabetLength, char *alphabet, int *cursorIndexPtr){
    int tapeLength, cursorIndex, end = 0, flag = 1;
    scanf("%d\n", &tapeLength);
    int *tape = (int *)malloc(sizeof(int) * tapeLength);
    char c;
    int index = -1;
    for(int i = 0; i < tapeLength; i++){
        if(flag){
            c = getchar();
            if(c == ' '){
                c = '_';
            }
            if (c == '\n' || c == EOF){
                flag = 0;
                c = '_';
            }

            for(int j = 0; j < alphabetLength; j++){
                if(alphabet[j] == c){
                    index = j;
                    break;
                }
            }
            if(index < 0){
                printf("symbol \'%c\' is not in alphabet\n", c);
                return 0;
            }
        }
        tape[i] = index; 
    }
    scanf("%d\n", &cursorIndex);
    *tapeLengthPtr = tapeLength;
    *tapePtr = tape;
    *cursorIndexPtr = cursorIndex;
    return 1;
}