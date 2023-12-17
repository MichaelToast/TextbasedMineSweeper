#include <stdio.h>
#include <stdbool.h>
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

int main(void) {
  bool win = false;
  Node board[X][Y] = {0};

  displayBoard(board);
  displayBoardValues(board);
  printf("Hopefully this works\n");
  return 0;
}

void displayBoard(Node board[][Y])
{
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

void displayBoardValues(Node board[][Y])
{
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
