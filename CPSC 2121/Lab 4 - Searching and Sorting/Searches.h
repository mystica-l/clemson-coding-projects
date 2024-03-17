/*
 * Name: Kenny Sun
 * Date Submitted: 2/19/2024 
 * Lab Section: CPSC 2121-003
 * Assignment Name: Lab 4: Searching and Sorting
 */

#pragma once

#include <vector>
#include <cmath>

/* linearSearch */
//Returns the index of a target value in a vector
template <class T>
int linearSearch(std::vector<T> data, T target){
  //Iterates through the vector and returns the index once target is found
  for(int i = 0; i < static_cast<int>(data.size()); i ++)
  {
    if(data[i] == target)
    {
      return i;
    }
  }
  return -1;
}

/* binarySearch */
//Returns the index of a target value in a vector
template <class T>
int binarySearch(std::vector<T> data, T target){
  //maxIterations uses logarithms as well as the fundamental way binarySearch works
  //To calculate the max number of times the binarySearch algorithm will have to be done
  int maxIterations = log2(data.size()) + 1;
  //Variable declaration
  int i = 0;
  int lowIndex = 0;
  int highIndex = data.size() - 1;
  //midIndex stores the middle of the vector/subvector that's being searched
  int midIndex = (highIndex + lowIndex) / 2;
  //Iterates through algorithm
  while(i < maxIterations)
  {
    //If the data is found at midIndex, return midIndex
    if(data[midIndex] == target)
    {
      return midIndex;
    }
    //If the data is less than the target,
    //Set low index to 1 after midIndex as we know that the data
    //Can't be before midIndex since the vector is already sorted
    else if(data[midIndex] < target)
    {
      lowIndex = midIndex + 1;
    }
    //If the data is higher than the target,
    //Set high index to 1 before midIndex as we know that the data
    //Can't be after midIndex since the vector is already sorted
    else
    {
      highIndex = midIndex - 1;
    }

    //Set midIndex to the new middle and increment i to keep searching
    midIndex = (highIndex + lowIndex) / 2;
    i++;
  }
  //Return if nothing is found
  return -1;
}
