#include "graph.h"
/* Good luck */

List* list;


void depth_first_search(Graph* mygraph, int node, int list_r[])
{
    List* tr = mygraph->table[node].outlist;
    list_r[node] = 1;
    
    while (tr) {
        if (!list_r[tr->index]) {
            depth_first_search(mygraph, tr->index, list_r);
        }
        tr = tr->next;
    }
}

List* add(List* q, int node)
{
    if(q)
    {
        List* tr = q;
        while(tr->next)
        {
            tr = tr->next;
        }
        tr->next = (List*)malloc(sizeof(List));
        tr = tr->next;
        tr->index = node;
    }
    else{
        q = (List*)malloc(sizeof(List));
        q->index = node;
        return q;
    }
    return q;
}

List* rm(List* q)
{
    if(q)
    {
        List* tr = q->next;
        free(q);
        return tr;
    }
    else return NULL;
}

void rep(List* q, int node, int list_r[])
{
    list_r[node] = 1;
    list = add(q, node);
}

void breadth_first_search(Graph* mygraph, int node, int list_r[])
{
    rep(NULL, node, list_r);
    while (list) {
        int the_node = list->index;
        list = rm(list);
        List* tr = mygraph->table[the_node].outlist;
        while (tr) {
            if (!list_r[tr->index]) {
                rep(list, tr->index, list_r);
            }
            tr = tr->next;
        }
    }
}















