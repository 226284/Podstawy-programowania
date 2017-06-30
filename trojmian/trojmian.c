/*
  Micha³ Wieczorek
  Sprawozdanie - trojmian.c
  05.11.2015r
*/
/*
  Testy programu:
  Test ma na celu sprawdzenie poprawno¶ci dzia³ania programu i znalezieniu ewentualnych b³êdów
    
  Testowanie polega³o na wprowadzaniu danych, tak aby sprawdzeniæ wszystkie 3 przypadki delty, tzn >0,=0 oraz <0, a pó¼niej okre¶leniu czy obliczone pierwiaski s± prawid³owe.

  1. Przypadek delty>0
    Dane wej¶ciowe  a=-5, b=2, c=3;
    Dane wyj¶ciowe x1=1.0, x2=0,6;
  2. Przypadek delty=0
    Dane wej¶ciowe a=1, b=2, c=1;
    Dane wyj¶ciowe x1=x2=-1.0
  3. Przypadek delty<0
    Dane wej¶ciowe a=4, b=-2, c=4;
    Dane wyj¶ciowe Brak rozwi±zañ rzeczywistych

  Z testu wynika, ¿e program dzia³a prawid³owo. Po wprowadzeniu danych wej¶ciowych, program zwraca odpowiednie warto¶ci.
*/

#include <stdio.h>
#include <math.h>
#include <float.h>

int main() {
  float a,b,c,delta;

  printf("Program oblicza pierwiastki rownania w postaci\n");
  printf("     2\n");
  printf("  a x + b x +c =0\n");
  printf("Podaj wartosc a:");
  scanf("%f",&a);
  printf("Podaj wartosc b:");
  scanf("%f",&b);
  printf("Podaj wartosc c:");
  scanf("%f",&c);
  
  if (a==0.0){    /*przypadek rownania liniowego */
    if (b!=0.0) 
      printf("Jest to równanie liniowe o rozwiazaniu x=%f\n",-c/b);
    else  if (c==0.0)  /* oraz a==b==0.0 */
      printf("Rozwiazaniem jest dowolne x\n");
    else              /* a==b==0.0 != c  */
      printf("Brak rozwiazan\n");}
  else {   /*przypadek rownania kwadratowego */
    delta=pow(b,2)-4.0*a*c;
    if (delta<0) 
      printf("Brak rozwiazan rzeczywistych\n");
    else            /* delta>=0 */
      if (delta>0) 
	printf("Rozwiazaniem sa x1=%f i x2=%f\n",(-b-sqrt(delta))/(2*a),(-b+sqrt(delta))/(2*a));
      else
      	printf("Rozwiazaniem sa x1=x2=%f\n",-b/(2*a));
  }
  return 0;
}
