#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "interface.h"
#include "LinkedList.h"

void initGame() {
    srand(time(NULL));  //    Seed the random number generator
    rand();             //    run rand() once randomize seed
    initscr();          //  Init ncurses
    noecho();
    curs_set(0);
    cbreak();

    checkScreenSize();
}

void gameLoop(Player* player, List* rooms) {
    char input;

    movePlayer(player, "Press q to exit...");

    do {
        int yOld, xOld, returnValue;
        yOld = player->y;
        xOld = player->x;

        input = getchar();

        mvprintw(player->y, player->x,".");

        //  Move the player based on keyboard input
        switch (input) {
            case 'w':
                player->y--;
                break;
            case 'a':
                player->x--;
                break;
            case 's':
                player->y++;
                break;
            case 'd':
                player->x++;
                break;
        }
        //  Check to see if the player is touching something that cannot be
        returnValue = checkMove(player, rooms, player->y, player->x);
        if (returnValue == 1) {
            movePlayer(player,"");
        } else if (returnValue == 2 ) {
            //  Get me out of here we went up or down stairs
            break;
        } else {
            player->y = yOld;
            player->x = xOld;
            movePlayer(player,"You cannot move there!");
        }
    } while (input != 'q');
}

void endGame() {
    endwin();
}

Room* initRoom(List* list) {
    Room *room = (Room*)malloc(sizeof(Room));
    if (room == NULL) throw("Unable to allocate memory!");

    //  Create linked list of room items
    room->itemsList = initList();

    //  Create a room and return the memory location
    addItem(list, room);

    return room;
}

RoomItem* initItem (List* list) {
    RoomItem *item = (RoomItem*)malloc(sizeof(RoomItem));
    if (item == NULL) throw("Unable to allocate memory!");

    item->x = 0;
    item->y = 0;
    item->symbol = '\0';
    item->direction = '\0';

    //  Add new item to itemslist
    addItem(list, item);

    return item;
}

void printRoom(List* rooms) {
    Room *roomPtr;
    RoomItem *roomItemPtr;
    int row, col;

    for (int r = 0; r < getSizeOfList(rooms); r++) {
        roomPtr = (Room*)getItem(rooms, r);

        for (int i = 0; i < roomPtr->length + 2; i++) {
            for (int j = 0; j < roomPtr->width + 2; j++) {

                col = ((r % 3) * 26) + j;
                row = ((r / 3) * 18) + i + 2;

                if (i == 0 || i == roomPtr->length + 1){
                    mvprintw(row,col,"-");
                } else if (j == 0 || j == roomPtr->width + 1) {
                    mvprintw(row,col,"|");
                } else {
                    mvprintw(row,col,".");
                }
             }
        }

        //draw items

        for (int k = 0; k < getSizeOfList(roomPtr->itemsList); k++) {
            roomItemPtr = (RoomItem*)getItem(roomPtr->itemsList, k);
            row = roomItemPtr->y;
            col = roomItemPtr->x;

            if (roomItemPtr->symbol == '@') {
                continue;
            } else if (roomItemPtr->direction == '\0') {
                mvprintw(((r / 3) * 18) + row + 3, ((r % 3) * 26) + col + 1, &roomItemPtr->symbol);
            } else {
                char string[2];
                string[0] = roomItemPtr->symbol;
                string[1] = '\0';

                if (roomItemPtr->direction == 'n') {
                    mvprintw(((r / 3) * 18) + 2, ((r % 3) * 26) + col, string);
                } else if (roomItemPtr->direction == 'e') {
                    mvprintw(((r / 3) * 18) + 2 + col, ((r % 3) * 26), string);
                } else if (roomItemPtr->direction == 'w') {
                    mvprintw(((r / 3) * 18) + 2 + col, ((r % 3) * 26) + roomPtr->width +1, "+");
                } else if (roomItemPtr->direction == 's') {
                    mvprintw(((r / 3) * 18) + 3 + roomPtr->length, ((r % 3) * 26) + col, "+");
                }
            }
        }

     }
     refresh();
 }

void checkScreenSize() {
    int x = 0, y = 0;

    getmaxyx(stdscr, y, x);
    if (x < 72 || y < 39) {
        endGame();
        throwError("Increase screen size!");
    }

}

void movePlayer(Player* player, char* str) {
    mvprintw(player->y, player->x,"@");
    message(str);
    displayStats(player);
}

