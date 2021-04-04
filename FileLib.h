//Shubhayu Shrestha 1001724804
#ifndef FileLib_h
#define FileLib_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "GameLib.h"


//Function Prototypes
FILE* OpenFile(int argc, const char *argv[],char mode[]);
int ReadFileIntoArray(Song tracks[], FILE* myFile);
void WriteToFile(Song tracks[], int index, FILE *FH);

#endif
