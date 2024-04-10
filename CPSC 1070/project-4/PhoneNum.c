/* File Name: PhoneNum.c
 * Name: Kenny Sun
 * Date: 12/3/2023
 * Purpose: Takes in a file and converts the contents of that file into 9 number
 * keypad style digits or takes the digits in the file and converts them into words
 * Citations:
 * Anon. ASCII table. Retrieved December 3, 2023a from https://www.asciitable.com/ 
 * Anon. FILE. Retrieved December 3, 2023b from https://cplusplus.com/reference/cstdio/FILE/ 
 * Anon. Fprintf. Retrieved December 3, 2023c from https://cplusplus.com/reference/cstdio/fprintf/ 
 * Anon. Fscanf. Retrieved December 3, 2023d from https://cplusplus.com/reference/cstdio/fscanf/ 
 * Academic Honesty Statement:
 * As members of the Clemson University community, we have inherited
 * Thomas Green Clemson’s vision of this institution as a “high seminary of
 * learning.” Fundamental to this vision is a mutual commitment to
 * truthfulness, honor, and responsibility, without which we cannot earn the
 * trust and respect of others. Furthermore, we recognize that academic
 * dishonesty detracts from the value of a Clemson degree. Therefore, we shall
 * not tolerate lying, cheating, or stealing in any form
 * Electronically Signed - Kenny Sun 
*/
#include "PhoneNum.h" //Source code needs own header
#include <stdlib.h> //Needed to allocate memory
#include <string.h> //Needed for string functions

/* conversionT9 */
//Takes in a file to read from, a file to output, and a conversion type and converts each line in the file
//From either words to a 9 number keypad texting style, or 9 number keypad texting style to words
void conversionT9(FILE *in, FILE *out, char type)
{  
  int numOfLines;
  //Initial scan for number of lines
  fscanf(in, "%d", &numOfLines); 
  char * nextLine;
  char * result;
  int i;
  fprintf(out, "%d\n", numOfLines);
  //Loops through each line and scans it in and either passes it to toWord or toDigits depending on type then saves it to the output
  for(i = 0; i < numOfLines; i ++)
    {
      nextLine = getNextChars(in);
      if(type == 'l')
	{
	  result = toDigits(nextLine);
	}
      else
	{
	  result = toWord(nextLine);
	}
      fprintf(out, "%s\n", result);
      free(result);
      result = NULL;
      free(nextLine);
      nextLine = NULL;
    }
}

//Array of each digit combination corresponding to the alphabet
const char * digitArray[26] = {"2", "22", "222", "3", "33", "333", "4", "44", "444", "5", "55", "555", "6", "66", "666", "7", "77", "777", "7777", "8", "88", "888", "9", "99", "999", "9999"};
//Alphabet array
const char * alphabet[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};

/* toWord */
//Takes in a string of digits separated by dashes and converts it into the word that would be formed if those digits were used in a 9 number keypad
char *toWord(char * digits)
{
  //Variable initialization
  //length holds the length of the digits input
  int length = strlen(digits);
  //numberOfChars counts the total number of characters the final return word has
  int numberOfChars = 0;

  //Counts the number of characters the final return word has (number of dashes + 1 as the end doesn't have a dash)
  int i;
  for(i = 0; i < length; i ++)
    {
      if(digits[i] == '-')
	{
	  numberOfChars++;
	}
    }
  numberOfChars += 1;
  
  //Allocates memory for the return string (+ 1 for null character)
  char * returnString = NULL;
  returnString = (char*)malloc((numberOfChars + 1) * sizeof(char));

  //Counter to iterates through each character of the return string
  int returnStringCounter = 0;

  //Characters processed to avoid going over the length of digits
  int charactersProcessed = 0;
  int clear;
  for(clear = 0; clear <= numberOfChars; clear ++)
  {
    returnString[clear] = '\0';
  }
  while(charactersProcessed < length)
    {
      //Counts the number of digits before a dash
      char singleChar = ' ';
      int numberOfNums = 0;
      //initialIndex is used when assigning the new string numbers from digits
      int initialIndex = charactersProcessed;
      //while there is no dash and the number is less than or equal (equal is used as a placeholder if there was a dash)
      while(singleChar != '-' && charactersProcessed <= length)
	{
	  //If we are not at the end, singleChar stores the next character to know when to exit b/c of a dash
	  if(charactersProcessed != length)
	    { 
	      singleChar = digits[charactersProcessed];
	    }
	  //numberOfNums and charactersProcessed gets iterated
	  numberOfNums ++;
	  charactersProcessed++;
	}
      //Removes the dash or null that was accounted for
      numberOfNums--;

      //Dynamically allocates memory for a string that stores a set of digits with the size of the number of digits + 1 for null
      char * numString;
      numString = (char*)malloc((numberOfNums + 1)* sizeof(char));
      int clear;
      for(clear = 0; clear <= numberOfNums; clear ++)
	{
	  numString[clear] = '\0';
	}
      
      //Iterates through the input and assigns the appropritate digits to numString
      int j;
      for(j = 0; j < numberOfNums; j ++)
	{
	  numString[j] = digits[j + initialIndex];
	}
      
      //Checks if numString matches to any of the premade digit arrays and adds the respective character to returnString if so
      int k;
      for(k = 0; k < 26; k ++)
	{
	  if(strcmp(digitArray[k], numString) == 0)
	    {
	      strcat(returnString, alphabet[k]);
	    }
	}
      //Free the dynamically allocated memory
      free(numString);
      numString = NULL;
    }
  return returnString;
}

