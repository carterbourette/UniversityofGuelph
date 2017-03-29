/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 **/

typedef struct struct_properties {
    char** string;
    int stLen;
    MYSQL mysql;
    MYSQL_RES *results;
    MYSQL_ROW row;
    MYSQL_FIELD *field;
} Properties;

/**
 * sqlConnect
 * Initialize the SQL variables.
 *
 * IN: (char**) string.
 * RETURN: NONE.
 *
 **/
void sqlConnect(Properties* p);

/**
 * delegate
 * Delegate job to required function.
 *
 * IN: (char**) string.
 * RETURN: NONE.
 *
 **/
void delegate(Properties* p);

/**
 * create
 * Create the tables required for program operation.
 *
 * IN: NONE.
 * RETURN: NONE.
 *
 **/
void create(Properties* p);

/**
 * clear
 * Remove all content within the database.
 *
 * IN: NONE.
 * RETURN: NONE.
 *
 **/
void clear(Properties* p);

/**
 * reset
 * Drop all tables in the database.
 *
 * IN: NONE.
 * RETURN: NONE.
 *
 **/
void reset(Properties* p);

/**
 * post
 * Print out all posts stored in the database.
 *
 * IN: NONE.
 * RETURN: NONE.
 *
 **/
void post(Properties* p);

/**
 * users
 * Print all users in the database.
 *
 * IN: NONE.
 * RETURN: NONE.
 *
 **/
void users(Properties* p);

/**
 * streams
 * Print all the streams in the database
 *
 * IN: NONE.
 * RETURN: NONE.
 *
 **/
void streams(Properties* p);

/**
 * select
 * Run a select query and return the resutls to stdout.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
void select(Properties* p);

 /**
  * query
  * Run a given query.
  *
  * IN: (properties*).
  * RETURN: NONE.
  *
  **/
void query(Properties* p);

/**
 * help
 * Print all the commands.
 *
 * IN: NONE.
 * RETURN: NONE.
 *
 **/
void help(Properties* p);
