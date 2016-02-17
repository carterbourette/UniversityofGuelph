/***
 Scrambled Words - Assignment #2
 CIS*1500

 Carter Bourette
 November 3, 2015
 0916638
 ***/

#ifndef __CBOURETTE_WORDSCRAM__
#define __CBOURETTE_WORDSCRAM__

/**
 * getFilename
 * Prompt user for filename
 *
 * IN: Pass in char[] array.
 * RETURN: NONE.
 * POST: Print prompt.
 *
 **/
 void getFilename(char *filename);

 /**
  * getRand
  * Returns random number between 0 - between (int)
  *
  * IN: (INT) range.
  * RETURN: (int) random number
  * POST: NONE
  *
  **/
 int  getRand(int between);

 /**
  * printCharArray
  * Prints char array
  *
  * IN: (CHAR[]) Array + (INT) size of array
  * RETURN: VOID
  * POST: Prints contents of array.
  *
  **/
 void printCharArray(char array[], int size);

 /**
  * processText
  * Reads file calls scramble for each word
  *
  * IN: Array filename (char[])
  * RETURN: VOID
  * POST: Print scrambled paragraph via scramble()
  *
  **/
 void processText(char filename[]);

 /**
  * scramble
  * Scramble letters in a word
  *
  * IN: Word (char[]) + size of word (int).
  * RETURN: NONE
  * POST: Prints scrambled word.
  *
  **/
 void scramble(char word[], int size);



#endif
