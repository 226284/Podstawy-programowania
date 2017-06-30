/**************************************************************************************/
/*                     FUNKCJA WCZYTUJĄCA I ZAPISUJĄCA OBRAZ                          */
/**************************************************************************************/
#include "wzw.h"
#include "struct.h"

#define DL_LINII 1000

/**************************************************************************************/
/*FUNKCJA WCZYTUJACA*/

int czytaj(FILE *plik_wej, dane_t *dane) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;
  char typ;                /* zmienna przechowująca czy format jest P2 czy P3 */
  int **r;                 /* tablice dla wczytania P3 */
  int **g;
  int **b;

  /*Sprawdzenie czy podano prawidłowy uchwyt pliku */
  if (plik_wej==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" */
  if (fgets(buf,DL_LINII,plik_wej)==NULL)/* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                            /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || ((buf[1]!='2') && (buf[1]!='3')) || koniec) { 
                                         /* Czy jest magiczne "P2" lub "P3"? */
                                         /* P3 dla obrazów kolorowych */ 
    fprintf(stderr,"Blad: To nie jest plik PGM lub PPM\n");
    return(0);
  }
  
  typ=buf[1];                             /* Zapamiętanie czy obraz jest P2 czy P3 */

  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_wej))=='#') {      /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_wej)==NULL) /* Przeczytaj ja do bufora */
	koniec=1;                           /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_wej);                /* Gdy przeczytany znak z poczatku linii */
    }                                       /* nie jest '#' zwroc go */
  } while (znak=='#' && !koniec);           /* Powtarzaj dopoki sa linie komentarza */
                                            /* i nie nastapil koniec danych */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_wej,"%d %d %d",&dane->wymx,&dane->wymy,&dane->szarosci)!=3){

    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }

  if(typ=='3'){  /* Jeśli P3 tworzymy 4 tablice: 3 do r,g,b oraz 1 dla czarno-białego */

  /* Tworzenie tablic dynamicznych dla wczytywanego obrazu */

  dane->tablica = (int**)malloc((dane->wymy)*sizeof(int*));    /* czarno-biały */
  r = (int**)malloc((dane->wymy)*sizeof(int*));                /* czerwony     */
  g = (int**)malloc((dane->wymy)*sizeof(int*));                /* zielony      */
  b = (int**)malloc((dane->wymy)*sizeof(int*));                /* niebieski    */
  
  for (i=0;i<dane->wymy;i++){
    dane->tablica[i] = (int*)malloc((dane->wymx)*sizeof(int)); /* to samo co   */
    r[i] = (int*)malloc((dane->wymx)*sizeof(int));             /* wyżej        */
    g[i] = (int*)malloc((dane->wymx)*sizeof(int));
    b[i] = (int*)malloc((dane->wymx)*sizeof(int));
  }
  
  /* Pobranie obrazu i zapisanie w tablicach r, g ,b */

  for (i=0;i<dane->wymy;i++) {
    for (j=0;j<dane->wymx;j++) {
      fscanf(plik_wej,"%d%d%d",&(r[i][j]),&(g[i][j]),&(b[i][j])); 
    }
  }
  fclose(plik_wej);                                  /* zamknięcie wczytywanego pliku */

  for (i=0;i<dane->wymy;i++) {
    for (j=0;j<dane->wymx;j++) {
      dane->tablica[i][j]=(r[i][j]+g[i][j]+b[i][j])/3; /* "przepisanie" kolorowego na */
    }                                                  /* szary obrazek               */
  }
  for (i=0;i<dane->wymy;i++){                /* tablice r g b, nie będą już potrzebne */
    free(r[i]); free(g[i]); free(b[i]);
  }

  free(r); free(g); free(b);
  
  return (dane->wymx)*(dane->wymy);   /* Czytanie zakonczone sukcesem    */
  }                                   /* Zwroc liczbe wczytanych pikseli */

  else{  /* Czyli P2 */
 
  /* Tworzenie tablicy dynamicznej dla wczytywanego obrazu */

  dane->tablica = (int**)malloc((dane->wymy)*sizeof(int*));
  
  for (i=0;i<dane->wymy;i++){
    dane->tablica[i] = (int*)malloc((dane->wymx)*sizeof(int));  }
  
  /* Pobranie obrazu i zapisanie w tablicy */
  for (i=0;i<dane->wymy;i++) {
    for (j=0;j<dane->wymx;j++) {
      if (fscanf(plik_wej,"%d",&(dane->tablica[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  fclose(plik_wej);
  return (dane->wymx)*(dane->wymy);   /* Czytanie zakonczone sukcesem    */
  }                                   /* Zwroc liczbe wczytanych pikseli */
}

/**************************************************************************************/
/* ZAPIS OBRAZU DO PLIKU */

void zapisz(FILE *plik_wyj, dane_t *dane){

int i,j;
  
  /* Wypisanie numeru magicznego, wymiarów i odcieni szarości obrazu */
  fprintf(plik_wyj, "P2\n#Przetworzony_obraz\n%d %d\n%d\n",   
	    dane->wymx, dane->wymy, dane->szarosci);
  
  /* Wypisanie samego obrazu */
  for (i=0;i<dane->wymy;i++) {
    for (j=0;j<dane->wymx;j++) {
	   
      fprintf(plik_wyj, "%3d ", dane->tablica[i][j]);

    }
  }
      
  fclose(plik_wyj);                 /* zamknięcie strumienia */

  for (i=0;i<dane->wymy;i++){       /* pamiętajmy o zwolnieniu wcześniej */

    free(dane->tablica[i]);         /* zaalokowanej pamięci */
  
  }

  free(dane->tablica);

  printf("Zakończono powodzeniem!\n"); /* końcowy komunikat :) */

}
/**************************************************************************************/
