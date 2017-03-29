/**
 * Carter Bourette (Nov 2015)
 * cbourette@gmail.com
 *
 * A Linked List storing a void ptr to be cast on return.
 * Edit: Fixed memory leak (Jan 2016)
 * Edit: Void Pointers as list structure (Feb 2016)
 **/

#ifndef __CBOURETTE_LINKEDLIST__
#define __CBOURETTE_LINKEDLIST__

typedef struct struct_item{
    void* ptr;
    struct struct_item *next;
} Item;

typedef struct struct_list{
    Item *first;
    Item *last;
} List;

/**
 * initList
 * Allocates memory on heap for List structure.
 *
 * IN: NONE.
 * RETURN: (LIST*) Address to a List on heap.
 * ERROR: If no memory is available, call throwError().
 *
 **/
List* initList();

void enqueue(List* list, void* location);

void* dequeue(List* list);

/**
 * addItem
 * Adds an item to the list.
 *
 * IN: (LIST*) pointer to list, and (int) integer value to store in list.
 * RETURN: VOID
 * ERROR: If no memory is available, call throwError().
 *
 **/
void addItem (List* list, void* location);

/**
 * deleteItem
 * Delete an item in the list by index.
 *
 * IN: (LIST*) pointer to list, and (int) integer value of index to delete.
 * RETURN: VOID
 *
 **/
void deleteItem (List* list, int index);

/**
 * getSizeOfList
 * Returns size of list.
 *
 * IN: (LIST*) pointer to list.
 * RETURN: (INT) number of items in the list.
 *
 **/
int getSizeOfList (List* list);

/**
 * getItem
 * Returns pointer to item.
 *
 * IN: (LIST*) pointer to list, and index you are searching for.
 * RETURN: (VOID*) of the item you stored.
 * NOTE: Cast this to desired type.
 *
 **/
void* getItem (List* list, int index);

/**
 * printList
 * Prints out the values in the list.
 *
 * IN: (LIST*) pointer to list.
 * RETURN: VOID
 *
 **/
void printList (List* list);

/**
 * freeList
 * Free the memory of all items in list, then the list structure.
 *
 * IN: (LIST*) pointer to list.
 * RETURN: VOID
 *
 **/
void freeList (List* list);

/**
 * throw
 * Print out an error message quit the program.
 *
 * IN: (CHAR*) an error message to echo to the user.
 * RETURN: VOID - Returns Error Code 1 to OS.
 *
 **/
void throw (char* str);

#endif
