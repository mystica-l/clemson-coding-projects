/*
 * Name: Kenny Sun
 * Date Submitted: 2/19/2024 
 * Lab Section: CPSC 2121-003
 * Assignment Name: Lab 4: Searching and Sorting
 */

#pragma once

#include <vector>
#include <time.h>

/* merge */
//Combines 2 vectors into 1 sorted vector
template <class T>
std::vector<T>merge(std::vector<T> firstHalf, std::vector<T> secondHalf)
{
  int i = 0;
  int j = 0;
  std::vector<T> returnVector;
  //While the iterators aren't finished
  while(i < firstHalf.size() || j < secondHalf.size())
  {
    //If every value of firstHalf has already been placed into returnVector
    //Keep adding the values of secondHalf
    if(i >= firstHalf.size())
    {
      returnVector.push_back(secondHalf[j]);
      j++;
    }
    //If every value of secondHalf has already been placed into returnVector
    //Keep adding the values of firstHalf
    else if(j >= secondHalf.size())
    {
      returnVector.push_back(firstHalf[i]);
      i++;
    } 
    //If firstHalf's next up value is less than secondHalf's next up value,
    //Add the firstHalf value to the vector and increment i
    else if(firstHalf[i] <= secondHalf[j])
    {
      returnVector.push_back(firstHalf[i]);
      i++;
    }
    //If secondHalf's next up value is less than firstHalf's next up value,
    //Add the secondHalf value to the vector and increment j
    else
    {
      returnVector.push_back(secondHalf[j]);
      j++;
    }
  }
  return returnVector;
}

/* mergeSort */
//Sorts a vector called first
template <class T>
std::vector<T> mergeSort(std::vector<T> first){

  //Check for base case
  if(first.size() > 1)
  {
    //Take the half index and create 2 vectors
    int half = first.size() / 2;
    std::vector<T> firstHalf;
    std::vector<T> secondHalf;

    //Save the first half of the first vector into firstHalf
    //and save the second half of the first vector into secondHalf
    for(int i = 0; i < half; i ++)
    {
      firstHalf.push_back(first[i]);
    }
    for(int i = half; i < first.size(); i ++)
    {
      secondHalf.push_back(first[i]);
    }

    //recursively call mergeSort for firstHalf and secondHalf
    firstHalf = mergeSort(firstHalf);
    secondHalf = mergeSort(secondHalf);
    //Before merging them to be sorted
    first = merge(firstHalf, secondHalf);
  }
  //Return first
  return first;
}

/* swap */
//Swaps 2 values in a vector by reference
//Using 2 indices given
template <class T>
void swap(std::vector<T> &inputVector, int index1, int index2)
{
  T temp = inputVector[index1];
  inputVector[index1] = inputVector[index2];
  inputVector[index2] = temp;
}

/* quickSort */
//Sorts a vector called first
template <class T>
std::vector<T> quickSort(std::vector<T> first)
{
  //base case
  if(first.size() <= 1)
  {
    return first;
  }
  //Random seeding for pivot positions
  srand(time(0));
  if(first.size() <= 1)
  {
    return first;
  }

  //pivotIndex = a random index using modulous
  int pivotIndex = rand() % first.size();

  //Save the pivotValue and move it to the front
  T pivotValue = first[pivotIndex];
  swap(first, 0, pivotIndex);

  //Set pivotIndex to 0
  pivotIndex = 0;

  //Iterates through the vector and follows the swapping rules
  //based off the pivot value
  for(int i = 1; i < first.size(); i ++)
  {
    if(first[i] < pivotValue)
    {
      swap(first, ++pivotIndex, i);
    }
  }

  //Swap the pivot value back to where pivotIndex ended up leaving a vector
  //With a pivot in the middle and all values below it on the left
  //And all values above it on the right
  swap(first, 0, pivotIndex);

  //Save the left side and right side of the vector around the pivotValue
  std::vector<T> left;
  std::vector<T> right;
  for(int i = 0; i < pivotIndex; i ++)
  {
    left.push_back(first[i]);
  }
  for(int i = pivotIndex + 1; i < static_cast<int>(first.size()); i ++)
  {
    right.push_back(first[i]);
  }

  //Recursively call quickSort
  left = quickSort(left);
  right = quickSort(right);

  //Mesh the left, pivot, and right back into one vector to return
  std::vector<T> returnVector;
  for(int i = 0; i < static_cast<int>(left.size()); i ++)
  {
    returnVector.push_back(left[i]);
  }
  returnVector.push_back(pivotValue);
  for(int i = 0; i < static_cast<int>(right.size()); i ++)
  {
    returnVector.push_back(right[i]);
  }
  return returnVector;
}


