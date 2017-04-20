#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Tree.h"

/**
 * initNode
 * Creates new node on the heap and returns the pointer of node.
 *
 * IN: NONE.
 * RETURN: (Node*) The node element.
 * ERROR: If malloc fails Node* is null.
 *
 **/
Node* initNode() {
    Node* ptr = (Node*)malloc(sizeof(Node));
    ptr->operator = '\0';
    ptr->operand = 0.0;
    ptr->variable = 0;
    ptr->left = NULL;
    ptr->right = NULL;
    return ptr;
}

/**
 * insertLeft
 * Inserts a node on the left of a parent node.
 *
 * IN: (Node*) Parent.
 * RETURN: NONE.
 * ERROR: NONE.
 *
 **/
 void insertLeft(Node* parent) {
     parent->left = initNode();
 }

/**
* insertRight
* Inserts a node on the right of a parent node.
*
* IN: (Node*) Parent.
* RETURN: NONE.
* ERROR: NONE.
*
**/
void insertRight(Node* parent) {
  parent->right = initNode();
}

void printTree(Node* tree) {
  if(tree == NULL) return;
  printf("------------------------\n\n");
  printf("\tNode: %p\n", tree);
  printf("Left: %p", tree->left);
  printf("\t\tRight: %p", tree->right);
  printf("\n\n------------------------\n");
  printTree(tree->left);
  printTree(tree->right);
}

/**
* convertToInt
* Convert string to int for cars values.
*
* IN: (char*) string with numbers.
* RETURN: (int) integer value.
* ERROR: NONE.
*
**/
int convertToInt(char* chars) {
  int sum = 0;
  for (int i = 0; i < strlen(chars); i++) {
      if (*(chars+i) > 47 && *(chars+i) < 58) {
          sum = sum *10;
          sum += *(chars+i) - '0';
      }
  }
  return sum;
}

/**
* stringify
* Return the pointer to a string on the heap.
*
* IN: (char*) The string to malloc.
* RETURN: (char*) The string malloc'd.
* ERROR: NONE.
*
**/
char* stringify(char* str) {
  char* string = (char*)malloc(sizeof(char) * strlen(str) + 1);
  strcpy(string,str);
  return string;
}

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
char* substring(char* str, int start, int end) {
  if (end > strlen(str))
      return NULL;
  char* substr = malloc(sizeof(char) * end - start + 2);
  int count = 0;
  for (int i = start; i < end + 1; i++ ){
      *(substr+count) = *(str+i);
      count++;
  }
  *(substr+count) = '\0';
  return substr;
}


/**
* getBranch
* Split the source equation up in segments of parenthesized text. Separated by an aperand.
*
* IN: (char*) A string to find the operator, operand and operator.
* RETURN: NONE.
* ERROR: Error.
*
**/
void getBranch(Node* node, char* str) {
   int isOpen = 0, startIndex= 1, endIndex = 0, foundOperator = 0;
   // Assume fully parenthesized and skip first and last
   for (int i = 1; i < strlen(str) - 1; i++) {
       if (*(str+i) == '(')
           isOpen++;
       else if (*(str+i) == ')') isOpen--;
       else if (isOpen == 0) {    //   It is an operator add it as operator
          int run = 1, start = i, c = i;
          double operatorDbl = 0.0;
          char* sub;

           switch (*(str+i)) {
               case '*':
               case '/':
               case '+':
               case '-':  //  Found an operator add it to the operator in the data structure.
                  node->operator = *(str+i);
                  foundOperator = 1;
                  break;
               case 'x':      //  Found a variable
                   if (foundOperator) {
                      insertRight(node);
                      node->right->variable =  *(str+i+1) - '0';
                   } else {
                      insertLeft(node);
                      node->left->variable = *(str+i+1) - '0';
                   }
                   i++;
                   foundOperator = 0;
                  break;
               default:   //  Get a double with some gross code
                   while(run) {
                       switch (*(str+c)) {
                           case '/':
                           case '*':
                           case '+':
                           case '-':
                           case ')':
                               run = 0;
                               i = c - 1;
                               sub = substring(str, start,c);
                               operatorDbl += (double)convertToInt(sub)/pow(10,c-start);
                               free(sub);
                               break;
                           case '.':
                               //  Handle the decimals
                               sub = substring(str, start,c);
                               operatorDbl = (double)convertToInt(sub);
                               free(sub);
                               start = c + 1;
                               break;
                       }
                       c++;
                   }
                   if (foundOperator) {
                      insertRight(node);
                      node->right->operand = operatorDbl;
                  } else {
                      insertLeft(node);
                      node->left->operand = operatorDbl;
                  }
                   foundOperator = 0;
                  break;
           }
       }
       if (isOpen == 0 && *(str+i) == '('){
           startIndex = i;
       } else if(isOpen == 0 && *(str+i) == ')') {
           endIndex = i;
           if (foundOperator) {
              node->right = initNode();
              getBranch(node->right, substring(str,startIndex,endIndex));
          } else {
              node->left = initNode();
              getBranch(node->left, substring(str,startIndex,endIndex));
          }
       }
   }
}


