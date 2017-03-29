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

void enqueue(List* list, void* location) {
    addItem(list, location);
}

void* dequeue(List* list) {
    void* location; Item* temp;

    if (list->first == NULL) return NULL;
    else if (list->first == list->last) {
        temp = list->first;
        location = temp->ptr;
        list->first = NULL;
        list->last = NULL;
        //free(temp);
    } else {
        temp = list->first;
        location = temp->ptr;
        list->first = list->first->next;
        free(temp);
    }
    return location;
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

    count = 0;

    while (ptr != NULL){
        count++;
        if (ptr == list->last) break;
        ptr = ptr->next;
    }
    return count;
}

void* getItem (List* list, int index) {
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
