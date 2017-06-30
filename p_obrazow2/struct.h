#ifndef STRUCT_H
#define STRUCT_H

  typedef struct{

    int szarosci;     /* Liczba odcieni szarości */
    int wymx;         /* Szerokość obrazka */
    int wymy;         /* Wysokość obrazka */
    int **tablica;     /* Tablica dla obrazu */

  }dane_t;
/*
  typedef struct{

    int r;
    int g;
    int b;

  }pixel;
*/
#endif
