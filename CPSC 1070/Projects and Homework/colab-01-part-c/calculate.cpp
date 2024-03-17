/* Kenny Chea Sun
 * CPSC 1071: 002
 * 5 Guys
 * September 13, 2023
 */
#include <iostream>
#include <cmath>
#include <iomanip> 
#include <cstdlib>
using namespace std;

//Prototypes for functions:
void outputManager();
double monthCalculator(double, double, double);

int main()
{
  outputManager();
  return 0;
}

//Output manager manages what the console displays
//and prints out as well as take in the necessary inputs
void outputManager()
{
  //Variables used for calculations
  double principalAmount;
  double annualInterestRate;
  double monthlyPayment;
  double months;
  double years;
  int extraMonthlyPayment;
  int additionalPayment = 15;
  double fewerMonths;
  
  cout << "** Welcome to the CPSC 1071 Payment Calculator **\n" << endl;

  //Takes in the principal amount and validates
  //that at a minimum, it's greater than 0 because otherwise,
  //there will be no loan to pay off.
  cout << "Enter the principal amount: ";
  cin >> principalAmount;
  while(principalAmount <= 0)
    {
      cout << "Your principal amount has to be greater than 0." << endl;
      cout << "Enter the principal amount: ";
      cin >> principalAmount;
    }

  //Takes in the annual interest rate.
  cout << "Enter the annual interest rate (in %): ";
  cin >> annualInterestRate;

  //Takes in the monthly payment and validates
  //that at a minimum, it's greater than 0 because otherwise,
  //the loan will never be paid off.
  cout << "Enter the monthly payment: ";
  cin >> monthlyPayment;
  while(monthlyPayment <= 0)
    {
      cout << "Your monthly payment has to be greater than 0." << endl;
      cout << "Enter the monthly payment: ";
      cin >> monthlyPayment;
    }
  cout << "\n";
  cout << "Calculating...\n" << endl;
  
  //months is assigned the value output by the
  //calculation function.
  months = monthCalculator(principalAmount, annualInterestRate, monthlyPayment);
  years = months / 12;
  cout << "Months: " << months << endl;
  //Values are printed out using formatting
  //from the iomanip header.
  cout << fixed << setprecision(0) << months << " months (";
  cout << fixed << setprecision(1) << years << " years) are needed to pay your loan off.\n" << endl;

  //Extra monthly payment is calculated by adding
  //additional payment to the current payment
  //and feeding that information into the calculator
  extraMonthlyPayment = monthlyPayment + additionalPayment;
  fewerMonths = monthCalculator(principalAmount, annualInterestRate, extraMonthlyPayment);

  //Rounding off to get the final fewer months value
  fewerMonths = round(months) - round(fewerMonths);

  //Prints out final statement
  cout << "Did you know if you paid an additional $" << additionalPayment << " per month, you would pay off your loan ";
  cout << fixed << setprecision(0) << fewerMonths << " months earlier?" << endl;
}

//Function to run the equation that calculates
//how many months it will take to pay off a loan
//given the 3 parameters.
double monthCalculator(double principalAmount, double annualInterestRate, double monthlyPayment)
{
  double numerator = log(monthlyPayment) - log(monthlyPayment - ((annualInterestRate/1200.0) * principalAmount));
  double denominator = log((annualInterestRate/1200.0) + 1.0);
  return numerator / denominator;
}
