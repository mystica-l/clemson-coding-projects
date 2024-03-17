/* File Name: PokerRules.h
 * Name: Kenny Sun
 * Date: 11/18/2023
 * Purpose: Header file for the PokerRules class
 */

#ifndef POKERRULES_H //Header guards
#define POKERRULES_H

#include "AnalyzeHand.h" //Needed to inherit from AnalyzeHand

//PokerRules class inherits from AnalyzeHand in a public manner so public member functions are stil available
class PokerRules : public AnalyzeHand
{
public:
  //Constructor (inherits and uses AnalyzeHand's constructor)
  PokerRules(vector<Card> inputHand) : AnalyzeHand(inputHand) { };
  //Member functions
  bool isWon();
  bool pair();
  bool twoPairs();
  bool threeOfAKind();
  bool fourOfAKind();
  bool straight();
  bool flush();
};

#endif
