#ifndef OPCJE_H
#define OPCJE_H

#include <stdio.h>
#include <string.h>

/* strukura do zapamietywania opcji podanych w wywolaniu programu */
typedef struct {
  FILE *plik_we, *plik_wy;        /* uchwyty do pliku wej. i wyj. */
  int progowanie, korekcja, rozmywanie, rozciaganie;     /* opcje */
  int w_progu;              /* wartosc progu dla opcji progowanie */
  int w_gamma;              /* wartość gamma dla korekcji         */
} opcje_t;

void wyzeruj_opcje(opcje_t *opcje);

int przetwarzaj_opcje(int argc, char **argv, opcje_t *opcje);

#endif
