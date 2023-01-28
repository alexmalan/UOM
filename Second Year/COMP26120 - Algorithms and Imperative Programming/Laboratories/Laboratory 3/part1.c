#include <stdio.h>
int numberOfElements, index;
int main()
{
  #define array_size 100
  //declare the arrays
  int array1[array_size] = {1, 3, 4, 8, 2};
  int array2[array_size] = {5, 32, 66, 100, 54, 333, 56};
  int array3[array_size] = {444, 23, 5, 4, 9, 10, 11, 43, 33, 78}; 
  //call the function for the arrays
  int largestElementOfTheArray1 = largest(array1, 5);
  int largestElementOfTheArray2 = largest(array2, 7);
  int largestElementOfTheArray3 = largest(array3, 10);

  //output the largest element of every array
  printf("The largest element of the array1 is on position:%d\n",
                       largestElementOfTheArray1 );
  printf("The largest element of the array2 is on position:%d\n",
                       largestElementOfTheArray2 );
  printf("The largest element of the array3 is on position:%d\n",
                       largestElementOfTheArray3 );
  return 0;
}

int largest(int a[100], int n)
{
  //set a max
  int max=0;
  int indexOfLargest;
  int index;
  for(index = 0; index< n; index++)
  {
    //find te max and stock its index
    if(a[index] >= max)
    {
      max = a[index];
      indexOfLargest = index;
    }
      
  }
  //return the index

  return indexOfLargest;
}