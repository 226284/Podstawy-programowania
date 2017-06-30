/*
Micha� Wieczorek, "Przetwarzanie obraz�w", 07.12.2015

Plik przetwarzanie_obrazow.c zawiera kod �r�d�owy programu oraz sprawozdanie w formie
komentarza. Do napisania programu zosta� wykorzystywany kod �r�d�owy z pliku odczyt.c
ze strony Dr Roberta Muszy�skiego.
*/

/*
Testy programu:
Testowanie programu wykona�em na dw�ch obrazach typu ".pgm", a mianowicie: kubus.pgm
oraz Lena.pgm.

W Te�cie nr 1 sprawdzi�em poprawno�� dzia�ania funkcji odczytu i zapisu obraz�w. Za�
W kolejnych testach, czy operacje na obrazie dzia�aj� prawid�owo. 

1) Po uruchomieniu programu wybra�em opcj� wczytaj obraz, nast�pnie wprowadzi�em nazw� 
obrazu "kubus.pgm", po wczytaniu zapisa�em go do pliku "kubus_1.pgm". A nast�pnie wy�w-
ietli�em go programem display. Orygina� by� zgodny z zapisanym plikiem.

Przy testowaniu funkcji programu takich jak progowanie bieli, korekcja gamma, rozmywa-
nie w pionie pos�ugiwa�em si� plikiem pdf zamieszczonym na stronie Dr Muszy�skiego.
W pliku pdf znajduj� si� obrazki przekonwertowane ju� danymi funkcjami. Testowanie po-
lega�o wi�c na wizualnym powr�wnaniu przetworzonych obraz�w z mojego programu, z tymi 
w pliku pdf.

2) Testowanie funkcji progowanie bieli:
Wczyta�em obraz kubus.pgm, a nat�pnie wybra�em opcj� "progowanie bieli" z Menu. Wprowa-
dzi�em pr�g bieli "20"%. Po zapisaniu obrazu por�wna�em go wizualnie z tym w pliku pdf

T� sam� czynno�� powt�rzy�em dla progu: "50" oraz "80", por�wnuj�c je wizualnie, nie 
stwierdzi�em �adnych r�nic.

3) Testowanie funkcji korekcja gamma:
Testowanie wygl�da�o podobnie, inne by�y tylko wprowadzane warto�ci. Testowa�em program
dla wsp�czynnika gamma: "0.5", "1.5", "2.5", ka�dowo por�wnuj�c obrazy.

4) Testowanie funkcji rozmywanie w pionie
W tym wypadku nie podajemy �adnych parametr�w dla funkcji. Po wybraniu opcji "rozmywa-
nie w pionie, program automatycznie przerabia obraz. Otrzymany wynik to rozmycie pionowe
o promieniu 1. R�wnie� w tym przypadku nie stwierdzi�em r�nic mi�dzy obrazami.

5) Testowanie funkcji rozci�ganie histogramu
W tym orzypadku musia�em pos�u�y� si� obrazem "Lena.pgm", gdy� plik "kubus.pgm" zawiera�
wszystkie odcienie szaro�ci (0-255). Nie mo�na wi�c by�o rozci�gn�� histogramu obrazu.
Po wybraniu opcji "rozci�ganie histogramu" dla obrazu "Lena.pgm" operacja wykona�a si�
automatycznie. Po zapisaniu obrazu stwierdzi�em wizualnie widoczne r�nice w odcieniach
szaro�ci obraz�w. Jednak alby sprawdzi� czy rozci�ganie przebieg�o prawid�owo wczyta�em
przetworzony obraz i znowu wybra�em opcj� rozci�gania histogramu. Po zapisaniu pliku
okaza�o si�, �e w tym wypadku nie ma r�nicy pomi�dzy obrazami.

Stwierdzam wi�c, �e program dzia�a prawid�owo.
*/ 

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define MAX 512            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */
#define MAX_KOL 255.0f
#define MIN_KOL 0


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

