#ifndef __CBOURETTE_NEWTON__
#define __CBOURETTE_NEWTON__

/*
    newtonApprox
    Iterative solution to Newton's approximation.
    IN: (double) the number to find the sq root of.
    OUT: (double) the sq root of input.
    POST: NONE.
*/
double newtonApprox(double x, double ep);

/*
    recurse
    Recursive solution to Newton's approximation.
    IN: (double) the number to find the sq root of.
    OUT: (double) the sq root of input.
    POST: NONE.
*/
double recurse(double x, double a, double ep);

#endif
