 /***
 The Game of Pig - Assignment #1
 CIS*1500
 
 Carter Bourette
 October 1, 2015
 0916638
 ***/

#include <stdio.h>    //    Used for printf and scanf
#include <stdlib.h>   //    Used for rand() function
#include <time.h>     //    Used for time

/***
showDice: Given a number (1-6) prints out die face
In: (int num) integer between 1-6
Out: None
Post: Prints image of Die
***/
void showDice(int num)
{
    if(num == 1)
    {
        printf("+---------+\n");
        printf("|         |\n");
        printf("|    o    |\n");
        printf("|         |\n");
        printf("+---------+\n");
        printf("\nYou rolled a %d, loose a turn!\n",num);
        return;
    }
    else if(num == 2)
    {
        printf("+---------+\n");
        printf("| o       |\n");
        printf("|         |\n");
        printf("|       o |\n");
        printf("+---------+\n");
    }
    else if(num == 3)
    {
        printf("+---------+\n");
        printf("| o       |\n");
        printf("|    o    |\n");
        printf("|       o |\n");
        printf("+---------+\n");
    }
    else if(num == 4)
    {
        printf("+---------+\n");
        printf("| o     o |\n");
        printf("|         |\n");
        printf("| o     o |\n");
        printf("+---------+\n");
    }
    else if(num == 5)
    {
        printf("+---------+\n");
        printf("| o     o |\n");
        printf("|    o    |\n");
        printf("| o     o |\n");
        printf("+---------+\n");
    }
    else if(num == 6)
    {
        printf("+---------+\n");
        printf("| o     o |\n");
        printf("| o     o |\n");
        printf("| o     o |\n");
        printf("+---------+\n");
    }
    printf("\nYou rolled a %d\n",num);
}

/***
randomNumber: Prints an integer between 1-6
In: None
Out: int
Post: None
***/
int randomNumber()
{
  return rand() % 6 + 1;     //    Return a random number between 1-6
}

/***
turn: Simulates 1 players turn
In: None
Out: int
Post: Calls showDice (output) prints: prompt, roll total, and turn total
***/
int turn()
{
    char response;
    int roll, turnTotal, playerTurn;
    
    turnTotal = 0;
    playerTurn = 1;

    while(playerTurn)     //    While it is players turn repeat
    {
        printf("Would you like to (r)oll or (h)old?");
        scanf(" %c",&response);
    
        if(response == 'r' || response == 'R')
        {
            roll = randomNumber();
            showDice(roll);
            if(roll == 1)
            {
                /*    For a roll of 1, end turn and return score of 0    */
                turnTotal = 0;
                playerTurn = 0;
            }
            else 
            {
                /*    Roll between 2-6, add points and continue turn    */
                turnTotal += roll;
                printf("Turn Total: %d\n\n",turnTotal);
            }
        } 
        else if(response =='h' || response == 'H')
        {
            /*    Player wants to hold, end turn    */
            playerTurn = 0;
        }
    }
    return turnTotal;    
}

/***
checkScore: Checks to see if player score is equal to or greater than the winning game score.
In: (int gameScore) the winning game score, (int playerScore) the current players total score, (int playerNum) which player score?
Out: (int) 'bool' value 1 if player score is less than the winning score, 0 if val greater than winning score
Post: None
***/
int checkScore(int gameScore, int playerScore, int playerNum)
{
    if(playerScore < gameScore)
    {
        return 1;             //   Keep game loop running
    }
    else
    {
        printf("\nCongratulations! Player %d wins!\n",playerNum);
        return 0;             //   Someone won, end game
    }
}
/***
 game: Runs one game
 In: None
 Out: None
 Post: Prints game prompts and die faces
 ***/
void game()
{
  int gameScore,game;        //    declare variable for game winning score and game
  int playerScore[3];        //    declare array for player scores
  
  game = 1;
  gameScore = 0;             //    initialize an int value - 1 while the game is ongoing
  playerScore[1] = 0;        //    initialize array values for player scores
  playerScore[2] = 0;
  
  printf("\n\nWelcome to Pigs!!\n");
  printf("-----------------\n\n");
  
  /*    Ask the user what the winning score will be until they provide correct answer (between 10-10 000)    */
  while(!(gameScore >= 10 && gameScore <= 10000))
  {
    printf("Please enter the score to play to (10 - 10000): ");
    scanf(" %d",&gameScore);
  }
  
  while(game)        //    Repeat player turns (alternating) until game ends
  {
    for(int i = 1; i < 3; i++)
    {
      if(!game)
      {
        break;
      }
      /*    Each player turn, output scores    */
      printf("\n-----------------\n");
      printf("Player 1 Score: %d\n",playerScore[1]);
      printf("Player 2 Score: %d\n",playerScore[2]);
      printf("-----------------\n\n");
      printf("Starting player %d's turn.\n",i);
      
      /*    Add the player score for their turn (calls turn) to their total score    */
      playerScore[i] += turn();
      
      /*    Check to see if the player won, if so quit while/game, output game winning message     */
      game = checkScore(gameScore,playerScore[i],i);
    }
  }

}

int main()
{
    int playing;
    char response;
  
    playing = 1;               //    'Bool' val
    srand(time(NULL));         //    Seed the random number generator
    rand();                    //    run rand() once randomizes set based on srand seed
  
    while(playing)
    {
        /* Call to game method to run 1 game */
        game();
        /* Ask if player wants to play again, otherwise quit the game loop and quit program */
        printf("Would you like to play again? (Y)es or (N)o?");
        scanf(" %c",&response);
        if (!(response == 'y' || response == 'Y'))
        {
            playing = 0;
        }
    }
  
    return 0;
}