/*Menu startowe*/
int menu(){

  int tmp=0;
    
  printf("\n"
         " *********************************\n"
         " *              MENU             *\n"
	 " *********************************\n"
         " *  1 WCZYTAJ OBRAZ              *\n"
	 " *                               *\n");
  printf(" *            -OPCJE-            *\n"
	 " *    2 (Pol)Progowanie bieli    *\n"
	 " *    3 Korekcja gamma           *\n"
	 " *    4 Rozmywanie w pionie      *\n"
	 " *    5 Rozciaganie histogramu   *\n"
	 " *                               *\n"
	 " *  6 Wyswietl oryginalny  obraz *\n"
	 " *  7 ZAPISZ OBRAZ               *\n"
	 " *  8 ZAKONCZ DZIALANIE PROGRAMU *\n"
	 " *********************************\n\n");

  printf(" Twoj wybor: ");
  scanf("%d",&tmp);
  printf("\n");

  return tmp;
    }

/*Progowanie bieli*/
void progowanie(int obraz_pgm[][MAX], int *wymx, int *wymy, int *szarosci, int PROG){
  
  int i,j;

  for(i=0; i<*wymy; i++){
    for(j=0; j<*wymx; j++){
      
      if(obraz_pgm[i][j]>=PROG)   /*MAX_KOL je�eli L(x,y)>=PROG*/
	obraz_pgm[i][j]=MAX_KOL;  /*L(x,y)  je�eli L(x,y)> PROG (warunek "sam si� wykona")*/
    }
  }
}

/*Korekcja gamma*/
void korekcja(int obraz_pgm[][MAX], int *wymx, int *wymy, float GAMMA){

  int i,j;

  for(i=0; i<*wymy; i++){
    for(j=0; j<*wymx; j++){
      
      obraz_pgm[i][j]=(powf(obraz_pgm[i][j]/MAX_KOL,1.0f/GAMMA))*MAX_KOL;
    }
 }
}

/*Rozmywanie w pionie*/
void rozmywanie(int obraz_pgm[][MAX], int *wymx, int *wymy){
  
  int i,j;
  
  for(i=1; i<*wymy-1; i++){
    for(j=0; j<*wymx; j++){
      
	obraz_pgm[i][j]=(1.0f/3.0f)*(obraz_pgm[i-1][j] + obraz_pgm[i][j] + obraz_pgm[i+1][j]);
	  
    }
  }
}

/*Rozci�ganie histogramu*/
void histogram(int obraz_pgm[][MAX], int *wymx, int *wymy){

  int max_wart=0, min_wart=255;

  int i,j;
  
  for(i=0; i<*wymy; i++){
    for(j=0; j<*wymx; j++){

      if(obraz_pgm[i][j]>max_wart)                           /*Program szuka maksymalnego argumentu tablicy */
	{max_wart=obraz_pgm[i][j];}                         
                                                            
      if(obraz_pgm[i][j]<min_wart)                           /*Program szuka minimalnego argumentu tablicy  */
	{min_wart=obraz_pgm[i][j];}
    }
  }

  for(i=0; i<*wymy; i++){
    for(j=0; j<*wymx; j++){
      
      obraz_pgm[i][j]=(obraz_pgm[i][j] - min_wart) * (MAX_KOL/(max_wart - min_wart));

    }
  }
}


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
  for (i=0;i<*wymy;i++) {
    for (j=0;j<*wymx;j++) {
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

/*Zapis obrazou do pliku*/

void zapisz(FILE *plik_wyj, int obraz_pgm[][MAX], int *wymx, int *wymy, int *szarosci){

  int i,j; /*Liczniki wypisuj�ce tablic�*/
  
  fprintf(plik_wyj, "P2\n#Przetworzony_obraz\n%d %d\n%d\n", *wymx, *wymy, *szarosci);

       for (i=0;i<*wymy;i++) {
	 for (j=0;j<*wymx;j++) {
	   
	   fprintf(plik_wyj, "%3d ", obraz_pgm[i][j]);

	   }
	 }
      
      fclose(plik_wyj);
    
}

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
