#include <stdio.h>
//do an enum for black and wite
enum colour {
  white =0 ,
  black= 1,
};
int main()
{
  //set an arra
  int numberOfRows, numberOfColumns, indexOfRows, indexOfColumns;
  int array[10][10];
  //and keep calling the unction to make a chessboard
  chessBoard(array, 2, 3);
  //then output it
  for(indexOfRows = 0; indexOfRows < 2; indexOfRows++)
  {
    for(indexOfColumns = 0; indexOfColumns < 3; indexOfColumns++)
      printf("%d ", array[indexOfRows][indexOfColumns]);
      printf("\n");
      
  }
  printf("%s\n", " " );
  chessBoard(array, 9, 9);

  for(indexOfRows = 0; indexOfRows < 9; indexOfRows++)
  {
    for(indexOfColumns = 0; indexOfColumns < 9; indexOfColumns++)
      printf("%d ", array[indexOfRows][indexOfColumns]);
      printf("\n");
      
  }
  printf("%s\n", " " );

  chessBoard(array, 10, 7);
  for(indexOfRows = 0; indexOfRows < 10; indexOfRows++)
  {
    for(indexOfColumns = 0; indexOfColumns < 7; indexOfColumns++)
      printf("%d ", array[indexOfRows][indexOfColumns]);
      printf("\n");
      

  }
  printf("%s\n", " " );

}

void chessBoard(int a[10][10], int n, int m)
{
  for(int i =0; i< n; i++)
  {
    for(int j = 0; j<m; j++)
    {
      //here if a cell has its indexes with the same parity then it should have
      //white and if not it should have black
      if(i%2 == 1 && j % 2 == 1)
        a[i][j] = 0;
      else if(i%2 == 1 && j % 2 == 0)
        a[i][j] = 1;
      else if(i % 2 == 0 && j % 2 == 0)
        a[i][j] = 0;
      else if(i % 2 == 0 && j % 2 == 1)
        a[i][j] = 1;
    }
  }

}