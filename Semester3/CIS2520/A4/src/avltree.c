/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 *
 * Assignment 4
 * Nov 28, 2016
 * Data Structures
 * Create an avl tree to import a given file.
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * AVL Tree Node
 **/
typedef struct struct_node{
    char* key;
    int occurances;
    struct struct_node *left;
    struct struct_node *right;
} Node;

/**
 * getHeight
 * Calculate the height of a tree.
 *
 * IN: (Node*) Tree root.
 * RETURN: (int) height.
 * ERROR: NONE.
 *
 **/
 int getHeight(Node* root) {
     if (root == NULL) return 0;
     int l = 0,r = 0;
     if (root->left) l = getHeight(root->left);
     if(root->right) r = getHeight(root->right);
     if (root->left == NULL && root->right == NULL) return 0;
     return l > r ? l + 1 : r + 1;
 }

/**
 * balanceFactor
 * Calculate the balance factor of a given node.
 *
 * IN: (Node*) the node to get the balance factor of.
 * RETURN: (int) Balance factor.
 * ERROR: NONE.
 *
 **/
 int balanceFactor(Node* node) {
     if (node == NULL) return 0;
     int bf = 0;
     if (node->left) bf = getHeight(node->left);    //  Subtract the right height from the left to get balanceFactor
     if (node->right) bf -= getHeight(node->right);
     return bf;
 }

 /**
  * rotateLeftRight
  * Perform a left right rotation.
  *
  * IN: (Node*) the node to rotate.
  * RETURN: (Node*) the node.
  * ERROR: NONE.
  *
  **/
  Node* rotateLeftRight(Node* node) {
      Node *a = node, *b = a->left, *c = b->right;

      a->left = c->right;
      b->right = c->left;
      c->left = b;
      c->right = a;

      return c;
  }

  /**
   * rotateRightLeft
   * Perform a right left rotation.
   *
   * IN: (Node*) the node to rotate.
   * RETURN: (Node*) the node.
   * ERROR: NONE.
   *
   **/
  Node* rotateRightLeft(Node* node) {
     Node *a = node, *b = a->right, *c = b->left;

     a->right = c->left;
     b->left = c->right;
     c->right = b;
     c->left = a;

 	return c;
  }

  /**
   * rotateLeftLeft
   * Perform a left left rotation.
   *
   * IN: (Node*) the node to rotate.
   * RETURN: (Node*) the node.
   * ERROR: NONE.
   *
   **/
  Node* rotateLeftLeft(Node* node) {
      Node *a = node, *b = a->left;

      a->left = b->right;
      b->right = a;

      return b;
  }

   /**
    * rotateRightRight
    * Perform a right right rotation.
    *
    * IN: (Node*) the node to rotate.
    * RETURN: (Node*) the node.
    * ERROR: NONE.
    *
    **/
   Node* rotateRightRight(Node* node) {
       Node *a = node, *b = a->right;

       a->right = b->left;
       b->left = a;

       return b;
   }

 /**
  * balanceTree
  * Given a node, do rotations to balance the tree.
  *
  * IN: (Node*) the node to balance.
  * RETURN: (Node*) the balanced node.
  * ERROR: NONE.
  *
  **/
  Node* balanceNode(Node* node) {
      if (node == NULL) return NULL;

      // Balance the nodes children
      if (node->left != NULL) node->left = balanceNode(node->left);
      if (node->right!= NULL) node->right = balanceNode(node->right);

      // Get the balance factor of the current node
      int bf = balanceFactor(node);

      // If the balance factor or the current node is <> +- 2 we need to rebalance
      if ( bf >= 2 ) {    //  Left heavy
 		if(balanceFactor(node->left) <= -1)  node = rotateLeftRight(node);
 		else node = rotateLeftLeft(node);
 	} else if( bf <= -2 ) {    //  Right heavy
 		if (balanceFactor(node->right) >= 1) node = rotateRightLeft(node);
 		else node = rotateRightRight(node);
 	}
     return node;
  }

/**
 * getSize
 * Return the size of the avl tree.
 *
 * IN: (Node*) the root.
 * RETURN: (int) size of tree.
 * ERROR: NONE.
 *
 **/
 int getSize(Node* root) {
     if (root == NULL) return 0;
     int l = getSize(root->left);
     int r = getSize(root->right);
     return r + l + 1;
 }

