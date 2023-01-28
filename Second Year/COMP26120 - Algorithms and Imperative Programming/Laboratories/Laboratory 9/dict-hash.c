#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>
#include <math.h>

#include "speller.h"
#include "dict.h"
typedef struct 
{ // hash-table entry
  Key_Type element; // only data is the key itself
  enum {empty, in_use, deleted} state;
} cell;

typedef unsigned int Table_size; // type for size-of or index-into hash table

struct table 
{
  cell *cells; Table_size table_size; // cell cells [table_size];
  Table_size num_entries; // number of cells in_use
  // add anything else that you need
};

int a;
int b;
collusions = 0;


// unsigned int randomInterval(unsigned int minimum, unsigned int maximum)
// {
//   int randomVariable;
//   const unsigned int interval = 1 + maximum - minimum;
//   const unsigned int bucket = max_random / range; 
//   const unsigned int lim = bucket * range;

//   do randomVariable = rand();
//   while(randomVariable >= lim)
//     return min + (r/ bucket);
  
// }

// int random_initialise()
// {
//   a = 
// }

// int compressmap(Key_Type k)
// {
//   return abs(a * k + b) % 3;
// }

int hashFunc(Key_Type k, Table t)
{
   int s = 0;
   int sz  = strlen(k);
   int index;
   int pl;
  for(index = 0; index < strlen(k); index++)
    pl = sz - index - 1;
    s = s + k[index] * pow(3,pl);

  unsigned int a = 30;
  unsigned int b = 9;
  while(a % strlen(k) == 0)
    a++;
  

  int key = (abs(a *s+b)) % t-> table_size;

  return key; 

}

Table initialize_table (Table_size size) 
{

  Table newTable = malloc(sizeof(struct table));
  newTable -> table_size =size;
  newTable -> num_entries = 0;
  newTable -> cells = (cell*)(malloc(size*sizeof(cell)));
  for(int index = 0; index < size; index++)
  {
    newTable ->cells[index].element = NULL;
    newTable -> cells[index].state = empty;
  }
  return newTable;
}

Table ins(int v, Key_Type k, Table t){
  t->cells[v].element = (Key_Type)(malloc((strlen(k) + 1) * sizeof(Key_Type)));
  strcpy(t->cells[v].element, k);
  t-> cells[v].state = in_use;
  t->num_entries++;
  return t;
}


Table linear_probing(Key_Type k, Table t)
{
  int index = 1;
  int ok = 0;
  int v = hashFunc(k,t);

  if(t-> cells[v].state == empty)
    ins(v,k,t);
  else
  {
    if(strcmp(t->cells[v].element, k) == 0)
      ok = 1;
    else
    {
      collusions++;
      while(ok ==0)
      {
        if(t->cells[(v+index) % t->table_size].state == in_use )
          index++;
        else
        {
          ins(v+index, k, t);
          ok = 1;
        }
      }
    }
  }
  return t;
}

Table quadradic_probing(Key_Type k, Table t)
{
  int index = 1;
  int ok = 0;
  int v = hashFunc(k, t);
  if(t->cells[v].state == empty)
    ins(v, k, t);
  else
  {
    if(strcmp(t->cells[v].element, k) == 0)
      ok = 1;
    else
    {
      collusions++;
      while(ok = 0)
      {
        if(t-> cells[(v+ index*index) % t->table_size].state == in_use)
          index++;
        else
        {
          ins(v + index * index, k, t);
          ok = 1;
        }
      }
    }
  }
  return t;
}

Table insert (Key_Type k, Table t) 
{
  int i = 0;
  //k = hashFunc (key, newTable-> table_size);

  // while(newTable -> cells[h].key != 0 && (i< newTable-.table_size))
  // {
  //   if(newTable -> cells[h].key == key)
  //   {
  //     newTable -> cells[h].
  //   }
  // }
  if(t->num_entries == t->table_size)
  {
    printf("Error! The size of the table is exceded!");
    exit(0);
  }

  if(mode != 1 || mode != 3)
    return linear_probing(k,t);
  else if(mode == 1|| mode == 3)
    return quadradic_probing(k,t);
}



Boolean find (Key_Type k, Table t) 
{
  int hash = hashFunc(k,t);
  int index;

  if(t->cells[hash].state == in_use && strcmp(t->cells[hash].element,k) == 0)
    return TRUE;
  else{
    for(index = hash + 1; index <= t->table_size; index++ )
    {
      if(t->cells[index].state == in_use && strcmp(t->cells[index].element, k)==0)
        return TRUE;
    }
    if(index == t->table_size + 1)
      for(index = 0; index < hash; index++)
        if(t->cells[index].state == in_use && strcmp(t->cells[index].element,k) == 0)
          return TRUE;

  }
  return FALSE;
}

void print_table (Table t) 
{
  for(int index = 0; index <=t -> table_size; index++)
    if(t -> cells[index].state != empty)
    {
      printf("%d%s\n", index, t -> cells[index].element);
    }
}

void print_stats (Table t) 
{
  printf("Table size: %d\n", t -> table_size);
  printf("Number of entries: %d\n", t->num_entries);
}
