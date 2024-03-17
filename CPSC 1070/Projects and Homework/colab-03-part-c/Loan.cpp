#include "Loan.h" //Source file needs to include header file
#include <iostream> //Includes iostream for output and input
#include <iomanip> //Includes iomanip for manipulation of text
#include <cmath> //Includes cmath to use rounding and other math

/* paymentDriver */
//Takes in all the inputs needed to calculate how many months it takes to pay off a loan
//Sends those values through input validators to ensure valid inputs
void Loan::paymentDriver()
{
  //Error message gets passed into validation functions by reference
  //and gets changed to the appropriate error message for the situation
  string errorMessage;

  //tempInput stores all of the values inputted by the users and is fed through input validators
  string tempInput;

  //Initialized necessary variables for calculations
  double principalAmount, annualInterestRate, monthlyPayment;

  cout << "Loan Payment Calculator\n" << endl;

  //Prompts user for the principal amount
  cout << "Enter the principal amount: $";
  cin >> tempInput;
  while(!validPrincipalAmount(tempInput, errorMessage))
    {
      cout << errorMessage << endl;
      cout << "Re-enter your principal amount: ";
      cin >> tempInput;
    }
  principalAmount = stod(tempInput);

  //Prompts user for annual interest rate
  cout << "Enter the annual interest rate (in percent): ";
  cin >> tempInput;
  while(!validAnnualInterestRate(tempInput, errorMessage))
    {
      cout << errorMessage << endl;
      cout << "Re-enter your rate (in percent): ";
      cin >> tempInput;
    }
  annualInterestRate = stod(tempInput);

  //Prompts user for monthly payment
  cout << "Enter the monthly payment: $";
  cin >> tempInput;
  while(!validMonthlyPayment(tempInput, errorMessage))
    {
      cout << errorMessage << endl;
      cout << "Re-enter your monthly payment :$";
      cin >> tempInput;
    }
  monthlyPayment = stod(tempInput);

  //Calls upon the actual calculator function and sends all necessary information into it
  paymentMonths(principalAmount, annualInterestRate, monthlyPayment);
}

/* Validation Functions */
//All validation Functions will start by validating the input string (from user) for a number
//Also checks for a + or - at the beginning
//Will then check that the number is valid for the situation

/* validPrincipalAmount */
//Validates the principal amount (greater than zero)
bool Loan::validPrincipalAmount(string principalAmount, string &errorMessage)
{
  for(int i = principalAmount.length() - 1; i > 0; i --)
  {
    if(!isdigit(principalAmount[i]))
    {
      errorMessage = "Your principal amount has to be a number.";
      return false;
    }
  }
  if(!isdigit(principalAmount[0]) && principalAmount[0] != '-' && principalAmount[0] != '+')
  {
    errorMessage = "Your principal amount has to be a number.";
    return false;
  }

  double doublePrincipalAmount = stod(principalAmount);
  errorMessage = "Principal amount cannot be negative.";
  return doublePrincipalAmount > 0;
}

/* validAnnualInterestRate */
//Validates the annual interest rate (greater than zero)
bool Loan::validAnnualInterestRate(string annualInterestRate, string &errorMessage)
{
  for(int i = annualInterestRate.length() - 1; i > 0; i --)
  {
    if(!isdigit(annualInterestRate[i]))
    {
      errorMessage = "Your rate has to be a number.";
      return false;
    }
  }
  if(!isdigit(annualInterestRate[0]) && annualInterestRate[0] != '-' && annualInterestRate[0] != '+')
  {
    errorMessage = "Your rate has to be a number.";
    return false;
  }

  double doubleAnnualInterestRate = stod(annualInterestRate);
  errorMessage = "Your rate cannot be less than zero.";
  return doubleAnnualInterestRate > 0;
}

/* validMonthlyPayment */
//validates the monthly payment (greater than zero)
bool Loan::validMonthlyPayment(string monthlyPayment, string &errorMessage)
{
  for(int i = monthlyPayment.length() - 1; i > 0; i --)
  {
    if(!isdigit(monthlyPayment[i]))
    {
      errorMessage = "Your monthly payment has to be a number.";
      return false;
    }
  }
  if(!isdigit(monthlyPayment[0]) && monthlyPayment[0] != '-' && monthlyPayment[0] != '+')
  {
    errorMessage = "Your monthly payment has to be a number.";
    return false;
  }

  double doubleMonthlyPayment = stod(monthlyPayment);
  errorMessage = "Your monthly payment cannnot be negative.";
  return doubleMonthlyPayment > 0;
}

/* paymentMonths */
//Takes in all necessary information and calculates the number of months it takes to pay off a loan
//and formats it all for the user to read
int Loan::paymentMonths(double principalAmount, double annualInterestRate, double monthlyPayment)
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
