#include "graph.h"

int main(int argc,char *argv[])
{
    Graph* mygraph;
    mygraph = (Graph*)malloc(sizeof(Graph));

  read_graph(mygraph,argv[1]);

  /* you take it from here */
    int index_d = 0;
    int index;
    int ok = 1;
    int temp;
    int min;
    int max;
    int minimum_index;
    int maximum_index;
    int vect[mygraph->MaxSize];
    List* node_outlist;
    
    while (ok) {
        if (mygraph->table[index_d].name) {
            ok = 0;
        }
        else
            index_d++;
    }
    temp = index_d;
    for (index=0; index<mygraph->MaxSize; index++) {
        vect[index] = 0;
    }
    
    for (index = 0; index< mygraph->MaxSize; index++) {
        node_outlist = mygraph->table[index].outlist;
        while (node_outlist) {
            vect[node_outlist->index] = vect[node_outlist->index] + 1;
            node_outlist = node_outlist->next;
        }
    }
    min = vect[0];
    max = vect[0];
    for(index = 1; index< mygraph->MaxSize; index++)
    {
        if ((min > vect[index] || min == 0) && vect[index] > 0) {
            min = vect[index];
            minimum_index = index;
        }
        if (max<vect[index]) {
            max = vect[index];
            maximum_index = index;
        }
    }
    
    printf("The maximum in degree is: %d - node: %s\n", max, mygraph->table[maximum_index].name);
    if(min == 0)
        printf("There is no node with in degree != 0");
    else
        printf("The minimum in degree is: %d - node: %s\n", min, mygraph->table[minimum_index].name);
    
    for(index = index_d; index < mygraph->MaxSize; index++)
        if(mygraph->table[index].out_degree > mygraph->table[index_d].out_degree)
            index_d = index;
    printf("The max out degree is: %d for the node: %s\n", mygraph->table[index_d].out_degree, mygraph->table[index_d].name);
    index_d = temp;
    
    for (index = index_d; index<mygraph->MaxSize; index++) {
        if (mygraph->table[index].out_degree > 0 && (mygraph->table[index].out_degree< mygraph->table[index_d].out_degree || mygraph->table[index_d].out_degree == 0)) {
            index_d = index;
        }
    }
    if (mygraph->table[index_d].out_degree == 0) {
        printf("There is no node with indegree != 0\n");
    }
    else
        printf("The miminum out degree is: %d for the node: %s\n", mygraph->table[index_d].out_degree, mygraph->table[index_d].name);
    
    
    return(0);
}
