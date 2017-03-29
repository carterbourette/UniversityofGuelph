/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 **/
#define _POSIX_SOURCE
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern char **getln();

/**
 * printMe
 * Print info about me.
 *
 * IN: NONE.
 * RETURN: NONE.
 *
 **/
void printMe() {
    printf("+***********************************************************+\n");
    printf("|     Assignment 1 - Writing a Shell                        |\n");
    printf("|     Author: Carter Bourette                               |\n");
    printf("|     Student ID: 0916638                                   |\n");
    printf("|     Email: cbourett@mail.uoguelph.ca                      |\n");
    printf("+***********************************************************+\n");
}

/**
* convertToInt
* Convert string to int for cars values.
*
* IN: (char*) string with numbers.
* RETURN: (int) integer value.
* ERROR: NONE.
*
**/
int convertToInt(char* chars) {
  int sum = 0;
  for (int i = 0; i < strlen(chars); i++) {
      if (*(chars+i) > 47 && *(chars+i) < 58) {
          sum = sum *10;
          sum += *(chars+i) - '0';
      } else {
          if (*(chars+i) == '0' || *(chars+i) == 'x') continue;
          sum = (int)strtol(chars, NULL, 0);
      }
  }
  return sum;
}

/**
 * guess
 * Guesssing game.
 *
 * IN: (char**) arguments.
 * RETURN: NONE.
 *
 **/
void guess(char** args) {
    if (args[1] == NULL || args[2] == NULL) printf("Invalid format: guess [ size of set ] [ your guess ]\n");
    srand(time(NULL));
    int ran = rand() % convertToInt(args[1]) + 1;
    if (ran == convertToInt(args[2])) printf("Hooray! You guessed the number! (%d)\n", ran);
    else printf("Sorry! The number was %d\n", ran);
}

/**
 * addEmUp
 * Given an expression of parameters add each value.
 *
 * IN: (int) number of arguments, (char**) the arguments as integer or hex value.
 * RETURN: NONE.
 *
 **/
void addEmUp(int numArgs, char** args) {
    int sum = 0;
    for(int i = 1; args[i] != NULL; i++) {
        sum += convertToInt(args[i]);
        if (i == numArgs) printf("%s", args[i]);
        else  printf("%s + ", args[i]);
    }
    printf(" = %d\n", sum);
}

/**
 * countEmUp
 * Print the number of arguments and their values.
 *
 * IN: (int) number of arguments given, (char**) the arguments.
 * RETURN: NONE.
 *
 **/
void countEmUp(int numArgs, char** args) {
    printf("argc = %d, args = ", numArgs);
    for(int i = 1; args[i] != NULL; i++) {
        if (i == numArgs) printf(" %s\n", args[i]);
        else printf(" %s,", args[i]);
    }
}

/**
 * contains
 * Return status if a string contains given delim.
 *
 * IN: (char*) the string, (char*) the delim.
 * RETURN: (int) status | 1 or 0.
 *
 **/
int contains(char** string, char* delim) {
    for(int i = 0; string[i] != NULL; i++) {
        if (!strcmp(string[i], delim)) return 1;
    } return 0;
}

/**
 * chopArg
 * Set an argument to NULL.
 *
 * IN: (char**) argument list, (char*) delim.
 * RETURN: NONE.
 *
 **/
void chopArg(char** string, char* delim) {
    for(int i = 0; string[i] != NULL; i++) {
        if (!strcmp(string[i], delim)) {
            string[i] = NULL;
        }
    }
}

/**
 * getArgFollowing
 * Return the argument following a given delimeter.
 *
 * IN: (char**) the argument list, (char*) the delimeter.
 * RETURN: (char*) the argument.
 *
 **/
char* getArgFollowing(char** string, char* delim){
    int found = 0;
    for(int i = 0; string[i] != NULL; i++) {
        if (found) {
            string[i-1] = NULL;
            return string[i];
        }
        if (!strcmp(string[i], delim)) found = 1;
    } return NULL;
}

/**
 * killProcess
 * Kill the child (if exists) before we exit.
 *
 * IN: (pid_t) Child process.
 * RETURN: NONE.
 *
 **/
void killProcess(pid_t pid) {
    if (pid !=-1)kill(pid, SIGINT);
    kill(getppid(),SIGINT);
    exit(0);
}

int main(int argc, char *argv[]) {
    char **args;
    pid_t  pid = -1, wait = -1;

    while (1) {
        FILE* file = NULL;
        int background = 0;

        printf(">> ");
        if (background == 0) args = getln();

        /* Determine number of arguments */
        if (args[0] == NULL) continue;
        int numArgs = 0, status = 0, cStatus = 0;
        for(int i = 1; args[i] != NULL; i++) numArgs++;

        /* If the command contains an & it must be executed in the background */
        if (contains(args,"&")) {
            chopArg(args, "&");
            background = 1;
        }
        if (!strcmp(args[0],"exit")) killProcess(pid);
        else {
            wait = waitpid(pid, &status, WNOHANG);
            pid = fork();
            switch(pid) {
                case 0:     /* Child */
                    /* Pipe input into program */
                    if (contains(args,"<")){
                        for(int i = 0; args[i] != NULL; i++) {
                            if (!strcmp(args[i], "<")) {
                                args[i] = args[i+1];
                                args[i+1] = NULL;
                            }
                        }
                    }
                    /* Pipe to an output file if specified */
                    if (contains(args,">")){
                        char* filename = getArgFollowing(args, ">");
                        if (filename != NULL) {
                            file = freopen(filename, "w+", stdout);
                            if (file == NULL) printf("Unable to open file\n");
                        }
                    } else if (background) {
                        /* Burn the output to dev/null */
                        file = freopen("/dev/null", "w+", stdout);
                        if (file == NULL) printf("Unable to open file\n");
                    }
                    /* My new commands */
                    if (!strcmp(args[0],"add")) addEmUp(numArgs,args);
                    else if (!strcmp(args[0],"args") || !strcmp(args[0],"arg")) countEmUp(numArgs,args);
                    else if (!strcmp(args[0],"author")) printMe();
                    else if (!strcmp(args[0],"guess") || !strcmp(args[0],"???")) guess(args);
                    /* Send to terminal to execute */
                    else if (execvp(args[0], args) == -1) perror("Error");
                    if (file != NULL) fclose(file);
                    printf("\n\n");
                    setbuf(stdout, NULL);
                    setpgid(0,0);
                    exit(0);
                    break;
                default:    /* Parent */
                    if (!background) waitpid(-1, &cStatus, 0);
            }
        }
    }
    return 0;
}
