#include <iostream>
#include "Date.h"
#include "MysteryMachine.h"
#include <string>

/* Default Date Constructor */
//Default constructor, sets date to Jan 1st, 2000
Date::Date()
{
  month = 1;
  day = 1;
  year = 2000;
}

/* Overloaded Date Constructor */
//Overloaded constructor, sets date to what the input is
Date::Date(int month, int day, int year)
{
  setYear(year);
  setMonth(month);
  setDay(day);
}

/* getMonth */
int Date::getMonth()
{
  return month;
}

/* getDay */
int Date::getDay()
{
  return day;
}

/* getYear */
int Date::getYear()
{
  return year;
}

/* setMonth */
//Sets month of date object to user argument
void Date::setMonth(int month)
{
  //If valid month, set to it, otherwise, set the month to January
  //Also run setDay function to ensure the date is still in check
  if(month <= 12 && month >= 1)
    {
      this->month = month;
      setDay(day);
    }
  else
    {
      cout << "Invalid month, setting month to January!" << endl;
      month = 1;
      month = 1;
      setDay(day);
      
    }
}
	

/* setDay */
//Sets day of the date object to user argument
void Date::setDay(int day)
{
  //If day is less than 1 set it to 1
  if(day < 1)
    {
      cout << "Invalid day! Day can't be less than 1. Setting day to 1. " << endl;
      this->day = 1;
    }
  //Checks if the day is greater than 29 on leap years
  else if(year % 4 == 0 && month == 2)
    {
      if(day > 29)
	{
	  cout << "Invalid day! Day can't be greater than the days in the month. Setting day to 29." << endl;
	  this->day = 29;
	}
      else
	{
	  this->day = day;
	}
    }
  //Checks if the day is greater than 31 on months with 31 days
  else if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
      if(day > 31)
	{
	  cout <<"Invalid day! Day can't be greater than the days in the month. Setting day to 31." << endl;
	  this->day = 31;
	}
      else
	{
	  this->day = day;
	}
    }
  //Checks if the day is greater than 30 on months with 30 days
  else if(month == 4 || month == 6 || month == 9 || month == 11)
    {
      if(day > 30)
	{
	  cout << "Invalid day! Day can't be greater than the days in the month. Setting day to 30." << endl;
	  this->day = 30;
	}
      else
	{
	  this->day = day;
	}
    }
  //Checks if the day is greater than 28 on February
  else if(month == 2)
    {
      if(day > 28)
	{
	  cout << "Invalid day! Day can't be greater than the days in the month. Setting day to 28." << endl;
	  this->day = 28;
	}
      else
	{
	  this->day = day;
	}
    }
}

/* setYear */
//Sets year of the date object to user argument
void Date::setYear(int year)
{
  //If year is less than 1, set it to 2023, otherwise set it as is
  if(year < 1)
    {
      cout << "Invalid year! Year can't be less than 1. Setting year to 2023." << endl;
      this->year = 2023;
    }
  else
    {
      this->year = year;
    }
  setDay(day);
}

/* getDayOfWeek */
//Uses mystery machine header file to get the specific day of the week based
//off the date (Mon-Sun from mm/dd/yyyy)
string Date::getDayOfWeek()
{
  MysteryMachine mysterymachine = MysteryMachine();
  Date indate = Date(this->month, this->day, this->year);
  return mysterymachine.getDayOfWeek(indate);
}

/* toString */
//Returns the date object as a string
string Date::toString()
{
  string strMonth = to_string(month);
  string strDay = to_string(day);
  string strYear = to_string(year);
  if(strMonth.length() == 1)
    {
      strMonth = "0" + strMonth;
    }
  if(strDay.length() == 1)
    {
      strDay = "0" + strDay;
    }
  return strMonth + "/" + strDay + "/" + strYear;
}

/* Overloaded Operators*/
/* Date + int */
//Moves the date int days forward
Date Date::operator+(int days)
{
  for(int i = 0; i < days; i ++)
    {
      ++*this;
    }
  return *this;
}

/* Date - int */
//Moves the date int days backwards
Date Date::operator-(int days)
{
  for(int i = 0; i < days; i ++)
    {
      --*this;
    }
  return *this;
}

/* Date++ */
//Returns the original date object before incrementing
Date Date::operator++(int)
{
  Date postfix = *this;
  ++*this; 
  return postfix;
}

/* ++Date */
//Date prefix incrementer, moves the date one day forward
Date Date::operator++(void)
{
  //daysInMonth is how many days there are in the month Date is in
  int daysInMonth = 0;
  //If the month is one w/ 31 days, set daysInMonth to 31, or 30
  if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
      daysInMonth = 31;
    }
  else if(month == 4 || month == 6 || month == 9 || month == 11)
    {
      daysInMonth = 30;
    }
  //Otherwise, it's February
  else
    {
      //Check for leap years and set daysInMonth accordingly
      if(year % 4 == 0)
	{
	  daysInMonth = 29;
	}
      else
	{
	  daysInMonth = 28;
	}
    }

  /* 3 situations:
  Day just increments one
  The month needs to switch over
  The month and year needs to switch over */

  //If it's not the last day of the month, increment day by one
  if(day < daysInMonth)
    {
      day++;
    }
  //If it's not the last day of the month and it's not december (year switch) set day to 1 and increment month by one
  else if(day == daysInMonth && month != 12)
    {
      day = 1;
      month++;
    }
  //Otherwise, it has to be the last day of the month on December so do a year switch
  else
    {
      day = 1;
      month = 1;
      year++;
    }

  return *this;
}



/* Date-- */
//Returns the original date before decremnting
Date Date::operator--(int)
{
  Date postfix = *this;
  --*this;
  return postfix;
}

/* --Date */
//Moves the date back one day
Date Date::operator--(void)
{
  /* 4 Situations:
  Day just decrements one
  The month switches into day 30
  The month switches into day 31
  A month and a year need to switch over
  The day backs up into a Febuary (leap year) */
  
  //Day is not the first day of the month, so decrement one
  if(day > 1)
    {
      day--;
    }
  //Day is the 1st on a month AFTER a month with 31 days, so decrement the month and set the day to 31
  else if(day == 1 && (month == 2 || month == 4 || month == 6 || month == 8 || month == 9 || month == 11))
    {
      day = 31;
      month --;
    }
  //Day is the 1st on a month AFTER a month with 30 days, so decrement the month and set the day to 30
  else if(day == 1 && (month == 5 || month == 7 || month == 10 || month == 12))
    {
      day = 30;
      month--;
    }
  //If it's on the January 1st, set the date to December 31st, and decrement a year
  else if(day == 1 && month == 1)
    {
      day = 31;
      month = 12;
      year --;
    }
  //Otherwise, it's March 1st
  else
    {
      //If it's a leap year, set the date to February 29th
      if(year % 4 == 0)
	{
	  month = 2;
	  day = 29;
	}
      //If it's not a leap year, set the date to February 28th
      else
	{
	  month = 2;
	  day = 28;
	}
    }
  return *this;
}
