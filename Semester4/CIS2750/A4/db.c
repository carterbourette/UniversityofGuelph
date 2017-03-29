/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 *
 * Assignment 4
 * March 27, 2017
 * Software System Integration and Development
 * Database Interface with Message Manager.
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include <mysql/mysql.h>*/
#include "/usr/local/mysql/include/mysql.h"
#include "stringy.h"
#include "db.h"

#define HOSTNAME  "localhost"
#define USERNAME  "root"
#define PASSWORD  "sys"
#define DATABASE  "A4"

/**
 * sqlConnect
 * Initialize the SQL variables.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
void sqlConnect(Properties* p) {
    mysql_init(&(p->mysql));
    mysql_options(&(p->mysql), MYSQL_READ_DEFAULT_GROUP, "mydb");
    if (!mysql_real_connect(&(p->mysql), HOSTNAME, USERNAME, PASSWORD,DATABASE, 0, NULL, 0)) {
       printf("Could not connect to host.\n");
    }
}

/**
 * delegate
 * Delegate job to required function.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
void delegate(Properties* p) {
    /*int i;*/
    /*for (i = 1; i < p->stLen; i++) {*/
        if (!strcmp(p->string[1], "-help"))  help(p);
        else if (!strcmp(p->string[1], "-create"))  create(p);
        else if (!strcmp(p->string[1], "-clear"))  clear(p);
        else if (!strcmp(p->string[1], "-reset"))  reset(p);
        else if (!strcmp(p->string[1], "-posts"))  post(p);
        else if (!strcmp(p->string[1], "-users"))  users(p);
        else if (!strcmp(p->string[1], "-streams"))  streams(p);
        else if (!strcmp(p->string[1], "-query"))  query(p);
        else
            printf("Command '%s' not found!\nFormat: ./db [ -create ] [ -clear ] [ -posts ] [ -users ] [ -streams ] [ -query ] [ -help ]\n",p->string[1]);
    /*}*/
}

/**
 * create
 * Create the tables required for program operation.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
void create(Properties* p) {
    MYSQL* mysql = &p->mysql;

    printf("Creating tables...\n");

    /* Create the Author table */
    if (mysql_query(mysql, "create table if not exists Author (id int not null auto_increment, username char(500), primary key (id), unique (username))") != 0)
        printf("Author table creation failed.\n");
    /* Create the stream table */
    if (mysql_query(mysql, "create table if not exists Stream (id int not null auto_increment, streamname char(500), primary key (id), unique (streamname))") != 0)
        printf("Stream table creation failed.\n");
    /* Create post table */
    if (mysql_query(mysql, "create table if not exists Post (id int not null auto_increment, author int, stream int, postdate int, message longtext, primary key (id))") != 0)
        printf("Post table creation failed.\n");
    /* Create StreamList */
    if (mysql_query(mysql, "create table if not exists StreamList (id int not null auto_increment, author int, stream int, lastMsg int, primary key (id))") != 0)
        printf("StreamList table creation failed.\n");
}

/**
 * clear
 * Remove all content within the database.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
void clear(Properties* p) {
    MYSQL* mysql = &p->mysql;

    printf("Clearing database...\n");

    if (mysql_query(mysql, "Delete from Author where 1") != 0)
        printf("Failed delete from Author table.\n");
    if (mysql_query(mysql, "Delete from Stream where 1") != 0)
        printf("Failed delete from Stream table.\n");
    if (mysql_query(mysql, "Delete from Post where 1") != 0)
        printf("Failed delete from Post table.\n");
    if (mysql_query(mysql, "Delete from StreamList where 1") != 0)
        printf("Failed delete from StreamList table.\n");
}

/**
 * reset
 * Drop all tables in the database.
 *
 * IN: NONE.
 * RETURN: NONE.
 *
 **/
void reset(Properties* p) {
    MYSQL* mysql = &p->mysql;

    if (mysql_query(mysql, "Drop tables Author, Post, Stream, StreamList") != 0)
        printf("Failed to reset database.\n");
    else
        printf("Database reset successfully!\n");
}

/**
 * post
 * Print out all posts stored in the database.
 *
 * IN: NONE.
 * RETURN: NONE.
 *
 **/
