#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

List* initList() {
    List *list = (List*)malloc(sizeof(List));
    if (list == NULL) throw("Unable to allocate memory!");
    //  Initalize list
    list->first = NULL;
    list->last = NULL;
    return list;
}

void addItem (List* list, void* ptr) {
    Item *newItem = (Item*)malloc(sizeof(Item));
    if (newItem == NULL) throw("Unable to allocate memory!");

    if (list->first == NULL) {
        list->first = newItem;
    } else {
        list->last->next = newItem;
    }
    newItem->ptr = ptr;
    list->last = newItem;
}

void insertAtIndex(List* list, void* location, int index) {
    Item *newItem = (Item*)malloc(sizeof(Item));
    if (newItem == NULL) throw("Unable to allocate memory!");

    newItem->ptr = location;

    int size = getSizeOfList(list);

    if (size == 0) {
        //  insert first node
        list->first = newItem;
        list->last = newItem;
        list->first->next = list->last;
        list->last->next = NULL;
    } else if (index >= size) {
        //  Add to end
        Item* temp = list->last;
        list->last = newItem;
        temp->next = list->last;
        list->last->next = NULL;
    } else if (index == 0) {
        //  insert before first node
        Item* temp = list->first;
        list->first = newItem;
        list->first->next = temp;
    } else {
        Item* temp = list->first;
        for (int i = 0; i < size; i++) {
            if (i == index-1) {
                Item* node = temp->next;
                temp->next = newItem;
                newItem->next = node;
                return;
            }
            temp = temp->next;
        }
    }
}

void deleteItem (List* list, int index) {
    Item* prev;
    Item* curr;
    Item* after;
    Item* anItem;

    anItem = list->first;

    int sizeOfList = getSizeOfList(list);

    //  Delete the only item in the list
    if (sizeOfList == 1){
        free(anItem);
        list->first = NULL;
        list->last = NULL;
    } else if (index == 0) {
        //  Delete the first item
        after = anItem->next;
        free(anItem);
        list->first = after;
    } else if (index == sizeOfList-1) {
        //  Delete the last item
        for (int i = 1; i <= sizeOfList; i++) {
            if (i == sizeOfList - 1) {
                prev = anItem;
            } else if(i == sizeOfList){
                curr = anItem;
            }
            anItem = anItem->next;
        }
        free(curr);
        list->last = prev;
    } else {
        for (int i = 0; i <= index+1; i++) {
            if (i == index - 1) {
                prev = anItem;
            } else if(i == index){
                curr = anItem;
            } else if(i == index + 1){
                after = anItem;
            }
            anItem = anItem->next;
        }
        free(curr);
        prev->next = after;
    }
}

int getSizeOfList (List* list) {
    int count;
    Item *ptr;

    ptr = list->first;

    //count = (ptr !=NULL) ? 0 : -1;
    count  = 0;

    while (ptr != NULL){
        count++;
        if (ptr == list->last) break;
        ptr = ptr->next;
    }
    return count;
}

void push(List* list, void* location) {
    insertAtIndex(list, location, 0);
}

void* pop(List* list) {
    if (list->first != NULL) {
        void* val = list->first->ptr;
        deleteItem(list, 0);
        return val;
    }
    return NULL;
}

void* getItem (List* list, int index) {
    if (list->first == NULL) return NULL;
    Item* item;
    item = list->first;
    for (int i = 0; i <= index; i++) {
        if (i == index) {
            return item->ptr;
        } else {
            if (item == list->last)
                break;
            else
                item = item->next;
        }
    }
    return NULL;
}

void printList (List* list) {
    Item *ptr;
    ptr = list->first;

    while (ptr != NULL){
        printf("Value: %p\n", ptr);
        if (ptr == list->last) break;
        ptr = ptr->next;
    }
}

void freeList (List* list) {
    Item *ptr, *next;
    ptr = list->first;

    while (ptr != NULL) {
        if (ptr == list->last) {
            free(ptr);
            break;
        } else {
            next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }
    free(list);
}

void throw (char* str) {
    printf("%s\n", str);
    exit(1);
}
