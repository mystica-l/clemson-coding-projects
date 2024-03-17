/* File Name: Driver.c
 * Name: Kenny Sun
 * Date: 12/5/2023
 * Purpose: Driver for the LinkedList file, calls makeList, printList, and clearList
 * Citations:
 * Anon. fgets. Retrieved December 5, 2023b from https://cplusplus.com/reference/cstdio/fgets/
 */
#include <stdio.h>
#include "Node.h"
#include "LinkedList.h"
int main()
{
  //Sets head to the head node created by makeList
  struct node * head = makeList();
  //Print it then clear the memory
  printList(head);
  clearList(head);
  head = NULL;
}
