#ifndef DATE_H
#define DATE_H
#include <string>

using namespace std;

class Date
{
 private:
  int month = 1;
  int day = 1;
  int year = 1;
  
 public:
  Date();
  Date(int month, int day, int year);
  
  int getMonth();
  int getDay();
  int getYear();

  void setMonth(int month);
  void setDay(int day);
  void setYear(int year);
  
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
