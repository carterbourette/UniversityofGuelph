/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 *
 * Assignment 2
 * Feb 27, 2017
 * CPU Simulator
 * FCFS and RR scheduler.
 *
 **/
#include "Schedule.h"

int main(int argc, char* argv[]) {

    Properties properties;

    /* Initialize lists */
    initProperties(&properties);

    /* Parse the command line args */
    parseProperties(&properties, argv, argc);

    /* Parse the file */
    parse(&properties);

    /* Start Simulation */
    if (properties.quantum != 0)
        RR(&properties);
    else
        FCFS(&properties);

    /* Print results */
    results(&properties);

    /* Clean up */
    freeProperties(&properties);
}
