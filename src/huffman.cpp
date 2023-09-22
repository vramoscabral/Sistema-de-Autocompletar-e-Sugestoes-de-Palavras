#include "huffman.hpp"
#include "metodo.hpp"

bool ArvHuff::Nointerno(string word)
{
  if (word == "a")
    return true;
  else
    return false;
}

void ArvHuff::makeTree(vector<pair<string, int>> vecheap)
{
  priority_queue<NoHuff*, vector<NoHuff*>, comparaNoHuffs> pq;

  for (auto& valor : vecheap)
    pq.push(new NoHuff(valor));

  while (pq.size() > 1)
  {
    NoHuff* left = pq.top();
    pq.pop();

    NoHuff* right = pq.top();
    pq.pop();

    NoHuff* novoNo = new NoHuff(make_pair("a", left->item.second + right->item.second));
    novoNo->esq = left;
    novoNo->dir = right;

    pq.push(novoNo);
  }

  raiz = pq.top();
}

void ArvHuff::printdelavb()
{
  outputav.clear();
  vecpreOrder(raiz);
  deleteav(raiz);
}

void ArvHuff::vecpreOrder(NoHuff *atual)
{ 
  NoHuff *at = atual;
  
  if (at != NULL) {
    if (!Nointerno(at->item.first))
      outputav.push_back(at->item);
    vecpreOrder(at->esq);
    vecpreOrder(at->dir);
  }
}

void ArvHuff::deleteav(NoHuff* &raiz)
{
  if (raiz == NULL)
    return;
  
  deleteav(raiz->esq);
  deleteav(raiz->dir);
 
  delete raiz;
  
  raiz = NULL;
}

vector<pair<string, int>> ArvHuff::getvect()
{
  return outputav;
}

vector<pair<string, int>> arvorehuff(priority_queue<Item> heap)
{
  vector<pair<string, int>> outp, vech;
  pair<string, int> valor;
  ArvHuff t;

  vech.clear();
  while (!heap.empty())
  {
    valor = make_pair(heap.top().name, heap.top().value);
    vech.push_back(valor);
    heap.pop();
  }
  
  t.makeTree(vech);
  t.printdelavb();
  outp = t.getvect();
  
  return outp;
}