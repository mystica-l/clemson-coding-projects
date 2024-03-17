/*
 * Name: Kenny Sun
 * Date Submitted:
 * Lab Section: 001
 * Assignment Name: Lab 1 - Linked Lists
 */

#pragma once

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

//This class represents a linked list of node objects
//Do not modify anything in the class interface
template <class T>
class List{

 private:
  Node<T> * start; //pointer to the first node in this list
  int mySize;  //size (or length) of this list

 public:
  List();
  ~List();
  int size();
  bool empty();
  void insertStart(T);
  void insertEnd(T);
  void insertAt(T, int);
  void removeStart();
  void removeEnd();
  void removeAt(int);
  T getFirst();
  T getLast();
  T getAt(int);
  int find(T);

  //Print the name and this list's size and values to stdout
  //This function is already implemented (no need to change it)
  void print(string name){
    cout << name << ": ";
    cout << "size = " << size();
    cout << ", values = ";
    Node<T> * iterator = start;
    while(iterator != nullptr){
      cout << iterator->value << ' ';
      iterator = iterator->next;
    }
    cout << endl;
  }

}; //end of class interface (you may modify the code below)

//Implement all of the functions below
//Construct an empty list by initializig this list's instance variables
template <class T>
List<T>::List()
{
  //Initializes start to nullptr and mySize to 0
  mySize = 0;
  start = nullptr;  
}

//Destroy all nodes in this list to prevent memory leaks
template <class T>
List<T>::~List()
{
  //Creates deletion node
  Node<T> * garbage = start;
  //Checks if the list is empty to begin with
  if(garbage != nullptr)
    {
      //Iterates through the entire list
      while(garbage->next != nullptr)
	{
	  //Moves start over and deletes the previous node via garbage
	  start = start->next;
	  delete garbage;
	  garbage = nullptr;
	  //Sets garbage to start to move down the node
	  garbage = start;
	}
      //Deletes the final node that isn't caught with the condition of the while loop
      delete garbage;
      garbage = nullptr;
      start = nullptr;
    }	  
}

//Return the size of this list
template <class T>
int List<T>::size()
{
  return mySize;
}

//Return true if this list is empty
//Otherwise, return false
template <class T>
bool List<T>::empty()
{
  return mySize == 0;
}

//Create a new node with value, and insert that new node
//into this list at start
template <class T>
void List<T>::insertStart(T value)
{
  //Creates an insertion node
  Node<T> * insert = new Node<T>(value);
  //If the list is empty, the start is the insertion node
  if(start == nullptr)
    {
      start = insert;
      insert = nullptr;
    }
  else
    {
      //Otherwise, set the next node after insertion to start and move start back to the insertion node
      insert->next = start;
      start = insert;
      insert = nullptr;
    }
  mySize++;
}

//Create a new node with value, and insert that new node
//into this list at end
template <class T>
void List<T>::insertEnd(T value){
  //Create an insertion node
  Node<T> * insert = new Node<T>(value);

  //Empty list check to directly set start as the insert
  if(start == nullptr)
    {
      start = insert;
      insert = nullptr;
    }
  //Otherwise add to the end of the list
  else
    {
      Node<T> * traverse = start;
      //Traverse to the end of the list
      while(traverse->next != nullptr)
	{
	  traverse = traverse->next;
	}
      //Set the next of the last node to insert
      traverse->next = insert;

      //clear up pointers
      traverse = nullptr;
      insert = nullptr;
    }
  mySize++;
}

//Create a new node with value <value>, and insert that new node at position j
template <class T>
void List<T>::insertAt(T value, int j){
  //Checks if j is a valid index
  if(j > mySize || j < 0)
    {
      cout << "Invalid index: The index you provided is out of the range of the list!" << endl;
    }
  else
    {
      //Checks for 0 indexes and ending indexes and using insertStart and insertEnd instead
      if(j == 0)
	{
	  insertStart(value);
	}
      else if(j == mySize)
	{
	  insertEnd(value);
	}
      else
	{
	  //Traverse to the index before the insertion
	  Node<T> * traverse = start;
	  int index = 0;
	  while(index < j - 1)
	    {
	      traverse = traverse->next;
	      index ++;
	    }
	  
	  //Save the location of the next node with a pointer
	  Node<T> * traverseNext = traverse->next;
	  //create the insertion node
	  Node<T> * insert = new Node<T>(value);

	  //Insertion process
	  traverse->next = insert;
	  insert->next = traverseNext;

	  //Clear pointer and increment size
	  traverse = nullptr;
	  traverseNext = nullptr;
	  insert = nullptr;
	  mySize++;
	}
    }      
}

