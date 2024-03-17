/*
* Name: Kenny Sun
* Date Submitted: 3/5/2024
* Lab Section: CPSC 2121-003
* Assignment Name: Lab 6 - Finding the Closest Pair of Points
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <cfloat>

using namespace std;

struct point
{
  double x;
  double y;
};

/* distanceFormula */
//Takes in 2 point structs and returns the distance between them
double distanceFormula(const point &point1, const point &point2)
{
  return sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
}

/* compare */
//Takes in the 2D vector of vectors,
//the row and column of what's being compared,
//and which direction is the comparison happening
double compare(const vector<vector<vector<point>>> &plane, const int &row, const int &col, const string &comparison)
{ 
  //Variable initaliation
  int size = plane[row][col].size();
  double min = DBL_MAX;

  //If we're comparing all the values within the cell
  if(comparison == "within")
  {
    //Iterate through each value
    for(int i = 0; i < size; i ++)
    {
      //And iterate through the values in front of it to compare
      for(int j = size; j > i; j --)
      {
        //Save and return the lowest value
        double distance = distanceFormula(plane[row][col][i], plane[row][col][j]);
        if(min > distance)
        {
          min = distance;
        }
      }
    }
    return min;
  }
  //If we're comparing all the values in the cell to the cell to the right
  else if(comparison == "right")
  {
    //col + 1 indicates a cell to the right
    int sizeRight = plane[row][col + 1].size();
    //Iterate through each value in the original cell
    for(int i = 0; i < size; i ++)
    {
      //And all the values in the right cell to compare
      for(int j = 0; j < sizeRight; j ++)
      {
        //Save and return the lowest value
        double distance = distanceFormula(plane[row][col][i], plane[row][col + 1][j]);
        if(min > distance)
        {
          min = distance;
        }
      }
    }
    return min;
  }
  //If we're comparign all the values in the cell to the cell below
  else if(comparison == "down")
  {
    //row + 1 indicates a cell below
    int sizeDown = plane[row + 1][col].size();
    //Iterate through each value in the original cell
    for(int i = 0; i < size; i ++)
    {
      //And all the values in the bottom cell to compare
      for(int j = 0; j < sizeDown; j ++)
      {
        //Save and return the lowest value
        double distance = distanceFormula(plane[row][col][i], plane[row + 1][col][j]);
        if(min > distance)
        {
          min = distance;
        }
      }
    }
    return min;
  }
  //Otherwise it's a diagonal
  else
  {
    //row + 1 and col + 1 indicate a diagonal cell
    int sizeDiagonal = plane[row + 1][col + 1].size();
    //Iterate through each value in the original cell
    for(int i = 0; i < size; i ++)
    {
      //And all the values in the diagonal bottom cell to compare
      for(int j = 0; j < sizeDiagonal; j ++)
      {
        //Save and return the lowest value
        double distance = distanceFormula(plane[row][col][i], plane[row + 1][col + 1][j]);
        if(min > distance)
        {
          min = distance;
        }
      }
    }
    return min;
  }
}

/*Implement the following function
  Reads in a file specified by the parameter
  Format of file: #of points on first line
  remaining (#of points) lines: x-value and y-value of point
  one point per line
  x-value and y-value are double-precision values and
  bounded by the unit square 0.0 <= x,y < 1.0
  Should use "spatial hashing" where the #of cells scales with the #of points
  and find the distance between the closest pair of points which will be
  returned as a double type value
*/

/* closestPair */
//Takes in a filename and uses spatial hasing to store all of the coordinate
//points in the file before returning the smallest distance between any
//2 points in the spatial hash map
double closestPair(string filename)
{
  //Get the number of points
  fstream input;
  input.open(filename);
  int numPoints;
  input >> numPoints;

  //I chose b to be the square root of the number of points + 1 because a generally good practice for sizes of hash tables
  //is for it to be a bit bigger than the number of inputs you have and this allows for that.
  //For example, if I have a 100 points, the square root of 100 is 10 + 1 leading to an 11x11 plane with 121 points
  //For a slightly more indexes to store information than there are elements
  int b = sqrt(numPoints) + 1;
  
  //Create a 2d vector of vectors
  vector<vector<vector<point>>> plane;

  //Populate plane with vectors of empty vectors
  for(int i = 0; i < b; i ++)
  {
    vector<vector<point>> temp;
    for(int j = 0; j < b; j++)
    {
      vector<point> temp2;
      temp.push_back(temp2);
    }
    plane.push_back(temp);
  }
  
  //Coordinate is divided by interval to find which index of the grid the point should be in
  double interval = 1.0 / b;
  
  //Add all the points into the 2D vector of vectors based on the interval
  for(int i = 0; i < numPoints; i ++)
  {
    point pointStruct;
    input >> pointStruct.x;
    input >> pointStruct.y;
    int row = pointStruct.y / interval;
    int col = pointStruct.x / interval;
    plane[row][col].push_back(pointStruct);
  }
  input.close();

  //Iterates through each vector in the 2D vector and sends them to the compare function
  double min = DBL_MAX;
  for(int row = 0; row < b; row++)
  {
    for(int col = 0; col < b; col++)
    {
      //within compares all the points within the same cell
      double distance = compare(plane, row, col, "within");
      if(min > distance)
      {
        min = distance;
      }
      //Check for an edge case on the right edge if not, compare everything on the right
      if(col != b - 1)
      {
        distance = compare(plane, row, col, "right");
        if(min > distance)
        {
          min = distance;
        }
      }
      if(row != b - 1)
      {
        distance = compare(plane, row, col, "down");
        if(min > distance)
        {
          min = distance;
        }
      }
      //Checks for anything on the bottom or the right edges, otherwise compare to the diagonal cell
      if(row != b - 1 && col != b - 1)
      {
        distance = compare(plane, row, col, "diagonal");
        if(min > distance)
        {
          min = distance;
        }
      }
      //Doing right, down, diagonal, effectively compares each cell
      //to one another without having to do all 8 cells each time
    }
  }
  //Returns the minimum value
  return min;
}




int main()
{
  double min;
  string filename;
  cout << "File with list of points within unit square: ";
  cin >> filename;

  time_t start, end; 

  /* You can call it like this : start = time(NULL); 
  in both the way start contain total time in seconds 
  since the Epoch. */
  time(&start); 

  // unsync the I/O of C and C++. 
  ios_base::sync_with_stdio(false); 

  min = closestPair(filename);
  cout << setprecision(16);
  cout << "Distance between closest pair of points: " << min << endl;

  // Recording end time. 
  time(&end); 

  // Calculating total time taken by the program. 
  double time_taken = double(end - start); 
  cout << "Time taken by program is : " << fixed 
      << time_taken << setprecision(5); 
  cout << " sec " << endl; 
  return 0;
}
