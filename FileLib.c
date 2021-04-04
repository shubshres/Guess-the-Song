//Shubhayu Shrestha 1001724804
#include "FileLib.h"
#include "GameLib.h"

FILE* OpenFile(int argc, const char *argv[], char mode[])
{
    char filename[FILE_NAME_SIZE] = {}; 
    FILE *FH; 

    
    if(argc == 2)
    {
        strcpy(filename,argv[1]);
        get_command_line_parameter(argv, "FILENAME=", filename);
    }
    else if(argc == 3)
    {
        get_command_line_parameter(argv, "FILENAME=", filename);
        get_command_line_parameter(argv, "MODE=", mode);
    }
    else
    {
        printf("Must be run with an input file name.\n");
        printf("Enter a file name at the prompt:  "); 
        fgets(filename,FILE_NAME_SIZE-1,stdin);
        filename[strlen(filename)-1] = '\0';
        printf("\n"); 
    }

    FH = fopen(filename, mode);

    while(FH == NULL)
    { 
        printf("\nCould not open the file named %s\n", filename);
        printf("Enter a file name at the prompt:  "); 


        fgets(filename,FILE_NAME_SIZE-1,stdin);
        filename[strlen(filename)-1] = '\0';
        FH = fopen(filename,mode);
    }
    return FH; 
} 


int ReadFileIntoArray(Song tracks[], FILE* FH)
{
    char FileLine[200] = {};
    char *token = NULL;
    int MenuCount = 0; 

    while(MenuCount < MAX_ENTRIES && fgets(FileLine,sizeof(FileLine)-1, FH) != NULL)
    {
		if(FileLine[0]== '\0')
		{
			continue;
		}
		if(FileLine[strlen(FileLine) - 1] == '\n')
		{
			FileLine[strlen(FileLine) - 1] = '\0';
		}

        token = strtok(FileLine, "|");
        
        tracks[MenuCount].artist = malloc(strlen(token)*sizeof(char)+1);
        strcpy(tracks[MenuCount].artist,token);
        CheckPhrase(tracks[MenuCount].artist);
        
        token = strtok(NULL, "|");
        tracks[MenuCount].songTitle = malloc(strlen(token)*sizeof(char)+1);
        strcpy(tracks[MenuCount].songTitle,token);
        CheckPhrase(tracks[MenuCount].songTitle);

        token = strtok(NULL, "|");
        strcpy(tracks[MenuCount].releaseDate,token);
        CheckPhrase(tracks[MenuCount].releaseDate);

        token = strtok(NULL, "|");
        tracks[MenuCount].albumName = malloc(strlen(token)*sizeof(char)+1);
        strcpy(tracks[MenuCount].albumName,token);
        CheckPhrase(tracks[MenuCount].albumName);
        
        strtok(tracks[MenuCount].albumName,"\n");
        
        MenuCount++;
    }
    return MenuCount;
}


void WriteToFile(Song tracks[], int index, FILE *FH)
{   

    int currentPosition; 
    int endPosition; 
    int difference; 

    fseek(FH, 0, SEEK_SET); 

    int i = 0; 
    while(tracks[i].artist != NULL)
    {
        if(i!=(index))
        {
            fprintf(FH, "%s|%s|%s|%s\n", tracks[i].artist, tracks[i].songTitle, tracks[i].releaseDate, tracks[i].albumName);
            i++;
        }
        else
        {
            i++;
        }
    }

    currentPosition = ftell(FH);
    
    fseek(FH, 0, SEEK_END);
    endPosition = ftell(FH);

    difference = abs(endPosition-currentPosition);

    fseek(FH, (currentPosition), SEEK_SET);
    
    int j; 
    for(j = 0; j <= difference; j++)
    {
        fprintf(FH, "%c", '\0');
    }

    int k = 0; 
    while(tracks[k].artist != NULL)
    {
        free(tracks[k].artist);
        free(tracks[k].songTitle);
        free(tracks[k].albumName);
        k++; 
    }

    fclose(FH); 
}
