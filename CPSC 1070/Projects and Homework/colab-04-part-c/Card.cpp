/* File Name: Card.cpp
 * Name: Kenny Sun
 * Date: 11/2/2023
 * Purpose: Source code for Card objects. Card objects contain member variables of enumerated types Faces and Suits that store the face and suit of the card. They can also print out themselves using the toString() function
 */

#include "Card.h" //Card.cpp uses a header file and this is needed
#include <iostream> //Needed to print out information regarding the card to the termninal

/* Default Constructor */
//Sets the card object's face and suit member variables to Ace of Hearts if no face or suit are given
Card::Card()
{
  face = static_cast<Faces>(1);
  suit = static_cast<Suits>(1);
}

/* OverLoaded Constructor */
//Sets the card object's face and suit member variables to the respective face and suit given the ints fed into the constructor
Card::Card(int face, int suit)
{
  this->face = static_cast<Faces>(face);
  this->suit = static_cast<Suits>(suit);
}

/* Copy Constructor */
//Constructor used when 1 card is assigned another card
Card::Card(const Card& copy)
{
  this->face = copy.face;
  this->suit = copy.suit;
}

//Static arrays faceArray and suitArray shared by all Card objects that contains the faces and suits and strings to be accessed when printing out the card information
string Card::faceArray[] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

string Card::suitArray[] = {"Hearts", "Diamonds", "Clubs", "Spades"};

/* toString */
//Prints out the card's information in the form of <face> of <suit> using the array of strings
string Card::toString()
{
  return faceArray[static_cast<int>(face) - 1] + " of " + suitArray[static_cast<int>(suit) - 1];
}
