/*
 * Name:
 * Date Submitted:
 * Lab Section:
 * Assignment Name:
 */

#include <iostream>
#include <vector>

using namespace std;

int nQueens(int);
void fillInvalidSquares(bool**, const int &, const int &, const int &);
void printField(bool**);
//columns stores the ints columns that are invalid

//Uses recursion to count how many solutions there are for
//placing n queens on an nxn chess board
int nQueens(int n)
{
    //Creates a 2D array of booleans that are all set to true
    bool** validSquares = new bool*[n];
    for(int i = 0; i < n; i ++)
    {
        validSquares[n] = new bool[n];
    }
    for(int row = 0; row < n; ++row)
    {
        for(int col = 0; col < n; ++col)
        {
            validSquares[row][col] = true;
        }
    }
    
}

void fillInvalidSquares(bool** validSquares, const int &row, const int &col, const int &size)
{
    //Set all squares below the queen to be false
    for(int i = row + 1; i < size; i ++)
    {
        validSquares[i][col] = false;
    }
    
    //Sets all the diagonals below the placed queen to false
    int dRow = row + 1;
    int dCol = col + 1;
    while(dRow < size && dCol < size)
    {
        validSquares[dRow][dCol] = false;
        dRow++;
        dCol++;
    }
    dRow = row + 1;
    dCol = col - 1;
    while(dRow < size && dCol >= 0)
    {
        validSquares[dRow][dCol] = false;
        dRow++;
        dCol--;
    }
}

void printField(bool** squares)
{
    for(int i = 0; i < 10; i ++)
    {
        for(int j = 0; j < 10; j ++)
        {
            if(squares[i][j] == true) cout << "0 ";
            else cout << "X ";
        }
        cout << endl;
    }
}

int main()
{
    bool** validSquares = new bool*[10];
    for(int i = 0; i < 10; i ++)
    {
        validSquares[i] = new bool[10];
    }
    for(int i = 0; i < 10; i ++)
    {
        for(int j = 0; j < 10; j ++)
        {
            validSquares[i][j] = true;
        }
    }
    fillInvalidSquares(validSquares, 9, 9, 10);
    printField(validSquares);
    cout << "1: " << nQueens(1) << endl;
    cout << "2: " << nQueens(2) << endl;
    cout << "3: " << nQueens(3) << endl;
    cout << "4: " << nQueens(4) << endl;
    cout << "5: " << nQueens(5) << endl;
    cout << "6: " << nQueens(6) << endl;
    cout << "7: " << nQueens(7) << endl;
    cout << "8: " << nQueens(8) << endl;
    cout << "9: " << nQueens(9) << endl;
    cout << "10: " << nQueens(10) << endl;
    cout << "11: " << nQueens(11) << endl;
    cout << "12: " << nQueens(12) << endl;
    return 0;
}