/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Schedule.h"

/**
 * initSimulation
 * Creates the event queue from the data parsed in the file.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
void initSimulation(Properties *properties) {
    int index[100][3];
    int count = 0;
    /* Populate the event queue by arrival */
    for (size_t i = 0; i < properties->numProcesses; i++) {
        Process* process = (Process*)getItem(properties->processes, i);

        for (size_t j = 0; j < process->numThreads; j++) {
            Thread* thread = (Thread*)getItem(process->threads, j);

            index[count][0] = thread->arrivalTime;
            index[count][1] = i;
            index[count][2] = j;
            count++;
        }
    }
    /* Bubble sort the arrival - index threads */
    for (size_t i = 0; i < count-1; i++) {
        for (size_t j = 0; j < count-1; j++) {
            if (index[j][0] > index[j+1][0]) {  /* Swap em */
                int temp1 = index[j][0];
                int temp2 = index[j][1];
                int temp3 = index[j][2];

                index[j][0] = index[j+1][0];
                index[j][1] = index[j+1][1];
                index[j][2] = index[j+1][2];

                index[j+1][0] = temp1;
                index[j+1][1] = temp2;
                index[j+1][2] = temp3;
            }
        }
    }
    /* Add the items in order to the event queue */
    for (size_t i = 0; i < count; i++) {
        Process* p = (Process*)getItem(properties->processes,index[i][1]);
        Thread* t = (Thread*)getItem(p->threads,index[i][2]);
        addItem(properties->event,t);
    }
}

/**
 * changeState
 * Change the current thread status.
 *
 * IN: (Properties*), (Thread*) thread to change the state of, (Status) status to change to.
 * RETURN: NONE.
 *
 **/
void changeState(Properties* properties, Thread* t, Status toStatus) {
    char* StatusCodes[5];
    StatusCodes[0] = "New";
    StatusCodes[1] = "Ready";
    StatusCodes[2] = "Running";
    StatusCodes[3] = "Blocked";
    StatusCodes[4] = "Terminated";

    if (properties->verbose) printf("At time %d: Thread {%d} of Process {%d} moves from %s to %s.\n", properties->simClock, t->id, t->parentID + 1, StatusCodes[t->status], StatusCodes[toStatus]);
    t->status = toStatus;
    if (t->status == Terminated) t->endTime = properties->simClock;
}

/**
 * isReady
 * Determine if we can operate on the thread in the ready queue.
 *
 * IN: (Thread*) current thread.
 * RETURN: (int) boolean status.
 *
 **/
int isReady(Properties* p, Thread* t) {
    if (t->status == Terminated ) return 0;
    else if (t->status == Blocked) {
        if ((p->simClock - t->IOburstStartTime) > t->IOBurst[t->currentBurst]) {
            changeState(p, t, Ready);
            t->IOBurst[t->currentBurst] = 0;
            t->currentBurst++;
            return 1;
        }//  printf("Time since: %d - ", (p->simClock - t->IOburstStartTime));
        return 0;
    }
    return 1;
}

/**
 * fetchEvent
 * Check for another event in the event queue.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
void fetchEvent(Properties* p) {
    Thread* event = NULL;
    if (p->event->first != NULL ) {
        /* Fetch event */
        event = (Thread*)p->event->first->ptr;
        /* If the event has occured, add to ready queue */
        while (event != NULL && event->arrivalTime <= p->simClock) {
            event = (Thread*)dequeue(p->event);
            changeState(p, event, Ready);
            enqueue(p->ready,event);
            if (p->event->first != NULL) event = (Thread*)p->event->first->ptr;
            else event = NULL;
        }
    }
}

/**
 * execTimer
 * Adds to the simulation clock.
 *
 * IN: (Properties*), (int) the amount of time to simulate.
 * RETURN: NONE.
 *
 **/
void execTimer(Properties *p, int eTime) {
    for (size_t i = 0; i < eTime; i++) {
        p->simClock += 1;
        fetchEvent(p);
    }
    if (!eTime) fetchEvent(p);
}

