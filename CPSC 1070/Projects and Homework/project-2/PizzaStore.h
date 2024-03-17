/* File Name: PizzaStore.h
 * Name: Kenny Sun
 * Date: 10/20/2023
 * Purpose: Header file for the PizzaStore class
 */

#ifndef PIZZASTORE_H //Header guards
#define PIZZASTORE_H

#include <string> //Needed for string objects

//Needed to avoid constage usage of std:: whenever using string objects or terminal functions
using namespace std;

//PizzaStore Class
class PizzaStore
{
public:
  //Constructors and Destructors
  PizzaStore();
  PizzaStore(string, int, double, double);
  ~PizzaStore();
  //Copy Constructor
  PizzaStore(const PizzaStore &);

  int tickUpdate();
  bool consumeSlices(int slices);
  void showStatus();
  string getName();
  int getTotalSlicesLeft();
  int randomInt(int, int);

private:
  //Private member variables
  string name;
  int maxPizzas;
  double productionPerTick;
  double successRate;

  //Declared in header file
  //Is used to point to an array that stores the slices of pizzas
  int *pizzaPointer;
};

#endif 
