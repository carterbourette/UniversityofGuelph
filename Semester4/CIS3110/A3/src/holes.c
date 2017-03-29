/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 **/

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "LinkedList.h"
 #include "stringy.h"
 #define MEMORYSIZE 128

typedef struct struct_process {
    char* id;
    int memory;
    int numSwap;
    int timeInMemory;
} Process;

typedef struct struct_properties {
    int lastIndex;
    int totalLoads;
    int numProcesses;
    int totalHoles;
    double cumulativeMemory;

    List* queue;
    List* inMemory;
    Process* memory[MEMORYSIZE];
    char* filename;
    int verbose;
} Properties;

/**
 * memoryMap : function pointer to the alogithm to map memory.
 * IN: (Properties*) prog properties, (Process*) process to insert.
 * RETURN: NONE.
 *
 **/
void (*mapMemory[4])(Properties*,Process*);

/**
 * insertMemory
 * Insert the process memory into the simulation memory.
 *
 * IN: (Properties*) prog properties, (Process*) process to map, (int) the index to insert.
 * RETURN: (Type) Description.
 *
 **/
void insertMemory (Properties* p, Process* process, int index) {
    for (int i = index; i < process->memory+index; i++)
        p->memory[i] = process;
    p->lastIndex = index + process->memory;
    p->totalLoads += 1;
    enqueue(p->inMemory, process);
}

/**
 * swapOldestProcess
 * Swap out the oldest process in memory.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
void swapOldestProcess(Properties* p) {
    int clear = 0;

    /* Find oldest process in memory */
    Process* oldest = (Process*)dequeue(p->inMemory);

    /* Search for the oldest process and clear it from memory */
    for (size_t i = 0; i < MEMORYSIZE; i++) {
        if (p->memory[i] == oldest) clear = 1;
        else clear = 0;
        if (clear) p->memory[i] = NULL;
    }
    oldest->numSwap += 1;

    /* Requeue the process */
    if (oldest->numSwap < 3) enqueue(p->queue, oldest);
    else free(oldest);
}

/**
 * firstFit
 * Find the first memory location big enough to hold the process.
 *
 * IN: (Properties*) prog properties, (Process*) process to insert.
 * RETURN: NONE.
 *
 **/
void firstFit(Properties* p, Process* process) {
    int requiredSize = process->memory, space = 0, startIndex = 0, swapRequired = 1;

    for (size_t i = 0; i < MEMORYSIZE; i++) {
        /* Record number of empty slots */
        if (p->memory[i] == NULL) {
            if (space == 0) startIndex = i;
            space++;
        }else space = 0;
        /* If we find enough space, insert the process */
        if (space >= requiredSize) {
            insertMemory(p, process, startIndex);
            swapRequired = 0;
            break;
        }
    }
    /* If we cannot find a slot in memory swap the oldest process, recursively loop until we can map the process */
    if (swapRequired) {
        swapOldestProcess(p);
        firstFit(p, process);
    }
}

/**
 * bestFit
 * Find the smallest memory location, able to hold the process.
 *
 * IN: (Properties*) prog properties, (Process*) process to insert.
 * RETURN: NONE.
 *
 **/
void bestFit(Properties* p, Process* process) {
    int requiredSize = process->memory, space = 0, minIndex = 0, swapRequired = 1, cPosition = 0, minBlockSize = 999;
    int memoryBlockSize[128][2]; // [n][0] - Represents size of block // [n][1] - Represents index

    for (size_t i = 0; i < MEMORYSIZE; i++) {
        /* Record number of empty slots */
        if (p->memory[i] == NULL) {
            if (space == 0) {
                memoryBlockSize[cPosition][1] = i;
            }
            space++;
        }

        if (p->memory[i] != NULL || i == MEMORYSIZE - 1) {
            memoryBlockSize[cPosition][0] = space;
            if (space == 0) memoryBlockSize[cPosition][1] = i;
            cPosition += 1;
            space = 0;
        }
    }

    /* Get the best block for the process */
    for (size_t i = 0; i < cPosition; i++) {
        if (memoryBlockSize[i][0] >= requiredSize && memoryBlockSize[i][0] <= minBlockSize) {
            minBlockSize = memoryBlockSize[i][0];
            minIndex = memoryBlockSize[i][1];
            swapRequired = 0;
        }
    }

    /* If we cannot find a slot in memory swap the oldest process, recursively loop until we can map the process */
    if (swapRequired) {
        swapOldestProcess(p);
        bestFit(p, process);
    } else {
        /* If we find enough space, insert the process */
        insertMemory(p, process, minIndex);
    }
}

