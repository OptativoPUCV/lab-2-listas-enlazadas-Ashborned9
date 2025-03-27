#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
  void *data;
  Node *next;
  Node *prev;
};

struct List {
  Node *head;
  Node *tail;
  Node *current;
};

typedef List List;

Node *createNode(void *data) {
  Node *new = (Node *)malloc(sizeof(Node));
  assert(new != NULL);
  new->data = data;
  new->prev = NULL;
  new->next = NULL;
  return new;
}

List *createList() {
  List *lista = (List *)malloc(sizeof(List));
  lista->head = NULL;
  lista->tail = NULL;
  lista->current = NULL;
  return lista;
}

void *firstList(List *list) {
  if (list == NULL) {
    return NULL;
  }
  if (list->head == NULL) {
    return NULL;
  }
  list->current = list->head;
  return list->head->data;
}

void *nextList(List *list) {
  if (list == NULL || list->current == NULL || list->current->next == NULL) {
    return NULL;
  }
  list->current = list->current->next;
  return list->current->data;
}

void *lastList(List *list) {
  if (list == NULL || list->head == NULL) {
    return NULL;
  }
  Node *aux = list->head;
  while (aux->next != NULL) {
    aux = aux->next;
  }
  list->current = aux;
  return list->current->data;
}

void *prevList(List *list) {
  if (list ==NULL || list->current ==NULL || list->current->prev == NULL){
    return NULL;
  }
  Node *aux = list->head;
  while(aux->next != list->current){
    aux = aux->next;
  }
  list->current = aux;
  return list->current->data;
}

void pushFront(List *list, void *data) {
  Node *NodoNuevo = createNode(data);
  NodoNuevo->prev = NULL;
  NodoNuevo->next = list->head;
  if (list->head != NULL) {
    list->head->prev = NodoNuevo;
  }
  else{
    list->tail = NodoNuevo;
  }
  list->head = NodoNuevo;
}

void pushBack(List *list, void *data) {
  list->current = list->tail;
  pushCurrent(list, data);
}

void pushCurrent(List *list, void *data) {
  if (list == NULL || list->current == NULL) {
    return;
  }
  Node *NodoNuevo = createNode(data);
  Node *Siguiente = list->current->next;
  NodoNuevo->prev = list->current;
  NodoNuevo->next = Siguiente;
  list->current->next = NodoNuevo;
  if (Siguiente != NULL){
    Siguiente->prev = NodoNuevo;
  }
  else{
    list->tail = NodoNuevo;
  }
  
}

void *popFront(List *list) {
  list->current = list->head;
  return popCurrent(list);
}

void *popBack(List *list) {
  list->current = list->tail;
  return popCurrent(list);
}

void *popCurrent(List *list) {
  if (list == NULL || list->current == NULL) {
    return NULL;
  }
  Node *aux = list->current;
  void *datoCur = aux->data;
  if (aux->prev != NULL)
  {
    aux->prev->next = aux->next;
  }
  else{
    list->head = aux->next;
  }
  if (aux->next != NULL)
    {
      aux->next->prev = aux->prev;
    }
    else{
      list->tail = aux->prev;
    }
  list->current = aux->next;
  free(aux);
  return datoCur;
}
  

void cleanList(List *list) {
  while (list->head != NULL) {
    popFront(list);
  }
}