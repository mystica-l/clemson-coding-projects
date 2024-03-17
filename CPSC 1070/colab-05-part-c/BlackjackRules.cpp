/* File Name: BlackjackRules.cpp
 * Name: Kenny Sun
 * Date: 11/18/2023
 * Purpose: Source for the BlackjackRules class
 * Checks if the value of a hand is 21 or under in black jack
 */
#include "BlackjackRules.h" //Source code needs own header file

/* isWon */
//Boolean function that returns whether or no thte value of a hand is 21 or under in black jack
bool BlackjackRules::isWon()
{
  //Iterates through each card and adds it's value to sum in blackjack
  int sum = 0;
  for(int i = 0; i < numOfCards; i ++)
    {
      //Exception made for Jacks, Queens, and Kings as their enumerated value isn't the same as their black jack value
      if(static_cast<int>(hand[i].getFace()) >= 10)
	{
	  sum += 10;
	}
	else
	{	  
	  sum += static_cast<int>(hand[i].getFace()) + 1;
	}
    }
  return sum <= 21;
}
