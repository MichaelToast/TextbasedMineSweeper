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

void displayBoard(Node[][Y]);
void displayBoardValues(Node[][Y]);
int hitMine(Node[][Y], int, int);

int main(void) {
  bool alive = false;
  Node board[X][Y] = {0};
  int userXvalue = -1;
  int userYvalue = -1;
  int flagCount = 0;
  char flag = 0;

  while (alive == false && flagCount != mineCount) { 
    system("clear");

    if (flagCount == mineCount) {
      // {Function to determine if game has been won}
    }

    printf("There are %d mines on the board\n", mineCount);

    displayBoard(board);
    while (userXvalue == -1 && userYvalue == -1) {
      printf("Place 'F' at beggining of your input to place/remove flag\n");
      printf("Enter X Y Coordiates: \n");
      scanf("%d%d%c", &userXvalue, &userYvalue, &flag); 
      //5 6F

      if (userXvalue > X || userYvalue > Y || userXvalue < 0 || userYvalue < 0) {
        printf("\033[1;31mINVALID COORDINATE \033[0m");
        userXvalue = -1;
        userYvalue = -1; 
      }

      else if (flag == 'f' || flag == 'F') {
        // {Function to place/remove flag}
        printf("YOU HAVE CHOSEN TO PLACE A FLAG\n");
        userXvalue = -1;
        userYvalue = -1;
        flag = 0;
      }
      else {
        alive = hitMine(board, userXvalue, userYvalue);

        if (alive == 0) {
          // {game over}
          printf("YOU HAVE HIT A MINE\n");
        }
        else {
          // {reveal spot}
        }

        userXvalue = -1;
        userYvalue = -1;
        
      }

      
    }
  
  }


  displayBoard(board);
  //displayBoardValues(board);
  return 0;
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
      
      printf("%i ", board[j][i].value);

    }
    printf("\n");
  }

}

int hitMine(Node board[][Y], int xValue, int yValue) {
  if (board[xValue][yValue].value == -1) {
    return true;
  }
  else {
    return false;
  }
  
}
