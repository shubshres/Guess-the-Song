//Shubhayu Shrestha 1001724804
//Coding Assignment #7

//Bonus Attempted

#include "FileLib.h"
#include "GameLib.h"

void get_command_line_parameter(char *argv[], char PName[], char PValue[])
{
    int i = 1; 
    while(argv[i] != NULL)
    {
        if(!strncmp(argv[i], PName, strlen(PName)))
        {
            strcpy(PValue, strchr(argv[i], '=')+1);
        }
        i++;
    }
}

int main(int argc, const char * argv[]) 
{
    char Phrase[MAX_INPUT] = {};
    char DashedPhrase[MAX_INPUT] = {};
    char UpperPhrase[MAX_INPUT] = {};
    Song tracks[MAX_ENTRIES] = {};
    
    int letterIn;
    int strikes = 0;
    char mode[2] = {};     
    int index; 

    if(argc == 3)
    {
        strcpy(mode, argv[2]);
    }
    else
    {
        strcpy(mode, "r+");
    }
    

    FILE* FH = OpenFile(argc, argv, mode);
    
    //ReadFileIntoArray(tracks, FH);
    
    index = StartGame(Phrase, FH, tracks);

    
    
    char *PhrasePtr = Phrase; 

    //calling function DashIt() passing the phrase that stargame filled and the empty array DashedPhrase

    //dashing that chosen phrase
    DashIt(PhrasePtr, DashedPhrase);
     
    //creating a for loop that will go through and uppercase each character of Phrase and store the result in UpperPhrase
    int i; 
    for(i = 0; i < strlen(Phrase)+1; i++)
    {
        *(UpperPhrase + i) = toupper(Phrase[i]); 
    }

    
    
    do
    {
        letterIn = GuessALetter(Phrase, DashedPhrase, UpperPhrase);
        if(letterIn == 0)
        {
            strikes++; 
            if(strikes<STRIKES)
            {
                printf("Strike %d\n\n", strikes);
            }
        }


    }while((strchr(DashedPhrase, '-') != NULL) && (strikes < STRIKES));

    if(strikes < STRIKES)
    {
        printf("\nTHE PHRASE WAS: %s\n", (UpperPhrase)); 
        printf("\nYOU WON WITH ONLY %d STRIKES!!!!\n\n", strikes); 
        WriteToFile(tracks, index, FH); 
    }
    else
    {
        printf("\n%d STRIKES - YOUR'RE OUT\n\n", strikes); 
        printf("THE PHRASE WAS: %s\n", (UpperPhrase)); 
        printf("Game over\n\n"); 
    }

    
    return 0;
}
