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

 /**
  * updateStream
  * Adds or updates a post.
  *
  * IN: (UserPost) the post to add or updates.
  * RETURN: NONE.
  *
  **/
 void updateStream(UserPost* post) {
     FILE* fp = openStream(post->streamName,Stream,"a+");

     fprintf(fp, "Sender: %s\n", post->username);
     fprintf(fp, "Date: %s", post->data);
     fprintf(fp, "%s\n", post->text);

     int location = ftell(fp);
     fclose(fp);

     fp = openStream(post->streamName, StreamData, "a+");
     fprintf(fp, "%d\n", location);
     fclose(fp);
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
     FILE* fp,*fp1, *fp2;

     /* Split on given delimeter */
     char* token = strtok(list, ", ");

     /* Call given function for each token */
     while( token != NULL ) {
         fp1 = openStream(token, Stream,"a+");
         fp2 = openStream(token, StreamData,"a+");
         fp = openStream(token, StreamUsers,"a+");
         fclose(fp1);
         fclose(fp2);
         fprintf(fp, "%s:0\n",username);
         fclose(fp);
         token = strtok(NULL, ", ");
     }
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
     FILE* fp, *tmp;
     char str[250], cpy[250], tmpS[50];
     int rv = 0;

     /* Split on given delimeter */
     char* token = strtok(list, ", ");

     /* Call given function for each token */
     while( token != NULL ) {
         fp = openStream(token, StreamUsers,"r");
         tmp = fopen("messages/temp.txt","w+");

         while (fgets(str, 250, fp) != NULL) {
             int i, flag = 0, count = 0;
             for (i=0; i < strlen(str); i++) {
                 if (str[i] == ':') {
                     cpy[i] = '\0';
                     flag = 1;
                 }
                 if (flag) tmpS[count++] = str[i];
                 else cpy[i] = str[i];
             }
             if(strcmp(username,cpy) != 0)  { fprintf(tmp, "%s", cpy); fprintf(tmp, "%s", tmpS); }
             else rv = 1;
         }

         fclose(fp);
         fclose(tmp);
         renameStream(token,StreamUsers);
         if (rv)
            printf("The user %s was successfully removed from the %s stream.\n", username, token);
        else
            printf("The user %s was not found in the %s stream.\n", username, token);
         token = strtok(NULL, ", ");
     }
 }

/**
 * verifyUser
 * Verify if the user exists in a given stream.
 *
 * IN: (char*) username, (char*) stream.
 * RETURN: (int) status.
 *
 **/
 int verifyUser(char* name, char* stream) {
     FILE* fp = openStream(stream, StreamUsers,"r");
     if (fp == NULL) return 0;
     char* temp;
     char str[255];

     while (fgets(str, 249, fp) != NULL) {
         temp = strtok(str, ":");
         if(strcmp(name,temp) == 0)  {
             fclose(fp);
             return 1;
         }
     }
     fclose(fp);
     return 0;
 }

/**
 * renameStream
 * Used to rename tempfile in stream.
 *
 * IN: (char*) stream and the (Type).
 * RETURN: NONE.
 *
 **/
 void renameStream(char* stream, Type type) {
     char filename[75];
     strcpy(filename,"messages/");
     strcat(filename,stream);

     switch(type) {
         case Stream:
           strcat(filename,"Stream.txt");
           break;
         case StreamData:
           strcat(filename,"StreamData.txt");
           break;
         case StreamUsers:
           strcat(filename,"StreamUsers.txt");
           break;
     }
     rename("messages/temp.txt",filename);
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
   * append
   * Append given text to a specified stream type.
   *
   * IN: (char*) stream, (Type) the stream type.
   * RETURN: NONE.
   *
   **/
  FILE* openStream(char* stream, Type type, char* mode) {
      FILE* fp;
      char filename[75];
      strcpy(filename,"messages/");
      strcat(filename,stream);

      switch(type) {
          case Stream:
            strcat(filename,"Stream.txt");
            break;
          case StreamData:
            strcat(filename,"StreamData.txt");
            break;
          case StreamUsers:
            strcat(filename,"StreamUsers.txt");
            break;
      }
      fp = fopen(filename,mode);
      perror(":");

      if(fp == NULL) {removeTemp(); printError("Unable to locate stream.", 1);}
      return fp;
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