/**
 * results
 * Print the results of the simulation.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
void results(Properties* p) {
    double sum = 0;
    int totalCPU = 0;
    /* Get each thread */
    for (size_t i = 0; i < getSizeOfList(p->finished); i++) {
        Thread* t = (Thread*)getItem(p->finished, i);

        if (p->detailed) {
            printf("Thread %d of Process %d\n\n", t->id, t->parentID+1);
            printf("   Arrival Time: %d\n", t->arrivalTime);
            printf("   Service Time: %d units\n", t->totalCPU);
            printf("       I/O Time: %d units\n", t->totalIO);
            printf("Turnaround Time: %d units\n", ((t->endTime) - (t->arrivalTime)));
            printf("    Finish Time: %d units\n", t->endTime);
            printf("\n");
        }
        sum += (t->endTime)-(t->arrivalTime);
        totalCPU += t->totalCPU;
    }
    totalCPU += p->cputime;
    printf("\n--Results ---------------------\n");
    printf("  Total Time required is %d units.\n", p->simClock);
    printf("  Average Turnaround Time is %.2lf time units.\n", (sum/getSizeOfList(p->finished)));
    printf("  CPU Utilization is %.0lf%%\n",((double)totalCPU/p->simClock)*100);
}

/**
 * RR
 * Round Robin scheduler.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
 void RR(Properties* properties) {
     Thread *thread = NULL, *lastThread = NULL;
     int simulationRunning = 1;

     initSimulation(properties);

     while (simulationRunning) {
         /* Check event queue for events */
         while (thread == NULL) {
             if (getSizeOfList(properties->event) == 0 && getSizeOfList(properties->ready) == 0) { simulationRunning = 0; break; }
             /* See if any events are ready to be loaded by  */
             execTimer(properties, 0);

             if(properties->debug) {
                 printf("At time %d: Fetch Ready: [ ",properties->simClock);
                 for (size_t i = 0; i < getSizeOfList(properties->ready); i++) {
                     Thread* t = (Thread*)getItem(properties->ready, i);
                     printf("P%dT%d ", t->parentID+1, t->id);
                 } printf("]\n");
             }

             /* Step 1: Fetch from ready queue */
             thread = dequeue(properties->ready);
             if (thread == NULL) execTimer(properties, 1);
         }

         if (!simulationRunning) break;

         /* Step 2: Check to see if we can operate on thread */
         if ( isReady(properties, thread) ) {
             /* Step 3: Do process or thread switch */
             if (lastThread != NULL && lastThread->parentID != thread->parentID){
                 if (properties->debug) printf("At time %d: Process Switch %d units\n",properties->simClock,  properties->processSwitch);
                 execTimer(properties, properties->processSwitch);
                 properties->cputime += properties->processSwitch;
             } else if (lastThread != NULL && lastThread->id != thread->id) {
                 if (properties->debug) printf("At time %d: Thread Switch %d units\n", properties->simClock, properties->threadSwitch);
                 execTimer(properties, properties->threadSwitch);
                 properties->cputime += properties->threadSwitch;
             }

             /* Step 4: Change the Process status to Running */
             changeState(properties, thread, Running);

             /* Step 5: Perform Burst */
             int burst = thread->currentBurst;

             /* Round Robin */
             if (properties->quantum > thread->CPUBurst[burst]){
                 if (properties->debug) printf("At time %d: P%dT%d: CPU burst %d units\n",properties->simClock, thread->parentID+1, thread->id,thread->CPUBurst[burst]);
                 execTimer(properties, thread->CPUBurst[burst]);
                 thread->CPUBurst[burst] = 0;
             } else {
                 if (properties->debug) printf("At time %d: P%dT%d: CPU burst %d units\n",properties->simClock, thread->parentID+1, thread->id,properties->quantum);
                 execTimer(properties, properties->quantum);
                 thread->CPUBurst[burst] = thread->CPUBurst[burst] - properties->quantum;
             }

             /* Step 6: Change the process state to respective value */
             if(thread->CPUBurst[burst] == 0 && thread->numBursts-1 == burst) {
                 // printf("Thread being terminated.\n");
                 changeState(properties, thread, Terminated);
                 thread->endTime = properties->simClock;
                 enqueue(properties->finished, thread);
             } else if (thread->CPUBurst[burst] == 0 && thread->IOBurst[burst] != 0) {
                 /* Start IO Job */
                 if (properties->debug) printf("At time %d: P%dT%d: Thread starting IO %d units, marking as blocked.\n",properties->simClock, thread->parentID+1, thread->id,thread->IOBurst[burst]);
                 thread->IOburstStartTime = properties->simClock;
                 changeState(properties, thread, Blocked);
                 enqueue(properties->ready, thread);
             } else {
                 /* Change the Process status to ready */
                 if (thread->CPUBurst[burst] == 0) thread->currentBurst = burst + 1;
                 changeState(properties, thread, Ready);
                 enqueue(properties->ready, thread);
             }
         } else {
             /* Thread is blocked or terminated move on... */
             if (properties->debug) printf("At time %d: P%dT%d: Marked as %d... (%d current units elapsed)\n",properties->simClock, thread->parentID+1, thread->id, thread->status, (properties->simClock-thread->IOburstStartTime));
             enqueue(properties->ready, thread);
             int allBlock = 1;
             for (size_t i = 0; i < getSizeOfList(properties->ready); i++) {
                 Thread* t = (Thread*)getItem(properties->ready,i);
                 if(t->status != Blocked) allBlock = 0;
             }
             if (allBlock) execTimer(properties, 1);
         }
         lastThread = thread;
         thread = NULL;
     }
 }

 /**
  * FCFS
  * First-Come-First-Serve scheduler.
  *
  * IN: (Properties*).
  * RETURN: NONE.
  *
  **/
