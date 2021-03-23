#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Piece {
  int rank, file, id, hits[4];
};
void expandBoard (int ** arr, int col, int row);

int main(void) {
  int n = 0;
  int y = 0;
  int x = 0;

  int **myArray;
	myArray = calloc(10000,  sizeof(int *));

	if(myArray == NULL) {
		  printf("out of memory\n");
		  return 0;
		}
	for(int i = 0; i < 100; i++) {
		myArray[i] = calloc(100, sizeof(int*));
		  if(myArray[i] == NULL) {
        printf("out of memory\n");
        return 0;
			}
		}

  scanf("%d", &n);

  int maxCol = 100;
  int maxRow = 100;
  char rookPositions[n][2];
  //read in the values 
  for (int i = 0; i < n; i++) {
    scanf("%d %d", &y, &x);
  // check the number is inside of maxRow and MaxCol if not expando board 
    if (y > maxCol && x > maxRow) {
      maxCol = y;
      maxRow = x;
      expandBoard(myArray, maxCol, maxRow);
    } else if (y > maxCol) {
      maxCol = y;
      expandBoard(myArray, maxCol, maxRow);
    } else if (x > maxRow){
      maxRow = x;
      expandBoard(myArray, maxCol, maxRow);
    }
    
    rookPositions[i][0] = y - 1;
    rookPositions[i][1] = x - 1;

    // creating struct per piece
		struct Piece *n1 = (struct Piece *) malloc(sizeof(struct Piece));
		n1->id = i + 1; 
		n1->rank = y - 1; 
		n1->file = x - 1; 

    myArray[n1->rank][n1->file] = n1->id;
  }

  // analysis
  for (int i = 0; i < n; i++) {
    if (myArray[rookPositions[i][0]][rookPositions[i][1]] > 0) {
      int tempJ = rookPositions[i][0];
      int tempK = rookPositions[i][1];
      int hitCounter = 0;
      char hitsID[4];
      memset(hitsID, 0, sizeof(hitsID));


      while (tempJ - 1 >= 0) { // checking up
        tempJ = tempJ - 1;
        if (myArray[tempJ][tempK] > 0) {
          // add to myArray
          hitsID[0] = myArray[tempJ][tempK];
          hitCounter++;
          // printf("counter when checking up: %d\n", hitCounter);
          break;
        }
      } 
      tempJ = rookPositions[i][0];
      tempK = rookPositions[i][1];
      while (tempK - 1 >= 0) { // checking left
        tempK = tempK - 1;
        if (myArray[tempJ][tempK] > 0) {
          // add to myArray
          hitsID[1] = myArray[tempJ][tempK];
          hitCounter++;
          // printf("counter when checking left: %d\n", hitCounter);
          break;
        }
      } 
      tempJ = rookPositions[i][0];
      tempK = rookPositions[i][1];
      while (tempJ + 1 <= maxCol - 1) { // checking down
        tempJ = tempJ + 1;
        if (myArray[tempJ][tempK] > 0) {
          // add to myArray
          hitsID[2] = myArray[tempJ][tempK];
          hitCounter++;
          // printf("counter when checking down: %d\n", hitCounter);
          break;
        }
      } 
      tempJ = rookPositions[i][0];
      tempK = rookPositions[i][1];
      while (tempK + 1 <= maxRow - 1) { // checking right
        tempK = tempK + 1;
        if (myArray[tempJ][tempK] > 0) {
          // add to myArray
          hitsID[3] = myArray[tempJ][tempK];
          hitCounter++;
          break;
        }
      }

        // print answer 
        printf("%d ", hitCounter);
        if (hitsID[0] > 0) {
          printf("%d ", hitsID[0]);
        }
        if (hitsID[1] > 0) {
          printf("%d ", hitsID[1]);
        }
        if (hitsID[2] > 0) {
          printf("%d ", hitsID[2]);
        }
        if (hitsID[3] > 0) {
          printf("%d ", hitsID[3]);
        }
        printf("\n");

      }
    }

  free(myArray);
  return 0;
}

void expandBoard (int ** arr, int col, int row) {
  arr = realloc(arr, col * sizeof(int *));

  for(int i = 0; i < col; i++) {
		arr[i] = realloc(arr[i], row * sizeof(int*));
		  if(arr[i] == NULL) {
        fprintf(stderr, "out of memory\n");
			}
		}
}
