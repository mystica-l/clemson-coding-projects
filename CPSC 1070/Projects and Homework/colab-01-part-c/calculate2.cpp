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
double interestCalculator(double, double, double);
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
  int additionalPayment = 10;
  double fewerMonths;
  double accumulatedInterest;
  double totalPaid;
  
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
  cout << fixed << setprecision(1) << years << " years) are needed to pay your loan of\
f.\n" << endl;

  //Extra monthly payment is calculated by adding
  //additional payment to the current payment
  //and feeding that information into the calculator
  extraMonthlyPayment = monthlyPayment + additionalPayment;
  fewerMonths = monthCalculator(principalAmount, annualInterestRate, extraMonthlyPayment);
    //Rounding off to get the final fewer months value
  fewerMonths = round(months) - round(fewerMonths);

  //Prints out final statement
  cout << "Did you know if you paid an additional $" << additionalPayment << " per mon\
th, you would pay off your loan ";
  cout << fixed << setprecision(0) << fewerMonths << " months earlier?\n" << endl;

  //Sets accumulatedInterest to the value from the interestCalculator
  accumulatedInterest = interestCalculator(principalAmount, annualInterestRate, monthlyPayment);
  //Computes totalPaid
  totalPaid = accumulatedInterest + principalAmount;

  //Prints out the accumulated interest that is paid as well as the total amount
  cout << "The total interest paid is $";
  cout << fixed << setprecision(2) << accumulatedInterest << " and the total amount you'll pay is $";
  cout << fixed << setprecision(2) << totalPaid << ".";

}

//Function to run the equation that calculates
//how many months it will take to pay off a loan
//given the 3 parameters.
double monthCalculator(double principalAmount, double annualInterestRate, double month\
lyPayment)
{
  double numerator = log(monthlyPayment) - log(monthlyPayment - ((annualInterestRate/1\
200.0) * principalAmount));
  double denominator = log((annualInterestRate/1200.0) + 1.0);
  return numerator / denominator;
}

//Function to calculate accumulating interest
//month by month using a while loop given the 3 parameters.
double interestCalculator(double principalAmount, double annualInterestRate, double monthlyPayment)
{
  double remainingLoanBalance = principalAmount;
  double monthlyInterestRate = ((annualInterestRate / 100) / 12);
  double monthlyInterestPaid = 0;
  double principalPaid;
  double accumulatingInterest = 0;
  while(remainingLoanBalance > 0)
    {
  monthlyInterestPaid = remainingLoanBalance * monthlyInterestRate;
  accumulatingInterest += monthlyInterestPaid;
  principalPaid = monthlyPayment - monthlyInterestPaid;
  remainingLoanBalance -= principalPaid;
    }
  return accumulatingInterest;
}
