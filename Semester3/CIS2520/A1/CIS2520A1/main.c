/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 *
 * Assignment 1
 * Data Structures
 * September 26, 2016
 **/

#include <stdio.h>
#include <sys/timeb.h>

#include "carbon.h"     //  Include the carbon file
#include "ackermann.h"  //  Include ackermanns function
#include "newton.h"     //  Include newtons approximation

int main() {
    int num = 0;

    //  Let's pop open a menu until the user quits
    while (num != 4) {
        printf("Enter (1) to run the carbon function.\n");
        printf("Enter (2) to run ackermanns function.\n");
        printf("Enter (3) to run Newton's approximation.\n");
        printf("Enter (4) to quit.\n\n");
        printf("Enter a number: ");
        scanf("%d", &num);

        //  Delegate tasks to the different .c files
        if (num == 1) {
            char* str = stringify("carbon");
            permutate(str, 0);
        } else if (num == 2) {
            int choice = 0;
            printf("Enter (1) to test Ackermann function with vals n = (0,4) and m = (0,3).\n");
            printf("Enter (2) to enter vals m and n.\n");
            scanf("%d",&choice);
            
            if(choice == 1) {
                //  Print out a sequence of results
                for (int i = 0; i < 4; i++) {
                    for (int k = 0; k < 4; k++) {
                        printf("The result of ack(%d,%d) is: %d\n", i,k, ackermann(i,k));
                    }
                }
                //  Make a big call
                printf("Please wait while I calculate ack(4,1).\n");
                printf("The result of ack(4,1) is: %d\n", ackermann(4,1));
            } else {
                int m, n;
                printf("n: ");
                scanf("%d",&n);
                printf("m: ");
                scanf("%d",&m);
                if (n >= 0 && n <= 5 && m >= 0 && m <= 5) {
                    printf("The result of ack(%d,%d) is: %d\n", n,m, ackermann(n,m));
                }
            }
        } else if (num == 3) {
            //  Speed test or just an input test
            int choice = 0;
            printf("Enter (1) to test Newton's function.\n");
            printf("Enter (2) to run a speed test of Newton's function.\n");
            scanf("%d",&choice);

            if(choice == 1) {
                //  Gather the information
                double x = 0, e = 0;
                printf("Enter an epsilon (a tiny number like 0.0001): ");
                scanf("%lf", &e);
                printf("Enter the number you would like to find the square root of: ");
                scanf("%lf", &x);
                if (x < 0) {
                    printf("Invalid Input!");
                } else {
                    printf("The number calculated by Newton's Approximation recursive implementation is: %.4lf\n", recurse(x, x/2,e));
                    printf("The number calculated by Newton's Approximation iterative implementation is: %.4lf\n", newtonApprox(x,e));
                    printf("Please note the numbers have been rounded to 4 decimal places.\n");
                }
            } else {
                struct timeb start, curr;
                double e = 0.00001, timer;

                printf("We are going to run each function for every number between 1-99999999 e = 0.00001\n");
                printf("Begin...\n");
                //  Start timer
                ftime(&start);
                for(int i = 1; i < 99999999; i++)
                    recurse(i, (double)i/2, e);

                //  End timer
                ftime(&curr);
                //  Calculate timer
                timer = ((double) (1000.0 * (curr.time - start.time) + (curr.millitm - start.millitm)))/1000;
                printf("Recursive function finished successfully taking %.4lfs.\n",timer);

                //  Start timer
                ftime(&start);

                for(int k = 1; k < 99999999; k++)
                    newtonApprox(k, e);

                //  End timer
                ftime(&curr);
                //  Calculate timer
                timer = ((double) (1000.0 * (curr.time - start.time) + (curr.millitm - start.millitm)))/1000;

                printf("Iterative function finished successfully taking %.4lfs.\n",timer);
            }
        }
        printf("\n\n\n");
    }
    //  Send a feel good message to an awesome TA :)
    printf("Have an awesome day!!\n\n");

    return 0;
}
