/* Kenny Chea Sun
 * CPSC 1071: 002
 * 5 Guys
 * October 1st, 2023
 */

#include <iostream> //Used to print things to the terminal and recieve inputs from the user cout/cin
#include <string> //Used for string objects
#include <iomanip> //Used for manipulation of text printed to the terminal like fixed and setprecision
#include <cmath> //Used for math functions necessary for the calculations like natural log and rounding

using namespace std;

//Prototypes for functions
void runMenuSystem();
void printMenu();
void estimateDriver();
double estimateEarnings(int, int, int, double, double, double);
void paymentDriver();
int paymentMonths(double, double, double);
bool validCurrentAge(string);
bool validComparisonAge(int, string);
bool validRetiredAge(int, int, string);
bool validSavings(string);
bool validMonthlyContributions(string);
bool validMoneyAmount(string);
bool validAnnualReturnPercentage(string);
bool validPrincipalAmount(string);
bool validAnnualInterestRate(string);
bool validMonthlyPayment(string);
string redoHandler(string);

/* main */
//First function called when program is run, used to call runMenuSystem
int main()
{
  runMenuSystem();
  return 0;
}

/* printMenu */
//Used to print out all the text necessary for the first section of the menu interface
void printMenu()
{
  cout << "******* Welcome to Clementine Financial *******\n" << endl;
  cout << "Menu:" << endl;
  cout << "        [E] Estimate how much money at retirement" << endl;
  cout << "        [L] Loan payoff calculator" << endl;
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
      while(input != "E" && input != "e" && input != "L" && input != "l" && input != "Q" && input != "q")
	{
	  cout << "\nThe provided choice was invalid! Please select again.\n" << endl;
	  printMenu();
	  cin >> input;
	}
    }

  //Checks if the choice was to estimate retirement savings and runs it
  if(input == "E" || input == "e")
    {
      estimateDriver();
      //redoHandler will prompt user for whether or not they want to rerun the estimate calculator and return either an "E" or a blank string depending on choice
      input = redoHandler("estimate");
      //runMenuSystem will reset it
      runMenuSystem();
    }
  //Same syntax as the estimate handler but with the time to pay off loan calculator instead
  else if(input == "L" || input == "l")
    {
      paymentDriver();
      //redoHandler will also prompt for a redo and return a "L" or a blank string dependng on the response by the user
      input = redoHandler("loan payoff");
      runMenuSystem();
    }
  else
    {
      //Blank so the program will quit upon a "Q"
    }
}

