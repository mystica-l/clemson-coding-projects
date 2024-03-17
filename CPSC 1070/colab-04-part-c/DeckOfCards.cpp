/* File Name: DeckOfCards.cpp
 * Name: Kenny Sun
 * Date: 11/2/2023
 * Purpose: Source code for the DeckOfCards object. Creates a deck with 52 cards that has the ability to shuffle and deal cards 1 by 1. DeckOfCards can also determine if all 52 cards have been dealt using the moreCards() function
 */

#include "DeckOfCards.h" //Needs own header file
#include <cstdlib> //Needed for random functions

using namespace std; //Needed to not type out std:: over and over

/* Default Constructor */
//Only constructor in the object fills the deck vector with 52 unqiue cards using nested for loops
DeckOfCards::DeckOfCards()
{
  //Provides the random function with a unique seed upon construction
  srand(time(0));
  for(int suit = 4; suit >= 1; suit --)
    {
      for(int face = 13; face >= 1; face --)
	{
	  Card add = Card(face, suit);
	  deck.push_back(add); 
	}
    }
  currentCard = 52;
}

/* shuffle */
//Iterates through each card in the deck and swaps it with another random card in the deck by calling swap() and randomInt().
void DeckOfCards::shuffle()
{
  //Resets to the top of the deck
  currentCard = 52;
  for(int i = 0; i < static_cast<int>(deck.size()); i ++)
    {
      swap(i, randomInt(0, deck.size() - 1));
    }
}

/* dealCard */
//Returns the card at the top of the deck using currentCard member variable
Card DeckOfCards::dealCard()
{
  Card returnCard = deck[currentCard - 1];
  currentCard --;
  return returnCard;
}

/* moreCards */
//Boolean function that returns whether or not all 52 cards have been dealt
bool DeckOfCards::moreCards()
{
  return !currentCard == 0;
}

/* randomInt */
//Generates a random int from min to max inclusive using modulus and returns it
int DeckOfCards::randomInt(int min, int max)
{
  int num;
  num = rand();
  num = num % (max + 1 - min) + min;
  return num;
}

/* swap */
//Swaps 2 cards given the index of the first card and the second card
void DeckOfCards::swap(int first, int second)
{
  Card temp = deck[first];
  deck[first] = deck[second];
  deck[second] = temp;
}
