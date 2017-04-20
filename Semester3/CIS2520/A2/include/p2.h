#ifndef __CBOURETTE_P2__
#define __CBOURETTE_P2__

typedef struct struct_Node{
    double myNumber;
} Node;

/**
 * createNode
 * Create a node to store in the list.
 *
 * IN: (int) the int to store.
 * RETURN: (Node*) Pointer to the node.
 *
 **/
Node* createNode(double a);

#endif
