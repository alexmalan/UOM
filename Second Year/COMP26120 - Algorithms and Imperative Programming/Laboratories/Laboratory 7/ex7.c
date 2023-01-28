#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned long hcf(unsigned long a, unsigned long b)
{
  if(a >= b)
  {
    if(b == 0)
      return a;
    else
    {
      unsigned long r = a%b;
      return hcf(b, r);
    }
  }
  else
  {
    if(a == 0)
      return b;
    else
    {
      unsigned long r = b%a;
      return hcf(a, r);
    }
  }
}

unsigned long fme(unsigned long g, unsigned long x, unsigned long p)
{
  unsigned long s = 1;
  int i;

  if(p)
  {
    for(i =1; i <= x; i++)
      s = s * g % p;
    return s;
  }
  
  else
    return 1;


}

unsigned long dl(unsigned long y, unsigned long g, unsigned long p)
{
  unsigned long x;
  unsigned long temp = 0;
  for(x = 1; x <= p - 1; x++)
  {
    if(fme(g, x, p) == y)
      temp = x;
  }
    
  return temp;
}

unsigned long imp(unsigned long y, unsigned long p)
{
  return fme(y, p-2, p);
}

int main()
{
  unsigned long p = 65537;
  unsigned long g = 3;
  printf("Prime modulus is: %lu\n", p);
  printf("Prime root wrt %lu is %lu\n", p, g );
  
  while(1)
  {  
    printf("Choose: e (encrypt) | d (decrypt) | k ( get public key) | x (exit)? ");
    unsigned long privateKey;
    unsigned long publicKey;
    unsigned long secretNr;
    char optionChosen;
    unsigned long a;
    unsigned long b;

    scanf("%s", &optionChosen);
      
    if(strcmp(&optionChosen, "k") == 0)
    {
      printf("Type private key: ");
      scanf("%lu", &privateKey);
      if(privateKey > p)
        printf("The value chosen is bigger than the primitive root\n");
      else if(privateKey < 1)
        printf("The value chosen is smaller than one\n");
      else
      {
        publicKey = fme(g, privateKey, p);
        printf("Public key is: %lu\n", publicKey);
      }

    }

    else if(strcmp(&optionChosen, "e") == 0)
    {
      printf("Type secret number to send: ");
      scanf("%lu", &secretNr);
      if(secretNr > p)
        printf("The value chosen is bigger than the primitive root\n");
      else if(secretNr < 1)
        printf("The value chosen is smaller than one\n");
      else
       {
        printf("Type recipient's public key: ");
        scanf("%lu", &publicKey);
          
        srand(time(NULL));
        unsigned long randomVariable = (rand()% (p-1)) + 1;
        unsigned long randomPublicKey = fme(g, randomVariable, p);
        unsigned long encryptedMessage = ((secretNr % p) * fme(publicKey, randomVariable, p)) % p;

        printf("The encrypted secret is: (%lu, %lu)\n", randomPublicKey, encryptedMessage);
      }
    }

    else if(strcmp(&optionChosen, "d") == 0)
    {
      printf("Type in received message in form (a,b): \n");
      printf("a:");
      scanf("%lu", &a);
      printf("\nb:");
      scanf("%lu", &b );

      printf("Type in your private key: ");
      scanf("%lu", &privateKey);

      printf("The decrypted secret is: %lu\n", (b * imp(fme(a, privateKey, p), p) % p) );
    }

    else if(strcmp(&optionChosen, "x") == 0)
      return 0;
    else
      printf("Invalid command!\n");
  }
  
  return 0;
}