/**
 * firstFit
 * Find the biggest location to hold the process.
 *
 * IN: (Properties*) prog properties, (Process*) process to insert.
 * RETURN: NONE.
 *
 **/
void worstFit(Properties* p, Process* process) {
    int requiredSize = process->memory, space = 0, minIndex = 0, swapRequired = 1, cPosition = 0, minBlockSize = 0;
    int memoryBlockSize[128][2]; // [n][0] - Represents size of block // [n][1] - Represents index

    for (size_t i = 0; i < MEMORYSIZE; i++) {
        /* Record number of empty slots */
        if (p->memory[i] == NULL) {
            if (space == 0) {
                memoryBlockSize[cPosition][1] = i;
            }
            space++;
        }

        if (p->memory[i] != NULL || i == MEMORYSIZE - 1) {
            memoryBlockSize[cPosition][0] = space;
            if (space == 0) memoryBlockSize[cPosition][1] = i;
            cPosition += 1;
            space = 0;
        }
    }

    /* Get the biggest block for the process */
    for (size_t i = 0; i < cPosition; i++) {
        if (memoryBlockSize[i][0] >= requiredSize && memoryBlockSize[i][0] > minBlockSize) {
            minBlockSize = memoryBlockSize[i][0];
            minIndex = memoryBlockSize[i][1];
            swapRequired = 0;
        }
    }

    /* If we cannot find a slot in memory swap the oldest process, recursively loop until we can map the process */
    if (swapRequired) {
        swapOldestProcess(p);
        bestFit(p, process);
    } else {
        /* If we find enough space, insert the process */
        insertMemory(p, process, minIndex);
    }
}

/**
 * nextFit
 * Place process in the next available slot after last process inserted.
 *
 * IN: (Properties*) prog properties, (Process*) process to insert.
 * RETURN: NONE.
 *
 **/
void nextFit(Properties* p, Process* process) {
    int requiredSize = process->memory, space = 0, startIndex = 0, swapRequired = 1, first = 1;

    for (size_t i = p->lastIndex; i < MEMORYSIZE; i++) {
        /* Record number of empty slots */
        if (p->memory[i] == NULL) {
            if (space == 0) startIndex = i;
            space++;
        } else space = 0;
        /* If we find enough space, insert the process */
        if (space >= requiredSize) {
            insertMemory(p, process, startIndex);
            swapRequired = 0;
            break;
        }
        if (i == MEMORYSIZE - 1 && swapRequired && first) i = 0, first = 0;
    }
    /* If we cannot find a slot in memory swap the oldest process, recursively loop until we can map the process */
    if (swapRequired) {
        swapOldestProcess(p);
        firstFit(p, process);
    }
}

/**
 * displayMemoryMap
 * Display an image of what the memory map would look like.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
void displayMemoryMap(Properties* p) {
    printf("|");
    for (size_t i = 0; i < MEMORYSIZE; i++) {
        if (p->memory[i] == NULL) printf("0|");
        else printf("%s|", p->memory[i]->id);
    } printf("\n");
}

/**
 * processStatus
 * Print statistics about the process.
 *
 * IN: (Properties*), (Process*) the current process.
 * RETURN: (Type) Description.
 *
 **/
