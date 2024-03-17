/* File Name: DeckOfCards.h
 * Name: Kenny Sun
 * Date: 11/2/2023
 * Purpose: Header file for the DeckOfCards.cpp class
 */

//Header guards
#ifndef DECKOFCARDS_H
#define DECKOFCARDS_H

#include <vector> //Needed for the deck vector which contains the cards
#include "Card.h" //Needed for the deck vector which has card objects

//Class declaration
class DeckOfCards
{
public:
  //Constructor
  DeckOfCards();
  //Member functions
  void shuffle();
  Card dealCard();
  bool moreCards();
private:
  //Member variables
  int currentCard;
  vector<Card> deck;
  
  int randomInt(int, int);
  void swap(int, int);
};

#endif
