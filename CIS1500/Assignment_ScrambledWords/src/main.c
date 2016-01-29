#include <stdlib.h>   //    Rand() function
#include <time.h>     //    Used for seeding random
#include "Scram.h"

int main()
{
    char filename[50];

    /*   Seed random    */
    srand(time(NULL));
    rand();

    /*   Prompt user for filename    */
    getFilename(filename);

    /*   Open file and scramble paragraph    */
    processText(filename);

    return 0;
}
