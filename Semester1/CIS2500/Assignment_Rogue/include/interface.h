#ifndef __CBOURETTE_INTERFACE__
#define __CBOURETTE_INTERFACE__

#include "LinkedList.h"     //  Needed for Room Struct List def

typedef struct struct_player {
    int y;
    int x;
    int room;
    int gold;
} Player;

typedef struct struct_room {
    int length;
    int width;
    int roomNumber;
    List* itemsList;
} Room;

typedef struct struct_room_item {
    int x;
    int y;
    char symbol;
    char direction;
} RoomItem;

/**
 * initGame
 * Initalize ncurses, setup options.
 *
 * IN: VOID
 * RETURN: VOID
 *
 **/
void initGame ();

/**
 * gameLoop
 * Handle player input and game execution.
 *
 * IN: (Player*) Hero structure, (List*) Linked List structure.
 * RETURN: (int) relative y position.
 *
 **/
void gameLoop (Player* player, List* rooms);

/**
 * endGame
 * Clean up after ncurses, free memory.
 *
 * IN: VOID
 * RETURN: VOID
 *
 **/
void endGame ();

/**
 * initRoom
 * Allocate memory for a room structure, add to list and
 * return memory address.
 *
 * IN: (List*) Linked List structure.
 * RETURN: (Room*) Address to a room structure.
 *
 **/
Room* initRoom (List* list);

/**
 * initItem
 * Allocate memory for a item structure, add to list and
 * return memory address.
 *
 * IN: (List*) Linked List structure.
 * RETURN: (Room*) Address to an item structure.
 *
 **/
RoomItem* initItem (List* list);

/**
 * printRoom
 * Build and print room structures to screen.
 *
 * IN: (List*) Linked List structure.
 * RETURN: VOID
 *
 **/
void printRoom (List* rooms);

/**
 * printRoom
 * Build and print room structures to screen, quit if
 * screen is insufficient.
 *
 * IN: VOID.
 * RETURN: VOID
 *
 **/
void checkScreenSize ();

/**
 * movePlayer
 * Move player, post message
 *
 * IN: (Player*) hero structure, (char*) message.
 * RETURN: VOID
 *
 **/
void movePlayer (Player* player, char* str);

/**
 * checkMove
 * Determines whether player move is valid.
 *
 * IN: (Player*) hero structure, (List*) Linked List structure,
 *     (int) y position to check, (int) x position to check.
 * RETURN: (int) relative y position.
 *
 **/
int checkMove (Player* player, List* rooms, int y, int x);

/**
 * getRelativeYPosition
 * Equation for room position.
 *
 * IN: (int) room number, (int) y position
 * RETURN: (int) relative y position.
 *
 **/
int getRelativeYPosition (int room, int yPos);

/**
 * getRelativeXPosition
 * Equation for room position.
 *
 * IN: (int) room number, (int) x position
 * RETURN: (int) relative x position.
 *
 **/
int getRelativeXPosition (int room, int xPos);

/**
 * message
 * Print a message at (0,0) for player.
 *
 * IN: (char*) message to display.
 * RETURN: VOID
 *
 **/
void message (char* str);

/**
 * displayStats
 * Display hero information.
 *
 * IN: (Player*) Hero structure
 * RETURN: VOID
 *
 **/
void displayStats (Player* player);

/**
 * clearDisplay
 * Clear ncurses output
 *
 * IN: VOID
 * RETURN: VOID
 *
 **/
void clearDisplay ();

/**
 * parseFile
 * Opens file parses level information and creates rooms.
 *
 * IN: (char*) file path, (Player*) Hero structure,
 *     (List*) Linked List structure.
 * RETURN: VOID
 *
 **/
void parseFile (char* path, Player* player, List* rooms);

/**
 * getSymbol
 * Give character, return display character
 *
 * IN: (char) file character.
 * RETURN: (char) game symbol.
 *
 **/
char getSymbol (char sym);

/**
 * getRandom
 * Generate a random number between given x and y.
 *
 * IN: (int) low inclusive, (int) high inclusive
 * RETURN: (int) Random number.
 *
 **/
int getRandom (int lower, int upper);

/**
 * throwError
 * Send an error back to the user
 *
 * IN: (char*) Error message
 * RETURN: VOID
 *
 **/
void throwError (char* str);

#endif
