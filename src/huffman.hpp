#ifndef HUFF_HPP
#define HUFF_HPP
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

struct NoHuff {
  pair<string, int> item;
  NoHuff* esq;
  NoHuff* dir;

  NoHuff(pair<string, int> item) : item(item), esq(NULL), dir(NULL) {}
};

struct comparaNoHuffs {
  bool operator()(NoHuff* a, NoHuff* b) {
    return a->item.second > b->item.second;
  }
};

class ArvHuff {
  private:
    NoHuff* raiz;

  public:
    vector<pair<string, int>> outputav;

    ArvHuff() {
      raiz = NULL;
    }

    void makeTree(vector<pair<string, int>> vecheap);
    bool Nointerno(string word);
    void printdelavb();
    void vecpreOrder(NoHuff* atual);
    void deleteav(NoHuff* &raiz);
    vector<pair<string, int>> getvect();
};

vector<pair<string, int>> arvorehuff(priority_queue<Item> heap);

#endif

