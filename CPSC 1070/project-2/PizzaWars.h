/* File Name: PizzaWars.h
 * Name: Kenny Sun
 * Date: 10/20/2023
 * Purpose: Header file for the PizzaWars class
 */

#ifndef PIZZAWARS_H //Header guards
#define PIZZAWARS_H

#include "Date.h" //Included because PizzaWars creates and uses Date objects
#include "PizzaStore.h" //Included because PizzaWars creates and uses PizzaStore objects

//const array so it can't be changed
//Containts all the halfHourArray increments for each tickUpdate
const string halfHourArray[21] = {"11:00", "11:30", "12:00", "12:30", "1:00", "1:30", "2:00", "2:30", "3:00", "3:30", "4:00", "4:30", "5:00", "5:30", "6:00", "6:30", "7:00", "7:30", "8:00", "8:30", "9:00"};

//PizzaWars Class
class PizzaWars
{
public:
  //Constructors and Destructors
  PizzaWars();
  ~PizzaWars();
  //Copy Constructor
  PizzaWars(const PizzaWars &);
  static void runSimulation();
  
protected:
  static Date*allocateWeekOfDates(Date);
  static void runSeriesSimulation(Date*, int);
  static string runDaySimulation(Date*, PizzaStore*, PizzaStore*);
  static void marchToSunday(Date*);
  static void writeToFile(Date*, PizzaStore*);
  static bool validateDate(string, int&, int&, int&);
};
#endif 
