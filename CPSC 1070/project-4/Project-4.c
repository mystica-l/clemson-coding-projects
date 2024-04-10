/* File Name: Project-4.c
 * Name: Kenny Sun
 * Date: 12/3/2023
 * Purpose: Driver file for PhoneNum.c, uses command line arguments to take in input files,
 * output files, and conversion type from the user
 * Also validates input and output files based on them ending with .txt, length of command
 * line argument, and whether or not the file object can open it
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
#include <string.h> //Needed for string comparison and string functions
#include "PhoneNum.h" //Multi file programming
int main(int argc, char* argv[])
{
  //Checks for the help flag and letters flag and sets the int to the indexes
  int helpFlag = 0;
  int lettersFlag = 0;
  int i;
  for(i = 0; i < argc; i ++)
    {
      if(strcmp(argv[i], "-h") == 0)
	{
	  helpFlag = i;
	}
      else if(strcmp(argv[i], "-L") == 0)
	{
	  lettersFlag = i;
	}
    }

  FILE * in;
  FILE * out;

  //Checks for a helpFlag
  if(helpFlag != 0)
    {
      printf("PhoneNum T9 Conversion Tool. Usage:\n");
      printf("PhoneNum.exe <input file> <output file> [-L]\n");
      printf("-L Sets input type as letters instead of digits\n");
      printf("-h To get help\n");
    }
  //Checks if there's only one command line argument (the executable)
  else if(argc == 1)
    {
      printf("No input file given\n");
      printf("No output file given\n");
      printf("Use -h to get help\n");
    }
  //Takes care of situations without the letter flag
  else if(lettersFlag == 0)
    {
      //If there are 2 arguments, there's only the executable and input
      if(argc == 2)
	{
	  in = fopen(argv[1], "r");
	  int lengthOf2ndArg = strlen(argv[1]);
	  //If the input file doesn't exist, or the length of the 2nd argument is less than 5 (minimum of 5 for a.txt), or if the end of the input argument is not ".txt", there's an invalid input...
	  if(in == NULL || lengthOf2ndArg < 5 || argv[1][lengthOf2ndArg - 1] != 't' || argv[1][lengthOf2ndArg - 2] != 'x' || argv[1][lengthOf2ndArg - 3] != 't' || argv[1][lengthOf2ndArg - 4] != '.')
	    {
	      printf("Invalid input file\n");
	      printf("No output file give\n");
	      printf("Use -h to get help\n");
	    }
	  //Else, there's a valid input file but no output
	  else
	    {
	      printf("No output file given\n");
	      printf("Use -h to get help\n");
	    }
	  fclose(in);
	}
      //If there are 3 arguments, there's the executable, input, and output...
      else if(argc == 3)
	{
	  int inputLength = strlen(argv[1]);
	  int outputLength = strlen(argv[2]);
	  in = fopen(argv[1], "r");
	  out = fopen(argv[2], "w");
	  int invalidInput = 0;
	  int invalidOutput = 0;

	  //Checks if the input or output is invalid and prints out accordingly or runs the program
	  if(in == NULL || inputLength < 5 || argv[1][inputLength - 1] != 't' || argv[1][inputLength - 2] != 'x' || argv[1][inputLength - 3] != 't' || argv[1][inputLength - 4] != '.')
            {
	      invalidInput = 1;
	    }
	  if(out == NULL || outputLength < 5 || argv[2][outputLength - 1] != 't' || argv[2][outputLength - 2] != 'x' || argv[2][outputLength - 3] != 't' || argv[2][outputLength - 4] != '.')
            {
	      invalidOutput = 1;
	    }
	  
	  if(invalidInput == 1 && invalidOutput == 1)
	    {
	      printf("Invalid input file\n");
	      printf("Invalid output file\n");
	      printf("Use -h to get help\n");
	    }
	  else if(invalidInput == 1 && invalidOutput == 0)
	    {
	      printf("Invalid input file\n");
	      printf("Use -h to get help\n");
	    }
	  else if(invalidOutput == 1 && invalidInput == 0)
	    {
	      printf("Invalid output file\n");
	      printf("Use -h to get help\n");
	    }
	  else
	    {
	      conversionT9(in, out, 'd');
	    }
	  
	  fclose(in);
	  fclose(out);
	}
      //Otherwise, there's too many command line arguments
      else
	{
	  printf("Too many command line arguments!\n");
	}
    }
  //Takes care of the remaining command line arguments with the letter flag
  else if(lettersFlag != 0)
    {
      //2 arguments means there's only the executable and -L flag so no input or output
      if(argc == 2)
	{
	  printf("No input file given\n");
	  printf("No output file given\n");
	  printf("Use -h to get help\n");
	}
      //Only executable, -L, and input
      else if(argc == 3)
	{
	  //Gets the index and length of the input command line argument
	  int inputIndex = 0;
	  int inputLength = 0;
	  if(lettersFlag == 1)
	    {
	      inputIndex = 2;
	    }
	  else
	    {
	      inputIndex = 1;
	    }
	  in = fopen(argv[inputIndex], "r");
	  inputLength = strlen(argv[inputIndex]);

	  //If the input is invalid...
	  if(in == NULL || inputLength < 5 || argv[1][inputLength - 1] != 't' || argv[1][inputLength - 2] != 'x' || argv[1][inputLength - 3] != 't' || argv[1][inputLength - 4] != '.')
	    {
	      printf("Invalid input file\n");
	      printf("No output file given\n");
	      printf("Use -h to get help\n");
	    }
	  //Otherwise the input is valid but still no output
	  else
	    {
	      printf("No output file given\n");
	      printf("Use -h to get help\n");
	    }
	  fclose(in);
	}
      //Executable, -L, input, and output
      else if(argc == 4)
	{
	  //Gets the index and length of the input and output
	  int inputIndex = 0;
	  int inputLength = 0;
	  int outputIndex = 0;
	  int outputLength = 0;
	  if(lettersFlag == 1)
	    {
	      inputIndex = 2;
	      outputIndex = 3;
	    }
	  else if(lettersFlag == 2)
	    {
	      inputIndex = 1;
	      outputIndex = 3;
	    }
	  else
	    {
	      inputIndex = 1;
	      outputIndex = 2;
	    }
	  
	  in = fopen(argv[inputIndex], "r");
          inputLength = strlen(argv[inputIndex]);
	  out = fopen(argv[outputIndex], "w");
	  outputLength = strlen(argv[outputIndex]);

	  int invalidInput = 0;
	  int invalidOutput = 0;

	  //Checks if the input or output is invalid and prints out accordingly or runs the program
          if(in == NULL || inputLength < 5 || argv[inputIndex][inputLength - 1] != 't' || argv[inputIndex][inputLength - 2] != 'x' || argv[inputIndex][inputLength - 3] != 't' || argv[inputIndex][inputLength - 4] != '.')
            {
              invalidInput = 1;
            }
          if(outputLength < 5 || argv[outputIndex][outputLength - 1] != 't' || argv[outputIndex][outputLength - 2] != 'x' || argv[outputIndex][outputLength - 3] != 't' || argv[outputIndex][outputLength - 4] != '.')
            {
              invalidOutput = 1;
            }

          if(invalidInput == 1 && invalidOutput == 1)
            {
              printf("Invalid input file\n");
              printf("Invalid output file\n");
              printf("Use -h to get help\n");
            }
          else if(invalidInput == 1 && invalidOutput == 0)
            {
              printf("Invalid input file\n");
              printf("Use -h to get help\n");
            }
          else if(invalidOutput == 1 && invalidInput == 0)
            {
              printf("Invalid output file\n");
              printf("Use -h to get help\n");
            }
          else
            {
	      conversionT9(in, out, 'l');
            }
	  fclose(in);
	  fclose(out);
	}
      //Otherwise, there's too many command line arguments
      else
        {
          printf("Too many command line arguments!\n");
        } 
    }
}
