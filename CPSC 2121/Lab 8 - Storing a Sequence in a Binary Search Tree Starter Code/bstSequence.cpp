/*
 * Name: Kenny Sun
 * Date Submitted: 4/3/2024
 * Lab Section: CPSC 2121-003
 * Assignment Name: Binary Search Tree Sequence
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>
#include <math.h>
#include "bstSequence.h"

using namespace std;

/* fix_size */
//Fixes the size of the the node
void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

/* insert */
// insert value v at rank r
Node *insert(Node *T, int v, int r)
{
    //Base case
    if(T == nullptr) return new Node(v);

    //Checks for rank of node
    int rank;
    if(T->left == nullptr) rank = 0;
    else rank = T->left->size;

    //Recursive calls to the left or the right tree depending on the rank value of the node vs the rank of the input
    if (r <= rank) T->left = insert(T->left, v, r);
    else T->right = insert(T->right, v, r - rank - 1);
    fix_size(T);    
    return T;
}

/* inorder_traversal*/
// returns a vector of key values corresponding to the inorder traversal of T (i.e., the contents of T in sorted order)
vector<int> inorder_traversal(Node *T)
{
  vector<int> inorder;
  vector<int> rhs;
  if (T == nullptr) return inorder;
  inorder=inorder_traversal(T->left);
  inorder.push_back(T->key);
  rhs=inorder_traversal(T->right);
  inorder.insert(inorder.end(), rhs.begin(), rhs.end());
  return inorder;
}

/* select */
// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
  assert(T!=nullptr && r>=0 && r<T->size);

  int rank_of_root = T->left ? T->left->size : 0;
  if (r == rank_of_root) return T;
  if (r < rank_of_root) return select(T->left, r);
  else return select(T->right, r - rank_of_root - 1);
}

/* split */
// Split tree T on rank r into tree L (containing ranks < r) and 
// a tree R (containing ranks >= r)
void split(Node *T, int r, Node **L, Node **R)
{
    int rank;
    if(T->left == nullptr) rank = 0;
    else rank = T->left->size;

    //Base case
    if (T == nullptr) {
        *L = nullptr;
        *R = nullptr;
        return;
    }

    //If r is less than or equal to the current rank
    if(r <= rank)
    {
        //Base case if there is no left branch
        if(T->left == nullptr)
        {
            *L = nullptr;
            *R = T;
        }
        else
        {
            //Current node and entire right side goes into right tree
            *R = T;
            Node *splitLeft = T->left;
            (*R)->left = nullptr;
            fix_size(*R);
            Node *tempRight = nullptr;
            Node *tempLeft = nullptr;
            //Split the left side and
            //Place resulting right side as current tree's left side
            //And resulting left side will become left tree
            split(splitLeft, r, &tempLeft, &tempRight);
            T->left = tempRight;
            fix_size(T);
            *L = tempLeft;
        }
    }
    else
    {
        //Base case if there is no right branch
        if(T->right == nullptr)
        {
            *R = nullptr;
            *L = T;
        }
        else
        {
            //Current node and entire left side goes into left tree
            *L = T;
            Node *splitRight = T->right;
            (*L)->right = nullptr;
            fix_size(*L);
            Node *tempRight = nullptr;
            Node *tempLeft = nullptr;
            //Split the right side and
            //Place resulting left side as current tree's right side
            //And resulting right side will become right tree
            split(splitRight, r - rank - 1, &tempLeft, &tempRight);
            T->right = tempLeft;
            fix_size(T);
            *R = tempRight;
        }
    }

}

/* insert_random */
// insert value v at rank r
Node *insert_random(Node *T, int v, int r)
{
    // If (v,r) is the Nth node inserted into T, then:
    // with probability 1/N, insert (v,r) at the root of T
    // otherwise, insert_random (v,r) recursively left or right of the root of T
  
    //Base case if insert_random has reached a leaf node
    if(T == nullptr)
    {
        //Create a new node and return it
        Node *insertNode = new Node(v);
        fix_size(insertNode);
        return insertNode;
    }

    //Get rank of the node
    int rank;
    if(T->left == nullptr) rank = 0;
    else rank = T->left->size;

    int baseCase = rand() % T->size;

    //Base case insertion
    if(baseCase == 0)
    {
        //Split the tree up with respect to k
        Node *splitLeft = nullptr;
        Node *splitRight = nullptr;
        split(T, r, &splitLeft, &splitRight);

        //Insert the new node and set the left and right pointers to the split up tree
        Node *insertNode = new Node(v);
        insertNode->left = splitLeft;
        insertNode->right = splitRight;
        fix_size(insertNode);
        return insertNode;
    }

    //If the r is less than or equal to current rank
    else if(r <= rank)
    {
        //Recursively inert right
        T->left = insert_random(T->left, v, r);
        fix_size(T);
        return T;
    }
    //Otherwise
    else
    {
        //Recursively insert left
        T->right = insert_random(T->right,v, r - rank - 1);
        fix_size(T);
        return T;
    }
}

