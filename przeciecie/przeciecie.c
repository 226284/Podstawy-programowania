/*Michał Wieczorek
Przecięcia zera
21.11.2015*/

/*Program na na celu sprawdzenie w ilu miejscach w danych zczytanych z pliku występuje przecięcie zera, czyli czy liczba ujemna zmienia się na dodatnią, oraz odwrotnie. Na końcu działania programu zwracana jest całkowita ilość przecięć w pliku.*/

/*Testy programu:
Na początku program testowany był z danymi wprowadzanymi z klawiatury:

Test1 (sprawdzenie dla liczb z przedziału (-10,10) z wykluczeniem zera:
Dane wejściowe: -9, -5, 2, -2, -3, -1, 5, 2, 8, 99
Dane wyjściowe: 3

Test2 (sprawdzenie dla liczb z przedziału (-10,10)
Dane wejściowe: 7, 2, 0, 2, -1, 0, 1, 5, -2, 0, 99
Dane wyjściowe: 3

Test3 (sprawdzenie dla liczb <= -10 oraz >= 10, aby dowiedzieć się czy zamiana liczb spoza przedziału (-10,10) na liczby MAX=10 i MIN=-10 działa prawidłowo)
Dane wejściowe: -50, 300, 288, 0, 100, -25, 35, 0, -78, 58, 0, 90, 99
Dane wyjściowe: 5

Test4 (sprawdzenie działania z pustymi wierszami (w pliku z danymi zdarzają się luki co jakiś czas))
Dane wejściowe: 5, 0,  , 3,  , -2, 18,  , 99
Dane wyjściowe: 2 

Test5 (sprawdzenie dla liczb zmiennoprzecinkowych)
Dane wejściowe: 0.99, 99.9, 88.5, -24.5, 0.34, 99
Dane wyjściowe: 2

Po testowaniu uruchomiłem program komendą(która "obcina" niepotrzebną część danej z pliku):

cut  -d ' ' -f 2 przeciecia_zera1.txt|./a.out
Dane wejściowe: przeciecia_zera1.txt
Dane wyjściowe: 119 przecięć

cut  -d ' ' -f 2 przeciecia_zera2.txt|./a.out
Dane wejściowe: przecięcie zera2.txt
Dane wyjściowe: 119

W rezultacie testów każdorazaowo dostałem poprawne wyniki, stwierdzam więc że program działa poprawie.
 */

#include <stdio.h>
#include <float.h>

int main(){

#define MAX 10
#define MIN -10

  float liczba=0;
  float poprzednia=0;
  int i=0;
  
  printf("\nProgram liczy ilość przecięć w zerze\n");

  while(liczba!=99) /*Pętla while wykona się każdorazowo, oprócz warunku kiedy liczba==99*/
  {
    scanf("%f",&liczba); /*Program wczytuje liczby, jedna po drugiej (zastosowanie pętli while)*/
    
    if(liczba<MIN) liczba=MIN; /*Jeśli wczytana liczba jest mniejsza od -10, to program przypisuje jej wartość -10*/
    else if(liczba>MAX && liczba!=99) liczba=MAX; /*Jeśli wczytana liczba jest większa od 10, to program przypisuje jej wartość 10. Należy też uwzględnić warunek, aby liczby 99 nie zamieniało na 10*/

    if((poprzednia*liczba)<0 && liczba!=99) /*Jeżeli poprzednia liczba pomnożona przez kolejną daje wynik ujemny to następuje przecięcie. Tu również należy wyrzucić 99, ponieważ liczba ma kończyć program, zatem nie może być brana pod uwagę do liczenia przecięć*/
      {	
	i++;/*nastepuje przeciecie*/
      }
    
    if(liczba!=0 && liczba!=99) /*Jeśli program wczyta 0, to je pomija, nie nadpisując go. Dzięki temu w następnym kroku, program porówna liczbę przed zerem i po zerze.*/
      {
	poprzednia=liczba;
      }
  }
  
  printf("\nIlość przecięć w podanym pliku wynosi:  ");
  printf("%d\n",i);
  
  printf("UWAGA! Liczba 99 nie jest brana pod uwagę!\n\n");
  
  return 0;
  
}


