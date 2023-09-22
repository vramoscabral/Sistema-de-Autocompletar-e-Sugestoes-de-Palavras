#ifndef METODO_HPP
#define METODO_HPP
#include <iostream>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#define K 20
using namespace std;

struct Item {
  string name;
  int value;

  Item(const string &n, int v) : name(n), value(v) {}

  bool operator<(const Item &other) const {
    return value > other.value; }
};

extern vector<string> stopword;
extern vector<unordered_map<string, int>> wordtxtsCounts;
extern vector<pair<string, int>> topKplus1;
extern vector<priority_queue<Item>> heapsoriginais;
extern vector<string> termos;

void stopwords_termos();
bool ehstopword(string word);
void mapeamento();
void topKitens();
void pesquisatermos();
void Output();

#endif