/**
 * Carter Bourette (Feb 2017)
 * cbourette@gmail.com
 *
 * A string library containing common string functions.
 * Edit: NONE.
 **/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stringy.h"

 /**
  * newSplit
  * Return a structure of type split, splits on a delimeter.
  *
  * IN: (char*) string, (char*) delimeter.
  * RETURN: (Split*) the structure containing substrings.
  * NOTE: Caller must free.
  *
  **/
Split* newSplit(char* string, char* delim) {
     Split* s = (Split*)malloc(sizeof(Split));
     s->substring = (char**)malloc(sizeof(char*) * 250);
     s->rows = 0;
     s->last = 0;

     int i = 0, k = 0, cols = 0, found = 0, stringLength = strlen(string);
     char temp[999];

     /* Crawl through string character by character */
     for (i = 0; i < stringLength; i++) {
         /* Check to see if the current character is a delimeter */
         for (k = 0; k < strlen(delim); k++) {
             if (string[i] == delim[k]) { found = 1; break; }
         }

         /* delim or last character add it to the substring array */
         if (found || (i == stringLength - 1 && !found)) {
             if (i == stringLength - 1 && !found) {
                 temp[cols] = string[i];
                 cols = cols + 1;
             }
             temp[cols] = '\0';
             if (strcmp(temp,"") != 0) {
                 s->substring[s->rows] = (char*)malloc(sizeof(char) * cols + 1);
                 strcpy(s->substring[s->rows],temp);
                 s->rows = s->rows + 1;
             }
             cols = 0;
         } else {
             temp[cols] = string[i];
             cols = cols + 1;
         } found = 0;
     }
     return s;
 }

/**
 * newSplitIgnoreSubDelimeters
 * Return a structure of type split, splits on a delimeter.
 *
 * IN: (char*) string, (char*) delimeter, (char*) ignore.
 * RETURN: (Split*) the structure containing substrings.
 * NOTE: Caller must free.
 *
 **/
Split* newSplitIgnoreSubDelimeters(char* string, char* delim, char* ignore) {
      Split* s = (Split*)malloc(sizeof(Split));
      s->substring = (char**)malloc(sizeof(char*) * 150);
      s->rows = 0;
      s->last = 0;

      int i = 0, k = 0, cols = 0, found = 0, inIgnore = 0, stringLength = strlen(string);
      char temp[999];

      /* name="add" */

      /* Crawl through string character by character */
      for (i = 0; i < stringLength; i++) {
          /* Check to see if the current character is a delimeter */
          for (k = 0; k < strlen(delim); k++) {
              if (string[i] == delim[k]) { found = 1; break; }
          }

          if (!inIgnore) {
              /* Check to see if the current character is an ignored character */
              for (k = 0; k < strlen(ignore); k++) { if (string[i] == ignore[k]) inIgnore = 1; }
          } else {
              /* Check to see if ignored character if so we no longer ignore */
              for (k = 0; k < strlen(ignore); k++) { if (string[i] == ignore[k]) inIgnore = 0; }
          }

          /* delim or last character add it to the substring array */
          if ((found && !inIgnore) || (i == stringLength - 1 && !found)) {
              if (i == stringLength - 1 && !found) {
                  temp[cols] = string[i];
                  cols = cols + 1;
              }
              temp[cols] = '\0';
              if (strcmp(temp,"") != 0) {
                  s->substring[s->rows] = (char*)malloc(sizeof(char) * cols + 1);
                  strcpy(s->substring[s->rows],temp);
                  s->rows = s->rows + 1;
              }
              cols = 0;
          } else {
              temp[cols] = string[i];
              cols = cols + 1;
          } found = 0;
      }
      return s;
  }

/**
 * freeSplit
 * Free the memory allocated by the split function.
 *
 * IN: (Split*) The split structure.
 * RETURN: NONE.
 *
 **/
void freeSplit(Split* s) {
      if (s->substring == NULL) return;
      int i;
      for (i = 0; i < s->rows; i++)
          free(s->substring[i]);
      free(s->substring);
  }

/**
 * newBuffer
 * Create a new buffer of given size.
 *
 * IN: (int) Buffer size.
 * RETURN: (char*).
 *
**/
Buffer* newBuffer(int size) {
    Buffer* b = (Buffer*)malloc(sizeof(Buffer));
    b->buffer = (char*)malloc(sizeof(char) * size);
    if (b == NULL || b->buffer == NULL) printError("Buffer allocation failed.",1);
    strcpy(b->buffer,"");
    b->size = size;
    b->currentIndex = 0;
    return b;
}

/**
 * bufferAppend
 * Append a string to the end of the buffer.
 *
 * IN: (Buffer*) the current buffer, (char*) the string to append.
 * RETURN: NONE.
 *
 **/
void bufferAppend(Buffer* buf, char* string) {
    int length = strlen(string);

    /* Extend buffer, if needed */
    if (length + buf->currentIndex >= buf->size) {
        buf->buffer = (char*) realloc(buf->buffer, buf->size * 1.5);
        if (buf->buffer == NULL) printError("Buffer allocation failed.",1);
        buf->size += buf->size * 1.5;
    }
    /* Copy string into buffer */
    strcat(buf->buffer,string);
    buf->currentIndex = buf->currentIndex + length;
}

/**
 * clearBuffer
 * Reset the index of the buffer.
 *
 * IN: (Buffer*) the buffer to clear.
 * RETURN: NONE.
 *
 **/
 void bufferClear(Buffer* b) {
     b->currentIndex = 0;
     b->buffer[b->currentIndex] = '\0';
 }

/**
* freeBuffer
* Free the memory allocated to a buffer.
*
* IN: (Buffer*) the buffer.
* RETURN: NONE.
*
**/
void freeBuffer(Buffer* b) {
    free(b->buffer);
    free(b);
}

/**
 * stringify
 * allocate a string.
 *
 * IN: NONE.
 * RETURN: (char*) Pointer to the string.
 * NOTE: Caller must free.
 *
 **/
char* stringify(char* str) {
      char *newstring = (char*) malloc(strlen(str)*sizeof(char) + 1);
      if (newstring == NULL) printError("Unable to allocate memory.",1);
      strcpy(newstring, str);
      return newstring;
}

/**
 * chomp
 * Remove trailing newline character.
 *
 * IN: (char*) the string.
 * RETURN: NONE.
 *
 **/
void chomp(char* str) {
     if (!str) return;
     int end = strlen(str)-1;
     if (str[end] == '\n') str[end] = '\0';
 }

/**
* printError
* Prints an error message.
*
* IN: (char*) message, (int) fatal error.
* RETURN: NONE.
*
**/
void printError(char* message, int fatal) {
   printf("%s\n", message);
   if(fatal) exit(1);
}
