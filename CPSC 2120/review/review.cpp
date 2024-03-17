#include "review.h"
#include <iostream>
using namespace std;

/* ReadStdIn */
//Reads in an int, double, and string in that order separated by whitespace
//before reprinting each of them out on new lines
void ReadStdIn()
{
  //Variable declaration
  int intVar;
  double doubleVar;
  string stringVar;

  //cin all 3 variables
  cin >> intVar;
  cin >> doubleVar;
  cin >> stringVar;
  //prints them out
  cout << intVar << endl << doubleVar << endl << stringVar << endl;
}

/* WriteOut */
//Takes in an input of either a string, int, or double then prints out
//and returns a 1 if the input was a string, a 2 if the input was an int,
//and a 3 if the input was a double
int WriteOut(string input)
{
  cout << input << endl;
  return 1;
}

int WriteOut(int input)
{
  cout << input << endl;
  return 2;
}

int WriteOut(double input)
{
  cout << input << endl;
  return 3;
}

/* ReadStdIn2 */
//Reads in phrases separated by white space and prints out the number of phrases read in after a "q"
void ReadStdIn2()
{
  //Variable declaration
  int count = 0;
  string input;
  
  //Initial read
  cin >> input;

  //Loop to keep reading
  while(input != "q")
    {
      count ++;
      cin >> input;
    }
  cout << count << endl;
}

/* ReadWrite */
//Reads in phrases separated by white spaces and prints them back out after a "q"
void ReadWrite()
{
  string input;
  string output;
  //Initial read
  cin >> input;

  //Loop to keep reading
  while(input != "q")
    {
      output += input;
      output += " ";
      cin >> input;
    }
  cout << output;

}

/* InitializeArray */
//Returns an int vector of size length filled with 0's
vector<int> InitializeArray(int length)
{
  vector<int> returnVector;
  for(int i = 0; i < length; i ++)
    {
      returnVector.push_back(0);
    }
  return returnVector;
}

/* LoopThrough */
//Loops through the input array and increments it all by 1
void LoopThrough(double * data, int size)
{
  for(int i = 0; i < size; i ++)
    {
      data[i] = data[i] + 1;
    }
}

/* Fibonacci */
//Returns the result of a number through the Fibonacci sequence
int Fibonacci(int a)
{
  //Base cases
  if(a == 1)
    {
      return 1;
    }
  else if(a == 0)
    {
      return 0;
    }
  //Fibonacci sequence
  else
    {
      return Fibonacci(a - 1) + Fibonacci(a - 2);
    }
}
