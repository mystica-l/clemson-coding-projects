/* File Name: Node.h
 * Name: Kenny Sun
 * Date: 12/5/2023
 * Purpose: //Holds the struct for the node
 */
#ifndef NODE_H //Header guards
#define NODE_H

struct node
{
  //Ptr for the string the node will store
  char * stringPtr;
  //Points to the next node in the linked list
  struct node * next;
};

#endif
