/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 *
 * Assignment 1
 * Data Structures
 * September 26, 2016
 **/

#include <math.h>

/*

     Let x be a positive real. To calculate the square root of x by Newton’s method, so that the square of the solution differs from x
     is within an accuracy of ǫ, we start with an initial approximation a = x/2. If |a ∗ a − x| ≤ ǫ ,
     we stop with the result a. Otherwise we replace a with the next approximation, defined by (a+x/a)/2.
     Then, we test the result again. In general, we keep on computing and testing
     successive approximations until we find one close enough to stop.

*/

/*
    newtonApprox
    Iterative solution to Newton's approximation.
    IN: (double) the number to find the sq root of. (epsilon) small number
    OUT: (double) the sq root of input.
    POST: NONE.
*/
double newtonApprox(double x, double ep) {
    //  Let's do the first approximation
    double a = x / 2;

    //  Check against accurracy of epsilon
    while (fabs((a*a)-x) >= ep) {
        a = (a+(x/a))/2;
    }
    return a;
}

/*
    recurse
    Recursive solution to Newton's approximation.
    IN: (double) the number to find the sq root of. (epsilon) small number
    OUT: (double) the sq root of input.
    POST: NONE.
*/
double recurse(double x, double a, double ep) {
    if (fabs((a*a)-x) > ep) {
        a = (a+(x/a))/2;
        a = recurse(x, a, ep);
    }
    return a;
}