int checkMove (Player* player, List* rooms, int y, int x) {
    chtype character;
    character = mvinch(y,x);

    if (character == '-' || character == '|') {
        return 0;
    } else if (character == '+') {
        int count, newY, newX;
        Room* room;
        RoomItem* item;

        newY = 0;
        newX = 0;
        count = 0;

        if (player->room == getSizeOfList(rooms) - 1) {
            room = (Room*)getItem(rooms, 0);
            player->room = 0;
        } else {
            room = (Room*)getItem(rooms, player->room++);
        }

        do {
            item = getItem(room->itemsList, count);
            count++;
        } while (item->symbol != '+');

        //  Get teleported position

        if (item->direction == 'n') {
            newY = getRelativeYPosition(player->room, 0);
            newX = getRelativeXPosition(player->room, item->x);
        } else if (item->direction == 'e') {
            newY = getRelativeYPosition(player->room, item->x);
            newX = getRelativeXPosition(player->room, 0);
        } else if (item->direction == 'w') {
            newY = getRelativeYPosition(player->room, item->x);
            newX = getRelativeXPosition(player->room, 0);
        } else if (item->direction == 's') {
            newY = getRelativeYPosition(player->room, room->length-1);
            newX = getRelativeXPosition(player->room, item->x);
        }
        player->x = newX;
        player->y = newY;
        movePlayer(player, "Teleporting...");
    } else if (character == '*') {
        player->gold += getRandom(0,50);
    } else if (character == 'T') {
        return 0;
    } else if (character == 'B' || character == 'S' || character == 'Z') {
        return 0;   //  Invalid move
    } else if (character == '>' || character == '<') {
        return 2;   //  Return quit code
    }
    return 1;   //  Valid move
}

int getRelativeYPosition (int room, int yPos) {
    return ((room / 3) * 18) + yPos + 2;
}

int getRelativeXPosition (int room, int xPos) {
    return ((room % 3) * 26) + xPos + 1;
}

void message(char* str) {
     mvprintw(1,0,str);
     clrtoeol();
     refresh();
 }

void displayStats (Player* player) {
    mvprintw(0,0,"Player\t\tRoom: %d\t\tGold: %d",player->room+1,player->gold);
    clrtoeol();
    refresh();
}

void clearDisplay () {
    int x = 0, y = 0;

    getmaxyx(stdscr, y, x);

    for (int i = 2; i < y; i++) {
        move(i,0);
        clrtoeol();
    }
    refresh();
}

void parseFile (char* path, Player* player, List* rooms) {
     FILE* file;
     char fileLine[150];
     int count, tempInt;

     file = fopen(path,"r");
     if (file == NULL) throwError("Error while opening file...");

     count = 0;
     tempInt = 0;

     while (fgets(fileLine, 150, file)) {
         char *token;
         Room* ptr;

         ptr = initRoom(rooms);
         ptr->roomNumber = count;

         // Tokenize and parse width
        token = strtok(fileLine," ");
        for (int i = 0; i < strlen(token); i++){
            if (*(token+i) != 'X') {
                tempInt = tempInt * 10 + ((*(token+i)) - '0');
                if (i == strlen(token) - 1) {
                    ptr->width = tempInt;
                    tempInt = 0;
                }
            } else {
                ptr->length = tempInt;
                tempInt = 0;
            }
        }
        //  Parse items
         while (token != NULL) {
             RoomItem *item;
             int inDigit, digit;
             inDigit = 0;
             digit = 0;

             token = strtok(NULL, " ");
             if (token == NULL) break;

             item = initItem(ptr->itemsList);

             for (int i = 0; i < strlen(token); i++){
                 char tokenChar;
                 tokenChar = *(token+i);

                 if (tokenChar == ',') {
                     item->y = digit;
                     digit = 0;
                     inDigit = 0;
                    continue;
                 }

                  if (isdigit(tokenChar)) {
                      digit = (digit * 10) + tokenChar - '0';

                      if (strlen(token)-1 == i) {
                          item->x = digit;
                      } else {
                          inDigit = 1;
                      }
                  } else if (inDigit != 0){
                     item->x = digit;
                  } else {
                      if (item->symbol == '\0') {
                          item->symbol = getSymbol(tokenChar);
                      } else {
                          item->direction = tokenChar;
                      }
                  }
             }
             if (item->symbol == '@') {
                 player->y = ((count / 3) * 18) + item->y + 3;
                 player->x = ((count % 3) * 26) + item->x + 1;
                 player->room = count;
                 player->gold = 0;
             }
             //printf("Other: %s\n", token);
         }
         count++;
     }
     fclose(file);
 }

char getSymbol(char sym) {
     if (sym == 'h') {
         return '@';
     } else if (sym == 'd') {
         return '+';
     } else if (sym == 'z') {
         return '<';
     } else if (sym == 'a') {
         return '>';
     } else if (sym == 'g') {
         return '*';
     } else if (sym == 'G') {
         return '8';
     } else if (sym == 'w') {
         return ')';
     } else if (sym == 'W') {
         return '(';
     } else if (sym == 'm') {
         int random;
         random = getRandom(1,4);
         if (random == 1) return 'A';
         else if (random == 2) return 'B';
         else if (random == 3) return 'S';
         else if (random == 4) return 'Z';
     } else if (sym == 'e') {
         return ']';
     } else if (sym == 'M') {
         return 'T';
     } else if (sym == 'p') {
         return '!';
     }
     return '\0';
 }

int getRandom (int lower, int upper) {
     return (rand() % upper) + lower;
 }

void throwError (char* str) {
     printf("%s\n", str);
     exit(1);
 }
