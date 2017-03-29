/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 **/

#ifndef __CBOURETTE_SCHEDULE__
#define __CBOURETTE_SCHEDULE__

#include "LinkedList.h"

typedef enum enum_status {
    New, Ready, Running, Blocked, Terminated
} Status;

typedef struct struct_properties {
    int simClock;

    int detailed;
    int verbose;
    int debug;

    int quantum;
    int threadSwitch;
    int processSwitch;
    int numProcesses;
    int cputime;

    List* processes;
    List* ready;
    List* event;
    List* finished;
} Properties;

typedef struct struct_process {
    int id;
    int numThreads;
    List* threads;
} Process;

typedef struct struct_thread {
    int id;
    int parentID;
    Status status;
    int arrivalTime;
    int endTime;
    int numBursts;
    int currentBurst;
    int IOburstStartTime;
    int totalCPU;
    int totalIO;
    int CPUBurst[100];
    int IOBurst[100];
} Thread;

typedef struct struct_event {
    int foriegnKey;
} Event;


/**
 * initSimulation
 * Creates the event queue from the data parsed in the file.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
void initSimulation(Properties *properties);

/**
 * changeState
 * Change the current thread status.
 *
 * IN: (Properties*), (Thread*) thread to change the state of, (Status) status to change to.
 * RETURN: NONE.
 *
 **/
void changeState(Properties* properties, Thread* t, Status toStatus);

/**
 * isReady
 * Determine if we can operate on the thread in the ready queue.
 *
 * IN: (Thread*) current thread.
 * RETURN: (int) boolean status.
 *
 **/
int isReady(Properties* p, Thread* t);

/**
 * fetchEvent
 * Check for another event in the event queue.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
void fetchEvent(Properties* p);

/**
 * execTimer
 * Adds to the simulation clock.
 *
 * IN: (Properties*), (int) the amount of time to simulate.
 * RETURN: NONE.
 *
 **/
void execTimer(Properties *p, int eTime);

/**
 * results
 * Print the results of the simulation.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
void results(Properties* p);

/**
 * RR
 * Round Robin scheduler.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
 void RR(Properties* properties);

/**
 * FCFS
 * First-Come-First-Serve scheduler.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
void FCFS(Properties* properties);

/**
 * parse
 * Parse the data file.
 *
 * IN: (Properties*) properties structure.
 * RETURN: NONE.
 *
 **/
void parse(Properties *properties);

/**
 * initProperties
 * Allocs lists and zeros properties.
 *
 * IN: (Properties*) the struct to init.
 * RETURN: NONE.
 *
 **/
void initProperties(Properties* p);

/**
 * newProcess.
 * Allocate and initialize a new thread.
 *
 * IN: NONE.
 * RETURN: (Process*).
 *
 **/
Process* newProcess();

/**
 * newThread
 * Allocate and initialize a new threads.
 *
 * IN: NONE.
 * RETURN: (Thread*).
 *
 **/
Thread* newThread();

/**
 * parseJob
 * Parse the job given in the file.
 *  Format: num_process thread_switch process_switch
 *
 * IN: (Properties*) program properties, (char*) file line.
 * RETURN: NONE.
 *
 **/
void parseJob(Properties *properties, char* string);

/**
 * parseProcess
 * Parse given file line, format: process_num #of_threads.
 *
 * IN: (char*) file line.
 * RETURN: (Process*) The process structure.
 *
 **/
Process* parseProcess(char* string);

/**
 * parseThread
 * Parse the given thread, format: thread# arrival_time num_bursts.
 *
 * IN: (char*) the file line.
 * RETURN: (Thread*) the thread.
 *
 **/
Thread* parseThread(char* string, int parentProcess);

/**
 * parseBurst
 * Parse the burst format: num_burst cpu_time IO_time.
 *
 * IN: (Thread*) the current thread, (char*) file line.
 * RETURN: NONE.
 *
 **/
void parseBurst(Thread* thread, char* string);

/**
 * parseProperties
 * Parse command line properties.
 *
 * IN: (Properties*) the properties, (char**) command line.
 * RETURN: NONE.
 *
 **/
 void parseProperties(Properties* properties, char** args, int arg);

 /**
  * freeProperties
  * Free all the alloc'd memory.
  *
  * IN: (Properties*).
  * RETURN: NONE.
  *
  **/
 void freeProperties(Properties* p);

 /**
  * printThread
  * Prints an individual thread.
  *
  * IN: (Thread*) the thread to print.
  * RETURN: NONE.
  *
  **/
 void printThread(Thread* t);

 /**
  * printThreads
  * Prints a list of threads.
  *
  * IN: (List*).
  * RETURN: NONE.
  *
  **/
 void printThreads(List* l);


/**
 * printError
 * Print error and quit (if specified).
 *
 * IN: (char*) error msg, (int) quit if 1.
 * RETURN: NONE.
 *
 **/
void printError(char* str, int quit);

#endif
