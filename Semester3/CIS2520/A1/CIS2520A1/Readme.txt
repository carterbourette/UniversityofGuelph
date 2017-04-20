——————————————————————————————————————————

Data Structures

Assignment #1
CIS*2520

Carter Bourette
Sept 26, 2016
0916638

——————————————————————————————————————————

Description:

This program is a compilation of three problems:
(1) A program to perform all permutations of the
word carbon. (2) A program demonstrating Ackermann's
function. (3) A program demonstrating the difference
in runtime between iterative and recursive code
through the implementation of Newton's Approximation.



Compilation:

This program can be compiled without error using:

    "gcc -std=c99 -Wall main.c newton.c ackermann.c carbon.c -Iinclude -o ./A1"

The program can be compiled by typing "make".



Usage:

The program can be run by executing (from the
A1 folder):

    "./A1"

Or by running the Makefile command
"make run" from the A1 folder.

    "make run"



Sample Output:
    Section 1: carbon.c
        Enter a number: 1

        carbon
        ..
        ..
        ..

        All permutations of carbon are printed ( n! ).

    Section 2: ackermann.c
        Enter a number: 2

        The result of ack(0,0) is: 1
        The result of ack(0,1) is: 2
        The result of ack(0,2) is: 3
        The result of ack(0,3) is: 4
        The result of ack(1,0) is: 2
        and so on...

    Section 3: newton.c

        Enter an epsilon (a tiny number like 0.0001): 0.001
        Enter the number you would like to find the square root of: 25
        The number calculated by Newton's Approximation recursive implementation is: 5.0000
        The number calculated by Newton's Approximation iterative implementation is: 5.0000



Observations:
I found that the recursive function was slower in execution time than the
iterative function. The results found below use the ftime library for
benchmark times.

Recursive function finished successfully taking 24.6770s.
Iterative function finished successfully taking 21.5700s.



References:

ftime function was found at http://www.phanderson.com/C/ftime.html.
