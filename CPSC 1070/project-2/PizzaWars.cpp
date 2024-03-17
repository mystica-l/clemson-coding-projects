/* File Name: PizzaWars.cpp
 * Name: Kenny Sun
 * Date: 10/20/2023
 * Purpose: Source code for the PizzaWars class, the PizzaWars object runs simulations day to day operation of 2 PizzaStores by creating PizzaStore objects and Date objects
 * and writes the results of these pizza wars to a log.txt file and the terminal
 */

#include <iostream> //Needed for cout and cin functions for insertion and extraction from the terminal
#include <iomanip> //Needed to format certain outputs to the terminal and log.txt
#include <fstream> //Needed to read and write to files such as log.txt to store results of the pizza wars
#include "PizzaWars.h" //Needs own header file
#include <ctime> //Needed for time(0) to seed the randomness
#include <cctype> //Needed for a function to check if the date inputted is a digit
#include <unistd.h> //Needed for usleep to pause function

/* Default Constructor */
PizzaWars::PizzaWars()
{

} 


/* Destructor */
PizzaWars::~PizzaWars()
{

}


/* Copy Constructor */
PizzaWars::PizzaWars(const PizzaWars& copy)
{

}

/* runSimulation */
//This function is the only function public and called by a PizzaWars object
//It prompts the user for a date, validates the date through the validateDate function,
//creates a pointer to an array of 7 dates, starting at the first Sunday through allocateWeekOfDates
//and calls runSeriesSimulation feeding it the date array
void PizzaWars::runSimulation()
{
  //These variables are passed into validateDate by reference to be later used to create a Date object
  int intMonth;
  int intDay;
  int intYear;
  string inputDate;
  cout << "Welcome to Pizza Wars!" << endl;
  cout << "This program simulates an epic battle between Core and Schilletter and their ability to keep up with the demand for pizza!" << endl << endl;
  cout << "Please enter the date you'd like to start the simulation in MM DD YYYY format: ";

  //Gets input from the user including white spaces
  getline(cin, inputDate);

  //validateDate returns whether or not the date inputted by the user is possible and returns that
  //Will keep prompting until there's a valid date
  while(!validateDate(inputDate, intMonth, intDay, intYear))
    {
      cout << "This is an invalid date." << endl;
      cout << "Please re-enter the date you'd like to start the simulation in MM DD YYYY format: ";
      getline(cin, inputDate);
    }

  //Creates a date object using the reference variables
  Date date = Date(intMonth, intDay, intYear);

  //Changes the date to a Sunday and lets you know
  if(date.getDayOfWeek() != "Sunday")
    {
      cout << "That day is not a Sunday, so we're moving to the nearest future Sunday to start" << endl;
    }
  
  Date *dateToSunday = &date;  
  marchToSunday(dateToSunday);
  dateToSunday = nullptr;
  
  Date *datePtr = allocateWeekOfDates(date);

  cout << "Starting on " << datePtr[0].toString() << endl;

  //runs 7 simulations based on the week
  runSeriesSimulation(datePtr, 7);

  //Frees up the memory once runSeriesSimulation is done
  delete [] datePtr;
  datePtr = nullptr;
}

