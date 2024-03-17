#include "Retirement.h" //Source file needs to include header file
#include <iostream> //Includes iostream for output and input
#include <iomanip> //Includes iomanip for manipulation of text
#include <cmath> //Includes cmath to use rounding and other math


/* estimateDriver */
//Estimate driver prompts the user for all inputs necessary to calculate how much will be saved by the user by retirement
//Calls upon several validation function to ensure things like non-negative numbers when appropriate and only numbers, etc.
void Retirement::estimateDriver()
{
  //Spaces string to account for weird formatting
  string spaces = "        ";

  //Error message gets passed into validation functions by reference
  //and gets changed to the appropriate error message for the situation
  string errorMessage;
  
  //Initialization for all necessary variables
  int currentAge, retiredAge;
  double alreadySaved, monthlyContribution, annualReturnPercentage;

  //temp is the string that stores all the inputs individually and is fed into input validators
  string tempInput;

  cout << "Estimate Savings at Retirement" << endl;
  cout << "Disclaimer: This is only a rough estimate!\n" << endl;

  //Prompts user for the first age
  cout << spaces << "Enter your current age in years: ";
  cin >> tempInput;
  while(!validCurrentAge(tempInput, errorMessage))
    {
      cout << spaces << errorMessage << endl;
      cout << spaces << "Re-enter your age in years: ";
      cin >> tempInput;
    }
  //Converts it to an int and stores it for the calculation
  currentAge = stoi(tempInput);

  //Prompts user for the retirement age
  cout << spaces << "Enter your target retirement age: ";
  cin >> tempInput;
  while(!validRetiredAge(currentAge, tempInput, errorMessage))
    {
      cout << spaces << errorMessage << endl;
      cout << spaces << "Re-enter your target age in years: ";
      cin >> tempInput;
    }
  //Converts it into an int and stores it for the calculation
  retiredAge = stoi(tempInput);

  //Prompts user for savings that have already been made
  cout << spaces << "How much have you saved towards retirement?: $";
  cin >> tempInput;
  while(!validSavings(tempInput, errorMessage))
    {
      cout << spaces << errorMessage << endl;
      cout << spaces << "Re-enter your savings: $";
      cin >> tempInput;
    }
  //Converts it into a double and stores it for the calculation
  alreadySaved = stod(tempInput);

  //Prompts user for monthly contribution to retirement
  cout << spaces << "Enter your monthly contribution to retirement: $";
  cin >> tempInput;
  while(!validMonthlyContributions(tempInput, errorMessage))
    {
      cout << spaces << errorMessage << endl;
      cout << spaces << "Re-enter your monthly contribution: $";
      cin >> tempInput;
    }
  //Converts it into a double and stores it for the calculation
  monthlyContribution = stod(tempInput);

  cout << spaces << "Enter the estimated annual return on investment (in percent): ";
  cin >> tempInput;
  while(!validAnnualReturnPercentage(tempInput, errorMessage))
    {
      cout << spaces << errorMessage << endl;
      cout << spaces << "Re-enter your rate (in percent): ";
      cin >> tempInput;
    }
  //Converst tempInput into a double and stores it for the calculation
  annualReturnPercentage = stod(tempInput);
  
  //Calls upon the actual calculator and feeds it all necessary variables and values
  estimateEarnings(currentAge, retiredAge, alreadySaved, monthlyContribution, annualReturnPercentage);
}

/* Validation Functions */
//All validation Functions will start by validating the input string (from user) for a number
//Also checks for a + or - at the beginning
//Will then check that the number is valid for the situation

/* validCurrentAge */
//Validates current age (greater than zero)
bool Retirement::validCurrentAge(string currentAge, string &errorMessage)
{
  for(int i = currentAge.length() - 1; i > 0; i --)
  {
    if(!isdigit(currentAge[i]))
    {
      errorMessage = "Your current age has to be a number.";
      return false;
    }
  }
  if(!isdigit(currentAge[0]) && currentAge[0] != '-' && currentAge[0] != '+')
  {
    errorMessage = "Your current age has to be a number.";
    return false;
  }

  int intAge = stoi(currentAge);
  errorMessage = "Age cannot be 0 or less.";
  return intAge > 0;
}

