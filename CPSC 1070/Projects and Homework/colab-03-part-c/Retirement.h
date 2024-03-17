#ifndef RETIREMENT_H //Header guards
#define RETIREMENT_H

#include <string> //String header file to use string objects
using namespace std; //used so std:: isn't necessary for every single string object or output

//Class
class Retirement
{
 public:
  void estimateDriver();

 private:
  double estimateEarnings(int, int, double, double, double);
  bool validCurrentAge(string, string&);
  bool validRetiredAge(int, string, string&);
  bool validSavings(string, string&);
  bool validMonthlyContributions(string, string&);
  bool validAnnualReturnPercentage(string, string&);
};

#endif