void post(Properties* p) {
    MYSQL* mysql = &p->mysql;
    int found = 0;

    /* Query the post table */
    if(mysql_query(mysql, "Select Post.id, streamname, username, message from (Post INNER JOIN Stream ON Post.stream=Stream.id) INNER JOIN Author ON Author.id=Post.author") != 0)
        printf("Query failed.\n");

    /* Fetch the results */
    if (!(p->results = mysql_store_result(mysql)))
        printf("Failed.\n");

    printf("+---------------------------------------------------------+\n");
    printf("|   Messages                                              |\n");
    printf("+---------------------------------------------------------+\n");
    /* Iterate over the results */
    while ((p->row = mysql_fetch_row(p->results))) {
        printf("Stream: %s\n", p->row[1]);
        printf("Username: %s\n", p->row[2]);
        printf("Message:\n%s\n", p->row[3]);
        printf("+---------------------------------------------------------+\n");
        found = 1;
    } if (!found) printf("|   no results found.                           |\n");
}

/**
 * users
 * Print all users in the database.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
void users(Properties* p) {
    MYSQL* mysql = &p->mysql;
    int found = 0;

    /* Query the post table */
    if(mysql_query(mysql, "Select * from Author where 1") != 0)
        printf("Query failed.\n");

    /* Fetch the results */
    if (!(p->results = mysql_store_result(mysql)))
        printf("Failed.\n");

    printf("+------------------------------+\n");
    printf("| id | name                    |\n");
    printf("+------------------------------+\n");
    /* Iterate over the results */
    while ((p->row = mysql_fetch_row(p->results))) {
        printf("   %s   %s\n", p->row[0], p->row[1]);
        found = 1;
    } if (!found) printf("|   no results found.          |\n");
    printf("+------------------------------+\n");
}

/**
 * streams
 * Print all the streams in the database.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
void streams(Properties* p) {
    MYSQL* mysql = &p->mysql;
    int found = 0;

    /* Query the post table */
    if(mysql_query(mysql, "Select * from Stream where 1") != 0)
        printf("Query failed.\n");

    /* Fetch the results */
    if (!(p->results = mysql_store_result(mysql)))
        printf("Failed.\n");

    printf("+------------------------------+\n");
    printf("| id | streamname              |\n");
    printf("+------------------------------+\n");
    /* Iterate over the results */
    while ((p->row = mysql_fetch_row(p->results))) {
        printf("   %s   %s\n", p->row[0], p->row[1]);
        found = 1;
    } if (!found) printf("|   no results found.          |\n");
    printf("+------------------------------+\n");
}

/**
 * query
 * Run a given query.
 *
 * IN: (properties*).
 * RETURN: NONE.
 *
 **/
void query(Properties* p) {
     MYSQL* mysql = &p->mysql;

     /* Query the post table */
     if(mysql_query(mysql, p->string[2]) != 0)
         printError("Query Failed, SQL error.",1);
     if ((p->results = mysql_store_result(mysql))) {
         while ((p->row = mysql_fetch_row(p->results))) {
             int numRow = mysql_num_fields(p->results);
             int i;
             for (i = 0; i < numRow; i++) {
                 printf("%s\t", p->row[i]);
             } printf("\n");
         }
     }
 }

/**
 * help
 * Print all the commands.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
void help(Properties* p) {
    printf("   Assignment 4: \n");
    printf("   Message Viewer w Database\n\n");
    printf("   Author: Carter Bourette\n");
    printf("   0916638\n\n");
    printf("   Commands\n");
    printf("      -clear :\n");
    printf("          Remove all information stored\n");
    printf("          within the database.\n");
    printf("      -reset :\n");
    printf("          Remove all the tables from\n");
    printf("          within the database.\n");
    printf("      -posts :\n");
    printf("          Print out all posts stored\n");
    printf("          within the database.\n");
    printf("      -users :\n");
    printf("          Print out all users stored\n");
    printf("          within the database.\n");
    printf("      -streams :\n");
    printf("          Print out all streams stored\n");
    printf("          within the database.\n");
    printf("         ----------           \n");
    printf("      -create :\n");
    printf("          Create all the tables\n");
    printf("          required by the database.\n");
    printf("      -query :\n");
    printf("          Execute an SQL query.\n");
    printf("          ./db -query [ query str ]\n");
}

int main(int argc, char* argv[]) {
    if (argc < 2) printError(" ./db [ -create ] [ -clear ] [ -posts ] [ -users ] [ -streams ] [ -query ] [ -help ]",1);

    /* Initialize properties */
    Properties properties;
    properties.string = argv;
    properties.stLen = argc;

    /* Initialize mysql properties */
    sqlConnect(&properties);

    /* Call the given command */
    delegate(&properties);

    /* Clean up after mysql */
    mysql_close(&properties.mysql);
    return 0;
}
