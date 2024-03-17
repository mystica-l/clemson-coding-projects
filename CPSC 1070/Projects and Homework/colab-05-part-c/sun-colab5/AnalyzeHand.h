/* File Name: AnalyzeHand.h
 * Name: Kenny Sun
 * Date: 11/18/2023
 * Purpose: Header file for the abstract AnalyzeHand class
 */

#ifndef ANALYZEHAND_H //Header guards
#define ANALYZEHAND_H

#include <vector> //The hand is stored in a vector so #include <vector> is needed
#include "Card.h" //Uses card objects

class AnalyzeHand
{
public:
  //Constructor
  AnalyzeHand(vector<Card>);
  //Member functions
  string toString();
  //Pure virtual function allowing for abstract class
  virtual bool isWon() = 0;
protected:
  //Protected member functions
  int numOfCards;
  vector<Card> hand;
};
#endif
