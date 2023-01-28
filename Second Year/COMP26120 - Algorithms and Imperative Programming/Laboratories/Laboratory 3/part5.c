#include <stdio.h>  
#include <stdlib.h> 
#include <math.h> 

int main(int argc, int *argv[])
{
  //read the file from the keyboard
  char *filename = argv[1];
  int c, count[100] = {0};

  FILE *stream = fopen(filename, "r");
  //if the stream cannot be oppened for reading output this message
  if(!stream)
  {
    printf(stderr,"can't open %s for reading\n", filename );
    exit(-1);
  }
  //else

  while((c = getc(stream))!=EOF)
  {
    //while you can read from the file, chec if the characters are from 
    //the range and he count them
    if(c >= 32 && c <= 126)
      count[c-32] ++; 
  }
  //now if the caracter appear once or more print them

  for(c = 0; c<= 95; c++)
  {
    if(count[c] != 0)
      printf("%d instances of character [%c]\n", count[c], ((char)c)+32);
  }
  return 0;
}