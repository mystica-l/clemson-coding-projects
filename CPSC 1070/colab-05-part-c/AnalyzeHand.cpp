/* File Name: AnalyzeHand.cpp
 * Name: Kenny Sun
 * Date: 11/18/2023
 * Purpose: Source code for the AnalyzeHand class
 * Takes in a vector of cards from a user and
 * is an abstract class that gets inherited by child
 * class to implement different games' isWon() functions
 */

#include "AnalyzeHand.h" //Source code needs own header file
#include <iostream> //Needed to print things out

/* Overloaded Constructor */
//Takes in a vector of cards and sets the hand member vector to that input hand as well as sets numOfCards to the number of cards in the hand
AnalyzeHand::AnalyzeHand(vector<Card> inputHand)
{
  hand = inputHand;
  numOfCards = inputHand.size();
}

/* toString */
//Print out all the cards in the hand in a formatted manner
string AnalyzeHand::toString()
{ 
  string returnString = "[";
  for(int i = 0; i < numOfCards; i ++)
    {
      returnString += hand[i].toString();
      returnString += ", ";
    }
  returnString += "]";
  return returnString;
}
