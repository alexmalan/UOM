#include <stdio.h>
#include <string.h>

int main(int argc, int *argv[])
{
  int index, maximumParameter;
  if(argc > 1)
  {
    //if there are parameters besides the executable
    maximumParameter = 1;
    for(index = 1; index < argc; ++index )
    {
      //we find the maximum one
      if(strlen(argv[index]) >= strlen(argv[maximumParameter]))
        maximumParameter = index;
    }
    //and then output it
    printf("The longest parameter is <%s>\n", argv[maximumParameter] );
  }
  else
    printf("There are no parameters\n");
}