/* validateDate */
//Takes in an input date and checks that it's a valid date before setting the reference variables
//To what the user inputted
bool PizzaWars::validateDate(string inputDate, int &month, int &day, int &year)
{
  //Iterates through the inputDate and checks for only 2 spaces throughout the string based on the format
  //Will also return false if there's any non-space or non-digit character
  int spaceCounter = 0;
  for(int i = 0; i < static_cast<int>(inputDate.length()); i++)
    {
      if(inputDate[i] == ' ')
        {
          spaceCounter++;
        }
      if(inputDate[i] != ' ' && !isdigit(inputDate[i]))
        {
          return false;
        }
    }
  if(spaceCounter != 2)
    {
      return false;
    }

  //Separates the string into it's first section for month
  string stringMonth = "";
  int index = 0;
  while(inputDate[index] != ' ')
    {
      stringMonth += inputDate[index];
      index++;
    }

  //Separates the string into it's second section for the day
  string stringDay = "";
  index++;
  while(inputDate[index] != ' ')
    {
      stringDay += inputDate[index];
      index++;
    }

  //Separates the string into it's final section for the year
  string stringYear = "";
  index++;
  while(index < static_cast<int>(inputDate.length()))
    {
      stringYear += inputDate[index];
      index++;
    }

  //If any value is longer than it should be, it'll return false
  if(stringMonth.length() > 2 || stringDay.length() > 2 || stringYear.length() != 4)
    {
      return false;
    }

  //Sets all the int values
  int intMonth = stoi(stringMonth);
  int intDay = stoi(stringDay);
  int intYear = stoi(stringYear);

  //If month is not valid, returns false
  if(intMonth < 1 || intMonth > 12)
    {
      return false;
    }

  //If day is less than 1, returns false
  if(intDay < 1)
    {
      return false;
    }
  //If the day is greater than 31 on a month with 31 days, return false
  if(intMonth == 1 || intMonth == 3 || intMonth == 5 || intMonth == 7 || intMonth == 8 || intMonth == 10 || intMonth == 12)
    {
      if(intDay > 31)
	{
	  return false;
	}
    }
  //Else if the day is greater than 30 on a month with 30 days, return false
  else if(intMonth == 4 || intMonth == 6 || intMonth == 9 || intMonth == 11)
    {
      if(intDay > 30)
	{
	  return false;
	}
    }
  //Otherwise, check for leap years with February
  else if(intMonth == 2)
    {
      if(intYear % 4 == 0)
	{
	  if(intDay > 29)
	    {
	      return false;
	    }
	}
      else
	{
	  if(intDay > 28)
	    {
	      return false;
	    }
	}
    }

  //If it passes and doesn't return false, set all the reference variables and return true
  month = intMonth;
  day = intDay;
  year = intYear;
  return true;
}


/* allocateWeekOfDates */
//This function takes in a date, and returns a pointer to a 7 long array
//Filled with incrementing dates starting from the date given
Date * PizzaWars::allocateWeekOfDates(Date date)
{
  Date* dateArrayPtr = new Date[7];
  for(int i = 0; i < 7; i ++)
  {
    dateArrayPtr[i] = date;
    date++;
  }
  return dateArrayPtr;
}

/* runSeriesSimulation */
//runSeriesSimulation calls runDaySimulation length amount of times and calls writeToFile
//With the winner of each day and date
void PizzaWars::runSeriesSimulation(Date *dates, int length)
{

  //Pointer that points to an individual day to be passed into runDaySimulation
  Date *singleDatePtr;

  //Pointers to PizzaStore objects to be passed into runDaySimulation
  PizzaStore *pizzaStore1Ptr;
  PizzaStore *pizzaStore2Ptr;

  //Null pointer for ties
  PizzaStore *pizzaStoreTiePtr;
  pizzaStoreTiePtr = nullptr;
  
  string winnerName;

  //Seeds the random function based on time
  srand(time(0));

  //Loops through the length (7 days)
  for(int i = 0; i < length; i ++)
  {
    //Creates 2 new PizzaStore objects of Core and Schilletter with their respective attributes to reset the pizzas to 8 slices a slot
    pizzaStore1Ptr = new PizzaStore("Core", 3, 2, .90);
    pizzaStore2Ptr = new PizzaStore("Schilletter", 6, 1, .80);

    //This pointer points to a single date inside of the dates parameter
    singleDatePtr = &dates[i];

    //winnerName is set to the string returned by runDaySimulation once a winner is determined
    winnerName = runDaySimulation(singleDatePtr, pizzaStore1Ptr, pizzaStore2Ptr);

    //Checks who won by using .getName() and calls writeToFile with the appropriate pointer
    if((*pizzaStore1Ptr).getName() == winnerName)
      {
	writeToFile(singleDatePtr, pizzaStore1Ptr);
      }
    else if((*pizzaStore2Ptr).getName() == winnerName)
      {
	writeToFile(singleDatePtr, pizzaStore2Ptr);
      }
    //Tie case with null tie pointer
    else
      {
	writeToFile(singleDatePtr, pizzaStoreTiePtr);
      }

    //Frees up the memory and sets them to nullptr to avoid dangling pointer
    //The pointers will get set to new PizzaStore objects to reset the slices on each run
    delete pizzaStore1Ptr;
    delete pizzaStore2Ptr;
    pizzaStore1Ptr = nullptr;
    pizzaStore2Ptr = nullptr;
  }
}