void FCFS(Properties* properties) {
     Thread *thread = NULL, *lastThread = NULL;
     int simulationRunning = 1;

     initSimulation(properties);

     while (simulationRunning) {
         /* Check event queue for events */
         while (thread == NULL) {
             if (getSizeOfList(properties->event) == 0 && getSizeOfList(properties->ready) == 0) { simulationRunning = 0; break; }
             /* See if any events are ready to be loaded by  */
             execTimer(properties, 0);

             if(properties->debug) {
                 printf("At time %d: Fetch Ready: [ ",properties->simClock);
                 for (size_t i = 0; i < getSizeOfList(properties->ready); i++) {
                     Thread* t = (Thread*)getItem(properties->ready, i);
                     printf("P%dT%d ", t->parentID+1, t->id);
                 } printf("]\n");
             }

             /* Step 1: Fetch from ready queue */
             thread = dequeue(properties->ready);
             if (thread == NULL) execTimer(properties, 1);
         }

         if (!simulationRunning) break;

         /* Step 2: Check to see if we can operate on thread */
         if ( isReady(properties, thread) ) {
             /* Step 3: Do process or thread switch */
             if (lastThread != NULL && lastThread->parentID != thread->parentID){
                 if (properties->debug) printf("At time %d: Process Switch %d units\n",properties->simClock,  properties->processSwitch);
                 execTimer(properties, properties->processSwitch);
                 properties->cputime += properties->processSwitch;
             } else if (lastThread != NULL && lastThread->id != thread->id) {
                 if (properties->debug) printf("At time %d: Thread Switch %d units\n", properties->simClock, properties->threadSwitch);
                 execTimer(properties, properties->threadSwitch);
                 properties->cputime += properties->threadSwitch;
             }

             /* Step 4: Change the Process status to Running */
             changeState(properties, thread, Running);

             /* Step 5: Perform Job */
             int burst = 0;

             while (1) {    /* FCFS */
                 if (thread->numBursts == burst) break;
                 if (properties->debug) printf("At time %d: P%dT%d: CPU burst %d units\n",properties->simClock, thread->parentID+1, thread->id,thread->CPUBurst[burst]);
                 execTimer(properties, thread->CPUBurst[burst]);
                 thread->CPUBurst[burst] = 0;
                 if (properties->debug) printf("At time %d: P%dT%d: waiting on IO job %d units\n",properties->simClock, thread->parentID+1, thread->id,thread->IOBurst[burst]);
                 execTimer(properties, thread->IOBurst[burst]);
                 thread->IOBurst[burst] = 0;
                 burst++;
             }

             /* Step 6: Change the process state to respective value */
             // printf("Thread being terminated.\n");
             changeState(properties, thread, Terminated);
             thread->endTime = properties->simClock;
             enqueue(properties->finished, thread);
         } else {
             /* Thread is blocked or terminated move on... */
             if (properties->debug) printf("At time %d: P%dT%d: Marked as %d... (%d current units elapsed)\n",properties->simClock, thread->parentID+1, thread->id, thread->status, (properties->simClock-thread->IOburstStartTime));
             enqueue(properties->ready, thread);
             int allBlock = 1;
             for (size_t i = 0; i < getSizeOfList(properties->ready); i++) {
                 Thread* t = (Thread*)getItem(properties->ready,i);
                 if(t->status != Blocked) allBlock = 0;
             }
             if (allBlock) execTimer(properties, 1);
         }
         lastThread = thread;
         thread = NULL;
     }
 }

