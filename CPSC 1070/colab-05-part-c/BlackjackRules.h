/* File Name: BlackjackRules.h
 * Name: Kenny Sun
 * Date: 11/18/2023
 * Purpose: Header file for the BlackjackRules class
 */

#ifndef BLACKJACKRULES_H //Header guards
#define BLACKJACKRULES_H

#include "AnalyzeHand.h" //BlackjackRules inherits from AnalyzeHand

//BlackjackRules class inherits from AnalyzeHand in a public manner so public member functions are stil available
class BlackjackRules : public AnalyzeHand
{
public:
  //Constructor that inherits and uses AnalyzeHand's constructor
  BlackjackRules(vector<Card> inputHand) : AnalyzeHand(inputHand) { };
  //Member functions
  bool isWon();
};
  
#endif
