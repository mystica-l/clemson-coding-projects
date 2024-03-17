/* File Name: Card.h
 * Name: Kenny Sun
 * Date: 11/2/2023
 * Purpose: Header file for the Card.cpp class
 */

//Header guards
#ifndef CARD_H
#define CARD_H

#include <string> //String is included as string objects are used when printing out card information

using namespace std; //Used to negate usage of cosntant std:: with every standard object

//Enumerated types for the possible faces of a card, from Ace to King
enum Faces {Ace = 0, Deuce, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King};

//Enumerated types for the 4 possible suits of a card
enum Suits {Hearts = 0, Diamonds, Clubs, Spades};

//Class Card
class Card
{
public:
  //Default Constructor
  Card();
  //Overloaded Constructor
  Card(int, int);
  //Copy Constructor
  Card(const Card& copy);
  //Member functions
  string toString();
  Faces getFace();
  Suits getSuit();
private:
  //Member variables
  Faces face;
  Suits suit;
  static string faceArray[13];
  static string suitArray[4];
};
#endif