/* estimateDriver */
//Estimate driver prompts the user for all inputs necessary to calculate how much will be saved by the user by retirement
//Calls upon several validation function to ensure things like non-negative numbers when appropriate, etc.
void estimateDriver()
{
  //Spaces string to account for weird formatting
  string spaces = "        ";

  //Initialization for all necessary variables
  int currentAge, comparisonAge, retiredAge;
  double alreadySaved, monthlyContribution, annualReturnPercentage;
  //temp is the string that stores all the inputs individually and is fed into input validators
  string tempInput;

  cout << "Estimate Savings at Retirement" << endl;
  cout << "Disclaimer: This is only a rough estimate!\n" << endl;

  //Prompts user for the first age
  cout << spaces << "Enter the first starting age in years: ";
  cin >> tempInput;
  //Sends tempInput into a validator with a while loop to ensure a valid input
  while(!validCurrentAge(tempInput))
    {
      cout << spaces << "Age cannot be 0 or less." << endl;
      cout << spaces << "Re-enter your age in years: ";
      cin >> tempInput;
    }
  //Converts it to an int and stores it for the calculation
  currentAge = stoi(tempInput);

  //Prompts user for the secnod age
  cout << spaces << "Enter the second starting age in years: ";
  cin >> tempInput;
  //Sends tempInput into a validator with a while loop to ensure a valid input
  while(!validComparisonAge(currentAge, tempInput))
    {
      cout << spaces << "Age cannot be 0 or less." << endl;
      cout << spaces << "Re-enter your second starting age in years: ";
      cin >> tempInput;
    }
  //Converts it into an int and stores it for the calculation
  comparisonAge = stoi(tempInput);

  //Prompts user for the retirement age
  cout << spaces << "Enter your target retirement age: ";
  cin >> tempInput;
  //Sends tempInput into a validator with a while loop to ensure a valid input
  while(!validRetiredAge(currentAge, comparisonAge, tempInput))
    {
      cout << spaces << "Your target age cannot be less than or equal your current age." << endl;
      cout << spaces << "Re-enter your target age in years: ";
      cin >> tempInput;
    }
  //Converts it into an int and stores it for the calculation
  retiredAge = stoi(tempInput);

  //Prompts user for savings that have already been made
  cout << spaces << "How much have you saved already towards retirement?: $";
  cin >> tempInput;
  //Sends tempInput into a validator with a while loop to ensure a valid input
  while(!validSavings(tempInput))
    {
      cout << spaces << "Your savings cannot be negative." << endl;
      cout << spaces << "Re-enter your savings: $";
      cin >> tempInput;
    }
  //Converts it into a double and stores it for the calculation
  alreadySaved = stod(tempInput);

  //Prompts user for monthly contribution to retirement
  cout << spaces << "Enter your monthly contribution to retirement: $";
  cin >> tempInput;
  //Sends tempInput into a validator with a while loop to ensure a valid input
  while(!validMonthlyContributions(tempInput))
    {
      cout << spaces << "Your monthly contribution cannot be less than or equal to zero." << endl;
      cout << spaces << "Re-enter your monthly contribution: $";
      cin >> tempInput;
    }
  //Converts it into a double and stores it for the calculation
  monthlyContribution = stod(tempInput);

  cout << spaces << "Enter the estimated annual return on investment (in percent): ";
  cin >> tempInput;
  //Sends tempInput into a validator with a while loop to ensure a valid input
  while(!validAnnualReturnPercentage(tempInput))
    {
      cout << spaces << "Your rate cannot be less than zero." << endl;
      cout << spaces << "Re-enter your rate (in percent): ";
      cin >> tempInput;
    }
  //Converst tempInput into a double and stores it for the calculation
  annualReturnPercentage = stod(tempInput);
  
  //Calls upon the actual calculator and feeds it all necessary variables and values
  estimateEarnings(currentAge, comparisonAge, retiredAge, alreadySaved, monthlyContribution, annualReturnPercentage);
}

/* validCurrentAge */
//Validates current age (greater than zero)
bool validCurrentAge(string currentAge)
{
  int intAge = stoi(currentAge);
  return intAge > 0;
}

/* validComparisonAge */
//Validates comparison age (greater than current age)
bool validComparisonAge(int currentAge, string comparisonAge)
{
  int intComparisonAge = stoi(comparisonAge);
  return intComparisonAge > currentAge;
}

/* validRetiredAge */
//Validates the retirementa ge (greater than current and comparison age)
bool validRetiredAge(int currentAge, int comparisonAge, string retiredAge)
{
  int intRetiredAge = stoi(retiredAge);
  return intRetiredAge > currentAge && intRetiredAge > comparisonAge;
}

/* validSavings */
//Validates the savings amount (non-negative)
bool validSavings(string savings)
{
  double doubleSavings = stod(savings);
  return doubleSavings >= 0;
}

/* validMonthlyContributions */
//Validates monthly contributions (greater than zero)
bool validMonthlyContributions(string monthly)
{
  double doubleMonthly = stod(monthly);
  return doubleMonthly > 0;
}

/* validAnnualReturnPercentage */
//Validates annual return percentage (non-negative)
bool validAnnualReturnPercentage(string annualReturnPercentage)
{
  double doubleReturnPercentage = stod(annualReturnPercentage);
  return doubleReturnPercentage >= 0;
}

