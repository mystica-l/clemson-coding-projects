/* File Name: PokerRules.cpp
 * Name: Kenny Sun
 * Date: 11/18/2023
 * Purpose: Source code for the PokerRules class
 * Takes in a vector of Card objects and is able to evaluate what type of hand it is in poker (pair, two pair, three of a kind, four of a kind, straight, flush)
 */

#include "PokerRules.h" //Source code needs own header file

/* isWon */
//Overriden function from the abstract AnalyzeHand class
//Returns whether or not the hand is considered winning and meets the requirements of
//a pair, two pair, three of a kind, four of a kind, straight, or flush
bool PokerRules::isWon()
{ 
  return pair() || twoPairs() || threeOfAKind() || fourOfAKind() || straight() || flush();
}

/* pair */
//Boolean function that returns whether or not there is a pair in the hand
bool PokerRules::pair()
{
  //Sorts the hand using insertion sort ordering the cards by face value
  int j;
  for(int i = 1; i < 5; i ++)
  {
    Card temp = hand[i];
    j = i - 1;
    while(j >= 0 && hand[j].getFace() > temp.getFace())
    {
      hand[j + 1] = hand[j];
      j--;
    }
    hand[j + 1] = temp;
  }

  //Iterates through the sorted hand and checks if any 2 back to back cards all have the same face value
  for(int i = 0; i < 4; i ++)
    {
      if(hand[i].getFace() == hand[i + 1].getFace())
	{
	  return true;
	}
    }
  return false;
}

/* twoPairs */
//Boolean function that returns whether or not there is a 2 pair in the hand
bool PokerRules::twoPairs()
{
  //Sorts the hand using insertion sort ordering the cards by face value
  int j;
  for(int i = 1; i < 5; i ++)
  {
    Card temp = hand[i];
    j = i - 1;
    while(j >= 0 && hand[j].getFace() > temp.getFace())
    {
      hand[j + 1] = hand[j];
      j--;
    }
    hand[j + 1] = temp;
  }

  //With two pair, there are only 3 possible combinations of two pair in a sorted hand so it is checked using if else statements
  // 0 0 1 2 2
  // 0 0 1 1 2
  // 0 1 1 2 2
  if(hand[0].getFace() == hand[1].getFace() && hand[3].getFace() == hand[4].getFace())
    {
      return true;
    }
  else if(hand[1].getFace() == hand[2].getFace() && hand[3].getFace() == hand[4].getFace())
    {
      return true;
    }
  else if(hand[0].getFace() == hand[1].getFace() && hand[2].getFace() == hand[3].getFace())
    {
      return true;
    }
  return false;
}

/* threeOfAKind */
//Boolean function that returns whether or not there are 3 of the same face value cards in a hand
bool PokerRules::threeOfAKind()
{
  //Sorts the hand using insertion sort ordering the cards by face value
  int j;
  for(int i = 1; i < 5; i ++)
  {
    Card temp = hand[i];
    j = i - 1;
    while(j >= 0 && hand[j].getFace() > temp.getFace())
    {
      hand[j + 1] = hand[j];
      j--;
    }
    hand[j + 1] = temp;
  }

  //Iterates through the sorted hand and checks if any 3 back to back cards all have the same face value
  for(int i = 0; i < 3; i ++)
    {
      if(hand[i].getFace() == hand[i + 1].getFace() && hand[i + 1].getFace() == hand[i + 2].getFace())
        {
          return true;
        }
    }
  return false;
}

/* fourOfAKind */
//Boolean function that returns whether or not there are 4 of the same face value cards in a hand
bool PokerRules::fourOfAKind()
{
  //Sorts the hand using insertion sort ordering the cards by face value
  int j;
  for(int i = 1; i < 5; i ++)
  {
    Card temp = hand[i];
    j = i - 1;
    while(j >= 0 && hand[j].getFace() > temp.getFace())
    {
      hand[j + 1] = hand[j];
      j--;
    }
    hand[j + 1] = temp;
  }

  //Iterates through the sorted hand and checks if any 4 back to back cards all have the same value
  for(int i = 0; i < 2; i ++)
    {
      if(hand[i].getFace() == hand[i + 1].getFace() && hand[i + 1].getFace() == hand[i + 2].getFace() && hand[i + 2].getFace() == hand[i + 3].getFace())
        {
          return true;
        }
    }
  return false;
}

/* straight */
//Boolean function that returns whether or not the hand meets the requirements for a poker straight
//Poker straight contains 5 cards in consecutive increasing order (ex: Three, Four, Five, Seven, Six) (doesn't have to be in order
bool PokerRules::straight()
{
  //Sorts the hand using insertion sort ordering the cards by face value
  int j;
  for(int i = 1; i < 5; i ++)
  {
    Card temp = hand[i];
    j = i - 1;
    while(j >= 0 && hand[j].getFace() > temp.getFace())
    {
      hand[j + 1] = hand[j];
      j--;
    }
    hand[j + 1] = temp;
  }


  //Special check for an Ace high straight as an Ace can be a straight for Ace-Five or Ten-Ace
  if(hand[0].getFace() == Ace && hand[1].getFace() == Ten && hand[2].getFace() == Jack && hand[3].getFace() == Queen && hand[4].getFace() == King)
    {
      return true;
    }

  //Iterates through the cards in the hand vector and checks each card after the next is in incrementing order as it's already sorted
  int start = static_cast<int>(hand[0].getFace());
  for(int i = 1; i < 5; i ++)
    {
      if(static_cast<int>(hand[i].getFace()) != start + i)
	{
	  return false;
	}
    }
  return true;
}
/* flush */
//Boolean function that returns whether or not all 5 cards are of the same suit
bool PokerRules::flush()
{
  //Iterates through all 5 cards and check if they're the same suit as the first
  int flushStart = static_cast<int>(hand[0].getSuit());
  for(int i = 1; i < 5; i ++)
    {
      if(static_cast<int>(hand[i].getSuit()) != flushStart)
        {
          return false;
        }
    }
  return true;
}
