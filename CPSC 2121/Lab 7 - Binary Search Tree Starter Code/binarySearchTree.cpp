/*
 * Name: Kenny Sun
 * Date Submitted: 3/29/2024
 * Lab Section: CPSC 2121-003
 * Assignment Name: Binary Search Tree
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>
#include <math.h>
#include "binarySearchTree.h"

using namespace std;


void treeprint(Node *root, int level)
{
        if (root == NULL)
                return;
        for (int i = 0; i < level; i++)
                printf(i == level - 1 ? "|-" : "  ");
        printf("%d\n", root->key);
        treeprint(root->left, level + 1);
        treeprint(root->right, level + 1);
}


/* fix_size */
//Updates the size of the BST node
void fix_size(Node *T)
{
    T->size = 1;
    if (T->left) T->size += T->left->size;
    if (T->right) T->size += T->right->size;
}

/* insert */
// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
    if (T == nullptr) return new Node(k);
    if (k < T->key) T->left = insert(T->left, k);
    else T->right = insert(T->right, k);
    fix_size(T);
    return T;
}

/* inorder_traversal */
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

/* find */
// return a pointer to the node with key k in tree T, or nullptr if it doesn't exist
Node *find(Node *T, int k)
{   
    //Base cases for if the key is found or if a dead end is reached
    if(k == T->key) return T;
    else if(k < T->key && T->left == nullptr) return nullptr;
    else if(k > T->key && T->right == nullptr) return nullptr;
    
    //Recursive call for whether or not to move down the tree right or left based on node's key and key to find
    if(k < T->key) return find(T->left, k);
    else return find(T->right, k);
}

/* select */
// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
    assert(T!=nullptr && r>=0 && r<T->size);

    //Rank variable initialization
    int rank;
    if(T->left == nullptr) rank = 0;
    else rank = T->left->size;

    //Base case for when the rank is found
    if(rank == r) return T;
    //If the rank of the node is greater than the rank to find, select left
    else if(rank > r) return select(T->left, r);
    //If the rank of the node is less than the rank to find, select right with adjusted rank
    else return select(T->right, r - rank - 1);
}

/* join */
// Join trees L and R (with L containing keys all <= the keys in R)
// Return a pointer to the joined tree.  
Node *join(Node *L, Node *R)
{
    //Base cases for null pointers
    if(L == nullptr && R == nullptr) return nullptr;
    if(L == nullptr) return R;
    if(R == nullptr) return L;
    
    //Probability to choose a root
    double leftKey = abs(static_cast<double>(L->key));
    double rightKey = abs(static_cast<double>(R->key));
    double probability = leftKey / (leftKey + rightKey);

    //Right tree is root
    if(static_cast<double>(rand()) / RAND_MAX > probability)
    {   
        //Base case
        if(R->left == nullptr)
        { 
            //Set the left of the right tree to the left tree and return it
            R->left = L;
            fix_size(R);
            return R;
        }
        else
        {
            //Set the left of the right tree to the join of the left tree and itself
            R->left = join(L, R->left);
            fix_size(R);
            return R;
        }
    }
    //Left tree is root
    else 
    {
        if(L->right == nullptr)
        {
            //Set the right of the left tree to the right tree and return it
            L->right = R;
            fix_size(L);
            return L;
        }
        else
        {
            //Set the right of the left tree to the join of the right tree and itself
            L->right = join(L->right, R);
            fix_size(L);
            return L;
        }
    }
}

/* remove */
// remove key k from T, returning a pointer to the resulting tree.
// it is required that k be present in T
Node *remove(Node *T, int k)
{
    assert(T != nullptr);
    //Base case for the node being found to remove
    if(T->key == k)
    {
        //Delete T and return the joined children
        Node* tempLeft = T->left;
        Node* tempRight = T->right;
        delete T;
        return join(tempLeft, tempRight);
    }
    //If k is greater than the key
    if(T->key < k)
    {
        //Recursively search right
        T->right = remove(T->right, k);
        return T;
    }
    //If k is less than the key
    if(T->key > k)
    {
        //Recurisvely search left
        T->left = remove(T->left, k);
        return T;
    }

    return T;
}

