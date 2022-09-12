#include "logic.h"
#include <stdio.h>

int Execute(int *tape, int tapeLength, int *cursorIndexPtr, int alphabetLength, char *alphabet, int modesQuantity, Instruction **instructions, int *modePtr){
    int cursorIndex = *cursorIndexPtr;
    int mode = *modePtr;
    Instruction curInstruction = instructions[mode][tape[cursorIndex]];
    if(curInstruction.action != STOP){
        mode = curInstruction.mode;
    }
    tape[cursorIndex] = curInstruction.symbol;
    switch (curInstruction.action)
    {
    case MOVE_RIGHT:
        cursorIndex += 1;
        cursorIndex %= tapeLength;
        break;
    case MOVE_LEFT:
        cursorIndex -= 1;
        if(cursorIndex < 0){
            cursorIndex = tapeLength - 1;
        }
        break;
    case STOP:
        return 0;
    default:
        break;
    }
    *cursorIndexPtr = cursorIndex;
    *modePtr = mode;
    
    return 1;
}