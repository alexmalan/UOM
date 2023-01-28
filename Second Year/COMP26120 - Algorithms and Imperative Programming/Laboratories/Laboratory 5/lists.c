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
 enum staff_or_student{staff, student, neither};
 enum staff_or_student array_staff_student[HOW_MANY] = {staff, student, staff, student, neither, neither, student};
 char *programme_name_and_room[HOW_MANY] = {"LF31", "CS", "LF15", "AI", "nothing", "nothing", "HCI"};
/* declare your struct for a person here */
struct person
{
  /* data */
  char* name;
  int age;
  struct person* next;
  enum staff_or_student identity;
  union data {
  char* programme_name;
  char* room_number;
  }personData;
};
struct person* people = NULL;

static struct person* insert_start(struct person* people, char *name, int age)
{
  /* put name and age into the next free place in the array parameter here */
  /* modify nextfreeplace here */
  struct person* newPerson = (struct person* )malloc (sizeof(struct person));
  if(newPerson == NULL)
    fprintf(stderr, "The allocation failed");

  newPerson->name = name;
  newPerson->age = age;
  newPerson->next = people;
  return newPerson;
}

static struct person* insert_end(struct person* people, char *name, int age)
{
  if(people == NULL)
    return insert_start(people, name, age);
  else
  {
  struct person* newPerson = (struct person* )malloc (sizeof(struct person));
  if(newPerson == NULL)
    fprintf(stderr, "The allocation failed");

  struct person* goTroughList = people;
  while(goTroughList->next != NULL)
    goTroughList = goTroughList->next;
  goTroughList->next = newPerson;

  newPerson->name = name;
  newPerson->age = age;
  newPerson->next = NULL;
  }
  return people;
}
static int compare_people_by_name(struct person* person, struct person* personAux)
{
  return strcmp(person->name, personAux->name);
}
static int compare_people_by_age(struct person* person, struct person* personAux)
{
  return person->age - personAux->age ;
}

static struct person* insert_sorted(struct person* people, char *name, int age, int(*compare_people)(struct person*, struct person*), enum staff_or_student array_staff_student, char *programme_name_and_room)
{

  struct person* newPerson = (struct person* )malloc (sizeof(struct person));
  if(newPerson == NULL)
    fprintf(stderr, "The allocation failed");

  newPerson->name = name;
  newPerson->age = age;
  if(array_staff_student == staff)
  {
    newPerson-> identity = staff;
    newPerson-> personData.room_number = programme_name_and_room;
  }
  else if (array_staff_student == student)
  {
    newPerson-> identity = student;
    newPerson-> personData.programme_name = programme_name_and_room;
  }
  else
    newPerson -> identity = neither;
  struct person* aux = people;
  if(aux == NULL || (aux != NULL && (*compare_people)(newPerson, aux)< 0 ))
  {
    newPerson->next = aux;
    return newPerson;
  }
  else
  {
    while (aux->next != NULL && (*compare_people)(newPerson, aux->next) >= 0)
      aux = aux->next;
    newPerson->next = aux->next;
    aux->next = newPerson;
    return people;
  }

  return people;
}
int main(int argc, char **argv)
{
  int index;
  /* declare the people array here */
  struct person* people = NULL;
  for (index = 0; index <HOW_MANY; index++)
  {
    people = insert_sorted (people, names[index], ages[index], compare_people_by_age, array_staff_student[index], programme_name_and_room[index]);
  }

  /* print the people array here*/
  struct person* aux = people;
  for(index = 0; index < HOW_MANY; index++ )
    {
      if(aux->identity == staff)
        printf("Name: %s Age: %d Room Number: %s\n", aux->name, aux->age, aux->personData.room_number);
      else if (aux->identity == student)
        printf("Name: %s Age: %d Student in: %s\n", aux->name, aux->age, aux->personData.programme_name);
      else
        printf("Name: %s Age: %d Isn't student or staff\n", aux->name, aux->age);

    aux = aux->next;
    }
    aux = people;
  for(index = 0;index < HOW_MANY; index++){
      aux = people->next;
    free(people);
    people = aux;
  }
  return 0;
}
