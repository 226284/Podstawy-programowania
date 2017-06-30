#include <stdio.h>

int main(){
  
  int znak;
  
  for(;;){
    
    printf("\nProste menu:\n   1-Pozycja pierwsza\n   2-Pozycja druga\n   3-Pozycja trzecia\n   4-Zakończ działanie\n\nTwój wybór: ");
    
    scanf("%d",&znak);
      
      switch(znak)
	{
	case 1:
	  printf("\nWybrano pozycję 1\n");
	  break;

	case 2:
	  printf("\nWybrano pozycję 2\n");
	  break;

	case 3:
	  printf("\nWybrano pozycję 3\n");
	  break;

	case 4:
	  printf("\nKoniec działania programu\n");
	  return 0;
	  break;

	default:
	  printf("\nProszę podać poprawną liczbę!\n");
	  break;
    }
  }
}
