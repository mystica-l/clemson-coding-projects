/* File Name: LinkedList.c
 * Name: Kenny Sun
 * Date: 12/5/2023
 * Purpose: //Prompts the user for inputs of strings and creates a linked list of that strings, also prints the list out and clears it
 * Citations:
 * Anon. fgets. Retrieved December 5, 2023b from https://cplusplus.com/reference/cstdio/fgets/
 */

#include "LinkedList.h" //Source code needs own header
#include <stdlib.h> //Needed for memory allocation
#include <stdio.h> //Needed to print things out and scan from stream
#include <string.h> //Needed to use string operations

/* printList */
//Iterates through the list and prints out what the user inputted
void printList(struct node * head)
{
  //Checks if there if stringPtr of the head is even pointing to anything
  if(head->stringPtr == NULL)
    {
      printf("No words or phrases were given, -99 was the first input.\n");
    }
  //Checks if head is the only node to avoid plurality
  else if(head->next == NULL)
    {
      int length = strlen(head->stringPtr);
      head->stringPtr[length - 1] = '\0';
      printf("You've entered the following node: %s\n", head->stringPtr);
    }
  else
    {
      printf("You've entered the following nodes: ");

      //Iterates through the list and removes all the new line characters and replaces them with null characters
      //Also counts the number of nodes
      struct node * temp = head;
      int numberOfNodes = 0;
      while(temp->next != NULL)
	{
	  int length = strlen(temp->stringPtr);
	  temp->stringPtr[length - 1] = '\0';
	  numberOfNodes ++;
	  temp = temp->next;
	}
      int length = strlen(temp->stringPtr);
      temp->stringPtr[length-1] = '\0';
      numberOfNodes ++;

      temp = head;
      //Checks if there are only 2 nodes for no commas
      if(numberOfNodes == 2)
	{
	  printf("%s and %s\n", temp->stringPtr, temp->next->stringPtr);
	}
      else
	{
	  //Iterates through the nodes and prints them all out
	  while(temp->next != NULL)
	    {
	      printf("%s, ", temp->stringPtr);
	      temp = temp->next;
	    }
	  printf("and %s\n", temp->stringPtr);
	}
    }
}

/* makeList */
//Prompts the user for words or phrases to store into a linked list and print back out later
//Returns the head node of that linked list
struct node * makeList()
{
  //Initial allocation of memory for just the head
  struct node * head = (struct node *)(malloc(sizeof(struct node)));
  char input[250] = "";
  while(strcmp(input, "-99\n") != 0)
    {
      printf("Enter a word or phrase, or -99 to end: ");
      fgets(input, 250, stdin);
      //If the input is -99 do nothing
      if(strcmp(input, "-99\n") == 0)
	{

	}
      //Checks if the head is the first node and if it is gives it's stringPtr memory and the input
      else if(head->stringPtr == NULL)
	{
	  head->stringPtr = (char*)(malloc((strlen(input) + 1) * sizeof(char)));
	  strcpy(head->stringPtr, input);
	}
      else
	{
	  //temp traverses to the end of the list otherwise
	  struct node * temp = head;
	  while(temp->next != NULL)
	    {
	      temp = temp->next;
	    }
	  //Allocates memory for the next node at the end of the list and moves to the new node
	  temp->next = (struct node *)(malloc(sizeof(struct node)));
	  temp = temp->next;
	  //Allocates the last node's stringPtr memory and copies the input into it
	  temp->stringPtr = (char*)(malloc((20) * sizeof(char)));
	  strcpy(temp->stringPtr, input);
	}
    }
  return head;
}

/* clearList */
//Takes the head of the linked list and iterates through it deallocatingg the memory for the stringPtr and the node itself
void clearList(struct node * head)
{
  struct node * temp = head;
  struct node * delete = temp;
  //Iterates through the list using delete to keep track of the deleted node and temp to stay 1 ahead as to not lose the connection
  while(temp->next != NULL)
  {
    temp = temp->next;
    free(delete->stringPtr);
    free(delete);
    delete = NULL;
    delete = temp;
  }
  //Frees the very last node
  free(delete->stringPtr);
  free(delete);
  delete = NULL;
  temp = NULL;
  head = NULL;
}
