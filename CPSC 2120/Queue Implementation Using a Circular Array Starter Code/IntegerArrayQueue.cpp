/* Name: Kenny Sun
 * Date: 2/13/2023
 * Class: CPSC 2120
 * File Name: IntegerArrayQueue.cpp
 * Desc: Implementation for a queue using a circular array
*/
#include "IntegerArrayQueue.h"

/* enqueue */
//Adds a value to the circular array and returns whether or not
//It was done
bool IntegerArrayQueue::enqueue(int value)
{
  //Checks for a full queue
  if(back + 2 == front || (front == 0 && back == size - 2) || (front == 1 && back == size - 1))
  {
    cout << "The queue is full." << endl;
    return false;
  }

  //Checks to rotate the index around
  if(back == size - 1)
  {
    back = 0;
  }
  else
  {
    back++;
  }
  //Sets the value and returns true
  array[back] = value;
  return true;
}

/* dequeue */
//Returns the last value that was added to the queue
//Returns 0 if the queue was empty
int IntegerArrayQueue::dequeue()
{
  //Empty queue check
  if(back + 1 % size == front)
  {
    return 0;
  }

  //Saves the value to return
  int returnValue = array[front];

  //Checks to rotate the index around
  if(front == size - 1)
  {
    front = 0;
  }
  else
  {
    front ++;
  }
  
  return returnValue;
}