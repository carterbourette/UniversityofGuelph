/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 *
 * Assignment 3
 * Nov 7, 2016
 * Data Structures
 * Use a tree struture to parse an arithmetic expression.
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"

int main(int argc, char* argv[]) {
    if (argc != 2) { printf("Please supply an equation.\n"); return 1;}
    Node* root = initNode();
    Node* myNode;

    getBranch(root, argv[1]);

    //  Some test values
    //getBranch(root, "(((x1+5.12)*(x2-7.68))/x3)");
    //getBranch(root, "((2.00+2.00)/3.00)");
    //getBranch(root, "(((2.0+(2.0 + 1.0))+(2.0+2.0))/3.0)");

    //  Command loop prompt the user for some stuff
    char choice ='\0';
    int var;
    double varVal;
    while (choice != '7') {
        printf("1. Display\n2. Preorder\n3. Inorder\n4. Postorder\n5. Update\n6. Calculate\n7. Exit\n\n");
        printf("Please enter a numeric choice: ");
        scanf("%c",&choice);
        getchar();
        system("clear");

        switch(choice) {
            case '1':   //  Display
                print_t(root);
                break;
            case '2':   //  Pre order
                printf("2. Preorder : \n");
                preOrder(root); printf("\n");
                break;
            case '3':   //  Inorder
                printf("3. Inorder : \n");
                inOrder(root);  printf("\n");
                break;
            case '4':   //  Post order
                printf("4. Postorder : \n");
                postOrder(root); printf("\n");
                break;
            case '5':   //  Update
                //  Get the var and value
                printf("Enter the variable you would like to change and corresponding value: i.e x3, 2.0\n");
                printf("Enter the variable and corresponding value: x");
                scanf("%d, %lf",&var, &varVal); getchar();

                myNode = getVar(root,3);
                if (myNode == NULL) printf("Unable to change variable.\n");
                else { myNode->operand = varVal; printNode(myNode); }
                break;
            case '6':   //  Calculate
                printf("The answer is: %.3f\n",calculate(root));
                break;
            case '7':   //  Quit
                printf("Thanks for checking out my tree!\n\n");
                break;
            default:
                printf("Invalid input! Please enter a valid\n");
                break;
        }
        printf("\n\n\n\n");
    }

    return 0;
}