void printNode(Node* n) {
  if (n == NULL) return;
  if (n->operator != '\0')
      printf("%c", n->operator);
  else if (n->variable != 0) {
      printf("x%d", n->variable);
  } else
      printf("%.2f", n->operand);
}

/**
 * inOrder
 * Traversal of the tree in order.
 *
 * IN: (Node*) the root of the tree to print.
 * RETURN: NONE.
 * ERROR: NONE.
 *
 **/
void inOrder(Node* n) {
  if (n == NULL) return;
  if(n->operator != '\0') {
      printf("(");
      inOrder(n->left);
      printNode(n);
      inOrder(n->right);
      printf(")");
  } else {
      printNode(n);
  }
}

/**
 * calculate
 * Calculate the tree.
 *
 * IN: (Type) Description.
 * RETURN: (Type) Description.
 * ERROR: Error.
 *
 **/
double calculate(Node* n) {
    double answer;
    if(n->operator != '\0') {
        double left = calculate(n->left);
        double right = calculate (n->right);
        switch (n->operator) {
            case '+':
                answer = left + right;
                break;
            case '-':
                answer = left - right;
                break;
            case '/':
                answer = left / right;
                break;
            case '*':
                answer = left * right;
                break;
        }
    } else {
        answer = n->operand;
    }
    return answer;
}

Node* getVar(Node* n, int var) {
    Node *l,*r;
    if (n == NULL) return NULL;
    if(n->variable == var) return n;
    l = getVar(n->left,var);
    r = getVar(n->right,var);
    if (l != NULL) return l;
    if (r != NULL) return r;
    return NULL;
}

/**
 * preOrder
 * Traversal of the tree pre order.
 *
 * IN: (Node*) the root of the tree to print.
 * RETURN: NONE.
 * ERROR: NONE.
 *
 **/
void preOrder(Node* n) {
  if (n == NULL) return;
  printf(" ");
  printNode(n);
  preOrder(n->left);
  preOrder(n->right);
}

/**
 * postOrder
 * Traversal of the tree post order.
 *
 * IN: (Node*) the root of the tree to print.
 * RETURN: NONE.
 * ERROR: NONE.
 *
 **/
void postOrder(Node* n) {
  if (n == NULL) return;
  postOrder(n->left);
  postOrder(n->right);
  printf(" ");
  printNode(n);
}




/*

print_t     Function used to create the tree drawing
http://stackoverflow.com/a/13755911

*/


int _print_t(Node *tree, int is_left, int offset, int depth, char s[20][555])
{
    char b[20];
    int width = 6;

    if (!tree) return 0;

    if (tree->operator !='\0') {
        sprintf(b, "  %c   ", tree->operator);
    } else if (tree->variable != 0) {
        sprintf(b, "  x%d ", tree->variable);
    } else {
        sprintf(b, "%.2lf   ", tree->operand);
    }


    int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }

    return left + width + right;
}

void print_t(Node *tree)
{
    char s[20][555];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}
