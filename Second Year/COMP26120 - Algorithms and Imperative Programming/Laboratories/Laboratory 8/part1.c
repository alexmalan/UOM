#include <stdlib.h>
#include <stdio.h>
#include <math.h>

FILE *fp;

typedef struct book
{
  double rating;
  double price;
  double relevance;
  int ID;
} B;

B *list;

int read_file(char *infile, int N)
{
  int c;
  if((fp=fopen(infile, "rb")))
    {
      fscanf(fp, "%*s\t%*s\t%*s\t%*s\n");
      c=0;
      while((!feof(fp))&&(c<N))
	{
	  fscanf(fp, "%lf\t%lf\t%lf\t%d\n", &list[c].rating,  &list[c].price, &list[c].relevance, &list[c].ID);	  
	  c++;
	}
      fclose(fp);      
    }
      else
    {
      fprintf(stderr,"%s did not open. Exiting.\n",infile);
      exit(-1);
    }
  return(c);
}

int comp_on_rating(const void *a, const void *b)
{
  if ((*(B *)a).rating < (*(B *)b).rating)
  {  
     return -1;
  }
    else 
  {
    if ((*(B *)a).rating > (*(B *)b).rating)
    {
      return 1;
    }
      else
    {
      return 0;
    }
  }  
}

int comp_on_relev(const void *a, const void *b)
{
 
  if ((*(B *)a).relevance < (*(B *)b).relevance)
  {  
     return -1;
  }
     else 
  {
     if ((*(B *)a).relevance > (*(B *)b).relevance)
     { 
       return 1;
     }
       else
     {
       return 0;
     }
  }  
}

int comp_on_price(const void *a, const void *b)
{
 
  if ((*(B *)a).price < (*(B *)b).price)
  { 
     return 1;
  }
     else 
  {
     if ((*(B *)a).price > (*(B *)b).price)
     {
       return -1;
     }
       else
     {
       return 0;
     }
  }  
}
B *temp;

void sort(int leftIndex, int middleIndex, int rightIndex, int(*compare)(const void *, const void *))
{
  int i, j, k;
i = 0;
j = leftIndex;

while(j <= middleIndex)
{
  temp[i++] = list[j++];
}
i = 0;
k = leftIndex;

while(k < j && j <= rightIndex)
if(compare(&temp[i], &list[j]) > 0)
  list[k++] = temp[i++];
else
  list[k++] = list[j++];
while(k<j)
  list[k++] = temp[i++];
}

void mysort(int leftIndex, int rightIndex, int(*compare)(const void *a, const void *b))
{
  if(leftIndex < rightIndex)
  {
    int middleIndex = (leftIndex + rightIndex)/2;

    mysort(leftIndex, middleIndex, compare);
    mysort(middleIndex + 1, rightIndex, compare);

    sort(leftIndex, middleIndex, rightIndex, compare);
  }

}

void user_interface(int N)
{

  // For Part 1 this function calls the sort function to sort on Price only
  mysort(0, N-1, comp_on_price);

  

  // For Part 2 this function
  // (1) asks the user if they would like to sort their search results
  // (2) asks for the most important field (or key), the next most etc
  // (3) calls your sort function
  

}
 

void print_results(int N)
{
    int i;
    if((fp=fopen("top20.txt","w")))
    {
      for(i=N-1;i>=N-20;i--)
      {  
	  printf("%g %g %g %d\n", list[i].rating, list[i].price, list[i].relevance, list[i].ID);
	  fprintf(fp, "%g %g %g %d\n", list[i].rating, list[i].price, list[i].relevance, list[i].ID);
	  
      }
      fclose(fp);
    }
      else
    {
      fprintf(stderr,"Trouble opening output file top20.txt\n");
      exit(-1);
    }

}


int main(int argc, char *argv[])
{
  int N;

  if(argc!=3)
    {
      fprintf(stderr, "./exec <input_size> <filename>\n");
      exit(-1);
    }

  N=atoi(argv[1]);

  list = (B *)malloc(N*sizeof(B));
  temp = (B*)malloc(((N+1)/2)*sizeof(B));
  
  N=read_file(argv[2], N);
  
  user_interface(N);
  
  print_results(N);

  return(0);
}