void processStatus(Properties *p, Process* process) {
    int emptyCount = 0, fullCount = 0, hole = 0, last = -1;
    for (size_t i = 0; i < MEMORYSIZE; i++) {
        /* If the current cell is different from the last one we have a hole */
        if (last != -1 && p->memory[i] == NULL && last !=0) hole++;
        if (p->memory[i] == NULL) {
            emptyCount++;
            last = 0;
        } else {
            fullCount++;
            last = 1;
        }
    }
    /* Set some properties */
    p->cumulativeMemory += (double)fullCount/MEMORYSIZE*100;
    p->totalHoles += hole;
    p->numProcesses += getSizeOfList(p->inMemory);
    printf("Pid: %s loaded, (%d) #processes = %d, #holes = %d, memusage = %.1lf%%, cumulative mem = %.1lf%%\n",process->id, process->memory, getSizeOfList(p->inMemory), hole, (double)fullCount/MEMORYSIZE*100, (double)p->cumulativeMemory/p->totalLoads);
}

/**
 * systemMemoryStatus
 * Get the final statistics.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
void systemMemoryStatus(Properties* p) {
    printf("Total loads = %d, average #processes = %.2lf, average #holes = %.2lf, cumulative mem = %.1lf%%\n",p->totalLoads, (double)p->numProcesses/p->totalLoads,(double) p->totalHoles/p->totalLoads, (double)p->cumulativeMemory/p->totalLoads);
}

/**
 * parse
 * Parse the input file, add the processes to the ready queue.
 *
 * IN: (Properties*).
 * RETURN: NONE.
 *
 **/
void parse(Properties* p) {
    char string[250];
    FILE* fp = fopen(p->filename, "r");
    if (fp == NULL) printError("Unable to open input file.",1);

    /* Create a process for each line in the input file */
    while (fgets(string, 249, fp) != NULL) {
        Process* process = (Process*) malloc(sizeof(Process));

        /* Split the string, set the process attributes */
        Split* tokens = newSplit(string," ");
        process->id = stringify(tokens->substring[0]);
        process->memory = atoi(tokens->substring[1]);
        process->numSwap = 0;
        process->timeInMemory = 0;

        /* Add it to the scheduling queue */
        addItem(p->queue, process);
        freeSplit(tokens);
    }
}

/**
 * initProperties
 * Initialize properties needed by the program.
 *
 * IN: (Properties*), (char**) command line args.
 * RETURN: NONE.
 *
 **/
void initProperties(Properties* p, char* argv[]) {
    p->filename = argv[1];
    p->verbose = 0;
    p->queue = initList();
    p->inMemory = initList();
    p->totalLoads = 0;
    p->numProcesses = 0;
    p->totalHoles = 0;
    p->cumulativeMemory = 0;
    p->lastIndex = 0;
    for (size_t i = 0; i < MEMORYSIZE; i++) {
        p->memory[i] = NULL;
    }
    if (argv[2] && !strcmp(argv[2],"-v"))  p->verbose = 1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) printError("Format: ./holes <filename>",1);

    /* Define memory mapping algorithm */
    char* string[4];
    mapMemory[0] = &firstFit;
    mapMemory[1] = &bestFit;
    mapMemory[2] = &worstFit;
    mapMemory[3] = &nextFit;
    string[0]    = "First-Fit";
    string[1]    = "Best-Fit";
    string[2]    = "Worst-Fit";
    string[3]    = "Next-Fit";

    /* Foreach memory mapping algorithm */
    for (size_t i = 0; i < 4; i++) {
        /* Print out function info */
        printf("+-----------------------------+\n");
        printf("   Method: %s\n", string[i]);
        printf("   Carter Bourette   0916638\n");
        printf("+-----------------------------+\n\n");

        /* Initialize properties */
        Properties properties;
        initProperties(&properties, argv);

        /* Parse the input file */
        parse(&properties);

        /* Start the simulation */
        while (1) {
            /* Fetch process from the queue */
            if (getSizeOfList(properties.queue) < 1) break;
            Process* currentProcess = (Process*)dequeue(properties.queue);

            /* Employ a mapping algorithm on the process */
            mapMemory[i](&properties, currentProcess);
            processStatus(&properties,currentProcess);
            if (properties.verbose) displayMemoryMap(&properties);
        }

        /* Print program statistics */
        systemMemoryStatus(&properties);

        /* Free up the queues */
        freeList(properties.queue);
        freeList(properties.inMemory);
    }
    return 0;
}
