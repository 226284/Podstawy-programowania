#include <stdio.h>

#define WIERSZE 3
#define KOLUMNY 7

int tab[10][10];

void wypelnij(int tab[10][10])
{
  int i,j;

  for(i=0;i<WIERSZE;i++)/*wiersze*/
    {
      for(j=0;j<KOLUMNY;j++)/*kolumny*/
	{
          tab[i][j]=i*j;
	}
    } 
}

void wypisz(int tab[10][10])
{
  int i,j;
    
  for(i=0;i<WIERSZE;i++)/*wiersze*/
    {
      for(j=0;j<KOLUMNY;j++)/*kolumny*/
	{
          printf("%3d ",tab[i][j]);
	}
      printf("\n");
    } 
}

void zmien_znaki(int tab[10][10])
{
  int i,j;
  
    for(i=0;i<WIERSZE;i++)/*wiersze*/
    {
      for(j=0;j<KOLUMNY;j++)/*kolumny*/
	{
	  tab[i][j]=tab[i][j]*(-1);
	}
    } 
}
int main(void){
  
  int tab[10][10];
  
  printf("\n");
  wypelnij(tab);
  printf("Zawartość oryginalna:\n");
  wypisz(tab);
  zmien_znaki(tab);
  printf("Zawatość po zmianie znaków:\n");
  wypisz(tab);
  printf("\n");
  
  return 0;
}
