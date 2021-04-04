//Shubhayu Shrestha 1001724804
#include "GameLib.h"

int StartGame(char ChosenPhrase[], FILE *FH, Song tracks[])
{
    int choice = 0; 
    int choiceCount = 0; 
    //creating empty character array DashPhrase
    char DashPhrase[MAX_INPUT] = {};
    
    fseek(FH, 0, SEEK_SET);
    int numberOfSongs = ReadFileIntoArray(tracks, FH);

    if(numberOfSongs == 0)
    {
        printf("All of the games have been played - please reload file\n");
        exit(0); 
    }
    

    //Printing the Welcome message
    printf("\nWelcome to 3 STRIKES - YOU'RE OUT - the CSE version\n\n");
    printf("Please pick a song from the following menu\n\n");  

    int i; 
    for(i = 0; i < numberOfSongs; i++)
    {
        printf("%d. %s's song that was released in %s in the album %s\n", i+1, tracks[i].artist, tracks[i].releaseDate, tracks[i].albumName);
    }


    //asking user to enter their choice and test to see if it is out of bounds.
    while(choice<1 || choice >= i+1)
    {
        if(choiceCount!=0)
        {
            printf("\nChoice was out of bounds...\n"); 
            printf("Please pick a phrase listed from the following menu:\n"); 
        }
        printf("\nEnter choice : ");
        scanf("%d", &choice); 
        getchar(); 
        choiceCount++; 
        printf("\n"); 
    }
    choice = choice-1; 
    
    //Return the dashphrase inside the chosen phrase

    //copying the chosen phrase and "passing" it back to the main function
    strcpy(ChosenPhrase,tracks[choice].songTitle);

    return choice; 
}

void DashIt(char *Phrase, char DashPhrase[]) // done
{   
    char *indexOf; 
    int j; 
    for(j = 0; j < strlen(Phrase)+1; j++)
    {
        *(DashPhrase + j) = toupper(Phrase[j]); 
    }

    indexOf = strpbrk(DashPhrase, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    
    while(indexOf != NULL)
    {
        *indexOf = '-';
        indexOf = strpbrk(DashPhrase, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    }
    
}

void CheckPhrase(char *Phrase) // done
{
    char *indexOf = NULL; 
    indexOf = strchr(Phrase,'-');

    int position = 0;

    if(indexOf != NULL)
    {
        int i;
        for(i = 0; i < strlen(Phrase);i++)
        {
            if(*(Phrase + i) == '-')
            {
                position = i;
            }
        }

        printf("\n\n%s contains a dash in position %d!! You broke the rules. We can’t play. BYE!!\n\n", Phrase, position+1); 
        exit(1);
    }
}

int GuessALetter(char Phrase[], char DashedPhrase[], char UpperPhrase[])
{
    char GuessLetter;
    char Guess;
    char *FindGuess = NULL;
    char UpperPhraseCopy[MAX_INPUT] = {}; 
    int FoundALetter = 0; 
    int distance; 
    

    strcpy(UpperPhraseCopy, UpperPhrase); 

    printf("%s\n\n", DashedPhrase); 

    //asking user to guess a letter
    printf("Guess a letter : ");
    scanf("%c", &GuessLetter);
    getchar(); 
    
    Guess = toupper(GuessLetter); 
    //printf("\n%c\n", Guess); //using this to see if the character was stored properly 

    FindGuess = strchr(UpperPhraseCopy, Guess); 
    //printf("\n%p\n", FindGuess); //using this to see if a pointer is held 



    while(FindGuess != NULL)
    {
        
        FoundALetter = 1; 
        //Use pointer arithmetic to find the distance between FindGuess and UpperPhraseCopy. Use that distance to set the element in DashedPhrase to that same element from Phrase.
        
        distance = abs(UpperPhraseCopy - FindGuess);
        *(DashedPhrase+distance) = *(UpperPhraseCopy+distance);


        //Set the element at the same location/distance in UpperPhraseCopy to dash. You can do this using [] or by dereferencing FindGuess. Doing this prevents an infinite loop.
        UpperPhraseCopy[distance] = '-';

        FindGuess = strchr(UpperPhraseCopy, Guess); 
        
    }

    return FoundALetter; 

}
