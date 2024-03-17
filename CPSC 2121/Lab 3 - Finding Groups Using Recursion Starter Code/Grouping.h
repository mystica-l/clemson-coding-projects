/*
 * Name: Kenny Sun
 * Date Submitted: 2/8/2024
 * Lab Section: CPSC2121-003
 * Assignment Name: Lab 3 - Finding Groups Using Recursion
 */

#pragma once

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Represents an occupied square in the grid
//Do not modify the GridSquare class or its member functions
class GridSquare
{
private:
  int row, col;
public:
  GridSquare(); //Default constructor, (0,0) square
  GridSquare(int r, int c); //(r,c) square
  //Compare with == operator, used in test cases
  bool operator== (const GridSquare r) const;
  int getRow(); //return row value
  int getCol(); //return column value
  //Output using << operator, used in Grouping::printGroups()
  friend ostream& operator<< (ostream& os, const GridSquare obj);
};

/*
Groups squares in 10x10 grid upon construction
Additional private helper functions may be added
Need to implement the constructor that takes a file name
as well as findGroup
The findGroup function's parameter list may be changed based
on how the function is implemented
*/

//Enumerated type for edge checking
enum Edge {MIDDLE, TOP_EDGE, BOTTOM_EDGE, RIGHT_EDGE, LEFT_EDGE, TOP_LEFT_CORNER, TOP_RIGHT_CORNER, BOTTOM_LEFT_CORNER, BOTTOM_RIGHT_CORNER};

class Grouping
{
private:
  int grid[10][10];
  vector<vector<GridSquare>> groups;
public:
  Grouping(); //Default constructor, no groups
  Grouping(string fileName); //Implement this function
  void findGroup(int r, int c, int prevR, int prevC); //Implement this function (recursive)
  void printGroups(); //Displays grid's groups of squares
  vector<vector<GridSquare>> getGroups(); //Needed in unit tests
  bool inGroup(int r, int c);
  Edge location(int r, int c);
};
