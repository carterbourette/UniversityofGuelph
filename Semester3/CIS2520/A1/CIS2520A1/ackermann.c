/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 *
 * Assignment 1
 * Data Structures
 * September 26, 2016
 **/

/*
    ackermann
    Recursive application of Ackermanns function.
    IN: (int) m, (int) n
    OUT: (int) result
    POST: NONE.
*/
int ackermann(int m, int n) {
    /*
        A(0,n) = n+1 for n ≥ 0
        A(m,0) = A(m−1,1) for m > 0
        A(m,n) = A(m−1,A(m,n−1)) for m ,n > 0
    */
    if (n >= 0 && m == 0 )
        return n + 1;
    else if (n == 0 && m > 0)
        return ackermann(m - 1, 1);
    else
        return ackermann(m - 1, ackermann(m, n - 1));
}