/* validRetiredAge */
//Validates the retirementa ge (greater than current and comparison age)
bool Retirement::validRetiredAge(int currentAge, string retiredAge, string &errorMessage)
{
  for(int i = retiredAge.length() - 1; i > 0; i --)
  {
    if(!isdigit(retiredAge[i]))
    {
      errorMessage = "Your retired age has to be a number.";
      return false;
    }
  }
  if(!isdigit(retiredAge[0]) && retiredAge[0] != '-' && retiredAge[0] != '+')
  {
    errorMessage = "Your retired age has to be a number.";
    return false;
  }

  int intRetiredAge = stoi(retiredAge);
  errorMessage = "Your target age cannot be less than or equal your current age.";
  return intRetiredAge > currentAge;
}

/* validSavings */
//Validates the savings amount (non-negative)
bool Retirement::validSavings(string savings, string &errorMessage)
{
  for(int i = savings.length() - 1; i > 0; i --)
  {
    if(!isdigit(savings[i]))
    {
      errorMessage = "Your savings has to be a number.";
      return false;
    }
  }
  if(!isdigit(savings[0]) && savings[0] != '-' && savings[0] != '+')
  {
    errorMessage = "Your savings has to be a number.";
    return false;
  }

  double doubleSavings = stod(savings);
  errorMessage = "Your savings cannot be negative.";
  return doubleSavings >= 0;
}

/* validMonthlyContributions */
//Validates monthly contributions (greater than zero)
bool Retirement::validMonthlyContributions(string monthly, string &errorMessage)
{
  for(int i = monthly.length() - 1; i > 0; i --)
  {
    if(!isdigit(monthly[i]))
    {
      errorMessage = "Your monthly contributions has to be a number.";
      return false;
    }
  }
  if(!isdigit(monthly[0]) && monthly[0] != '-' && monthly[0] != '+')
  {
    errorMessage = "Your monthly contributions has to be a number.";
    return false;
  }

  double doubleMonthly = stod(monthly);
  errorMessage = "Your monthly contribution cannot be less than or equal to zero.";
  return doubleMonthly > 0;
}

/* validAnnualReturnPercentage */
//Validates annual return percentage (non-negative)
bool Retirement::validAnnualReturnPercentage(string annualReturnPercentage, string &errorMessage)
{
  for(int i = annualReturnPercentage.length() - 1; i > 0; i --)
  {
    if(!isdigit(annualReturnPercentage[i]))
    {
      errorMessage = "Your rate has to be a number.";
      return false;
    }
  }
  if(!isdigit(annualReturnPercentage[0]) && annualReturnPercentage[0] != '-' && annualReturnPercentage[0] != '+')
  {
    errorMessage = "Your rate has to be a number.";
    return false;
  }

  double doubleReturnPercentage = stod(annualReturnPercentage);
  errorMessage = "Your rate cannot be less than zero.";
  return doubleReturnPercentage >= 0;
}

/* estimateEarnings */
//Calculates how much will be saved based on all of the information and formats it for the user
double Retirement::estimateEarnings(int currentAge, int retiredAge, double alreadySaved, double monthlyContribution, double annualReturnPercentage)
{
  //Variables intitialized, months are needed since the interest occurs monthly
  //Starting balance is set to what has already been saved
  //monthlyReturnPercentage is annual divdied by 1200 (12 for months, 100 for percentage)
  //moneyDeposited tracks how much is deposited overtime and is set to starting balance
  int currentAgeMonths = (retiredAge - currentAge) * 12;
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
  cout << "...calculating\n" << endl;
  cout << "Estimated Retirement Savings: $";
  cout << fixed << setprecision(2) << balance << endl;
  cout << "Estimated Retirement Growth: $";
  cout << fixed << setprecision(2) << balance - moneyDeposited << endl << endl;
  return balance;
}