/* runDaySimulation */
//This function takes in a Date object, and 2 PizzaStore objects and competes them to see
//Who runs out of pizza first
//Competes them by consuming a random amount of slices for each half hour the stores are open
//And baking new pizzas as well
//It will then return the name of the winning pizza store or a blank string otherwise
string PizzaWars::runDaySimulation(Date *datePtr, PizzaStore *pizzaStore1Ptr, PizzaStore *pizzaStore2Ptr)
{
  cout << "\n\nRunning simulation for " << (*datePtr).getDayOfWeek() << " " << (*datePtr).toString() << endl << endl << endl;

  //Bools to determine when someone looses
  bool store1NoLoss = true;
  bool store2NoLoss = true;
  bool loser = false;

  //timeSlots is the max index the loop can run through as weekends arren't open as long but both open at the same time
  int timeSlots;
  
  if((*datePtr).getDayOfWeek() == "Sunday" || (*datePtr).getDayOfWeek() == "Saturday")
    {
      //Closes at 8:00 instead of 9:00
      timeSlots = 19;
    }
  else
    {
      //Runs through all 21 time slots in the array
      timeSlots = 21;
    }

  //Loops through each half hour
  for(int i = 0; i < timeSlots; i++)
    {
      //Prints the time
      cout << halfHourArray[i] << endl;

      //Random ints are determined for how many slices are consumed
      int store1SlicesConsumed = (*pizzaStore1Ptr).randomInt(5, 20);
      int store2SlicesConsumed = (*pizzaStore2Ptr).randomInt(5, 20);

      //Prints how many slices were consumed
      cout << store1SlicesConsumed << " slice(s) are consumed at " << (*pizzaStore1Ptr).getName() << endl;
      cout << store2SlicesConsumed << " slice(s) are consumed at " << (*pizzaStore2Ptr).getName() << endl;

      //consumeSlices returns a boolean depending on whether or not the order was able to be completed
      store1NoLoss = (*pizzaStore1Ptr).consumeSlices(store1SlicesConsumed);
      store2NoLoss = (*pizzaStore2Ptr).consumeSlices(store2SlicesConsumed);
      (*pizzaStore1Ptr).showStatus();
      (*pizzaStore2Ptr).showStatus();

      //Will exit the loop (i = timeSlots) and set loser to true once a store's boolean is set to false
      if(!store1NoLoss || !store2NoLoss)
	{
	  loser = true;
	  i = timeSlots;
	}
      if(!loser)
	{
	  //Calls tickUpdate to add new pizzas and shows how many pizzas were added
	  cout << (*pizzaStore1Ptr).tickUpdate() << " pizza(s) were added at " << (*pizzaStore1Ptr).getName() << endl;
	  cout << (*pizzaStore2Ptr).tickUpdate() << " pizza(s) were added at " << (*pizzaStore2Ptr).getName() << endl;
	  (*pizzaStore1Ptr).showStatus();
	  (*pizzaStore2Ptr).showStatus();
	  cout << endl;
	}
      usleep(50000);
    }

  //Checks the winner and prints out the winner's name as well as returns it
  if(store1NoLoss && !store2NoLoss)
    {
      cout << (*pizzaStore1Ptr).getName() << " wins!" << endl;
      return (*pizzaStore1Ptr).getName();
    }
  else if(!store1NoLoss && store2NoLoss)
    {
      cout << (*pizzaStore2Ptr).getName() << " wins!" << endl;
      return (*pizzaStore2Ptr).getName();
    }
  //Tie cases
  else 
    {
      cout << "TIE!" << endl;
      return "";
    }
}

/* marchToSunday */
//Takes in a datePtr and will shift it to Sunday as long as it's not Sunday
void PizzaWars::marchToSunday(Date* datePtr)
{
  while((*datePtr).getDayOfWeek() != "Sunday")
    {
      (*datePtr)++;
    }
}

/* writeToFile */
//Takes in a datePtr and the store name of the winner and write to a file the date and which store won that day
void PizzaWars::writeToFile(Date *datePtr, PizzaStore *winner)
{
  ofstream logFile;

  //Opens log.txt or creates it if it's not there
  //We didn't cover ofstream::app
  //I came across it as whenever I would try and write to the file, it would overwrite everything instead of appending
  //I found it on cplusplus.com on a forum where someone else had the same issue
  logFile.open("log.txt", ofstream::app);

  //First checks for a nullptr aka a tie and writes to the file accordingly
  if(winner == nullptr)
    {
      logFile << setw(10) << left << (*datePtr).getDayOfWeek();
      logFile << setw(10) << left << (*datePtr).toString();
      logFile << "Tie!" << endl;
    }
  //Otherwise, the winner pointer points to a PizzaStore object and it will print out the winner
  else
    {
      logFile << setw(10) << left << (*datePtr).getDayOfWeek();
      logFile << setw(10) << left << (*datePtr).toString();
      logFile << (*winner).getName() << " won with " << (*winner).getTotalSlicesLeft() << " slices left!" << endl;
    }
  logFile.close();
}