/**
 * createNode
 * Malloc for a new node.
 *
 * IN: (char*) key.
 * RETURN: (Type) Description.
 * ERROR: Error.
 *
 **/
 Node* createNode(char* key) {
     Node* ptr = (Node*)malloc(sizeof(Node));
     ptr->key = (char*)malloc(sizeof(char) * strlen(key) + 1);
     strcpy(ptr->key, key);
     ptr->occurances = 1;
     ptr->left = NULL;
     ptr->right = NULL;
     return ptr;
 }

 /**
  * insertNode
  * Insert a node into the avl tree following phonetic order.
  *
  * IN: (Node*) the root node, (char*) key.
  * RETURN: (Node*) the inserted node.
  * ERROR: Return NULL.
  * NOTE: Caller must free struct and contained string.
  *
  **/
Node* insertNode(Node* node, char* key) {
     if (node == NULL) {
         node = createNode(key);
         //printf("key: %s, frequency: %d\n",node->key,node->occurances);
     } else if (strcmp(key,node->key) == 0) {
         node->occurances += 1;
         //printf("key: %s, frequency: %d\n",node->key,node->occurances);
     } else if (strcmp(key,node->key) < 0) {
         node->left = insertNode(node->left, key);
     } else if (strcmp(key,node->key) > 0) {
         node->right = insertNode(node->right, key);
     }
      return node;
  }

/**
* search
* Search for a given key in the tree.
*
* IN: (Node*) the root node, (char*) the key.
* RETURN: (Node*) the node.
* ERROR: Return NULL if not found.
*
**/
Node* search(Node* root, char* key) {
    if (root == NULL) return NULL;
    Node* n = NULL;
    if (strcmp(root->key,key) == 0) return root;
    n = search(root->left,key);
    if (n == NULL) n = search(root->right,key);
    return n;
}

 /**
  * deleteNode
  * Merc a node and free the memory.
  *
  * IN: (Node*) The node to delete.
  * RETURN: NONE.
  * ERROR: NONE.
  *
  **/
void deleteNode(Node* node) {
      free(node->key);
      free(node);
  }

  /**
  * removeKey
  * Remove a given key from the tree.
  *
  * IN: (Node*) the root node, (Node*) the node to remove from.
  * RETURN: (int) status of delete. (1 on success)
  * ERROR: NONE.
  *
  **/
 int removeKey(Node* root, char* key) {
       if (root == NULL) return 0;
       Node *temp = root, *prev = NULL, *node = NULL, *old = NULL;
       int leftSet = 0;

       while(temp) {
           if (strcmp(temp->key, key) == 0) {
               if (temp->occurances > 1) {
                   temp->occurances -= 1;
                   return 1;
               } else { //  Otherwise we're gonna need to delete
                   if (temp->left == NULL & temp->right == NULL) {  //   Merc a lone node
                       if (prev == NULL) {
                           deleteNode(temp);
                           temp = NULL;
                       } else {
                           deleteNode(temp);
                           temp = NULL;
                           if (leftSet == 1) prev->left = NULL;
                           else prev->right = NULL;
                       }
                       return 1;
                   } else {   //  Has kids
                       if (temp->right != NULL && temp->left != NULL) { //  At last two kiddies
                           //   Traverse to the right of this node and leftmost child
                           node = temp;
                           int inLeft = 0;
                           old = node;
                           node = node->right;
                           while (node->left != NULL) {
                               old = node;
                               node = node->left;
                               inLeft = 1;
                           }
                           //   Swap the left most child with the node we are deleting
                           temp->occurances = node->occurances;
                           temp->key = (char*)realloc(temp->key, sizeof(char) * strlen(node->key) + 1);
                           strcpy(temp->key, node->key);
                           //   Delete the moved node
                           deleteNode(node);
                           //   Remove pointers to that node
                           if (inLeft == 1)  old->left = NULL;
                           else old->right = NULL;
                       } else if (temp->right == NULL && temp->left != NULL) {
                           //   Swap child with parent and delete child
                           temp->occurances = temp->left->occurances;
                           temp->key = (char*)realloc(temp->key, sizeof(char) * strlen(temp->left->key) + 1);
                           strcpy(temp->key, temp->left->key);
                           //   Delete temp left
                           deleteNode(temp->left);
                           //   Remove pointers to that node
                           temp->left = NULL;
                       } else if (temp->right != NULL && temp->left == NULL) {
                           //   Swap child with parent and delete child
                           temp->occurances = temp->right->occurances;
                           temp->key = (char*)realloc(temp->key, sizeof(char) * strlen(temp->right->key) + 1);
                           strcpy(temp->key, temp->right->key);
                           //   Delete temp left
                           deleteNode(temp->right);
                           //   Remove pointers to that node
                           temp->right = NULL;
                       }
                       return 1;
                   }
               }
           } else if(strcmp(temp->key,key) > 0) {
               prev = temp;
               temp = temp->left;
               leftSet = 1;
           } else if(strcmp(temp->key,key) < 0) {
               prev = temp;
               temp = temp->right;
               leftSet = 0;
           }
       }
       return 0;
}

