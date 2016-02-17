#include <stdio.h>
#include "LinkedList.h"

int main () {

 /**
  *
  * Fun with void LinkedLists
  * -------------------------
  * Create a new list
  * - List* list;
  * addItem (pointerToList, pointerOfItem)
  * getItem (pointerToList, intIndexInList)
  * getSizeOfList (pointerToList)
  * deleteItem (pointerToList, intIndexToRemove)
  * printList (pointerToList)
  *
  **/

  List* linkedlist;

  int a = 1, b = 2, c = 3, d = 4;
  int* ptr;

  //    Add items by l
  addItem (linkedlist, &a);
  addItem (linkedlist, &b);
  addItem (linkedlist, &c);
  addItem (linkedlist, &d);

  //    Print some information
  printList (linkedlist);
  printf("The list contains %d items!\n\n", getSizeOfList (linkedlist));

  //    Delete index 2, item 3 (int c)
  deleteItem (linkedlist, 2);

  //    Print some information
  printList (linkedlist);
  printf("The list contains %d items!\n\n", getSizeOfList (linkedlist));

  //    Lets grab index 1, item 2 (int b) and print the value
  //    Remember to cast the return value, see LinkedList.h
  ptr = (int*) getItem (linkedlist, 1);
  printf("Getting index 1:\tValue: %d\n", *ptr );

    return 0;
}
