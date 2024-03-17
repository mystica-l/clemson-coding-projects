/* File Name: hw-4.c
 * Name: Kenny Sun
 * Date: 11/19/2023
 * Purpose: Generates 20 random sentences using a set list of articles, nouns, verbs, and prepositions
 */

#include <stdio.h> //Needed for output
#include <stdlib.h> //Needed for random numbers and dynamic memory allocation
#include <time.h> //Needed to seed random numbers
#include <ctype.h> //Needed for toupper()
#include <string.h> //Needed as we use string objects and functions

int main()
{
  //char pointer arrays containing articles, noun, verbs, and prepositions
  char* article[5] = {"the", "a", "one", "some", "any"};
  char* noun[5] = {"boy", "girl", "dog", "town", "car"};
  char* verb[5] = {"drove", "jumped", "ran", "walked", "skipped"};
  char* preposition[5] = {"to", "from", "over", "under", "on"};

  //Declaration of ints that are randomized and select from the pointer arrays
  int articleNum, nounNum, verbNum, prepositionNum, articleNum2, nounNum2;

  //Seeding of random
  srand(time(0));

  //For loop that prints 20 sentences
  int i;
  for(i = 0; i < 20; i ++)
    {
      //Random numbers
      articleNum = rand() % 5;
      nounNum = rand() % 5;
      verbNum = rand() % 5;
      prepositionNum = rand() % 5;
      articleNum2 = rand() % 5;
      nounNum2 = rand() % 5;

      //Dynamically allocated character pointer that gets the size of the first article
      char * firstWord;
      firstWord = (char *) malloc(sizeof(article[articleNum]));

      //Copy the word into the pointer and makes the first letter upper case 
      strcpy(firstWord, article[articleNum]);
      firstWord[0] = toupper(firstWord[0]);

      //Prints out each sentence
      printf("%s %s %s %s %s %s.\n", firstWord, noun[nounNum], verb[verbNum], preposition[prepositionNum], article[articleNum2], noun[nounNum2]);

      //Frees dynamically allocated memory
      free(firstWord);
      firstWord = NULL;
    }
}
