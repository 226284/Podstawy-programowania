#ifndef WZW_H
#define WZW_H

#include<stdio.h>
#include<stdlib.h>

#include "struct.h"

/******************************************************************************/

int czytaj(FILE *plik_wej, dane_t *dane);

void zapisz(FILE *plik_wyj, dane_t *dane);

#endif

/******************************************************************************/
