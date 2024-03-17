/* File Name: Date.h
 * Name: Kenny Sun
 * Date: 10/20/2023
 * Purpose: Header file for the Date class
 */

#ifndef DATE_H //Header guards
#define DATE_H

//Included for the usage of string objects
#include <string>

//Used to avoid constant usage of std:: for every string object and terminal output
using namespace std;

//Date Class
class Date
{
  private:
    //Private member variables
    int month = 1;
    int day = 1;
    int year = 1;
  
  public:
    //Constructors
    Date();
    Date(int month, int day, int year);
    
    //Getters
    int getMonth();
    int getDay();
    int getYear();

  //Setters
    void setMonth(int month);
    void setDay(int day);
    void setYear(int year);

  //Overloaded operators
    Date operator+(int days);
    Date operator-(int days);
    Date operator++(void);
    Date operator++(int);
    Date operator--(void);
    Date operator--(int);

    string toString();
    string getDayOfWeek();
};

#endif
