#include <stdio.h>

int main(){
  
  #define prog 20 
  int a;    
  
  printf("\n");
  printf("Program wczytuje aktualną temperaturę, a następnie ją porównuje\n\n");
  printf("Podaj temperaturę we Wrocławiu:  ");
  scanf("%d",&a);

  if(a<prog) printf("Nie jest zbyt ciepło!\n");
  else printf("Jest bardzo ładna pogoda!\n\n");

  return 0;
}
