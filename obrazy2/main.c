#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#include "modul.h"

#define MAX 512            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */
#define MAX_KOL 255.0f
#define MIN_KOL 0


int main() {
  int obraz[MAX][MAX];
  int wymx,wymy,odcieni;
  int odczytano = 0;
  FILE *plik;
  FILE *plik2;
  char nazwa[100];
  char nazwa2[100];
  int opcja;
  int prog;
  float gamma;

  do{

    opcja=menu();

    switch(opcja)
    {
      case 1:
	  printf("\nWybrano pozycje 1 - Wczytywanie obrazu\n");
	  
	  /* Wczytanie zawartosci wskazanego pliku do pamieci */
	  printf("\nPodaj nazwe pliku do odczytu:\n");
	  scanf("%s",nazwa);
	  plik=fopen(nazwa,"r");

	  if (plik != NULL) {       /* co spowoduje zakomentowanie tego warunku */
	    odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
	    fclose(plik);
	  }
	    
	  printf(" NOTE: Obraz zostal wczytany");
	  break;

      case 2:
	  printf("\nWybrano pozycje 2 - (Pol)Progowanie bieli\n");
	  printf("\nPodaj prog bieli [0 - 100]:  ");
	  scanf("%d",&prog);
	  
	  prog=((255*prog)/100);
	  
	  progowanie(obraz,&wymx,&wymy,&odcieni,prog);
	  
	  printf(" NOTE: Obraz zostal zmodyfikowany");

	  break;

      case 3:
	  printf("\nWybrano pozycje 3 - Korekcja gamma\n");
	  
	  printf("\nPodaj wspolczynnik gamma: \n");
	  scanf("%f",&gamma);
	  
	  korekcja(obraz, &wymx, &wymy, gamma);

	  printf(" NOTE: Obraz zostal zmodyfikowany");
	  
	  break;
      
      case 4:
	  printf("\nWybrano pozycje 4 - Rozmywanie w pionie\n");
	
	  rozmywanie(obraz, &wymx, &wymy);
	  
	  printf(" NOTE: Obraz zostal zmodyfikowany");
	  break;

      case 5:
	  printf("\nWybrano pozycje 5 - Rozciaganie histogramu\n");
	  
	  histogram(obraz, &wymx, &wymy);
	  
	  printf(" NOTE: Obraz zostal zmodyfikowany");
	  break;

      case 6:
	  printf("\nWybrano pozycje 6 - Wyswietlanie oryginalnego obrazu\n");
	 
	  /* Wyswietlenie poprawnie wczytanego obrazu zewnetrznym programem */
	  if (odczytano != 0)
	  wyswietl(nazwa);
  
	  break;

      case 7:
	  printf("\nWybrano pozycje 7 - Zapis obrazu do pliku\n");

	  /* Zapisywanie zawartosci tablicy do pliku */
	  printf("\nPodaj nazwe pliku do zapisu:\n");
	  scanf("%s",nazwa2);
	  plik2=fopen(nazwa2,"w");
	  zapisz(plik2, obraz, &wymx, &wymy, &odcieni);

	  printf(" NOTE: Obraz zostal zapisany");
	  
  	  break;
	  
       case 8:
	  printf("\nKoniec dzialania programu\n");
	  return 0;
      
       default:
	  printf("\nProsze podac poprawna liczbe!\n");
	  break;
    }
  }while(1);
  
}
