#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* these arrays are just used to give the parameters to 'insert',
   to create the 'people' array 
*/

#define HOW_MANY 7
char *names[HOW_MANY]= {"Simon", "Suzie", "Alfred", "Chip", "John", "Tim",
		      "Harriet"};
int ages[HOW_MANY]= {22, 24, 106, 6, 18, 32, 24};

/* declare your struct for a person here */
struct person
{
  /* data */
  char name[20];
  int age;
}*people[100];


static void insert(struct person *people[100], char *name, int age, int *nextfreeplace) 
{
  /* put name and age into the next free place in the array parameter here */
  /* modify nextfreeplace here */
  people[*nextfreeplace] = (struct person *) malloc(sizeof(struct person));
  while(people[*nextfreeplace] != NULL)
  {strcpy(people[*nextfreeplace]->name, name);
  people[*nextfreeplace]->age = age;
  (*nextfreeplace)++;}
}

int main(int argc, char **argv) 
{

  /* declare the people array here */
  int *nextfreeplace = 0;

  for (int index = 0; index <HOW_MANY; index++)
  {
    insert (people, names[index], ages[index], &nextfreeplace);
  }

  /* print the people array here*/
  for(int index = 0; index < HOW_MANY; index++ )
    printf("Name: %s Age: %d\n", people[index]->name, people[index]->age);

  for(int index = 0;index < HOW_MANY; index++)
    free(people[index]);
  return 0;
}
