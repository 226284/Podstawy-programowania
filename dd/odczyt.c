#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define MAX 512            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */

/************************************************************************************
 * Funkcja wczytuje obraz PGM z pliku do tablicy       	       	       	       	    *
 *										    *
 * \param[in] plik_we uchwyt do pliku z obrazem w formacie PGM			    *
 * \param[out] obraz_pgm tablica, do ktorej zostanie zapisany obraz		    *
 * \param[out] wymx szerokosc obrazka						    *
 * \param[out] wymy wysokosc obrazka						    *
 * \param[out] szarosci liczba odcieni szarosci					    *
 * \return liczba wczytanych pikseli						    *
 ************************************************************************************/

int czytaj(FILE *plik_we,int obraz_pgm[][MAX],int *wymx,int *wymy, int *szarosci) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;

  /*Sprawdzenie czy podano prawid�owy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien by� P2 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || (buf[1]!='2') || koniec) {  /* Czy jest magiczne "P2"? */
    fprintf(stderr,"Blad: To nie jest plik PGM\n");
    return(0);
  }

  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d",wymx,wymy,szarosci)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i=0;i<*wymx;i++) {
    for (j=0;j<*wymy;j++) {
      if (fscanf(plik_we,"%d",&(obraz_pgm[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  return *wymx**wymy;   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */


/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */
void wyswietl(char *n_pliku) {
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}

void negatyw(int obraz_pgm[][MAX],int *wymx,int *wymy, int *szarosci)

{
  int i,j;
  //int (*obraz_pgm)[obraz->wymy];


  //obraz_pgm = (int(*)[obraz->wymy]) obraz->obraz_pgm;
  for(i=0; i<(*wymx); i++) {
    for(j=0; j<(*wymy); j++) {
      obraz_pgm[i][j]=(*szarosci)-obraz_pgm[i][j];
    }
  }
}


int zapis(int obraz_pgm[][MAX], int *wymx, int *wymy, int *szarosci)

{

  int i,j;
  FILE *plik;
  char nazwa[100];



  printf("Podaj nazwe pliku\n");
  scanf("%s",nazwa);
  plik=fopen(nazwa,"w");


  fprintf(plik, "P2\n%d %d\n%d ",*wymx,*wymy,*szarosci);


  for (j=0;j<(*wymx);j++){
    for (i=0;i<(*wymy);i++){
	  fprintf(plik, "%d ",obraz_pgm[j][i]);
	}
    }
  return 0;
} 

void konturowanie(int obraz_pgm[][MAX], int *wymx, int *wymy,int *szarosci){

  int i,j;

  for(i=0; i<(*wymx); i++) {
    for(j=0; j<(*wymy); j++){
      //printf("CHUJ!!\n");
      if(i==(*wymx-1)){   
      if(j==(*wymy-1)){
      obraz_pgm[i][j]=obraz_pgm[i][j];  /*Warunek ostatni wiersz i kolumna*/
      } else obraz_pgm[i][j]=abs((obraz_pgm[i][j+1]-obraz_pgm[i][j])); /*Przypadek ostatniej kolumny*/     
      } else if(j==(*wymy-1)){
      	obraz_pgm[i][j]=((obraz_pgm[i+1][j]-obraz_pgm[i][j])); /* Ostatni wiersz */
      } else {
      	obraz_pgm[i][j]=abs((obraz_pgm[i+1][j]-obraz_pgm[i][j]))+abs((obraz_pgm[i][j+1]-obraz_pgm[i][j]));
      }
      /*pozostalee przypadki*/
    }
    }
}

int korekcja_gamma(float *gamma, int obraz_pgm[][MAX], int *wymx, int *wymy,int *szarosci){
  if((*gamma) <= 0.0){
      printf("BLAD!\n");
      return 0;
  }

  float dzielnik = pow((*szarosci),((1-(*gamma))/(*gamma)))
    ;
  for(int i=0; i<(*wymx); i++){
    for(int j=0; j<(*wymy); j++){

      obraz_pgm[i][j] = (int)(pow((obraz_pgm[i][j]),((1/(*gamma))/dzielnik)))*255;
    }
  }
  return 1;
}

int main() {
  int obraz[MAX][MAX] ;
  int wymx,wymy,odcieni;
  int end=1;
  int odczytano = 0;
  FILE *plik;
  char nazwa[100];
  char tab_wybor[5];
  /* Wczytanie zawartosci wskazanego pliku do pamieci */
  /*  printf("Podaj nazwe pliku:\n");
  scanf("%s",nazwa);
  plik=fopen(nazwa,"r");
  */
  /*
 if (plik != NULL) {       /* co spowoduje zakomentowanie tego warunku */
  /*odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
    fclose(plik); 
    } */

  /* Wyswietlenie poprawnie wczytanego obraza zewnetrznym programem */
  // if (odczytano != 0)
  // wyswietl(nazwa);
  while(end !=0)
    {
    printf("Menu Przetwarzania Obrazow\n");
    printf("1 - Wczytaj Obraz\n");
    printf("2 - Wyswietl Obraz\n");
    printf("3 - Negatyw\n");
    printf("4 - Konturowanie\n");
    printf("5 - Korekcja Gamma\n");
    printf("6 - Rozciaganie Histogramu\n");
    printf("7 - Zapisz plik\n");
    printf("0 - Koniec\n");
    scanf("%1s", &tab_wybor);
    switch(tab_wybor[0])

    {


    case '1':  /*Wywołana zostaje funkcja wczytania obrazu. */
      printf("Podaj nazwe obrazu wraz z rozszerzeniem, ktory chcesz wczytac:\n");
      scanf("%s",nazwa);
      plik=fopen(nazwa,"r");
      if (plik != NULL)odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
      else printf("Blad, niepoprawny plik\n");
      break;
    

    case '2':  /*Wywołana zostaje funkcja display. */
      wyswietl(nazwa);

      break;
    


    case '3':  /* Wywołana zostaje funkcja negatywu. */
      negatyw(obraz,&wymx,&wymy,&odcieni);
      break;
    


    case '4': /* Wywołana zostaje funkcja konturowania obrazu. */
      
      
      konturowanie(obraz,&wymx,&wymy,&odcieni);
      break;
    


    case '5':  /* Wywołana zostaje funkcja rozmywania poziomego obrazu. */
      printf("podaj wartosc gamma\n");
      float gamma=0;
      scanf("%f", &gamma);
   
	 korekcja_gamma(&gamma,obraz,&wymx,&wymy,&odcieni);
      break;
    
    case '6'://histogram

      break;

    case '7':  /* Wywolana zostaje funkcja zapisania zmodyfikowanego obrazu. */
      zapis(obraz,&wymx,&wymy,&odcieni); 
      break;
    


    case '0':  /* Program zostaje wylaczony. */
      printf("Zakoncz program\n\n");
      end=0;
      break;
    


    default:  /* Przypadek, gdy zostaje wpisany numer opcji, którego nie ma w menu. */
      printf("Wybrano niewlasciwa opcje\n");
      break;
    


    }

    }



  return 0;
}
