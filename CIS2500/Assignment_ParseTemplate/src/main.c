#include <stdio.h>
#include <stdlib.h>
#include "template.h"

int main( int argc, char *argv[] )  {

    if ( argc != 4 ) throwError("Please enter the correct arguments...\nFormat: ./progName templateFile variableFile outputFile");

    Properties documentProperties;

    initProperties (&documentProperties, argv);
    setToHash (&documentProperties);
    interpretTemp (&documentProperties);
    printDocumentProperties (documentProperties);
}
