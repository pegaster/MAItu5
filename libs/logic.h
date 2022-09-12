#ifndef __LOGIC__
#define __LOGIC__
#include "structs.h"

int Execute(int *tape, int tapeLength, int *cursorIndexPtr, int alphabetLength, char *alphabet, int modesQuantity, Instruction **instruction, int *modePtr);

#endif