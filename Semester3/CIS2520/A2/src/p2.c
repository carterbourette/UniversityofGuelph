/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 
 * Assignment 2
 * Data Structures
 * October 17, 2016
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "p2.h"
#include "Cars.h"
#include "Parse.h"
#include "LinkedList.h"

int main(int argc, char* argv[]) {
    //  Create a stack
    if (argc < 2) {
        printf("Invalid arguments! %d\n", argc);
        printf("To run part 2:\n./A2p2 \"12+53-*\"\n");
        exit(1);
    }
    char* str = argv[1];

    printf("Computing %s...\n", str);

    List* list = initList();

    for (int i = 0; i < strlen(str); i++) {
        //  While we have integers push them onto the stack
        if (str[i] > 47 && str[i] < 58) {
            double num = str[i] - '0';
            push(list, createNode(num));
        } else {
            //  When we hit an operator pop the nodes off the stack in reverse order.
            Node* b = (Node*)pop(list);
            Node* a = (Node*)pop(list);

            //  Perform the operation and push it back onto the stack.
            switch(str[i]) {
                case '+':
                    push(list, createNode(a->myNumber + b->myNumber));
                    break;
                case '-':
                    push(list, createNode(a->myNumber - b->myNumber));
                    break;
                case '*':
                    push(list, createNode(a->myNumber * b->myNumber));
                    break;
                case '/':
                    if (b->myNumber != 0) push(list, createNode(a->myNumber / b->myNumber));
                    else {
                        printf("Divide by zero!\n");
                        exit(1);
                    }
                    break;
                default:
                    printf("Invalid input!\n");
                    exit(1);
            }
            //  Free the numbers we're done with.
            free(a);
            free(b);
        }
    }
    //  When we're done with the inital string pop the answer of the list.
    Node* answer = (Node*)pop(list);
    printf("The answer is %.2lf\n", answer->myNumber);

    //  Take care of memory
    free(answer);
    freeList(list);
}

/**
 * createNode
 * Create a node to store in the list.
 *
 * IN: (double) the int to store.
 * RETURN: (Node*) Pointer to the node.
 *
 **/
Node* createNode(double a) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (n == NULL) return NULL;
    n->myNumber = a;
    return n;
}