//Remove node at start
//Make no other changes to list
template <class T>
void List<T>::removeStart(){
  //Initial check for an empty list
  if(start == nullptr)
    {
      cout << "Empty list: Unable to remove start!" << endl;
    }
  //Checks if the size is 1 and if it is delete start
  else if(mySize == 1)
    {
      delete start;
      start = nullptr;
      mySize = 0;
    }
  else
    {
      //Saves the garbage node and moves the new start down 1 on the list
      Node<T> * garbage = start;
      start = start->next;
      //Deletes and decrements
      delete garbage;
      garbage = nullptr;
      mySize--;
    }
}

//Remove node at end
//Make no other changes to list
template <class T>
void List<T>::removeEnd(){
  //Initial check for an empty list
  if(start == nullptr)
    {
      cout << "Empty list: Unable to remove end!" << endl;
    }
  //Checks if the size is 1 and if it is delete start
  else if(mySize == 1)
    {
      delete start;
      start = nullptr;
      mySize = 0;
    }
  else
    {
      //Creation of garbage, traverse, and newEnd node
      Node<T> * garbage;
      Node<T> * traverse = start;
      Node<T> * newEnd = start;

      //Moves traverse to the end
      while(traverse->next != nullptr)
	{
	  traverse = traverse->next;
	}

      //Moves newEnd to 1 before the end
      while(newEnd->next != traverse)
	{
	  newEnd = newEnd->next;
	}

      //Removes the connection with nullptr
      newEnd->next = nullptr;

      //Deletes the end and clears up pointers and decrements
      garbage = traverse;
      delete garbage;
      traverse = nullptr;
      garbage = nullptr;
      newEnd = nullptr;
      mySize--;      
    }
}

//Remove node at position j
//Make no other changes to list
template <class T>
void List<T>::removeAt(int j){
  //Initial index range check
  if(j < 0 || j > mySize - 1)
    {
       cout << "Invalid index: The index you provided is out of the range of the list!" << endl;
    }
  //Checks for removal of the first or last nodes
  else if(j == 0)
    {
      removeStart();
    }
  else if(j == mySize - 1)
    {
      removeEnd();
    }
  else
    {
      //Creation of garbage, beforeGarbage, and afterGarbage nodes
      int beforeGarbageIndex = 0;
      Node<T> * garbage;
      Node<T> * beforeGarbage = start;
      Node<T> * afterGarbage;
      //Moves beforeGarbage to 1 before the index to be removed
      while(j - 1 > beforeGarbageIndex)
	{
	  beforeGarbage = beforeGarbage->next;
	  beforeGarbageIndex ++;
	}

      //Sets afterGarbage to the index being removed
      afterGarbage = beforeGarbage;
      afterGarbage = afterGarbage->next;

      //Save the position of the removed node with garbage and move afterGarbage over
      garbage = afterGarbage;
      afterGarbage = afterGarbage->next;

      //Relink the linked list
      beforeGarbage->next = afterGarbage;

      //Delete garbage and decrement
      delete garbage;
      garbage = nullptr;
      mySize--;
    }    
      
}

//Return the value of the first node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getFirst(){
  //Empty list check
  if(mySize == 0)
    {
      return T();
    }
  else
    {
      return start->value;
    }
}

//Return the value of the last node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getLast(){
  //Empty list check
  if(mySize == 0)
    {
      return T();
    }
  else
    {
      //Traverse to the end and return the value there
      Node<T> * traverse = start;
      while(traverse->next != nullptr)
	{
	  traverse = traverse->next;
	}
      return traverse->value;
    }
}

//Return the value of the node at position j in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getAt(int j){
  //Empty list check
  if(mySize == 0)
    {
      return T();
    }
  //Out of bounds check
  else if(j < 0 || j > mySize - 1)
    {
       cout << "Invalid index: The index you provided is out of the range of the list!" << endl;
    }
  else
    {
      //Iterator to get to the index of the node and return it's value
      Node<T> * traverse = start;
      for(int i = 0; i < j; i ++)
	{
	  traverse = traverse->next;
	}
      return traverse->value;
    }
}

//Return the position of the (first) node whose value is equal to the key
//Otherwise, return -1
template <class T>
int List<T>::find(T key){
  //Iterates through the linked list checking for matching values and returning when it's found
  Node<T> * traverse = start;
  int index = 0;
  while(traverse->next != nullptr)
    {
      if(traverse->value == key)
	{
	  return index;
	}
      traverse = traverse->next;
      index++;
    }
  return -1;
}
