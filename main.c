#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define X 9
#define Y 9
#define mineCount 10

typedef struct node {
  int value; //-1 = bomb
  int shown; // 0 = hidden, 1 = shown, 2 = flagged
} Node;

void setUpBoard(Node[][Y], int[][2]);
void displayBoard(Node[][Y]);
void displayBoardValues(Node[][Y]);
void revealNode(Node[][Y], int, int);
void floodFill(struct node[][Y], int, int);
void placeFlag(Node[][Y], int, int);
int hitMine(Node[][Y], int, int);
int checkWin(Node[][Y], int[][2]);

int main(void) {
  srand(time(NULL));
  bool alive = true;
  bool win = false;
  Node board[X][Y] = {0};
  int mineLocations[mineCount][2] = {0};
  int userXvalue = -1;
  int userYvalue = -1;
  char flag = 0;

  printf("\033[1;34mWelcome to MineSweeper!!!\033[0m\n");
  
  setUpBoard(board, mineLocations);

  while (alive == true && win == false) { 
    system("clear");

    printf("There are %d mines on the board\n", mineCount);
    displayBoard(board);

    while (userXvalue == -1 && userYvalue == -1) {
      printf("Place 'F' at end of your input to place/remove flag\n");
      printf("Enter X Y Coordiates: ");
      scanf("%d%d%c", &userXvalue, &userYvalue, &flag); 
      //Coordinates Entered:x y
      
      if (userXvalue > X || userYvalue > Y || userXvalue < 0 || userYvalue < 0) {
        printf("\033[1;31mINVALID COORDINATE \033[0m\n");
        userXvalue = -1;
        userYvalue = -1; 
      }
    }

    if (flag == 'f' || flag == 'F') {
      placeFlag(board, userXvalue, userYvalue);
      userXvalue = -1;
      userYvalue = -1;
      flag = 0;
      }
    else {
      alive = hitMine(board, userXvalue, userYvalue);

      if (alive == false) {
        printf("YOU HAVE HIT A MINE\n");
        break;
      }
      else {
        revealNode(board, userXvalue, userYvalue);
      }
      userXvalue = -1;
      userYvalue = -1;
      }

    win = checkWin(board, mineLocations);
    
  }

  system("clear");
  if (win == true) {
    printf("\033[1;34mCONGRATULATIONS!!!\033[0m\n"); 
    displayBoardValues(board);
    printf("\033[1;34mYou win!!!\033[0m\n"); 
    printf("\033[1;34mThanks for playing\033[0m\n");
  }
  else if (alive == false) {
    printf("\033[1;31mYOU HIT A MINE \033[0m\n");
    displayBoardValues(board);
    printf("\033[1;31mGame Over\033[0m\n");
    printf("\033[1;34mThanks for playing\033[0m\n"); 
  }
  printf("If you would like to play again, please restart the program");
  return 0;
}

void setUpBoard(Node board[][Y], int mineLocations[][2]) {
  int mineXcoor = 0;
  int mineYcoor = 0;
  //setting all values to 0;
  for (int i = 0; i < X; i ++) {
    for (int j = 0; j < Y; j++) {
      board[i][j].value = 0;
      board[i][j].shown = 0;
    }
  }

  //placing mines
  for (int i = 0; i < mineCount; i++) {
    mineXcoor = rand()%(X);
    mineYcoor = rand()%(Y);

    if (board[mineXcoor][mineYcoor].value == 0) {
      board[mineXcoor][mineYcoor].value = -1;
      mineLocations[i][0] = mineXcoor;
      mineLocations[i][1] = mineYcoor;
    }
    else {
      i--;
    }
  }

  //placig the numbers around the mines:
  for (int i = 0; i < mineCount; i ++)
  {
    //checking around the mine locations
    for (int x = -1; x < 2; x ++)
    {
      for (int y = -1; y < 2; y ++)
      {
        //if I am not out of bounds
        if (mineLocations[i][0] + x >= 0 && mineLocations[i][0] + x < X 
          && mineLocations[i][1] + y >= 0 && mineLocations[i][1] + y < Y)
        {
          //Increasing the values around the mines
          if(board[mineLocations[i][0] + x][mineLocations[i][1] + y].value != -1)
          {
            board[mineLocations[i][0] + x][mineLocations[i][1] + y].value = (board[mineLocations[i][0] + x][mineLocations[i][1] + y].value) + 1;
            //not a space, not a bomb. so it is a number
          }
        }
      }
    }
  }
}

