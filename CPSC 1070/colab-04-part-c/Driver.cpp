/* File Name: Driver.cpp
 * Name: Kenny Sun
 * Date: 11/2/2023
 * Purpose: Testing both the Card and DeckOfCards classes
 */

#include "Card.h" //Needed for card objects
#include "DeckOfCards.h" //Needed for the deck object
#include <iostream> //Needed to print things to the terminal

using namespace std; //Needed to not type out std:: over and over

int main()
{
  //Card testing
  //Default constructor should make it an ace of hearts
  Card aceOfHearts = Card();
  cout << "Ace of Hearts: " << aceOfHearts.toString() << endl;
  //Overloaded constructor should make it an ace of hearts
  aceOfHearts = Card(1, 1);
  //Overloaded constructor should make it a three of clubs
  Card threeOfClubs = Card(3, 3);
  //Overloaded constructor should make it a king of spades
  Card kingOfSpades = Card(13, 4);

  cout << "Ace of Hearts: " << aceOfHearts.toString() << endl;
  cout << "Three of Clubs: " << threeOfClubs.toString() << endl;
  cout << "King of Spades: " << kingOfSpades.toString() << endl << endl << endl << endl; 
  
  //Deck testing
  //Create deck object
  DeckOfCards deck = DeckOfCards();
  cout << "This should print Ace of Hearts, followed by Deuce of Hearts... all the way to King of Spades with whether or not there are more cards to be dealt printed in between." << endl;
  for(int i = 0; i < 52; i ++)
  {
    cout << deck.dealCard().toString() << endl;
    if(deck.moreCards())
      {
      cout << "More cards to deal!" << endl;
      }
    else
      {
	cout << "Out of cards :(" << endl;
      }
  }

  cout << endl << endl;
  //Shuffles the deck, should reset whether or not there are more cards to deal and shuffle them
  deck.shuffle();
  cout << "This should print out each card in random order with whether or not there are more cards to be dealt printed in between." << endl;
  for(int i = 0; i < 52; i ++)
  {
    cout << deck.dealCard().toString() << endl;
    if(deck.moreCards())
      {
      cout << "More cards to deal!" << endl;
      }
    else
      {
        cout << "Out of cards :(" << endl;
      }
  }
}