/**
 * simulate
 * If Quantum is set - Round Robin, else FCFS.
 *
 * IN: (Properties*) pointer to properties structure.
 * RETURN: NONE.
 *
 **/
void simulate(Properties *properties) {

}

/**
 * parse
 * Parse the data file.
 *
 * IN: (Properties*) properties structure.
 * RETURN: NONE.
 *
 **/
void parse(Properties *properties) {
    Process* process;
    Thread* thread;
    char line[150];

    while ( fgets(line, 150, stdin) != NULL ) {
         /* Parse Job */
         parseJob(properties, line);

         /* Parse Each Process */
         for (size_t i = 0; i < properties->numProcesses; i++) {
             fgets(line, 150, stdin);
             process = parseProcess(line);

             /* Parse Each Thread */
             for (size_t j = 0; j < process->numThreads; j++) {

                 fgets(line, 150, stdin);
                 thread = parseThread(line,i);

                 /* Parse Each Burst */
                 for (size_t k = 0; k < thread->numBursts; k++) {

                     fgets(line, 150, stdin);
                     parseBurst(thread, line);
                     thread->currentBurst = 0;
                 }
                 int totalCPU = 0, totalIO = 0;
                 for (size_t k = 0; k < thread->numBursts; k++) {
                     totalCPU += thread->CPUBurst[k];
                     totalIO += thread->IOBurst[k];
                 }
                 thread->totalCPU = totalCPU;
                 thread->totalIO = totalIO;

                 addItem(process->threads, thread);
             }
             addItem(properties->processes, process);
         }
     }
}

/**
 * initProperties
 * Allocs lists and zeros properties.
 *
 * IN: (Properties*) the struct to init.
 * RETURN: NONE.
 *
 **/
void initProperties(Properties* p) {
    p->simClock = 0;
    p->cputime = 0;
    p->debug = 0;
    p->detailed = 0;
    p->verbose = 0;
    p->quantum = 0;
    p->threadSwitch = 0;
    p->processSwitch = 0;
    p->numProcesses = 0;
    p->processes = initList();
    p->ready = initList();
    p->event = initList();
    p->finished = initList();
}

/**
 * newProcess.
 * Allocate and initialize a new thread.
 *
 * IN: NONE.
 * RETURN: (Process*).
 *
 **/
Process* newProcess() {
    Process *p = (Process*)malloc(sizeof(Process));
    if (!p) printError("Unable to allocate memory.", 1);
    p->id = 0;
    p->numThreads = 0;
    p->threads = initList();
    return p;
}

/**
 * newThread
 * Allocate and initialize a new threads.
 *
 * IN: NONE.
 * RETURN: (Thread*).
 *
 **/
Thread* newThread() {
    Thread *t = (Thread*)malloc(sizeof(Thread));
    if (!t) printError("Unable to allocate memory.", 1);
    t->id = 0;
    t->parentID = 0;
    t->arrivalTime = 0;
    t->numBursts = 0;
    t->totalCPU = 0;
    t->totalIO = 0;
    t->status = New;
    return t;
}

