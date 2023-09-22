#include "avl.hpp"
#include "metodo.hpp"

int TreeAVL::getaltura(NoAVL* node)
{
  if (node == NULL)
    return 0;
  return node->altura;
}

// Função para calcular o fator de balanceamento de um nó
int TreeAVL::balanceamento(NoAVL* no)
{
  if (no == NULL)
    return 0;
  return getaltura(no->esq) - getaltura(no->dir);
}

NoAVL* TreeAVL::rotdir(NoAVL* y)
{
  NoAVL* x = y->esq;
  NoAVL* subarv2 = x->dir;

  x->dir = y;
  y->esq = subarv2;

  y->altura = max(getaltura(y->esq), getaltura(y->dir)) + 1;
  x->altura = max(getaltura(x->esq), getaltura(x->dir)) + 1;

  return x;
}

NoAVL* TreeAVL::rotesq(NoAVL* x)
{
  NoAVL* y = x->dir;
  NoAVL* subarv2 = y->esq;

  y->esq = x;
  x->dir = subarv2;

  x->altura = max(getaltura(x->esq), getaltura(x->dir)) + 1;
  y->altura = max(getaltura(y->esq), getaltura(y->dir)) + 1;

  return y;
}

void TreeAVL::insert(priority_queue<Item> heap)
{
  pair<string, int> valor;

  while (!heap.empty())
  {
    valor = make_pair(heap.top().name, heap.top().value);
    raiz = avlinsert(raiz, valor);
    heap.pop();
  }
  
}

NoAVL* TreeAVL::avlinsert(NoAVL* atual, pair<string, int> valor)
{
  if (atual == NULL)
    return new NoAVL(valor);

  if (valor.second <= atual->item.second)
    atual->esq = avlinsert(atual->esq, valor);
  else
    atual->dir = avlinsert(atual->dir, valor);

  atual->altura = 1 + max(getaltura(atual->esq), getaltura(atual->dir));
    
  int balance = balanceamento(atual);

  if (balance > 1)
  {
    if (valor.second <= atual->esq->item.second)
      return rotdir(atual);
    else
    {
      atual->esq = rotesq(atual->esq);
      return rotdir(atual);
    }
  }

  if (balance < -1)
  {
    if (valor.second > atual->dir->item.second)
      return rotesq(atual);
    else
    {
      atual->dir = rotdir(atual->dir);
      return rotesq(atual);
    }
  }

  return atual;
}

void TreeAVL::printdelavb()
{
  outputav.clear();
  vecpreOrder(raiz);
  deleteav(raiz);
}

void TreeAVL::vecpreOrder(NoAVL* atual)
{ 
  NoAVL* at = atual;
  
  if (at != NULL) {
    outputav.push_back(at->item);
    vecpreOrder(at->esq);
    vecpreOrder(at->dir);
  }
}

void TreeAVL::deleteav(NoAVL* &raiz)
{
  if (raiz == NULL)
    return;
  
  deleteav(raiz->esq);
  deleteav(raiz->dir);
 
  delete raiz;
  
  raiz = NULL;
}

vector<pair<string, int>> TreeAVL::getvect()
{
  return outputav;
}

vector<pair<string, int>> arvavl(priority_queue<Item> heap)
{
  vector<pair<string, int>> outp;
  pair<string, int> valor;
  TreeAVL t;
  t.insert(heap);
  
  t.printdelavb();
  outp = t.getvect();
  
  return outp;
}
