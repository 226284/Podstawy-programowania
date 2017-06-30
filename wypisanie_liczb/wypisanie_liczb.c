#include <stdio.h>

int main()
{
  int i=1;
  
  printf("\n");
  printf("Program wypisuje liczby od 1 do 99\n\n");
  
  for(i=1;i<100;i++) 
  {
    printf("%2d   ",i);
    
    if(i%10==0) printf("\n");
  }
  printf("\n");

  return 0;
}
