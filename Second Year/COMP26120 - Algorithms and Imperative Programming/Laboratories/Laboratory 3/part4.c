#include <stdio.h>
#include <float.h>
#include <string.h>

//declare the two functions we are going to use
float c2f ( float c);
float f2c ( float f);
int main(int argc, char *argv[])
{
  char fArg[] = "-f";
  char cArg[] = "-c";
  
  float arg2;
  //convert a char to float
  sscanf(argv[2], "%f", &arg2);
  if(strcmp(argv[1], &cArg) == 0)
  {
    //if the parameter is -c converted to f
    float fValue = c2f(arg2);
    printf("%f C = ", arg2);
    printf("%f F\n", fValue);
  }
  else if(strcmp(argv[1], &fArg) == 0)
  {
    //else if the parameter is -f converted to c
    float cValue = f2c(arg2);
    printf("%f C = ", cValue);
    printf("%f F\n", arg2);
  }
  
}

//the two methods
float c2f ( float c)
{
  float f;
  f = 9*c/5 + 32;
  return f;
}
      
float f2c ( float f)
{
  float c;
  c = ((f-32) * 5)/9;
  return c;
}