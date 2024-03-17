#ifndef LOAN_H //Header guards
#define LOAN_H

#include <string> //String header file to use string objects
using namespace std; //used so std:: isn't necessary for every single string object or output

//Class
class Loan
{
 public:
  void paymentDriver();
  
 private:
  int paymentMonths(double, double, double);
  bool validPrincipalAmount(string, string&);
  bool validAnnualInterestRate(string, string&);
  bool validMonthlyPayment(string, string&);
};
#endif
