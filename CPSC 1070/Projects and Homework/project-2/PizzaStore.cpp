/* File Name: PizzaStore.cpp
 * Name: Kenny Sun
 * Date: 10/20/2023
 * Purpose: Source code for the PizzaStore object, creates PizzaStores that can display their pizzas, eat pizzas, replenish pizzas, etc.
 */

#include "PizzaStore.h" //Needs own header files
#include <iostream> //Needed to use functions such as cout and cin to insert and extract things from the stream
#include <iomanip> //Needed to manipulate text and have it displayed properly, especially when displaying status
#include <cstdlib> //Needed for the random function to randomly consume slices and accidentally drop pizzas

/* Default Constructor */
PizzaStore::PizzaStore()
{
  //Name of the pizza store
  this->name = "Pizza Store";
  //Maximum pizzas out at any given moment
  this->maxPizzas = 4;
  //Maximum amount of pizzas baked when tickUpdate is called
  this->productionPerTick = 2;
  //Success percentage of a pizza being baked
  this->successRate = 0.85;

  //pizzaPointer is a pointer that is a member variable of PizzaStore.cpp
  //It's set to point to an array of 4 8 slice pizzas
  this->pizzaPointer = new int(4);
  for(int i = 0; i < maxPizzas; i ++)
    {
      pizzaPointer[i] = 8;
    }
}

/* Overloaded Constructor */
PizzaStore::PizzaStore(string name, int maxPizzas, double productionPerTick, double successRate)
{
  this->name = name;
  this->maxPizzas = maxPizzas;
  this->productionPerTick = productionPerTick;
  this->successRate = successRate;
  this->pizzaPointer = new int(maxPizzas);
  for(int i = 0; i < maxPizzas; i++)
    {
      pizzaPointer[i] = 8;
    }
}

/* PizzaStore Destructor */
PizzaStore::~PizzaStore()
{
  //Frees the memory pointed to by pizzaPointer when the object goes out of scope
  delete pizzaPointer;
  //Set to nullptr to avoid dangling pointers
  pizzaPointer = nullptr;
}

/* Copy Constructor*/
//Ensures no pointer issues are caused when PizzaStore is copied over
PizzaStore::PizzaStore(const PizzaStore& copy)
{
  name = copy.name;
  maxPizzas = copy.maxPizzas;
  productionPerTick = copy.productionPerTick;
  successRate = copy.successRate;
  pizzaPointer = new int(maxPizzas);
  for(int i = 0; i < maxPizzas; i++)
    {
      pizzaPointer[i] = copy.pizzaPointer[i];
    }
}


/* randomInt */
//Generates a random int from min to max inclusive using modulus and returns it
int PizzaStore::randomInt(int min, int max)
{
  int num;
  num = rand();
  num = num % (max + 1 - min) + min;
  return num;
}

/* tickUpdate */
//tickUpdate will bake pizzas based on productionPerTick and attempt to add them to slots with 0 slices assuming the pizza isn't dropped
int PizzaStore::tickUpdate()
{
  //Initialize variables
  int pizzasAttempted = 0;
  int pizzasAdded = 0;
  bool hitMaxPizzas = false;

  //Loops through each slot in pizzaPointer
  for(int i = 0; i < maxPizzas; i ++)
    {
      //Can't attempt to bake more pizzas than productionPerTick
      if(pizzasAttempted >= productionPerTick)
	{
	  hitMaxPizzas = true;
	}
      //If the slot has 0 pizzas and we haven't hit the max
      if(pizzaPointer[i] == 0 && !hitMaxPizzas)
	{
	  //And the pizza isn't dropped...
	  if(randomInt(1, 100) <= successRate * 100)
	    {
	      //Set the slices to 8, increment pizzasAttempted, increment pizzasAdded
	      pizzaPointer[i] = 8;
	      pizzasAttempted ++;
	      pizzasAdded ++;
	    }
	  else
	    {
	      //Oh no! The pizza was dropped! Increment pizzasAdded
	      pizzasAttempted ++;
	    }
	}
    }
  //Returns pizzasAdded as it's printed out by PizzaWars
  return pizzasAdded;
}

/* consumeSlices */
//Function that will attempt to consume the given amount of slices from pizzaPointer
//Will return false if more slices are wanting to be consumed than the number of slices available
bool PizzaStore::consumeSlices(int slices)
{
  //pizzaIndex cycles through all the values in pizzaPointer
  int pizzaIndex = 0;

  //For loop counts the amount of slices being consumed until they run out or don't
  for(int i = 0; i < slices; i ++)
    {
      //Checks if the current pizza slot is 0
      if(pizzaPointer[pizzaIndex] == 0)
	{
	  //Increments pizzaIndex to move to the next pizza
	  pizzaIndex ++;
	  //Will return false as once pizzaIndex is past maxPizzas, there's no more pizza
	  if(pizzaIndex >= maxPizzas)
	    {
	      return false;
	    }
	  //i is decremented as to ensure loop still counts the slice
	  i--;
	}
      else
	{
	  //Otherwise, just one of the slices there
	  pizzaPointer[pizzaIndex] = pizzaPointer[pizzaIndex] - 1;
	}
    }

  //If the function makes it all the way through the for loop, it had enough slices and will return true
  return true;
}

/* showStatus */
//showStatus displays the name of the PizzaStore as well as the amount of slices in each index of pizzaPointer
void PizzaStore::showStatus()
{
  cout << setw(22) << right << name << ": ";
  for(int i = 0; i < maxPizzas; i ++)
    {
      cout << pizzaPointer[i] << " ";
    }
  cout << endl;
}

/* getName */
//Returns the name of the PizzaStore
string PizzaStore::getName()
{
  return name;
}

/* getTotalSlicesLeft */
//Loops through pizza pointer and adds up all the slices inside of pizzaPointer and returns it
int PizzaStore::getTotalSlicesLeft()
{
  int sum = 0;
  for(int i = 0; i < maxPizzas; i ++)
    {
      sum += pizzaPointer[i];
    }
  return sum;
}
