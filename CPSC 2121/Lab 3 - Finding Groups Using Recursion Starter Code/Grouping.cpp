/*
 * Name: Kenny Sun
 * Date Submitted: 2/8/2024
 * Lab Section: CPSC 2121-003
 * Assignment Name: Lab 3 - Finding Groups Using Recursion
 */

#include "Grouping.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Implement the (parameterized) constructor and findGroup functions below

/* Constructor */
//Takes in a file name and fills a grid array with 1's
//and 0's based on the X's and .'s in the text file
Grouping::Grouping(string filename)
{
  ifstream fileReader;
  fileReader.open(filename);
  char c;
  int row = 0;
  int col = 0;
  //Iterates through all the characters
  while(fileReader >> c)
    {
      if(c == '.')
	{	  
	  grid[row][col] = 0;
	}
      else
	{
	  grid[row][col] = 1;
	}
      //Changes grid index to accurately place 1's and 0's
      if(col != 9)
	{
	  col ++;
	}
      else
	{
	  col = 0;
	  row ++;
	}
    }
  //Loops through and sends every X square not already in a group to the find group function
  for(int r = 0; r < 10; r ++)
    {
      for(int c = 0; c < 10; c ++)
	{
	  if(!inGroup(r, c) && grid[r][c] == 1)
	    {
	      findGroup(r, c, -1, -1);
	    }
	}
    }
}

/* findGroup */
//Takes in a X square's position as well as the previous square that called it
//And sorts those X squares into groups depending on whether or not they're touching
//In the original text grid
void Grouping::findGroup(int r, int c, int prevR, int prevC)
{
  //Checks if the previous square that called the function is already in a group
  //If not, create a new group
  if(!inGroup(prevR, prevC))
    {
      vector<GridSquare> add;
      add.push_back(GridSquare(r, c));
      groups.push_back(add);
    }
  //Otherwise, if the previous call is already in a group
  //Add it to that group
  else if(inGroup(prevR, prevC))
    {
      //rowIndex stores the index of where the previous square is
      int rowIndex;
      for(int i = 0; i < static_cast<int>(groups.size()); i ++)
	{
	  for(int j = 0; j < static_cast<int>(groups[i].size()); j ++)
	    {
	      if(groups[i][j].getRow() == prevR && groups[i][j].getCol() == prevC)
		{
		  rowIndex = i;
		}
	    }
	}
      //Stores it there
      groups[rowIndex].push_back(GridSquare(r, c));
    }
  //Uses location function to check for edges and checks if the surrounding squares aren't already in a group
  //And if they're an X send them to the findGroup function filling in the previous square parameters
  Edge position = location(r, c);
  if(position == MIDDLE || position == BOTTOM_EDGE || position == LEFT_EDGE || position == RIGHT_EDGE || position == BOTTOM_LEFT_CORNER || position == BOTTOM_RIGHT_CORNER)
    {
      if(!inGroup(r - 1, c) && grid[r - 1][c] == 1)
	{
	  findGroup(r - 1, c, r, c);
	}
    }
  if(position == MIDDLE || position == BOTTOM_EDGE || position == TOP_EDGE || position == RIGHT_EDGE || position == TOP_RIGHT_CORNER || position == BOTTOM_RIGHT_CORNER)
    {
      if(!inGroup(r, c - 1) && grid[r][c - 1] == 1)
	{
	  findGroup(r, c - 1, r, c);
	}
    }
  if(position == MIDDLE || position == BOTTOM_EDGE || position == TOP_EDGE || position == LEFT_EDGE || position == TOP_LEFT_CORNER || position == BOTTOM_LEFT_CORNER)
    {
      if(!inGroup(r, c + 1) && grid[r][c + 1] == 1)
	{
	  findGroup(r, c + 1, r, c);
	}
    }
  if(position == MIDDLE || position == TOP_EDGE || position == LEFT_EDGE || position == RIGHT_EDGE || position == TOP_LEFT_CORNER || position == TOP_RIGHT_CORNER)
    {
      if(!inGroup(r + 1, c) && grid[r + 1][c] == 1)
	{
	  findGroup(r + 1, c, r, c);
	}
    }
}

/* inGroup */
//Checks if a square's index is already in a group
//Returns true or false if they're already in/not in a group
bool Grouping::inGroup(int r, int c)
{
  for(int i = 0; i < static_cast<int>(groups.size()); i ++)
    {
      for(int j = 0; j < static_cast<int>(groups[i].size()); j ++)
	{
	  if(groups[i][j].getRow() == r && groups[i][j].getCol() == c)
	    {
	      return true;
	    }
	}
    }
  return false;
}

/* location */
//Uses an enumerated type and returns whether or not a row/column pair is at a certain edge case
Edge Grouping::location(int r, int c)
{
  bool topEdge = false;
  bool leftEdge = false;
  bool rightEdge = false;
  bool bottomEdge = false;
  if(r == 0)
    {
      topEdge = true;
    }
  else if(r == 9)
    {
      bottomEdge = true;
    }
  if(c == 0)
    {
      leftEdge = true;
    }
  else if(c == 9)
    {
      rightEdge = true;
    }
  if(!topEdge && !leftEdge && !rightEdge && !bottomEdge)
    {
      return MIDDLE;
    }
  else if(topEdge && !leftEdge && !rightEdge)
    {
      return TOP_EDGE;
    }
  else if(leftEdge && !topEdge && !bottomEdge)
    {
      return LEFT_EDGE;
    }
  else if(rightEdge && !topEdge && !bottomEdge)
    {
      return RIGHT_EDGE;
    }
  else if(bottomEdge && !leftEdge && !rightEdge)
    {
      return BOTTOM_EDGE;
    }
  else if(topEdge && leftEdge)
    {
      return TOP_LEFT_CORNER;
    }
  else if(topEdge && rightEdge)
    {
      return TOP_RIGHT_CORNER;
    }
  else if(bottomEdge && leftEdge)
    {
      return BOTTOM_LEFT_CORNER;
    }
  else
    {
      return BOTTOM_RIGHT_CORNER;
    }
}
//Simple main function to test Grouping
//Be sure to comment out main() before submitting
/*
int main()
{
  
    Grouping input1("input1.txt");
    input1.printGroups();
    
    return 0;
}
*/

//Do not modify anything below

GridSquare::GridSquare() : row(0), col(0) {} //Default constructor, (0,0) square

GridSquare::GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square

//Compare with == operator, used in test cases
bool GridSquare::operator== (const GridSquare r) const
{
    if ((row == r.row) && (col == r.col))
    {
        return true;
    }
    return false;
}

int GridSquare::getRow() //return row value
{
    return row;
}

int GridSquare::getCol() //return column value
{
    return col;
}

//Output using << operator, used in Grouping::printGroups()
//Function definition for <ostream> << <GridSquare>
ostream& operator<< (ostream& os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

Grouping::Grouping() : grid{},groups() {} //Default constructor, no groups

void Grouping::printGroups() //Displays grid's groups of squares
{
  for(int g=0; g<groups.size(); g++)
    {
        cout << "Group " << g+1 << ": ";
        for(int s=0; s<groups[g].size(); s++)
        {
            cout << " " << groups[g][s];
        }
        cout << endl;
    }
}

vector<vector<GridSquare>> Grouping::getGroups() //Needed in unit tests
{
    return groups;
}