/**
* getAVLSpecs
* Print the stats of the avl tree.
*
* IN: (Node*) root node.
* RETURN: NONE.
* ERROR: NONE.
*
**/
void getAVLSpecs(Node* root) {
    int height = getHeight(root);
    int size = getSize(root);
    printf("height: %d, size: %d\n",height,size);
}

/**
 * findAllAbove
 * Print the stats of all nodes above given frequency.
 *
 * IN: (Node*) the root node, (int) frequency.
 * RETURN: NONE.
 * ERROR: NONE.
 *
 **/
 void findAllAbove(Node* node, int frequency) {
     if (node == NULL) return;
     if (node->occurances > frequency)
         printf("key: %s,\tfrequency: %d\n",node->key,node->occurances);
     findAllAbove(node->left, frequency);
     findAllAbove(node->right, frequency);
 }

/**
* parseFromFile
* Parse a file inserting each key.
*
* IN: (Node*) root node, (char*) filename.
* RETURN: NONE.
* ERROR: NONE.
*
**/
Node* parseFromFile(Node* root, char* filename) {
  FILE* fp = fopen(filename, "r");
  char line[500], *token;
  //Node* temp = NULL;
  if (fp == NULL) printf("Unable to read from file: %s\n", filename);
  else{
      while (fgets(line, 500, fp)) {
          // For every non-null line insert each key on the line
          if(strcmp(line,"") != 0 && strcmp(line," ") != 0 && strcmp(line,"\n") != 0) {
              token = strtok(line," \n\0");
               while( token != NULL ) {
                   root = insertNode(root, token);

                   root = balanceNode(root);
                   token = strtok(NULL," \n\0");
               }
          }
      }
      fclose(fp);
  }
  return root;
}

/**
 * checkKey
 * Hack solution to deleting the root.
 *
 * IN: (Node*) the root node.
 * RETURN: (Node*) the root node.
 * ERROR: NONE.
 *
 **/
 Node* checkKey(Node* node) {
     if (strcmp(node->key, "") == 0) return NULL;
     return node;
 }

void printAll(Node* node) {
    if (node == NULL) return;
    printf("key: %s, frequency: %d",node->key,node->occurances);
    printf("\t\t%p\tl:%p\tr:%p\n",node,node->left,node->right);
    printAll(node->left);
    printAll(node->right);
}

int main(int argc, char* argv[]) {
    int running = 1, choice = 0, frequency = 0;
    char input[50];
    Node *node = NULL, *root = NULL;
    //  Print a welcome banner
    printf("+-------------------------+\n");
    printf("|   Welcome to AVL        |\n");
    printf("|   Carter Bourette       |\n");
    printf("|   0916638    A4         |\n");
    printf("+-------------------------+\n\n\n");

    while (running) {
        //  Print the meun
        printf("\n");
        printf("1. Initialization\n");
        printf("2. Find\n");
        printf("3. Insert\n");
        printf("4. Remove\n");
        printf("5. Check height and size\n");
        printf("6. Find all (above given frequency)\n");
        printf("7. Exit\n");
        printf("avl/> ");
        scanf("%d",&choice);
        //  Delegate
        switch(choice) {
            case 1: //  Init
                printf("filename: ");
                scanf("%s", input);
                printf("Please wait...\n");
                root = parseFromFile(root,input);
                break;
            case 2: //  Find
                printf("find key: ");
                scanf("%s", input);
                node = search(root, input);
                if (node == NULL)
                    printf("no_such_key\n");
                else
                    printf("key: %s, frequency: %d\n",node->key,node->occurances);
                break;
            case 3: //  Insert
                printf("insert key: ");
                scanf("%s", input);
                root = insertNode(root, input);
                root = balanceNode(root);
                break;
            case 4: //  Remove
                printf("remove key: ");
                scanf("%s", input);
                if (removeKey(root, input)) {
                    root = checkKey(root);
                    balanceNode(node);
                    node = search(root, input);
                    if (node)   printf("key: %s, frequency: %d\n",node->key,node->occurances);
                    else printf("Node deleted.\n");
                } else printf("no_such_key\n");
                break;
            case 5: //  Check height and size
                getAVLSpecs(root);
                break;
            case 6: //  Find all above given
                printf("frequency: ");
                scanf("%d", &frequency);
                findAllAbove(root, frequency);
                break;
            case 7: //  Quit
                printf("Have a good day!\n");
                running = 0;
                break;
            case 8:
                printAll(root);
                printf("Balance Factor of root node: %d\n", balanceFactor(root));
                //balanceTree(root);
        }
    }
    return 0;
}