/* split */
// Split tree T on key k into tree L (containing keys <= k) and a tree R (containing keys > k)
void split(Node *T, int k, Node **L, Node **R)
{
    //Base case
    if (T == nullptr) {
        *L = nullptr;
        *R = nullptr;
        return;
    }

    //If key is greater than k
    if(T->key > k)
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
            split(splitLeft, k, &tempLeft, &tempRight);
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
            split(splitRight, k, &tempLeft, &tempRight);
            T->right = tempLeft;
            fix_size(T);
            *R = tempRight;
        }
    }
    
}

/* insert_random */
// insert key k into the tree T, returning a pointer to the resulting tree
Node *insert_random(Node *T, int k)
{
    // If k is the Nth node inserted into T, then:
    // with probability 1/N, insert k at the root of T
    // otherwise, insert_random k recursively left or right of the root of T

    //Base case if insert_random has reached a leaf node
    if(T == nullptr)
    {
        //Create a new node and return it
        Node *insertNode = new Node(k);
        fix_size(insertNode);
        return insertNode;
    }
    int baseCase = rand() % T->size;
    //Base case insertion
    if(baseCase == 0)
    {
        //Split the tree up with respect to k
        Node *splitLeft = nullptr;
        Node *splitRight = nullptr;
        split(T, k, &splitLeft, &splitRight);

        //Insert the new node and set the left and right pointers to the split up tree
        Node *insertNode = new Node(k);
        insertNode->left = splitLeft;
        insertNode->right = splitRight;
        fix_size(insertNode);
        return insertNode;
    }
    //If the key is less than k
    else if(T->key < k)
    {
        //Recursively inert right
        T->right = insert_random(T->right, k);
        fix_size(T);
        return T;
    }
    //If the key is greater than k
    else
    {
        //Recursively insert left
        T->left = insert_random(T->left, k);
        fix_size(T);
        return T;
    }
}

/* printVector */
//Prints out all the elements of a vector
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
  vector<int> A(10,0);
  
  // put 0..9 into A[0..9] in random order
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
  cout << "Contents of A (to be inserted into BST):\n";
  printVector(A);
  
  // insert contents of A into a BST
  Node *T = nullptr;
  for (int i=0; i<10; i++) T = insert(T, A[i]);
  
  // print contents of BST (should be 0..9 in sorted order)
  cout << "Contents of BST (should be 0..9 in sorted order):\n";
  inorder=inorder_traversal(T);
  printVector(inorder);

  // test select
  for (int i=0; i<10; i++) {
    Node *result = select(T, i);
    if (!result || result->key != i) cout << "Select test failed for select(" << i << ")!\n";
  }

  // test find: Elements 0..9 should be found; 10 should not be found
  cout << "Elements 0..9 should be found; 10 should not be found:\n";
  for (int i=0; i<11; i++) 
    if (find(T,i)) cout << i << " found\n";
    else cout << i << " not found\n";

  // test split
  Node *L, *R;
  split(T, 4, &L, &R);
  cout << "Contents of left tree after split (should be 0..4):\n";
  inorder=inorder_traversal(L);
  printVector(inorder);
  cout << "Left tree size " << L->size << "\n";
  cout << "Contents of right tree after split (should be 5..9):\n";
  inorder=inorder_traversal(R);
  printVector(inorder);
  cout << "Right tree size " << R->size << "\n";
    
  // test join
  T = join(L, R);
  cout << "Contents of re-joined tree (should be 0..9)\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
  cout << "Tree size " << T->size << "\n";
  
  // test remove
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
  for (int i=0; i<10; i++) {
    T = remove(T, A[i]);
    cout << "Contents of tree after removing " << A[i] << ":\n";
    inorder=inorder_traversal(T);
    printVector(inorder);
    if (T != nullptr)
      cout << "Tree size " << T->size << "\n";
  }

  // test insert_random
  cout << "Inserting 1 million elements in order; this should be very fast...\n";
  for (int i=0; i<1000000; i++) T = insert_random(T, i);
  cout << "Tree size " << T->size << "\n";
  cout << "Done\n";
  
  return 0;
}

*/