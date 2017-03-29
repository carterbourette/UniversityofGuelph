/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 **/

#ifndef __CBOURETTE_POSTLIB__
#define __CBOURETTE_POSTLIB__

typedef struct struct_UserPost{
    char* username;
    char* streamName;
    char* data;
    char* text;
} UserPost;

typedef enum type {
   Stream = 6,
   StreamData = 10,
   StreamUsers = 11
} Type;

/**
 * updateStream
 * Adds or updates a post.
 *
 * IN: (UserPost) the post to add or updates.
 * RETURN: NONE.
 *
 **/
void updateStream(UserPost* post);

/**
 * addUser
 * Adds a user with given name and adds to
 * comma separated stream list.
 *
 * IN: (char*) The users name, (char*) comma separated list of streams.
 * RETURN: NONE.
 *
 **/
void addUser(char* username, char* list);

/**
 * removeUser
 * Find a user with given name and delete in all occurances
 * of the given comma separated list.
 *
 * IN: (char*) the users name, (char*) comma separated list
 * RETURN: NONE.
 *
 **/
void removeUser(char* username, char* list);

/**
 * freeEntry
 * Free the memory allocated to an entry.
 *
 * IN: (UserPost) the structure to free.
 * RETURN: NONE.
 *
 **/
 void freeEntry(UserPost* post);

/**
 * readInput
 * Prompt the user for input.
 *
 * IN: (int) boolean, does the enter key end the prompt.
 * RETURN: (char*) the requested input.
 * NOTE: Caller must free.
 *
 **/
char* readInput(int enterToExit);

/**
 * readTemp
 * Read the temp file for information related to post and addauthor.
 *
 * IN: (int) Var to read.
 * RETURN: (char*) text.
 *
 **/
char* readTemp(int stream);

/**
 * removeTemp
 * Remove the temporary file.
 *
 * IN: NONE.
 * RETURN: NONE.
 *
 **/
void removeTemp();

/**
 * query
 * Run a query on the database.
 *
 * IN: (char*) query string.
 * RETURN: NONE.
 *
 **/
 FILE* query(char* query);

#endif