/* toDigits */
//Takes in a word and converts each character to it's respective digits needed to type out the word on a 9 number keypad separating each letter with a dash
char *toDigits(char *word)
{
  //Variable initialization
  //lengthOfWord stores the length of the input word
  int lengthOfWord = strlen(word);
  //digitLength stores the total length of the final return string (numbers, dashes, and null)
  int digitLength = 0;

  //Iterates through the word and sums up the final length
  int i;
  for(i = 0; i < lengthOfWord; i ++)
    {
      int charToInt = ((int) word[i]) - 97;
      //Plus 1 for dashes or null
      digitLength += strlen(digitArray[charToInt]) + 1;
    }

  //Dynamically allocates memory to returnString the size that the string should be
  char * returnString;
  returnString = (char*)malloc(digitLength * sizeof(char));
  int clear;
  for(clear = 0; clear < digitLength; clear ++)
    {
      returnString[clear] = '\0';
    }
  //Loops through each letter in word and concatenates a set of digits corresponding and a dash if need be
  int j;
  for(j = 0; j < lengthOfWord; j ++)
    {
      if(j != lengthOfWord - 1)
	{
	  int charToInt = (int) word[j] - 97;
	  strcat(returnString, digitArray[charToInt]);
	  strcat(returnString, "-");
	}
      else
	{
	  int charToInt = (int) word[j] - 97;
          strcat(returnString, digitArray[charToInt]);
	}
    }
  return returnString;
}

/* getNextChars */
//Takes in a file and reads the next line of the file and returns it in a dynamically allocated array of characters
char *getNextChars(FILE *in)
{  
  //Variable Initialization
  char input[100] = "";

  //Scan a line into input
  fscanf(in, "%s", input);
  int numberOfChars = 0;
  //Counts the number of characters
  while(input[numberOfChars] != '\0')
    {
      numberOfChars ++;
    }

  //Dynamically allocates memory to returnString to hold the size of the line in the file and assigns it to it
  char * returnString;
  returnString = (char*)malloc((numberOfChars + 1)* sizeof(char));
  int clear;
  for(clear = 0; clear <= numberOfChars; clear++)
    {
      returnString[clear] = '\0';
    }
  int i;
  for(i = 0; i < numberOfChars; i ++)
    {
      returnString[i] = input[i];
    }
  returnString[numberOfChars] = '\0';
  return returnString;
}

//Array of the single digit corresponding to the alphabet
const char * singleDigitArray[26] = {"2", "2", "2", "3", "3", "3", "4", "4", "4", "5", "5", "5", "6", "6", "6", "7", "7", "7", "7", "8", "8", "8", "9", "9", "9", "9"};

/* textonymFind */
//Takes in a word and find all "textonyms" of that word in the dictionary and prints them out
//Textonym: 2 words that have the same digits used to type out using a T9 system
void textonymFind(char * word)
{
  //Opens dictionary file
  FILE * dictionary;
  dictionary = fopen("/usr/share/dict/words", "r");
  
  int length = strlen(word);
  char * wordToDigits;
  //102401 lines in the dictionary
  const int dictionaryWords = 102401;
  //Allocates memory for wordToDigits
  wordToDigits = (char*)malloc((length + 1) * sizeof(char));
 
  int i;
  //Clears the word
  for(i = 0; i <= length; i ++)
    {
      wordToDigits[i] = '\0';
    }
  //Makes the input word into a string of digits
  for(i = 0; i < length; i ++)
    {
      strcat(wordToDigits, singleDigitArray[(int) (word[i]) - 97]);
    }

  //Iterates through each word in the dictionary
  int j;
  for(j = 0; j < dictionaryWords; j ++)
    {
      //Stores a single word into dictionaryWord and gets its length
      //23 is the longest word length
      //Found using an external C++ program that iterated through the dictionary and found the longest word
      char dictionaryWord[24] = "";
      fscanf(dictionary, "%s", dictionaryWord);      
      int specialCharacters = 0;
      int dictionaryWordLength = 0;
      while(dictionaryWord[dictionaryWordLength] != '\0')
	{
	  dictionaryWordLength ++;
	}
      
      int k;
      //Checks for any special characters and converts the word to lower case
      for(k = 0; k < dictionaryWordLength; k ++)
	{
	  if(( (int) dictionaryWord[k] < 65 ) || ( (int) dictionaryWord[k] > 122 ) || ( (int) dictionaryWord[k] > 90 && (int) dictionaryWord[k] < 97))
	    {
	      specialCharacters = 1;
	    }
	  else
	    {
	      if( (int) dictionaryWord[k] >= 65 && (int) dictionaryWord[k] <= 90)
		{
		  dictionaryWord[k] = (char) ( (int) dictionaryWord[k] + 32 );
		}
	    }
	}

      //Ignroes all words with special characters
      if(specialCharacters == 0)
	{
	  //Allocates memory for the converted dictionary word
	  char * dictionaryWordToDigits;
	  dictionaryWordToDigits = (char*)malloc((dictionaryWordLength + 1) * sizeof(char));

	  //Clears the word
	  int l;
	  for(l = 0; l <= dictionaryWordLength; l ++)
	    {
	      dictionaryWordToDigits[l] = '\0';
	    }

	  //Iterates through the word and adds the appropriate digits
	  for(l = 0; l < dictionaryWordLength; l ++)
	    {
	      strcat(dictionaryWordToDigits, singleDigitArray[(int) (dictionaryWord[l]) - 97]);
	    }

	  //Compares both sets of digits and prints them out
	  if(strcmp(wordToDigits, dictionaryWordToDigits) == 0)
	    {
	      printf("%s\n", dictionaryWord);
	    }
	  //Frees dynamic memory
	  free(dictionaryWordToDigits);
	  dictionaryWordToDigits = NULL;
	}
    }
  free(wordToDigits);
  wordToDigits = NULL;
}
