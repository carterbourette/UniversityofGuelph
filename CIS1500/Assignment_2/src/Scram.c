#include <stdio.h>
#include <stdlib.h>
#include "Scram.h"

void getFilename(char *filename)
{
    printf("Enter the filename you want to read from: ");
    scanf(" %s",filename);
}

int getRand(int between)
{
    if (between > 0)
        return rand() % between;
    else
        return 0;
}

void printCharArray(char array[], int size)
{
    int i;

    for (i = 0; i < size; i++) {
        printf("%c",array[i]);
    }
}

void processText(char filename[])
{
    /***
     File reading from TutorialsPoint
     "C File I/O." www.tutorialspoint.com. Accessed October 2015.
     ***/

    FILE *fp;
    int charater, count, reading, newLine;
    char word[50];

    //  Initalize variables
    count = 0;
    reading = 1;

    //  Open file for reading
    fp = fopen(filename,"r");
    if (fp == NULL)
    {
        printf("Problem reading from file...Quit\n");
    }
    else
    {
        printf("Reading from file...\n");
        printf("Scrambled the contents of the file as follows:\n\n");

        while (reading)
        {
            //  Go through file char by char
            charater = fgetc(fp);
            newLine = 0;

            if ( feof(fp) )
            {
                scramble(word,count);
                reading = 0;
            }
            else
            {
                //  Check for punctuation, call scramble reset count and word
                if (charater == 10 ||  charater == 13 || charater == 32 || charater == 33  || charater == 44 || charater == 45 || charater == 46 || charater == 63 )
                {
                    //  If it's a newline or break, make it a space, we'll print the new line after
                    if ( charater == 10 || charater == 13 )
                    {
                        charater = 32;
                        newLine = 1;
                    }
                    //  We have a word, scramble it, then print either punctuation or space
                    scramble(word,count);
                    printf("%c",charater);
                    //  If there was a line break, now print the new line
                    if (newLine)
                        printf("\n");
                    count = 0;
                }
                else
                {
                    //  Still reading word add the letter character
                    word[count] = charater;
                    count++;
                }
            }
        }
        //  We opened the file, we better close the file
        fclose(fp);
    }
}

void scramble(char word[], int size)
{
    int i, k, j, rand, numBetween;
    char *point[size];
    char newWord[size];

    //  If the word is 3 or less characters we can't scramble it
    if (size > 3)
    {
        //  Gives us the number of letters we are scrambling
        numBetween = size - 2;

        //   Set the first and last letter of the word
        newWord[0] = word[0];
        newWord[size -1] = word[size -1];

        //  Array of location of letters in word[]
        for (i = 0; i < numBetween; i++)
        {
            point[i] = &word[i+1];
        }
        //  For each letter we need to scramble, grab a random value from the array of pointers
        for (k = 1; k < size - 1; k++)
        {
            rand = getRand(numBetween-1);
            newWord[k] = *point[rand];
            //   For every pointer above selected item (rand->maxSize) set selected pointer to next val
            for (j = rand; j < numBetween; j++)
            {
                point[j] = point[j + 1];
            }
            numBetween--;
        }
        //  Print the new word
        printCharArray(newWord,size);
    }
    else
    {
        //  We couldn't scramble the word (too short) print the original word
        printCharArray(word,size);
    }
}
