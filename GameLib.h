//Shubhayu Shrestha 1001724804
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileLib.h"

#ifndef GameLib_h
#define GameLib_h
#define MAX_INPUT 81
#define STRIKES 3
#define MAX_ENTRIES 100
#define FILE_NAME_SIZE 50

typedef struct
{
    char *artist; 
    char *songTitle; 
    char *albumName;
    char releaseDate[5];
}Song;


//Function Prototypes
int StartGame(char ChosenPhrase[], FILE *FH, Song tracks[]);
void checkPhrase(char *Phrase);
void DashIt(char *Phrase, char DashedPhrase[]);
int GuessALetter(char Phrase[], char DashedPhrase[], char UpperPhrase[]);

#endif 
