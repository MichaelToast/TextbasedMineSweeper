#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define X 9
#define Y 9

const int mineCount = 10;

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
  int flagCount = 0;
  char flag = 0;

  setUpBoard(board, mineLocations);
  displayBoardValues(board);


  while ((alive == true || win == false) && flagCount != mineCount) { 
    //system("clear");

    if (flagCount == mineCount) {
      // {Function to determine if game has been won}
    }

    printf("There are %d mines on the board\n", mineCount);
    displayBoard(board);

    while (userXvalue == -1 && userYvalue == -1) {
      printf("Place 'F' at end of your input to place/remove flag\n");
      printf("Enter X Y Coordiates: ");
      scanf("%d%d%c", &userXvalue, &userYvalue, &flag); 
      //5 6F

      if (userXvalue > X || userYvalue > Y || userXvalue < 0 || userYvalue < 0) {
        printf("\033[1;31mINVALID COORDINATE \033[0m");
        userXvalue = -1;
        userYvalue = -1; 
      }
    }

      if (flag == 'f' || flag == 'F') {
        // {Function to place/remove flag}
        placeFlag(board, userXvalue, userYvalue);
        flagCount ++;
        userXvalue = -1;
        userYvalue = -1;
        flag = 0;
      }
      else {
        alive = hitMine(board, userXvalue, userYvalue);

        if (alive == false) {
          // {game over}
          printf("YOU HAVE HIT A MINE\n");
        }
        else {
          revealNode(board, userXvalue, userYvalue);
          // {reveal spot}
        }
        userXvalue = -1;
        userYvalue = -1;

        if (flagCount == mineCount) {
          win = checkWin(board, mineLocations);
        }
      }
  }

  //user has exited the game loop, meaning they have either won or died

  displayBoard(board);
  
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
        printf("F ");
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
        printf("b ");
      }
      else {
        printf("%i ", board[j][i].value);
      }  

    }
    printf("\n");
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
    //if the square is flagged, remove the flag
    board[xValue][yValue].shown = 0; 
    return;
  }
  
}

int checkWin(Node board[][Y], int mineLocations[][2]) {
  //go through the mine locations and check if they are all flagged
  int correctCount = 0;
  for (int i = 0; i < mineCount; i ++) { 
    if (board[(mineLocations[i][0])][(mineLocations[i][1])].shown == 2) {
      correctCount ++;
    }
  }
  if (correctCount == mineCount) {
    return true;
  }
  else {
    return false; 
  }
  
}