/**
 * parseJob
 * Parse the job given in the file.
 *  Format: num_process thread_switch process_switch
 *
 * IN: (Properties*) program properties, (char*) file line.
 * RETURN: NONE.
 *
 **/
void parseJob(Properties *properties, char* string) {
    int position = 0;
    char* delim = " ";
    char* token = strtok(string, delim);

    while (token != NULL) {
        switch (position) {
             case 0: /* number of processes */
                properties->numProcesses = atoi(token);
                break;
             case 1: /* thread switch */
                 properties->threadSwitch = atoi(token);
                 break;
             case 2: /* process switch */
                 properties->processSwitch = atoi(token);
                 break;
         }
         token = strtok(NULL, delim);
         position++;
    }
}

/**
 * parseProcess
 * Parse given file line, format: process_num #of_threads.
 *
 * IN: (char*) file line.
 * RETURN: (Process*) The process structure.
 *
 **/
Process* parseProcess(char* string) {
    int position = 0;
    char* delim = " ";
    char* token = strtok(string, delim);
    Process* process = newProcess();

    while (token != NULL) {
        switch (position) {
            case 0: /* Process ID */
                process->id = atoi(token);
                break;
            case 1: /* # of threads */
                process->numThreads = atoi(token);
                break;
        }
        token = strtok(NULL, delim);
        position++;
    }
    return process;
}

/**
 * parseThread
 * Parse the given thread, format: thread# arrival_time num_bursts.
 *
 * IN: (char*) the file line.
 * RETURN: (Thread*) the thread.
 *
 **/
Thread* parseThread(char* string, int parentProcess) {
     int position = 0;
     char* delim = " ";
     char* token = strtok(string, delim);
     Thread* thread = newThread();
     thread->parentID = parentProcess;
     while (token != NULL) {
         switch (position) {
             case 0: /* Thread ID*/
                thread->id = atoi(token);
                break;
             case 1: /* Arrival time */
                thread->arrivalTime = atoi(token);
                break;
             case 2: /* Number of Bursts */
                thread->numBursts = atoi(token);
                break;
         }
         token = strtok(NULL, delim);
         position++;
     }
     return thread;
 }

/**
 * parseBurst
 * Parse the burst format: num_burst cpu_time IO_time.
 *
 * IN: (Thread*) the current thread, (char*) file line.
 * RETURN: NONE.
 *
 **/
void parseBurst(Thread* thread, char* string) {
     int position = 0;
     char* delim = " ";
     char* token = strtok(string, delim);

     while (token != NULL) {

         switch (position) {
             case 0: /* Burst ID */
                thread->currentBurst = atoi(token)-1;
                break;
             case 1: /* CPU Time */
                thread->CPUBurst[thread->currentBurst] = atoi(token);
                break;
             case 2: /* IO Time (optional default to 0) */
                 thread->IOBurst[thread->currentBurst] = atoi(token);
                 break;
         }
         token = strtok(NULL, delim);
         position++;
     }
 }

/**
 * parseProperties
 * Parse command line properties.
 *
 * IN: (Properties*) the properties, (char**) command line.
 * RETURN: NONE.
 *
 **/
void parseProperties(Properties* properties, char** args, int arg) {
     for (int i = 1; i < arg; i++) {
         if (!strcmp(args[i],"-d"))
             properties->detailed = 1;
         else if (!strcmp(args[i],"-v"))
             properties->verbose = 1;
         else if (!strcmp(args[i],"-debug"))
            properties->debug = 1;
         else if (!strcmp(args[i],"-r")) {
             properties->quantum = atoi(args[i + 1]);
             printf("Round Robin (quantum = %d time units):\n", properties->quantum);
         }
     }
 }

/**
 * freeProperties
 * Free all the alloc'd memory.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
void freeProperties(Properties* p) {
    freeList(p->processes);
    freeList(p->ready);
    freeList(p->event);
    freeList(p->finished);
}

/**
 * printError
 * Print error and quit (if specified).
 *
 * IN: (char*) error msg, (int) quit if 1.
 * RETURN: NONE.
 *
 **/
void printError(char* str, int quit) {
    printf("%s\n", str);
    if (quit) exit(1);
}
