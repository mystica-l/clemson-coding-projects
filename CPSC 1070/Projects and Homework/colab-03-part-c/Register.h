#ifndef REGISTER_H //header files
#define REGISTER_H

#include <string> //Include string for string objects
#include <fstream> //Include fstream to read from files
#include <vector> //Include vector so we can use vectors since arrays aren't feasible given that we don't know the size of the file

using namespace std; //used so std:: isn't necessary for every single string object or output

class Register
{
 private:
  string filename;
  string getFileName();
  void setFileName(string);
  bool readFromFile();
  void printFile();
  ifstream fileReader; //Used to read files
  enum Transactions {RESTAURANT, MERCHANDISE, UTILITY, COFFEESHOP, AUTOMOTIVE, DEPOSIT, OTHER};
  vector<string> dateVector;
  vector<Transactions> transactionVector;
  vector<string> locationVector;
  vector<double> creditDebitVector;
  bool validatingFileName = true;
 
 public:
  bool processTransaction();
};

#endif
