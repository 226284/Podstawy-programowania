
#define MAX 512            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */
#define MAX_KOL 255.0f
#define MIN_KOL 0

int menu();
void progowanie(int obraz_pgm[][MAX], int *wymx, int *wymy, int *szarosci, int PROG);
void korekcja(int obraz_pgm[][MAX], int *wymx, int *wymy, float GAMMA);
void rozmywanie(int obraz_pgm[][MAX], int *wymx, int *wymy);
void histogram(int obraz_pgm[][MAX], int *wymx, int *wymy);
int czytaj(FILE *plik_we, int obraz_pgm[][MAX], int *wymx, int *wymy, int *szarosci);
void wyswietl(char *n_pliku);
void zapisz(FILE *plik_wyj, int obraz_pgm_[][MAX], int *wymx, int *wymy, int *szarosci);

