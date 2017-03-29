#include <stdlib.h>
#include <stdio.h>
#include "interface.h"
#include "LinkedList.h"

int main(int argc, char *argv[] ) {

    if (argc != 2) throwError("Please enter the correct arguments...\nFormat: ./programName inputFile");

    Player* hero = (Player*)malloc(sizeof(Player));
    if (hero == NULL) throwError("Insufficient memory!\nExecution failed!\n");

    //  Create a dynamic array for rooms
    List* roomsList = initList();

    //  Parse input file given by arg[1]
    parseFile(argv[1], hero, roomsList);

    //  init ncurses and config terminal
    initGame();

    printRoom(roomsList);

    //  While game is running, game loop runs
    gameLoop(hero, roomsList);

    //  Before quit, display gold
    message("Thank you for playing! Press any key to exit.");
    clearDisplay();
    getchar();

    //  Clean up ncurses
    endGame();

    //  Free up room sublist of items
    for (int i = 0; i < getSizeOfList(roomsList); i++) {
        Room *ptr;
        ptr = getItem(roomsList, i);
        freeList(ptr->itemsList);
    }

    //  Free room list and player struct
    freeList(roomsList);

    free(hero);

    return 0;
}