/* estimateEarnings */
//Calculates how much will be saved based on all of the information and formats it for the user
double estimateEarnings(int currentAge, int comparisonAge, int retiredAge, double alreadySaved, double monthlyContribution, double annualReturnPercentage)
{
  //Variables intitialized, months are needed since the interest occurs monthly
  //Starting balance is set to what has already been saved
  //monthlyReturnPercentage is annual divdied by 1200 (12 for months, 100 for percentage)
  //moneyDeposited tracks how much is deposited overtime and is set to starting balance
  int currentAgeMonths = (retiredAge - currentAge) * 12;
  int comparisonAgeMonths = (retiredAge - comparisonAge) * 12;
  double balance = alreadySaved;
  double monthlyReturnPercentage = annualReturnPercentage / 1200;
  double moneyDeposited = alreadySaved;

  //For each month, the balance grows by how much was added to the account + how much the balance is times the monthly return precentage
  for(int i = 0; i < currentAgeMonths; i++)
    {
      //Keeps track of how much was deposited to compare actual growth to money inputted
      moneyDeposited += monthlyContribution;
      double growth = balance * monthlyReturnPercentage;
      balance = balance + monthlyContribution + growth;
    }

  //Prints text to the terminal and the amounts in a formatted manner
  //Shows the user the total savings and how much money was actually grown
  cout << ".\n." << endl;
  cout << "...calculating" << endl;
  cout << "For starting to save at retirement at age " << currentAge << ":\n" << endl;
  cout << "Estimated Retirement Savings: $";
  cout << fixed << setprecision(2) << balance << endl;
  cout << "Estimated Retirement Growth: $";
  cout << fixed << setprecision(2) << balance - moneyDeposited << endl;

  //comparisonBalance and comparisonMonthlyDeposited do the same thing as the originals but use the comparison age instead
  double comparisonBalance = alreadySaved;
  double comparisonMoneyDeposited = alreadySaved;
  for(int i = 0; i < comparisonAgeMonths; i++)
    {
      comparisonMoneyDeposited += monthlyContribution;
      double growth = comparisonBalance * monthlyReturnPercentage;
      comparisonBalance = comparisonBalance + monthlyContribution + growth;
    }

  //Shows the user how much was missed out on in terms of money if they start saving for retirement later
  cout << "\nFor starting to save at retirement at age " << comparisonAge << ":\n" << endl;
  cout << "Estimated Retirement Savings: $";
  cout << fixed << setprecision(2) << comparisonBalance << endl;
  cout << "Estimated Retirement Growth: $";
  cout << fixed << setprecision(2) << comparisonBalance - comparisonMoneyDeposited << endl;
  cout << "\n\n\nFor a difference in waiting " << comparisonAge - currentAge << " years before starting to invest in retirement, you can miss out potentially on $";
  cout << fixed << setprecision(2) << balance - comparisonBalance << endl;

  return balance;
}

/* paymentDriver */
//Takes in all the inputs needed to calculate how many months it takes to pay off a loan
//Sends those values through input validators to ensure valid inputs
void paymentDriver()
{
  //tempInput stores all of the values inputted by the users and is fed through input validators
  string tempInput;

  //Initialized necessary variables for calculations
  double principalAmount, annualInterestRate, monthlyPayment;
  cout << "Loan Payment Calculator\n" << endl;

  //Prompts user for the principal amount
  cout << "Enter the principal amount: $";
  cin >> tempInput;
  //Sends tempInput into a validator with a while loop to ensure a valid input
  while(!validPrincipalAmount(tempInput))
    {
      cout << "Principal amount cannot be negative." << endl;
      cout << "Re-enter your principal amount: ";
      cin >> tempInput;
    }
  //Converts it to a double and stores it for calculations
  principalAmount = stod(tempInput);

  //Prompts user for annual interest rate
  cout << "Enter the annual interest rate (in percent): ";
  cin >> tempInput;
  //Sends tempInput into a validator with a while loop to ensure a valid input
  while(!validAnnualInterestRate(tempInput))
    {
      cout << "Your rate cannot be less than zero." << endl;
      cout << "Re-enter your rate (in percent): ";
      cin >> tempInput;
    }
  //Converts it into a double and stores it for calculations
  annualInterestRate = stod(tempInput);

  //Prompts user for monthly payment
  cout << "Enter the monthly payment: $";
  cin >> tempInput;
  //Sends tempInput into a validator with a while loop to ensure a valid input
  while(!validMonthlyPayment(tempInput))
    {
      cout << "Your monthly payment cannnot be negative." << endl;
      cout << "Re-enter your monthly payment :$";
      cin >> tempInput;
    }
  //Converts it into a double and stores it for calculations
  monthlyPayment = stod(tempInput);

  //Calls upon the actual calculator function and sends all necessary information into it
  paymentMonths(principalAmount, annualInterestRate, monthlyPayment);
}

