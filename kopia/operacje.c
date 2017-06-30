#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#include "operacje.h"
#include "struct.h"

#define MAX_KOL 255.0f
#define MIN_KOL 0

/*************************************************************************************/

/*PROGOWANIE BIELI*/

void progowanie(dane_t *dane, int PROG){
  
  int i,j;

  for(i=0; i<dane->wymy; i++){
    for(j=0; j<dane->wymx; j++){
      
      if(dane->tablica[i][j]>=PROG)   /*MAX_KOL jeżeli L(x,y)>=PROG*/
	dane->tablica[i][j]=MAX_KOL;  /*L(x,y)  jeżeli L(x,y)> PROG*/
    }
  }
}

/*************************************************************************************/

/*KOREKCJA GAMMA*/

void korekcja(dane_t *dane, float GAMMA){

  int i,j;

  for(i=0; i<dane->wymy; i++){
    for(j=0; j<dane->wymx; j++){
      
      dane->tablica[i][j]=(powf(dane->tablica[i][j]/MAX_KOL,1.0f/GAMMA))*MAX_KOL;
    }
 }
}

/*************************************************************************************/

/*ROZMYWANIE W PIONIE*/

void rozmywanie(dane_t *dane){
  
  int i,j;
  
  for(i=1; i<(dane->wymy)-1; i++){
     for(j=0; j<(dane->wymx); j++){
      
        dane->tablica[i][j]=(1.0f/3.0f)*(dane->tablica[i-1][j] + dane->tablica[i][j] + dane->tablica[i+1][j]);
	  
    }
  }
}

/**************************************************************************************/

/*ROZCIĄGANIE HISTOGRAMU*/

void histogram(dane_t *dane){

  int max_wart=0, min_wart=255;

  int i,j;
  
  for(i=0; i<dane->wymy; i++){
    for(j=0; j<dane->wymx; j++){

      if(dane->tablica[i][j]>max_wart) /*Program szuka maksymalnego argumentu tablicy */
	{max_wart=dane->tablica[i][j];}                         
                                                            
      if(dane->tablica[i][j]<min_wart) /*Program szuka minimalnego argumentu tablicy  */
	{min_wart=dane->tablica[i][j];}
    }
  }

  for(i=0; i<dane->wymy; i++){
    for(j=0; j<dane->wymx; j++){
      
      dane->tablica[i][j]=(dane->tablica[i][j] - min_wart) * (MAX_KOL/(max_wart - min_wart));

    }
  }
}