/* did_x_beat_y */
// Returns true if team x defeated team y
// Leave this function unmodified
bool did_x_beat_y(int x, int y)
{
  assert (x != y);
  if (x > y) return !did_x_beat_y(y,x);
  unsigned long long lx = x;
  unsigned long long ly = y;
  return ((17 + 8321813 * lx + 1861 * ly) % 1299827) % 2 == 0;
}

/* order_n_teams */
// Return a BST containing a valid ordering of n teams
Node *order_n_teams(int n)
{
  Node *T = nullptr;

  // start by inserting the first team
  T = insert_random(T, 0, 0);

  // now insert the other teams...
  for (int i=1; i<n; i++)
  {
    // insert team i so the sequence encoded by the BST remains valid
    if (did_x_beat_y(i, select(T,0)->key)) // can we insert at beginning?
      T = insert_random(T, i, 0);
    else if (did_x_beat_y(select(T,T->size-1)->key, i)) // can we insert at end?
	    T = insert_random(T, i, T->size);
    else
    {
        //maxIterations uses logarithms as well as the fundamental way binary search works
        //To calculate the max number of times the binary search algorithm will have to be done
        int maxIterations = log2(T->size) + 20;
        //Variable declaration
        int j = 0;
        int lowRank = 0;
        int highRank = T->size - 1;
        //midRank stores the binary splits
        int midRank = (highRank + lowRank) / 2;
        //Iterates through algorithm
        while(j < maxIterations)
        {
            //Base case if there's no more need for adjustments, just 2 values to insert between
            if(lowRank == highRank - 1)
            {
                //Insert i into highRank
                T = insert_random(T, i, highRank);
                j = maxIterations;
            }
            //If midRank beat i, adjust lowRank
            else if(did_x_beat_y(select(T, midRank)->key, i))
            {
                lowRank = midRank;
            }
            //Otherwise, adjust highRank
            else
            {
                highRank = midRank;
            }

            //Set midRank to the new middle and increment j to keep searching
            midRank = (highRank + lowRank) / 2;
            j++;
        }
        // 7 5 4 2 0 3 1 6    (when inserting team i=8)
        // W W W L L L W L
    }
  }
  return T;
}

/* printVector */
//Prints a vector
void printVector(vector<int> v)
{
    for (int i=0; i<v.size(); i++)
    {
        cout << v[i] << endl;
    }
}
/*
int main(void)
{
  vector<int> inorder;
  Node *T = nullptr;

  // test insert at beginning
  for (int i=0; i<5; i++)
    T = insert_random(T, i+1, 0);
  cout << "Tree should contain 5 4 3 2 1:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
  // test insert at end
  for (int i=5; i<10; i++)
    T = insert_random(T, i+1, T->size);
  cout << "Tree should contain 5 4 3 2 1 6 7 8 9 10:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
  
  // test insert at middle
  for (int i=10; i<15; i++)
    T = insert_random(T, i+1, T->size/2);
  cout << "Tree should contain 5 4 3 2 1 12 14 15 13 11 6 7 8 9 10:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);

  // once insert is working, the next step is to build the
  // insert_random function -- to test this, just change
  // calls to insert above to insert_random.

  int N = 100000; // this should run quickly even for very large N!
  Node *S = order_n_teams(N);
  if (S == nullptr || S->size != N)
    cout << "Size of tree returned by order_n_teams is wrong\n";
  else {
    cout << "Team ordering:\n";
        inorder=inorder_traversal(S);
        printVector(inorder);
    for (int i=0; i<N-1; i++) {
      Node *x = select(S, i);
      Node *y = select(S, i+1);
      if (!did_x_beat_y(x->key, y->key)) {
        cout << "Invalid sequence: team " << x->key << " (position " << i <<
	              ") lost to team " << y->key << " (position " << i+1 << ")\n";
      }
    }
  }  
  
  return 0;
}
*/