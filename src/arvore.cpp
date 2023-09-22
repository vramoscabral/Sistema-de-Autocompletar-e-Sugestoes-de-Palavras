#include "arvore.hpp"
#include "metodo.hpp"

void Tree::arvorebinsert(pair<string, int> valor)
{
  No *novo = new No();
  novo->item = valor;
  novo->dir = NULL;
  novo->esq = NULL;

  if (raiz == NULL)
    raiz = novo;
  else 
  {
    No *atual = raiz;
    No *ant;
    while(true)
    {
      ant = atual;
      if (valor.second <= atual->item.second)
      {
        atual = atual->esq;
        if (atual == NULL)
        {
          ant->esq = novo;
          return;
        } 
      }  // fim da condição ir a esquerda
      else
      { // ir para direita
        atual = atual->dir;
        if (atual == NULL)
        {
          ant->dir = novo;
          return;
        }
      }
    }
  }
}

void Tree::printdelavb()
{
  outputav.clear();
  vecpreOrder(raiz);
  deleteav(raiz);
}

void Tree::vecpreOrder(No *atual)
{ 
  No *at = atual;
  
  if (at != NULL) {
    outputav.push_back(at->item);
    vecpreOrder(at->esq);
    vecpreOrder(at->dir);
  }
}

void Tree::deleteav(No* &raiz)
{
  if (raiz == NULL)
    return;
  
  deleteav(raiz->esq);
  deleteav(raiz->dir);
 
  delete raiz;
  
  raiz = NULL;
}

vector<pair<string, int>> Tree::getvect()
{
  return outputav;
}

vector<pair<string, int>> arvoreb(priority_queue<Item> heap)
{
  vector<pair<string, int>> outp;
  pair<string, int> valor;
  Tree t;
  
  while (!heap.empty())
  {
    valor = make_pair(heap.top().name, heap.top().value);
    t.arvorebinsert(valor);
    heap.pop();
  }
  t.printdelavb();
  outp = t.getvect();
  
  return outp;
}