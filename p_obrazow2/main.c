#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

/*ZAWARCIE WSZYTKICH PLIKÓW NAGŁÓWKOWYCH*/

#include "operacje.h"
#include "wzw.h"
#include "struct.h"
#include "opcje.h"

/*************************************************************************************/

/*FUNKCJA GŁÓWNA*/

int main(int argc, char **argv) {

  opcje_t opcje;
  dane_t dane;

  switch (przetwarzaj_opcje(argc,argv,&opcje)){

  case 0:                                             /* 0 - poprawne wczytanie opcji */
    
    czytaj(opcje.plik_we, &dane);                           /* funkcja wczytująca */

    if (opcje.progowanie==1)
      progowanie(&dane, opcje.w_progu);

    else if (opcje.korekcja==1)
      korekcja(&dane, opcje.w_gamma);

    else if (opcje.rozmywanie==1)
      rozmywanie(&dane);

    else if (opcje.rozciaganie==1)
      histogram(&dane);

    zapisz(opcje.plik_wy,&dane);                            /* funkcja zapisująca */

    break;

  case -1: 
    fprintf(stderr,"Niepoprawna opcja\n");
    break;

  case -2: 
    fprintf(stderr,"Brak nazwy\n");
    break;

  case -3: 
    fprintf(stderr,"Brak wartosci\n");
    break;

  case -4: 
    fprintf(stderr,"Brak pliku\n");
    break;
  }
  
  return 0;
}
