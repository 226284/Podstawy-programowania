#include <stdio.h>
#include <stdlib.h>

#include "funkcje.h"

void push(t_elem *lista, unsigned int wsk){
    t_elem *nowy;
    nowy = (*lista) malloc(sizeof(lista));
    nowy->liczba = wsk;
    nowy->next = last;
    return nowy;
}

void pop(t_elem *lista, unsigned int *t_elem){
  t_elem *wsk = lista;
  t_elem *usun = wsk->next;
  wsk->next = usun->next;
  free(usun);
}

void print(t_elem *lista){
  t_elem *wsk = lista;
  while(wsk != NULL)
    {
      printf("%d", wsk->liczba);
      wsk= wsk->next;
    }
}

