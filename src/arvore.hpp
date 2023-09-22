#ifndef ARVORE_HPP
#define ARVORE_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
using namespace std;
#include "metodo.hpp"

struct No {
  pair<string, int> item;
  No* esq;
  No* dir;
};

class Tree {
  private:
    No* raiz;

  public:
    vector<pair<string, int>> outputav;

    Tree() {
      raiz = NULL;
    }
    void arvorebinsert(pair<string, int> item);
    void printdelavb();
    void vecpreOrder(No* atual);
    void deleteav(No* &raiz);
    vector<pair<string, int>> getvect();
};

vector<pair<string, int>> arvoreb(priority_queue<Item> heap);

#endif