/**
 * Carter Bourette
 * cbourette@gmail.com
 *
 * A Tree structure that stores a expression data type.
 *
 **/

#ifndef __CBOURETTE_TESTING__
#define __CBOURETTE_TESTING__

typedef struct struct_node{
    char operator;
    double operand;
    int variable;
    struct struct_node *left;
    struct struct_node *right;
} Node;

/**
 * initNode
 * Creates new node on the heap and returns the pointer of node.
 *
 * IN: NONE.
 * RETURN: (Node*) The node element.
 * ERROR: If malloc fails Node* is null.
 *
 **/
Node* initNode();

/**
 * insertLeft
 * Inserts a node on the left of a parent node.
 *
 * IN: (Node*) Parent.
 * RETURN: NONE.
 * ERROR: NONE.
 *
 **/
 void insertLeft(Node* parent);

 /**
  * insertRight
  * Inserts a node on the right of a parent node.
  *
  * IN: (Node*) Parent.
  * RETURN: NONE.
  * ERROR: NONE.
  *
  **/
  void insertRight(Node* parent);


  void printTree(Node* node);

  /**
   * convertToInt
   * Convert string to int for cars values.
   *
   * IN: (char*) string with numbers.
   * RETURN: (int) integer value.
   * ERROR: NONE.
   *
   **/
  int convertToInt(char* chars);

  /**
   * stringify
   * Return the pointer to a string on the heap.
   *
   * IN: (char*) The string to malloc.
   * RETURN: (char*) The string malloc'd.
   * ERROR: NONE.
   *
   **/
  char* stringify(char* str);

  /**
   * substring
   * Given a string and two indicies return a new string.
   *
   * IN: (char*) the original string, (int) start index, (int) end index.
   * RETURN: (char*) the substring.
   * ERROR: malloc returns NULL on memory fail.
   * NOTE: Caller must free substring
   *
   **/
  char* substring(char* str, int start, int end);

  /**
   * inOrder
   * Traversal of the tree in order.
   *
   * IN: (Node*) the root of the tree to print.
   * RETURN: NONE.
   * ERROR: NONE.
   *
   **/
  void inOrder(Node* n);

  /**
   * preOrder
   * Traversal of the tree pre order.
   *
   * IN: (Node*) the root of the tree to print.
   * RETURN: NONE.
   * ERROR: NONE.
   *
   **/
  void preOrder(Node* n);

  /**
   * postOrder
   * Traversal of the tree post order.
   *
   * IN: (Node*) the root of the tree to print.
   * RETURN: NONE.
   * ERROR: NONE.
   *
   **/
  void postOrder(Node* n);

  /**
  * getBranch
  * Split the source equation up in segments of parenthesized text. Separated by an aperand.
  *
  * IN: (char*) A string to find the operator, operand and operator.
  * RETURN: NONE.
  * ERROR: Error.
  *
  **/
  void getBranch(Node* node, char* str);

  /**
   * calculate
   * Calculate the expression stored within the tree.
   *
   * IN: (Node*) the root node.
   * RETURN: (Double) the sum.
   * ERROR: NONE.
   *
   **/
   double calculate(Node* n);

   Node* getVar(Node* n, int var);

   void printNode (Node* n);

   void print_t(Node *tree);

   int _print_t(Node *tree, int is_left, int offset, int depth, char s[20][555]);

#endif