void displayBoard(Node board[][Y]) {
  int colNum = 0;
  for (int i = 0; i < Y; i++) {
    for (int j = 0; j < X; j++) {
      if (i == 0 && j == 0) {
        //Numbers going across the top
        for (int k = 0; k < X; k ++) {
          if (k == 0) {
            printf("  ");
          }
          printf("\033[1;31m%i \033[0m", k);
        }
        printf("\n");
      }
      //Numbers going across the side
      if(j == 0) {
        printf("\033[1;31m%i \033[0m", colNum);
        colNum ++;
      }

      if (board[j][i].shown == 1) {
        printf("%i ", board[j][i].value);
      }
      else if (board[j][i].shown == 2) {
        printf("\033[1;35mF \033[0m");
      }
      else {
        printf("- ");
      }

    }
    printf("\n");
  }

}

void displayBoardValues(Node board[][Y]) {
  int colNum = 0;
  for (int i = 0; i < Y; i++) {
    for (int j = 0; j < X; j++) {
      if (i == 0 && j == 0) {
        //Numbers going across the top
        for (int k = 0; k < X; k ++) {
          if (k == 0) {
            printf("  ");
          }
          printf("\033[1;31m%i \033[0m", k);
        }
        printf("\n");
      }
      //Numbers going across the side
      if(j == 0) {
        printf("\033[1;31m%i \033[0m", colNum);
        colNum ++;
      }

      if (board[j][i].value == -1) {
        printf("B ");
      }
      else {
        printf("%i ", board[j][i].value);
      }  

    }
    printf("\n");
  }

}

void revealNode(Node board[][Y], int xValue, int yValue) {
  board[xValue][yValue].shown = 1;
  if (board[xValue][yValue].value == 0) {
    floodFill(board, xValue, yValue);
  } 
}

void floodFill(struct node board[][Y], int x, int y) {
  for (int i = -1; i < 2; i ++) {
    for (int j = -1; j < 2; j ++) {
      //checking if I am in bounds
      if (x + i >= 0 && x + i < X && y + j >= 0 && y + j < Y) {
        if (board[x + i][y + j].value != -1 && board[x + i][y + j].shown == 0) {
          revealNode(board, (x + i), (y + j));
        }
      }
    }
  }
}

void placeFlag(Node board[][Y], int xValue, int yValue) {
  //function used to both place and remove flags
  if (board[xValue][yValue].shown == 0) {
    board[xValue][yValue].shown = 2;
    return;
  }
  else if (board[xValue][yValue].shown == 2) {
    board[xValue][yValue].shown = 0; 
    return;
  }
  else {
    return;
  }
  
}

int hitMine(Node board[][Y], int xValue, int yValue) {
  //plug into the 'alive' variable
  if (board[xValue][yValue].value == -1) {
    return false;
  }
  else {
    return true;
  }
}

int checkWin(Node board[][Y], int mineLocations[][2]) {
  int count = 0; 

  //game of minesweeper is won once you clear all the spaces that are not mines
  for (int i = 0; i < 8; i ++) { 
    for (int j = 0; j < 8; j ++) {
      if ((board[i][j].shown == 0 || board[i][j].shown == 2) && board[i][j].value != -1) {
        //If hidden (with a flag or not), and it is not a mine, increase the count
        count ++;
      }
    }
  }
  if (count == 0) { 
    //this means that there are NO blank spaces over things that are not a mine
    return 1;
  }
  else {
    return 0;
  }
  
}