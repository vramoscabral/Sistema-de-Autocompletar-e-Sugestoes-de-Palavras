#ifndef AVL_HPP
#define AVL_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;
#include "metodo.hpp"

struct NoAVL {
  pair<string, int> item;
  NoAVL* esq;
  NoAVL* dir;
  int altura;

  NoAVL(pair<string, int> item) : item(item), esq(NULL), dir(NULL), altura(1) {}
};

class TreeAVL {
  private:
    NoAVL* raiz;

  public:
    vector<pair<string, int>> outputav;

    TreeAVL() {
      raiz = NULL;
    }

    int getaltura(NoAVL* node);
    int balanceamento(NoAVL* node);
    NoAVL* rotdir(NoAVL* y);
    NoAVL* rotesq(NoAVL* x);

    void insert(priority_queue<Item> heap);
    NoAVL* avlinsert(NoAVL* raiz, pair<string, int> item);
    void printdelavb();
    void vecpreOrder(NoAVL* atual);
    void deleteav(NoAVL* &raiz);
    vector<pair<string, int>> getvect();
};

vector<pair<string, int>> arvavl(priority_queue<Item> heap);

#endif
