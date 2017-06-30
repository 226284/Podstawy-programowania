#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int dane;
  element_t *nastepny;
}element_t;

int liczba_elem;

/******************************************************************************//* Dodawanie elementu do stosu */

void dodawanie(t_element **element){
  
  int *p, *pp;
  
  if (*nastepny == NULL){
    glowa = (element*) malloc(sizeof(element));
    glowa->dana = dana;
    glowa->nastepny = NULL;
  }

  else{
    p = glowa;
    
    for(){
      if(!p->nastepny) brake;
    
      p = p->nastepny;
      
      p->nastepny = (*int) malloc(sizeof(int));
      
      p = p->nastepny;
      
      p->nastepny=NULL;
    }
  }
}

/******************************************************************************/
/* Usuwanie elementu ze stosu */

void (

int main(){
  
  int wybor;
  
  printf("*******************"
	 "*  1-Dodawanie    *"
	 "*  2-odejmowanie  *"
         "*  0-Koniec       *"
	 "*******************");
  
  scanf("%d",&wybor);

  switch(wybor){

  case 1:
    dodawanie( , );
    break;

  case 2:
    odejmowanie( , );
    break;
    
  case 0:
    return 0;

  }