/* validPrincipalAmount */
//Validates the principal amount (greater than zero)
bool validPrincipalAmount(string principalAmount)
{
  double doublePrincipalAmount = stod(principalAmount);
  return doublePrincipalAmount > 0;
}

/* validAnnualInterestRate */
//Validates the annual interest rate (greater than zero)
bool validAnnualInterestRate(string annualInterestRate)
{
  double doubleAnnualInterestRate = stod(annualInterestRate);
  return doubleAnnualInterestRate > 0;
}

/* validMonthlyPayment */
//validates the monthly payment (greater than zero)
bool validMonthlyPayment(string monthlyPayment)
{
  double doubleMonthlyPayment = stod(monthlyPayment);
  return doubleMonthlyPayment > 0;
}

/* paymentMonths */
//Takes in all necessary information and calculates the number of months it takes to pay off a loan
//and formats it all for the user to read
int paymentMonths(double principalAmount, double annualInterestRate, double monthlyPayment)
{
  //Variables initialized
  double months;
  //Additional payment is initialized to 15 to show the comparison if the user paid an extra $15 a month
  int additionalPayment = 15;

  //Calculations
  double numerator = log(monthlyPayment) - log(monthlyPayment - ((annualInterestRate/1200.0) * principalAmount));
  double denominator = log((annualInterestRate/1200.0) + 1.0);
  months = numerator / denominator;

  //Calculations with the extra $15 a month
  double fewerMonths;
  numerator = log(monthlyPayment + additionalPayment) - log(monthlyPayment + additionalPayment - ((annualInterestRate/1200.0) * principalAmount));
  denominator = log((annualInterestRate/1200.0) + 1.0);
  fewerMonths = numerator / denominator;

  //Shows the years needed to pay off
  double years = months / 12;
  
  //values are printed out using formatting
  cout << "\nCalculating...\n" << endl;
  cout << fixed << setprecision(0) << months << " months (";
  cout << fixed << setprecision(1) << years << " years) are needed to pay your loan off.\n" << endl;

  //Shows the comparison between the monthly payment and the monthly payment with the additional $15
  double diffMonths = round(months) - round(fewerMonths);

  //Prints out final statement
  cout << "Did you know if you paid an additional $" << additionalPayment << " per month, you would pay off your loan ";
  cout << fixed << setprecision(0) << diffMonths << " months earlier?\n" << endl;

  return round(months);
}

/* redoHandler */
//Called in runMenuSystem
//Prompts user after each calcuation if they want to run another one and returns appropriate string based on if they do or not
string redoHandler(string choice)
{
  cout << "Calculate another " << choice << "? (y/n): ";

  string calculateAnother;
  cin >> calculateAnother;
  //Sends calculateAnother into a validator with a while loop to ensure a valid input
  while(calculateAnother != "y" && calculateAnother != "n" && calculateAnother != "Y" && calculateAnother != "N")
    {
      cout << "\nThe provided choice was invalid! Please select again.\n" << endl;
      cout << "Calculate another " << choice << "? (y/n): ";
      cin >> calculateAnother;
    }

  //If the choice is "Y", depending on which calculator was just run, choice will be different and it will return a different
  //value for input to be set to in the runMenuSystem function so when runMenuSystem is ran again after it, it will remain the
  //same due to static variables immediately jumping into another calculation
  if(calculateAnother == "y" || calculateAnother == "Y")
    {
      cout << "\n";
      if(choice == "loan payoff")
	{
          return "L";
        }
      else
        {
          return "E";
        }
    }
    else
    {
      //Sets string to "" if no is selected so the menu can prompt the user again
      cout << "\n";
      return "";
    }
}
