#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
//declaring three indexes that will serve us as counters for the characters
int index1, index2, index3;
int main (int argc, char *argv[])
{
  char argInput[20];
  char argOutput[20];
  int c;
  char *filename = argInput;

  //inut the input file
  printf("Type in your input file:\n");
  scanf("%s", argInput);
  
  //set the readeble file
  FILE *stream = fopen(filename, "r");
  if (!stream) 
  {
    //if you cannot read from file output this message
    fprintf(stderr, "can't open %s for reading\n", filename);
    exit(-1);
  }

  //input the output file
  char *filenameOutput = argOutput;

  printf("Type in your output file:\n");
  scanf("%s", argOutput);

  //set the writable file
  FILE *streamOutput = fopen(filenameOutput, "w");
  if (!streamOutput)
  {
    //if you cannot write in the file output this message
    fprintf(stderr, "can't open %s for writing\n", filenameOutput);
    exit(-1);
  }

  //while you still can read characters
  while((c = getc(stream))!=EOF)     
  {
    //the charachter counter increases
    index1++;
    //if the character is low upper it and count it
    if(islower(c) )
    {  
      putc(toupper(c), streamOutput);
      index2++;
    }
    //otherwise lower it
    else if(isupper(c))
    {  
      putc(tolower(c),streamOutput);
      index3++;
    }
    //else leave it like it is
    else 
      putc(c, streamOutput);
  }
  

  index1 = index1 + 1;
  //print in file the number of characthers
  fprintf(streamOutput,"\nRead %d",index1 );
  fprintf(streamOutput," characters in total, %d converted to uppercase,", index2);
  fprintf(streamOutput," %d to lower case\n", index3);

  fclose(stream);
  fclose(streamOutput);

  return(0);

}