/* Name: Kenny Sun
 * Date: 10/13/23
 * This file is meant to test out my Date.h and
 * Date.cpp files and make sure things are working
 * correctly and as expected
 */


#include <iostream>
#include "Date.h"
#include <string>
#include "MysteryMachine.h"
using namespace std;

int main()
{
  //Test cases for creating invalid dates:
  //Invalid month
  Date date1 = Date(13, 10, 2023);
  cout << "Set date to 13/10/2023: " << date1.toString() << endl;
  //Invalid everything
  Date date2 = Date(0, -1, 0);
  cout << "Set date to 00/-1/0000: " << date2.toString() << endl;
  //Setting month from a valid date to an invalid date
  Date date3 = Date(10, 31, 2023);
  cout << "Set date to: " << date3.toString() << endl;
  date3.setMonth(9);
  cout << "After setting month to 9: " << date3.toString() << endl;
  date3.setMonth(2);
  cout << "After setting month to 2: " << date3.toString() << endl;
  //Setting day to an invalid day
  date3.setDay(-1);
  cout << date3.toString() << endl;
  date3.setDay(1000);
  cout << date3.toString() << endl;

  //Test all the getter functions
  cout << "Month: " << date3.getMonth() << endl;
  cout << "Day: " << date3.getDay() << endl;
  cout << "Year: " << date3.getYear() << endl;
  
  //Test case for adjusting dates
  Date regularDate = Date(10, 10, 2023);
  regularDate.getDayOfWeek();
  cout << "\nStart Date: " << regularDate.toString() << endl;
  regularDate++;
  cout << "Postfix Add: " << regularDate.toString() << endl;
  ++regularDate;
  cout << "Prefix Add: " << regularDate.toString() << endl;
  regularDate--;
  cout << "Postfix Subtract: " << regularDate.toString() << endl;
  --regularDate;
  cout << "Prefix Subtract: " << regularDate.toString() << endl;
  regularDate = regularDate + 5;
  cout << "Add 5: " << regularDate.toString() << endl;
  regularDate = regularDate - 5;
  cout << "Minus 5: " << regularDate.toString()<< endl;
  cout << "Weekday: " << regularDate.getDayOfWeek() << endl;

  //Test case for crossing months on the 30th day
  //  regularDate.setMonth(4);
  //regularDate.setDay(30);
  //regularDate.setYear(2023);
  cout << "\nStart Cross Month Date: " << regularDate.toString() << endl;
  regularDate++;
  cout << "Postfix Add: " << regularDate.toString() << endl;
  regularDate--;
  cout << "Postfix Subtract: " << regularDate.toString() << endl;
  ++regularDate;
  cout << "Prefix Add: " << regularDate.toString() << endl;
  --regularDate;
  cout << "Prefix Subtract: " << regularDate.toString() << endl;
  regularDate = regularDate + 5;
  cout << "Add 5: " << regularDate.toString() << endl;
  regularDate = regularDate - 5;
  cout << "Minus 5: " << regularDate.toString() << endl;

  //Test case for crossing months on the 31st day
  Date crossMonths = Date(10, 10, 2023);
  crossMonths.setMonth(1);
  crossMonths.setDay(31);
  cout << "\nStart Cross Month Date: " << crossMonths.toString() << endl;
  crossMonths++;
  cout << "Postfix Add: " << crossMonths.toString() << endl;
  crossMonths--;
  cout << "Postfix Subtract: " << crossMonths.toString() << endl;
  ++crossMonths;
  cout << "Prefix Add: " << crossMonths.toString() << endl;
  --crossMonths;
  cout << "Prefix Subtract: " << crossMonths.toString() << endl;
  crossMonths = crossMonths + 5;
  cout << "Add 5: " << crossMonths.toString() << endl;
  crossMonths = crossMonths - 5;
  cout << "Minus 5: " << crossMonths.toString() << endl;

  //Test case for crossing years
  Date crossYears = Date(12, 31, 2022);
  cout << "\nStart Cross Years Date: " << crossYears.toString() << endl;
  crossYears++;
  cout << "Postfix Add: " << crossYears.toString() << endl;
  crossYears--;
  cout << "Postfix Subtract: " << crossYears.toString() << endl;
  ++crossYears;
  cout << "Prefix Add: " << crossYears.toString() << endl;
  --crossYears;
  cout << "Prefix Subtract: " << crossYears.toString() << endl;
  crossYears = crossYears + 5;
  cout << "Add 5: " << crossYears.toString() << endl;
  crossYears = crossYears - 5;
  cout << "Minus 5: " << crossYears.toString() << endl;

  //Test case for crossing months on a leap year
  Date leapYear = Date(2, 28, 2000);
  cout << "\nStart Leap Year Date: " << leapYear.toString() << endl;
  leapYear++;
  cout << "Postfix Add: " << leapYear.toString() << endl;
  ++leapYear;
  cout << "Prefix Add: " << leapYear.toString() << endl;
  leapYear--;
  cout << "Postfix Subtract: " << leapYear.toString() << endl;
  --leapYear;
  cout << "Prefix Subtract: " << leapYear.toString() << endl;
  leapYear = leapYear + 5;
  cout << "Add 5: " << leapYear.toString() << endl;
  leapYear = leapYear - 5;
  cout << "Minus 5: " << leapYear.toString() << endl;


  //Test case for crossing months on a non-leap year
  leapYear.setYear(2001);
  cout << "\nStart Leap Year Date: " << leapYear.toString() << endl;
  leapYear++;
  cout << "Postfix Add: " << leapYear.toString() << endl;
  ++leapYear;
  cout << "Prefix Add: " << leapYear.toString() << endl;
  leapYear--;
  cout << "Postfix Subtract: " << leapYear.toString() << endl;
  --leapYear;
  cout << "Prefix Subtract: " << leapYear.toString() << endl;
  leapYear = leapYear + 5;
  cout << "Add 5: " << leapYear.toString() << endl;
  leapYear = leapYear - 5;
  cout << "Minus 5: " << leapYear.toString() << endl << endl;

  //Testing getDayOfWeek function
  Date newDate = Date(9, 30, 2023);
  for(int i = 0; i < 7; i ++)
    {
      cout << newDate.toString() << ": " << newDate.getDayOfWeek() << endl;
      newDate++;
    }
}
