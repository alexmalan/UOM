#include "graph.h"
#include <string.h>

int initialize_graph (Graph *mygraph, int MaxSize) 
{
  // your code goes here
    mygraph->MaxSize = MaxSize;
    mygraph->table = (Node*)malloc(mygraph->MaxSize * sizeof(Node));
    printf("The maximum size is initialized: %d\n", mygraph->MaxSize);
    
}
int insert_graph_node (Graph *mygraph, int n, char *name) 
{
  // your code goes here
    if( n >= mygraph->MaxSize)
        printf("The insertion cannot be made as the size is to small for the index.\n");
    else
    {
        mygraph->table[n].name= strdup(name);
        mygraph->table[n].outlist = NULL;
        mygraph->table[n].out_degree = 0;
    }
    
}
int insert_graph_link (Graph *mygraph, int source, int target)
{
  // your code goes here
    mygraph->table[source].out_degree = mygraph->table[source].out_degree + 1;
    
    List *it = mygraph->table[source].outlist;
    
    if(it)
    {
        while (it->next) {
            it = it->next;
        }
        it->next = (List*)malloc(sizeof(List));
        it = it->next;
        it->index = target;
    }

    else
    {
        mygraph->table[source].outlist = (List*)malloc(sizeof(List));
        it = mygraph->table[source].outlist;
        it->index = target;
    }
}
// use to check result of strdup, malloc etc.
void check (void *memory, char *message) 
{
  if (memory == NULL) 
  {
    fprintf (stderr, "Can't allocate memory for %s\n", message);
    exit (3);
  }
}
int read_graph (Graph *mygraph, char *filename)
/* 
 * Reads in graph from FILE *filename which is of .gx format.
 * Stores it as Graph in *mygraph. 
 * Returns an error if file does not start with MAX command,
 * or if any subsequent line is not a NODE or EDGE command. 
 * Does not check that node numbers do not exceed the maximum number
 * Defined by the MAX command. 
 * 8/2/2010 - JLS
 */
{
  FILE *fp;
  char command[80], name[80];
  int i, s, t;
  fp= fopen (filename, "r");
  if (fp==NULL) 
  {
    fprintf(stderr,"cannot open file %s\n", filename);
    return -1;
  }
  printf ("Reading graph from %s\n", filename);
  fscanf (fp,"%s", command);
  if (strcmp (command, "MAX")!=0) 
  {
    fprintf (stderr, "Error in graphics file format\n");
    return -1;
  } 
  else 
  {
    fscanf (fp, "%d", &i);
    initialize_graph (mygraph, i+1); // +1 so nodes can be numbered 1..MAX
    while (fscanf (fp, "%s", command)!=EOF) 
    {
      if (strcmp (command, "NODE")==0) 
      {
        fscanf (fp, "%d %s", &i, name);
        insert_graph_node (mygraph, i, name);
      } 
      else 
      {
        if (strcmp (command, "EDGE")==0) 
        {
          fscanf (fp, "%d %d", &s, &t);
          insert_graph_link (mygraph, s, t);
        } 
        else 
        {
          return -1;
        }
      }
    }
  }
  return 0;
}
void print_graph (Graph *mygraph)
/* 
 * Prints out Graph *mygraph to the stdout in .gx format - JLS
 */
{
  int i;
  List *current;
  printf ("MAX %d\n", mygraph->MaxSize);
  for (i=0; i<mygraph->MaxSize; i++)
    if (mygraph->table[i].name!=NULL) 
    {
      printf ("NODE %d %s\n", i, mygraph->table[i].name);
      current= mygraph->table[i].outlist;
      while (current!=NULL) 
      {
        printf ("EDGE %d %d\n", i, current->index);
        current= current->next;
      }
    }
}
