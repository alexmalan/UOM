#include "graph.h"
#include <string.h>

int main(int argc, int *argv[])
{
  Graph* mygraph;
  mygraph = (Graph*)malloc(sizeof(Graph));

  read_graph(mygraph, argv[2]);
  int index_d = 0;
  int counter = 0;
  int list_r[mygraph->MaxSize];
  int index;

  while(0==0)
  {
    if(mygraph->table[index_d].name !=NULL)
      break;
    else
      index_d++;
  }

  if(strcmp(argv[1], "-depth") == 0)
    printf("Depth First Search:\n");
  else if(strcmp(argv[1], "-breadth") == 0)
    printf("Breadth First Search\n");

  for(index = index_d; index < mygraph->MaxSize;index++)
    if(mygraph->table[index].out_degree > 0 && (mygraph->table[index].out_degree < mygraph->table[index_d].out_degree || mygraph->table[index_d].out_degree == 0))

  printf("The smallest out degree is: %d for node %s \n",mygraph->table[index_d].out_degree, mygraph->table[index_d].name );

  for(index = 0; index < mygraph->MaxSize; index++)
    list_r[index] = 0;

  if(strcmp(argv[1], "-depth") == 0)
    depth_first_search(mygraph, index_d, list_r);
  else if(strcmp(argv[1], "-breadth") == 0)
    breadth_first_search(mygraph, index_d, list_r);

  for(index = 0; index < mygraph->MaxSize; index++)
    if(list_r[index] == 1)
      counter++;

  for(index = 0; index < mygraph->MaxSize;index++)
    if(mygraph->table[index_d].name !=NULL && list_r[index] == 1)
    {  index_d = index;
      break;
    }

  for(index = index_d; index < mygraph->MaxSize;index++)
    if(list_r[index] == 1 && mygraph->table[index].out_degree > mygraph->table[index_d].out_degree)
      index_d = index;
  printf("The Highest out degree %d is for node %s\n",mygraph->table[index_d].out_degree, mygraph->table[index_d].name );
  printf("Nr of nodes reachable: %d\n", counter);



}