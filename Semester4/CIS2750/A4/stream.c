/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 **/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stream.h"
#include "stringy.h"
#include <unistd.h>

 /**
  * updateStream
  * Adds or updates a post.
  *
  * IN: (UserPost) the post to add or updates.
  * RETURN: NONE.
  *
  **/
 void updateStream(UserPost* post) {
     FILE* output = NULL;
     char *authorID = NULL, *streamID = NULL;
     char returnStr[200];
     Buffer* b = newBuffer(250);

     /* Query the UserID */
     bufferAppend(b, "Select id from Author where username='");
     bufferAppend(b,post->username);
     bufferAppend(b,"'");
     output = query(b->buffer);
     bufferClear(b);
     if (output) {
         fgets(returnStr, 199, output);
         authorID = stringify(returnStr);
         fclose(output);
     }

     /* Query the stream ID */
     bufferAppend(b, "Select id from Stream where streamname='");
     bufferAppend(b,post->streamName);
     bufferAppend(b,"'");
     output = query(b->buffer);
     bufferClear(b);
     if (output) {
         fgets(returnStr, 199, output);
         streamID = stringify(returnStr);
         fclose(output);
     }

     /* Insert post */
    bufferAppend(b, "INSERT INTO Post(author, stream, postdate, message) VALUES (");
    bufferAppend(b,authorID);
    bufferAppend(b,",");
    bufferAppend(b,streamID);
    bufferAppend(b,",");
    bufferAppend(b,post->data);
    bufferAppend(b,",'");
    bufferAppend(b,post->text);
    bufferAppend(b,"')");
    query(b->buffer);
    free(authorID);
    free(streamID);
    freeBuffer(b);
    removeTemp();
 }

 /**
  * addUser
  * Adds a user with given name and adds to
  * comma separated stream list.
  *
  * IN: (char*) The users name, (char*) comma separated list of streams.
  * RETURN: NONE.
  *
  **/
 void addUser(char* username, char* list) {
     Buffer* b = newBuffer(250);
     FILE* output = NULL;
     char *authorID = NULL, *streamID = NULL;
     char returnStr[200];

     /* Split on given delimeter */
     char* token = strtok(list, ", ");

     /* Create the necessary files for the user */
     while( token != NULL ) {
         /* Insert the user if they do not exist */
         bufferAppend(b,"Insert Ignore into Author (username) values ('");
         bufferAppend(b,username);
         bufferAppend(b,"')");
         query(b->buffer);
         bufferClear(b);

        /* Get the id */
         bufferAppend(b,"Select id from Author where username='");
         bufferAppend(b,username);
         bufferAppend(b,"'");
         output = query(b->buffer);
         bufferClear(b);

         /* Get the result of the query from the output */
         if (output) {
            fgets(returnStr, 199, output);
            authorID = stringify(returnStr);
            pclose(output);
        } else printError("Failed to insert!", 1);

         /* Insert the stream if it does not exist, get it's id */
         bufferAppend(b,"Insert Ignore into Stream (streamname) values ('");
         bufferAppend(b,token);
         bufferAppend(b,"')");
         query(b->buffer);
         bufferClear(b);

         bufferAppend(b, "Select id from Stream where streamname='");
         bufferAppend(b,token);
         bufferAppend(b,"'");
         output = query(b->buffer);
         bufferClear(b);

         /* Get the result of the query from the output */
         if (output) {
             fgets(returnStr, 199, output);
             streamID = stringify(returnStr);
             pclose(output);
         } else printError("Failed to insert!", 1);

         /* Insert the user into the stream - streamlist */
         bufferAppend(b,"insert into StreamList (author, stream, lastMsg) values (");
         bufferAppend(b,authorID);
         bufferAppend(b,",");
         bufferAppend(b,streamID);
         bufferAppend(b,",0)");
         output = query(b->buffer);
         if (output) pclose(output);
         bufferClear(b);

         free(authorID);
         free(streamID);
         token = strtok(NULL, ", ");
     }
     freeBuffer(b);
     removeTemp();
     printf("The user %s was successfully added to the %s stream(s).\n", username, list);
 }

 /**
  * removeUser
  * Find a user with given name and delete in all occurances
  * of the given comma separated list.
  *
  * IN: (char*) the users name, (char*) comma separated list
  * RETURN: NONE.
  *
  **/
 void removeUser(char* username, char* list) {
     FILE* output = NULL;
     char *authorID = NULL, *streamID = NULL;
     char returnStr[200];
     Buffer* b = newBuffer(250);

     /* Split on given delimeter */
     char* token = strtok(list, ", ");

     /* Call given function for each token */
     while( token != NULL ) {

        /* Query the UserID */
        bufferAppend(b, "Select id from Author where username='");
        bufferAppend(b,username);
        bufferAppend(b,"'");
        output = query(b->buffer);
        bufferClear(b);
        if (output) {
            fgets(returnStr, 199, output);
            authorID = stringify(returnStr);
            pclose(output);
        }

        /* Query the stream ID */
        bufferAppend(b, "Select id from Stream where streamname='");
        bufferAppend(b,token);
        bufferAppend(b,"'");
        output = query(b->buffer);
        bufferClear(b);
        if (output) {
            fgets(returnStr, 199, output);
            streamID = stringify(returnStr);
            pclose(output);
        }

        /* Delete all from streamlist where stream= streamID and author = author ID */
        bufferAppend(b, "Delete from StreamList where stream = '");
        bufferAppend(b, streamID);
        bufferAppend(b, "' and author = '");
        bufferAppend(b, authorID);
        bufferAppend(b,"'");
        query(b->buffer);
        bufferClear(b);
         token = strtok(NULL, ", ");
     }
     freeBuffer(b);
     printf("The user %s was successfully removed from the %s stream(s).\n", username, list);
 }

 /**
  * freeEntry
  * Free the memory allocated to an entry.
  *
  * IN: (UserPost) the structure to free.
  * RETURN: NONE.
  *
  **/
  void freeEntry(UserPost* post) {
      free(post->username);
      free(post->streamName);
      free(post->data);
      free(post->text);
  }

  /**
   * readInput
   * Prompt the user for input.
   *
   * IN: (int) boolean, does the enter key end the prompt.
   * RETURN: (char*) the requested input.
   * NOTE: Caller must free.
   *
   **/
  char* readInput(int enterToExit) {
      char c;
      char string[2500];
      int index = 0;

      /* While input not CTRL-D or EOF */
      while ( (c = getchar()) != EOF ) {
          if (enterToExit && c == '\n') break;
          string[index] = c;
          index++;
      }
      string[index] = '\0';
      /* Return a heap string */
      return stringify(string);
  }

  /**
   * readTemp
   * Read the temp file for information related to post and addauthor.
   *
   * IN: (int) Var to read.
   * RETURN: (char*) text.
   *
   **/
  char* readTemp(int stream) {
       char line[1999];
       Buffer* b = newBuffer(250);
       FILE* fp = fopen("info.txt","r");
       if (!fp) printError("Unable to open temp file.", 1);
       /* Get the streams line */
       fgets(line, 1999, fp);
       if (stream) {
           char* out = stringify(line);;
           chomp(out);
           return out;
       }
       /* If we want the post it will be in the rest of the file. */
       while (fgets(line, 1999, fp)) {
           bufferAppend(b, line);
       } return b->buffer;
   }

 /**
  * removeTemp
  * remove the file.
  *
  * IN: NONE.
  * RETURN: NONE.
  *
  **/
  void removeTemp() {
       remove("info.txt");
  }

  /**
   * query
   * Run a query on the database.
   *
   * IN: (char*) query string.
   * RETURN: NONE.
   * NOTE: Caller must free. See pclose();
   **/
   FILE* query(char* query) {
       Buffer* b = newBuffer(250);

       /* Add the query string to api call */
       bufferAppend(b, "./db -query \"");
       bufferAppend(b, query);
       bufferAppend(b, "\" > results.txt");
       /* Make the call to db */
       system(b->buffer);

       FILE* out = fopen("results.txt", "r");
       /* free the Buffer */
       freeBuffer(b);
       return out;
   }
