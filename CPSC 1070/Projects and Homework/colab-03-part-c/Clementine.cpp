#include <iostream> //Used to output and input things from the terminal
#include <string> //Used so string objects can be sed
#include "Loan.h"
#include "Retirement.h"
#include "Register.h"
using namespace std; //Used so std:: isn't necessary for every single string object or output

//Function prototypes
void runMenuSystem();
void printMenu();
string redoHandler(string);

int main()
{
  runMenuSystem();
  return 0;
}
  
/* printMenu */
//Used to print out all the text necessary for the first section of the menu interface
void printMenu()
{
  static bool firstRun = true;
  if(firstRun)
  {
    cout << "Starting Clementine Financial Bank" << endl;
    firstRun = false;
  }
  cout << "******* Welcome to Clementine Financial *******\n" << endl;
  cout << "Menu:" << endl;
  cout << "        [E] Estimate how much money at retirement" << endl;
  cout << "        [L] Loan payoff calculator" << endl;
  cout << "        [R] Run transaction classifier" << endl;
  cout << "        [Q] Quit program\n" << endl;
  cout << " Enter your choice and press enter: ";
}

/* runMenuSystem */
//Run menu system manages the menu and takes in user input to run calculations as well as quit
//and rerun programs 
void runMenuSystem()
{
  //Static variable
  //Input stores what the user wants to do and is only set to a blank string at the start of the program or when a user declines to rerun a certain calculation
  static string input = "";

  //Asks user for choice when input is a blank string
  if(input == "")
  {
      printMenu();
      cin >> input;
      //Input validation for only uppercase/lower case E, L, and Q
      while(input != "E" && input != "e" && input != "L" && input != "l" && input != "Q" && input != "q" && input != "R" && input != "r")
      {
        cout << "\nThe provided choice was invalid! Please select again.\n" << endl;
        printMenu();
        cin >> input;
      }
  }

  //Checks if the choice was to estimate retirement savings and runs it
  if(input == "E" || input == "e")
  {
    Retirement retirementObject;
    retirementObject.estimateDriver();
    //redoHandler will prompt user for whether or not they want to rerun the estimate calculator and return either an "E" or a blank string depending on choice
    input = redoHandler("estimate");
    //runMenuSystem will reset it
    runMenuSystem();
  }
  //Same syntax as the estimate handler but with the time to pay off loan calculator instead
  else if(input == "L" || input == "l")
  {
    Loan loanObject;
    loanObject.paymentDriver();
    //redoHandler will also prompt for a redo and return a "L" or a blank string dependng on the response by the user
    input = redoHandler("loan payoff");
    runMenuSystem();
  }
  else if(input == "R" || input == "r")
  {
    Register registerObject;
    registerObject.processTransaction();
    //redoHandler will also prompt for a redo and return a "L" or a blank string dependng on the response by the user
    input = redoHandler("register");
    runMenuSystem();
  }
  else
  {
    //Blank so the program will quit upon a "Q"
  }
}

/* redoHandler */
//Called in runMenuSystem
//Prompts user after each calcuation if they want to run another one and returns appropriate string based on if they do or not
string redoHandler(string choice)
{
  if(choice == "register")
  {
    cout << "Would you like to process another transaction register? (y/n): ";
  }
  else
  {
  cout << "Calculate another " << choice << "? (y/n): ";
  }

  string calculateAnother;
  cin >> calculateAnother;
  //Sends calculateAnother into a validator with a while loop to ensure a valid input
  while(calculateAnother != "y" && calculateAnother != "n" && calculateAnother != "Y" && calculateAnother != "N")
  {
    cout << "Invalid Input! Please choose again." << endl;
    if(choice == "register")
    {
      cout << "Would you like to process another transaction register? (y/n): ";
    }
    else
    {
    cout << "Calculate another " << choice << "? (y/n): ";
    }
    cin >> calculateAnother;
  }

  //If the choice is "Y", depending on which calculator was just run, choice will be different and it will return a different
  //value for input to be set to in the runMenuSystem function so when runMenuSystem is ran again after it, it will remain the
  //same due to static variables immediately jumping into another calculation
  if(calculateAnother == "y" || calculateAnother == "Y")
  {
      if(choice == "loan payoff")
      {
        return "L";
      }
      else if(choice == "estimate")
      {
        return "E";
      }
      else
      {
        return "R";
      }
  }
  else
  {
    //Sets string to "" if no is selected so the menu can prompt the user again
    cout << "\n";
    return "";
  }
}