/* Name : Kenny Sun
 * Date : September 20th, 2023
 * Purpose: The purpose of this program is to simulate a popular game from the show The Price is Right
 * known as Bullseye.
 * Bullseye is a game that revolves around giving contestants household items as well as a price range
 * in which contestants must select individual items and guess how many of those items' price would add up to
 * the predetermined price range.
 * Citations: TA Ethan helped with figuring out multiple character input reading
 */

#include <iostream> 
#include <iomanip>
#include <cstdlib>
#include <string>
#include <ctime>
#include <cctype>

using namespace std;

//Prototypes for functions
void runGame();
char runMenu();
int randomInt(int, int);
double getPrice(int, int);
void assignItems(string[]);
void manageFirstRun(string[], double[]);
bool runBid(string[], double[]);
void displayBoard(string[], double[]);
bool validRunBid(string[], string);
int guessQuantity(string);
bool validGuessQuantity(string);

/* main */
//Main function runs on program start and calls for runGame();
int main()
{
  runGame();
  return 0;
}

/* runGame */
//Creates all the game arrays
//Calls upon the menu system and maanges the inputs recieved from the menu system
//to perform other opeartions
//Manages attempts lefts
//Calls upon the assignItems function to create random boards and manageFirstRun to reset the games
void runGame()
{
  //Array and variable intialization
  string items[5];
  double itemChosenResults[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
  int attemptsLeft = 3;
  bool alreadyWon = false;
  srand(time(0));

  //Generates a random item from the sets to put into the array
  assignItems(items);

  //Checks whether or not this was the program's first run for resets
  manageFirstRun(items, itemChosenResults);

  char menuInput = '0';
  //While loop to constantly prompt for menu inputs unless there's a restart or quit
  while(menuInput != '4' && menuInput != '3')
    {
      cout << attemptsLeft << " attempt(s) left" << endl;
      menuInput = runMenu();

      //Checks inputs 1-4 and performs their respective menu actions
      if(menuInput == '1')
	{
	  if(!alreadyWon)
	    {
	      if(attemptsLeft > 0)
		{
		  alreadyWon = runBid(items, itemChosenResults);
		  attemptsLeft --;
		}
	      else
		{
		  cout << "You've run out of attempts, reset to play more!" << endl;
		}
	    }
	  else
	    {
	      cout << "You've already won, reset to play more!" << endl;
	    }
	}
      else if(menuInput == '2')
	{
	  cout << "\n";
	  displayBoard(items, itemChosenResults);
	  cout << "\n";
	}
      else if(menuInput == '3')
	{
	  cout << "Resetting..." << endl;
	  runGame();
	}
      else if(menuInput == '4')
	{
	  cout << "Thank you for playing!" << endl;
	}
    } 
}

/* runMenu */
//Prints out the menu and asks for inputs
//Performs input validations and returns chars to runGame
char runMenu(void)
{
  string input;
  cout << "\n";
  cout << "---- CPSC 1070 Bullseye Menu ----\n\n" << endl;
  cout << "[1] Bid on an item" << endl;
  cout << "[2] Display current board" << endl;
  cout << "[3] Restart the game" << endl;
  cout << "[4] Quit\n" << endl;
  cout << "Your choice?: ";
  cin >> input;

  //While loop for input validation
  while((input != "1" && input != "2") && (input != "3" && input != "4"))
    {
      cout << "Invalid input, please try again" << endl;
      cout << "Your choice?: ";
      cin >> input;
    }
  char returnChar = input[0];
  return returnChar;
}

/* runBid */
//Ran when menuInput == 1 to ask for an item to pid on
//Calls upon validRunBid to perform input validation for the item
//Calls upon guessQuantity to get a quantity for the item
//Calls upon getPrice to get a random price and prints out
//as well as return whether or not there was a successful guess
bool runBid(string items[5], double itemChosenResults[5])
{
  string input;
  
  cout << "Choose an item (1-5): ";
  cin >> input;

  //While loop for input validation
  while(!validRunBid(items, input))
    {
      cout << "Invalid input, please try again\n" << endl;
      cout << "Choose an item (1-5): ";
      cin >> input;
    }
  int inputInt = stoi(input);

  //Grabs guess amount from guessQuantity
  int guessAmount = guessQuantity(items[inputInt - 1]);

  double price;

  //Generates a price for the object that is bid on using the getPrice function
  if(inputInt == 1)
    {
      price = getPrice(3, 10);
    }
  else if(inputInt == 2)
    {
      price = getPrice(1, 3);
    }
  else if(inputInt == 3)
    {
      price = getPrice(1, 2);
    }
  else if(inputInt == 4)
    {
      price = getPrice(3, 5);
    }
  else
    {
      price = getPrice(1, 4);
    }

  //Returns a win or loss depending on guess
  double priceTimesGuess = guessAmount * price;

  itemChosenResults[inputInt - 1] = priceTimesGuess;
  if(priceTimesGuess >= 10.0 && priceTimesGuess <= 13.0)
    {
      cout << "\n" << items[inputInt - 1] << " has a unit cost of $";
      cout << fixed << setprecision(2) << price << ", so the total price is $";
      cout << fixed << setprecision(2) << priceTimesGuess << ". Which is between 10 and 13!\nCongrats!!!" << endl;
      items[inputInt - 1] = "";
      return true;
    }
  else
    {
      cout << "\n" << items[inputInt - 1] << " has a unit cost of $";
      cout << fixed << setprecision(2) << price << ", so the total price is $";
      cout << fixed << setprecision(2) << priceTimesGuess << ". Which unfortunately is not between $10 and 13" << endl;
      return false;
    }
}

/* guessQuantity */
//Used to give a number to runBid, returns an int
int guessQuantity (string itemName)
{
  string input;
  cout << itemName << " is selected. How many?: ";
  cin >> input;

  //While loop for input validation
  while(!validGuessQuantity(input))
    {
      cout << "Invalid input, please try again \n" << endl;
      cout << itemName << " is selected. How many?: ";
      cin >> input;
    }
  int inputInt = stoi(input);
  return inputInt;
}

/* validRunBid */
//Function for runBid input validation and is a bool function for valid / not returns
bool validRunBid(string items[5], string input)
{
  //Checks whether or not a bid is 1-5 items
  if(input != "1" && input != "2" && input != "3" && input != "4" && input != "5")
  {
    return false;
  }
  int inputInt = stoi(input);

  //Checks if the item has already been guessed
  if(items[inputInt - 1].length() < 1)
  {
  return false;
  }
  return true;
}

/* validGuessQuantity */
//Function for guessQuantity input validation and is a bool function for valid / not returns
bool validGuessQuantity(string input)
{
  //Checks to make sure each number is a digit
  for(int i = 0; i < static_cast<int>(input.length()); i ++)
    {
      if(!isdigit(input[i]))
	{
	  return false;
	}
    }

  //Checks to make sure there are no negative / 0 numbers
  int temp = stoi(input);
  if(temp <= 0)
    {
      return false;
    }
  return true;
}

/* displayBoard */
//Runs when the menuInput == 2
//Displays the board populated with items
//Displays the X's depending on hits or misses
void displayBoard(string items[5], double itemChosenResults[5])
{
  //bullseyeString is a string with the 10 / 13 borders and white space to fill X's in
  string bullseyeString = "                            |        |                       ";
  cout << "-----------------------------------------" << endl;
  cout << "|   1   |   2   |   3   |   4   |   5   |" << endl;
  
  //For loop to print out each object with the appropriate formatting
  for(int i = 0; i < 5; i ++)
    {
      if(itemChosenResults[i] == 0)
	{
	  cout << "|" << left << setw(7) << items[i];
	}
      else
	{
	  cout << "|       ";
	}
    }
  cout << "|" << endl;
  cout << "|   1   |   2   |   3   |   4   |   5   |" << endl;
  cout << "-----------------------------------------\n" << endl;

  //Checks itemChosenResults to see guesses and their prices to populate the X's
  for(int i = 0; i < 5; i ++)
    {
      if(itemChosenResults[i] != 0)
	{
	  //Any value that is less than or equal to 20 has their X exactly
	  //at the index that is three times it's value
	  //Any X past 20 is just put at the end
	  int temp = itemChosenResults[i];
	  if(temp <= 20)
	    {
	      bullseyeString[temp * 3] = 'X';
	    }
	  else
	    {
	      bullseyeString[60] = 'X';
	    }
	}
    }
  cout << bullseyeString << endl;
  cout << "  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20" << endl;
}

/* randomInt */
//Generates a random int from min to max inclusive using modulus and reutrns it
int randomInt(int min, int max)
{
  int num;
  num = rand();
  num = num % (max + 1 - min) + min;
  return num;
}

/* getPrice */
//Generates a random price from min $ to max $ includive using modulus and returns it
double getPrice(int min, int max)
{
  //Values are multiplied by 100 to include cents
  int price;
  int newMin = min * 100;
  int newMax = max * 100;
  price = rand() % (newMax + 1 - newMin) + newMin;
  double doublePrice = static_cast<double>(price);
  doublePrice /= 100;
  return doublePrice;
}

/* assignItems */
//Randomly assigns items to each entry in itemSet using randomInt
void assignItems(string itemSet[])
{
  string meats[] = {"Turkey", "Ham", "Chicken", "Beef"};

  string fruits[] = {"Apple", "Pear", "Grape", "Orange"};

  string drinks[] = {"Water", "Soda", "Juice", "Tea"};

  string items[] = {"Frame", "Candle", "Pillow", "Vase"};

  string snacks[] = {"Popcorn", "Chips", "Cookies", "Granola"};

  itemSet[0] = meats[randomInt(0, 3)];
  itemSet[1] = fruits[randomInt(0, 3)];
  itemSet[2] = drinks[randomInt(0, 3)];
  itemSet[3] = items[randomInt(0, 3)];
  itemSet[4] = snacks[randomInt(0, 3)];

}

/* manageFirstRun */
//Function that prints out the initial starting statement and is used to check for resets
void manageFirstRun(string items[], double itemChosenResults[])
{
  //static bool firstRun is a static variable utilized to initialize to true just at the start and retain it's
  //false state across different game runs to ensure the starting statement is printed out only once
  //Also used to avoid global variables
  static bool firstRun = true;
  if(firstRun)
    {
      cout << "Welcome to the CPSC 1070 Bullseye!\n" << endl;
      cout << "The goal is to get between $10 and $13 by picking an item and a quantity." << endl;
      cout << "There are five items, but you only get three tries.\n" << endl;
      displayBoard(items, itemChosenResults);
      cout << "\n";
    }
  firstRun = false;
}
  
