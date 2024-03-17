/* File Name: Dealer.cpp
 * Name: Kenny Sun
 * Date: 11/18/2023
 * Purpose: Driver file for the BlackJackRules and PokerRules class
 * Takes in command line arguments to determine how to evaluate a preadded vector of cards with either poker or black jack rules
 */

#include <iostream> //Needed to print things out to the terminal
#include "BlackjackRules.h" //Needed for BlackjackRules objects
#include "PokerRules.h" //Needed for PokerRules objects
#include "Card.h" //Needed for Card objects to give to BlackjackRules and PokerRules

using namespace std; //Needed to avoid repetitve std::

/* main */
//Takes in command line arguments of either a 1 or 0 after the executable and evalutes a precoded hand in either black jack or poker rules
int main(int argc, char *argv[])
{
  //Creates vector of cards
  vector<Card> newHand;
  newHand.push_back(Card(10, 1));
  newHand.push_back(Card(1, 1));
  newHand.push_back(Card(11, 1));
  newHand.push_back(Card(12, 1));
  newHand.push_back(Card(5, 2));

  //Validation check for the correct command line arguments
  //Won't run if there are more than 2 command line arguments or if the second command line argument isn't a 1 or 0
  string input;
  if(argc != 2)
    {
      input = "";
    }
  else
    {
      input = argv[1];
    }

  //0 represents black jack
  if(input == "0")
    {
      //Creates BlackjackRules object with the hand and prints out the hand and whether or not it is winning based on the BlackjackRules criteria
      BlackjackRules blackJackObject = BlackjackRules(newHand);
      cout << "******* Welcome to Blackjack Rules *******" << endl << endl;
      cout << "We are checking the Hand:" << endl;
      cout << "\t" << blackJackObject.toString() << endl << endl;
      cout << "...Checking" << endl << endl;
      if(blackJackObject.isWon())
	{
	  cout << "This is a Winning hand!" << endl;
	}
      else
	{
	  cout << "This is a Losing hand!" << endl;
	}
      cout << endl;
    }
  //1 represents poker
  else if(input == "1")
    {
      //Creates PokerRules object with the hand and prints out the hand and whether or not it is winning based on the PokerRules criteria
      PokerRules pokerObject = PokerRules(newHand);
      cout << "******* Welcome to Poker Rules *******" << endl << endl;
      cout << "We are checking the Hand:" << endl;
      cout << "\t" << pokerObject.toString() << endl << endl;
      cout << "...Checking" << endl << endl;
      if(pokerObject.isWon())
        {
          cout << "This is a Winning hand!" << endl;
        }
      else
	{
	  cout << "This is a Losing hand!" << endl;
	}
      cout << endl;
    }
  //Otherwise it's invalid
  else
    {
      cout << "Invalid command line argument! Please follow your execution with either 0 or 1!" << endl;
    }
}
