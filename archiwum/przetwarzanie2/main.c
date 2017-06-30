/**************************************************************************************/
/*                       FUNKCJA GŁÓWNA ORAZ SPRAWOZDANIE                             */
/**************************************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

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
      progowanie(&dane, opcje.w_prog);

    else if (opcje.korekcja==1)
      korekcja(&dane, opcje.w_gamma);

    else if (opcje.rozmywanie==1)
      rozmywanie(&dane);

    else if (opcje.rozciaganie==1)
      histogram(&dane);

    zapisz(opcje.plik_wy,&dane);                            /* funkcja zapisująca */

    break;

  case -1:                                              /* opcje wywołujące błędy */
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

/**************************************************************************************/
/* SPRAWOZDANIE */

/* 
--------------- Michał Wieczorek, "Przetwarzanie obrazów 2", 13.01.2016 ----------------

Archiwum tar zawiera pliki:
 main.c      - Funkcja główna oraz sprawozdanie
 opcje.c     - Funkcje zerujące oraz przetwarzające opcje
 opcje.h     - Struktura do przetwarzania opcji
 operacje.c  - Funkcje przetwarzające obraz
 operacje.h
 struct.h    - Struktura do przechowywania obrazu
 wzw.c       - Funkcja wczytająca i zapisująca obraz
 wzw.h
 makefile

Do pisania programu użyłem kodów źródłowych ze strony Dr. Muszyńskiego: opcje.c oraz
odczyt.c

*/
/*

Aby poprawnie skompilować program należy wpisać w terminalu:
  make
A skompilować powtórnie należy użyć komendy:
  make clean; make

Uruchomienie programu:
  ./a.out -i [<nazwa obrazka do wczytania>.pgm || <nazwa obrazka do wczytania>.ppm]
       -o [<nazwa obrazka do zapisu>.pgm] -p [próg bieli](0-100) 
       -g [współczynnik gamma](>0) -r -h

Opcje: -i oraz -o należy podać obowiązkowo, pozostałe opcje można dodać opcjonalnie,
       należy jednak pamiętać aby podać tylko jedną z nich.

Testy działania programu:
  - do testów użyłem obrazków: kubus.pgm, Lena.pgm oraz Lena2.ppm

1) ./a.out -i kubus.pgm -o kubus2.pgm
      - powstaje nowy obraz kubus2.pgm identyczny do kubus.pgm

2) ./a.out -i kubus.pgm -o prog50.pgm -p 50
      - powstaje obraz prog50.pgm po operacji progowania na poziomie 50%

3) ./a.out -i kubus.pgm -o gamma05.pgm -g 0.5
      - powstaje obraz gamma05.pgm po korekcji gamma o współczynniku 0.5

4) ./a.out -i kubus.pgm -o rozmywanie.pgm -r
      - powstaje obraz rozmywanie.pgm o rozmyciu pionowym  o promieniu 1

5) ./a.out -i Lena.pgm -o histogram.pgm -h
      - powstaje obraz histogram.pgm który ma rozciągniety histogram
    
6) ./a.out -i
      - Komunikat: Brak nazwy

7) ./a.out 
      - Komunikat: Brak pliku

8) ./a.out dasdasdas
      - Komunikat: Niepoprawna opcja

9) ./a.out -i kubus.pgm
      - obraz zostaje wypisany na standardowym wyjściu

10) ./a.out -i Lena2.ppm -o Kolor.pgm
      - kolorowy obraz Lena2.ppm zostaje automatycznie zamieniony na czarno biały,
        oraz zapisany w pliku Kolor.pgm

11) ./a.out -i Lena2.ppm -o hist.pgm -h
      - obraz zostaje przerobiony na czarno biały oraz następuje rozciągniecie jego
        histogramu

 - Wnioski -
Po przeprowadzeniu powyższych testów stwierdzam, iż program działa prawidłowo. 

*/
