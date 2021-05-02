#include <stdio.h>
#include <string.h>
#include "string-practice.h"

void printFirstLetters(char string[MAX_STRING][NAME_LENGTH])
{
    printf("First letters: ");
    for (int i = 0; i < MAX_STRING; i++) {
        printf("%c", string[i][0]);
    }
}

void printLastLetters(char string[MAX_STRING][NAME_LENGTH]) 
{
  printf("Last letters: ");
  for (int i = 0; i < MAX_STRING; i++) {
      printf("%c", string[i][strlen(string[i]) - 1]);
    }
}

/*
char *searchShortestName(char string[MAX_STRING][NAME_LENGTH]) 
{

  int shortest = -1;
  int index = -1;

  for (int i = 1; i < MAX_STRING; i++) {
    
    int current = 0;

    for (int j = 0; j < strlen(string[i]); i++) {
      
    }
    
    
    
  }

  return string[index];
}
*/

