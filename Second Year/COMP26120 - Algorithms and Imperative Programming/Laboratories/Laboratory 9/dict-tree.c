#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "speller.h"
#include "dict.h"

typedef struct node *tree_ptr;
struct node 
{
  Key_Type element; // only data is the key itself
  tree_ptr left, right;
  // add anything else that you need
};

struct table 
{
  tree_ptr head; // points to the head of the tree
  // add anything else that you need
};

Table initialize_table(/*ignore parameter*/) 
{
	Table newTree = malloc(sizeof(struct table));
	newTree -> head = NULL;
	return newTree;
}

struct node *new_node(Key_Type k)
{
  struct node *newNode = malloc(sizeof(struct node));
  newNode -> element = strdup(k);
  newNode -> right = NULL;
  newNode -> left = NULL;
}

struct node *ins(tree_ptr nT, Key_Type k)
{
  if(nT == NULL)
    nT = new_node(k);
  else if(strcmp(k, nT->element) < 0)
    nT-> left = ins(nT->left,k);
  else if(strcmp(k, nT->element) > 0)
    nT->right = ins(nT->right, k);
}

Table insert(Key_Type k,Table newTree) 
{
  if(newTree -> head)
    ins(newTree ->head , k);
  else
    newTree-> head = new_node(k);
  return newTree;
}

Boolean find_node( Key_Type k, tree_ptr nT)
{
  if(nT == NULL)
    return FALSE;
  if(strcmp(k, nT-> element) <0 )
    return find_node(k, nT->left);
  else if(strcmp(k, nT-> element) >0 )
    return find_node(k, nT->right);
  else 
    return TRUE;
}


Boolean find(Key_Type k, Table newTree) 
{
  return find_node(k, newTree->head );
}


void print_table(Table newTree) 
{
  printf("The post_order traversal is:\n");
  tree_ptr tree_to_print = newTree ->head;
  post_order(tree_to_print);

}

void print_stats (Table newTree) 
{
  tree_ptr stats = newTree -> head;
  
  int depth = max_depth(stats);
  printf("The depth is: %d\n", depth);

}

void post_order(tree_ptr nT)
{
  if(nT == NULL)
    return 0;
  post_order(nT->left);
  post_order(nT->right);
  printf("%d", nT->element);
}

int max_depth(tree_ptr nT)
{
  if(nT == NULL)
    return 0;
  else
  {
    int left_depth = max_depth(nT -> left);
    int right_depth = max_depth(nT -> right);
    if(left_depth > right_depth)
      return(left_depth + 1);
    else
      return(right_depth + 1);
  }
}