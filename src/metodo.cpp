#include "metodo.hpp"
#include "arvore.hpp"
#include "avl.hpp"
#include "huffman.hpp"
vector<string> stopword;
vector<unordered_map<string, int>> wordtxtsCounts;
vector<pair<string, int>> topKplus1;
vector<priority_queue<Item>> heapsoriginais;
vector<string> termos;

void stopwords_termos()
{
  ifstream stfile("dataset/input/stopwords.txt");
  string line, word;

  while (getline(stfile, line))
  {
    istringstream iss(line);
    while (iss >> word)
    {
      stopword.push_back(word);
    }
  }

  stfile.close();

  ifstream tfile("dataset/input/input.txt");

  while (getline(tfile, line))
  {
    istringstream iss(line);
    while (iss >> word)
    {
      termos.push_back(word);
    }
  }

  tfile.close();
}

bool ehstopword(string word)
{
  for (long unsigned int i = 0; i < stopword.size(); i++)
  {
    if (word == stopword[i])
      return true;
  }
  return false;
}

void mapeamento()
{
  for (int i = 1; i < 7; i++)
  {
    unordered_map<string, int> wordCount;
    ifstream inputFile("dataset/input/texts/text" + to_string(i) + ".txt");
    string line, word;

    while (getline(inputFile, line))
    {
      transform(line.begin(), line.end(), line.begin(), ::tolower);
      istringstream iss(line);
      while (iss >> word)
      {
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
        if (!word.empty() && !ehstopword(word))
          wordCount[word]++;
      }
    }

    inputFile.close();
    wordtxtsCounts.push_back(wordCount);
  }
}

void topKitens()
{
  for (int i = 0; i < 6; i++)
  {
    unordered_map<string, int> wordCount = wordtxtsCounts[i];
    pair<string, int> toplus1;
    int count = 0;
    priority_queue<Item> heap;

    for (const auto &pair : wordCount)
    {
      if (count == K)
        break;
      heap.push(Item(pair.first, pair.second));
      count++;
    }

    for (const auto &pair : wordCount)
    {
      if (pair.second > heap.top().value)
      {
        toplus1 = make_pair(heap.top().name, heap.top().value);
        heap.pop();
        heap.push(Item(pair.first, pair.second));
      }
    }

    topKplus1.push_back(toplus1);
    heapsoriginais.push_back(heap);
  }
}

void pesquisatermos()
{
  int n=0, aux;
  vector<pair<string, int>> outarv;
  
  for (long unsigned int h = 0; h<termos.size(); h++)
  {
    n++;
    string termo = termos[h];
    ofstream arq;
    arq.open("dataset/out" + to_string(n) + ".data");

    if (h >= 1)
      arq << "----------------------------------" << endl << endl;
    arq << "---palavra <" << termo << ">---" << endl << endl;
    for (int i = 0; i < 6; i++)
    {
      unordered_map<string, int> wordCount = wordtxtsCounts[i];

      aux=0;
      for (const auto &pair : wordCount)
      {
        if (termo == pair.first)
        {
          arq << "Está presente no texto " << i + 1 << endl;
          aux = 1;
        }
      }

      if (aux == 1)
      {
        priority_queue<Item> heap = heapsoriginais[i];
        priority_queue<Item> heap2;
        
        while (!heap.empty())
        {
          if (termo == heap.top().name)
          {
            arq << "e também é um dos top K elementos." << endl;
            arq << "Frequência: " << heap.top().value << " vezes" << endl << endl;
            aux = 2;
            heap2.push(Item(topKplus1[i].first, topKplus1[i].second));
          }
          else
            heap2.push(Item(heap.top().name, heap.top().value));
          heap.pop();
        }

        if (aux == 2)
        {
          outarv = arvoreb(heap2);
          arq << "arvore binaria: " << endl << endl;
          for (long unsigned int z=0; z<outarv.size(); z++)
            arq << "<" << outarv[z].first << ">-<" << outarv[z].second << ">; ";
          arq << endl << endl;
          outarv = arvavl(heap2);
          arq << "arvore AVL: " << endl << endl;
          for (long unsigned int z=0; z<outarv.size(); z++)
            arq << "<" << outarv[z].first << ">-<" << outarv[z].second << ">; ";
          arq << endl << endl;
          outarv = arvorehuff(heap2);
          arq << "arvore Huffman: " << endl << endl;
          for (long unsigned int z=0; z<outarv.size(); z++)
            arq << "<" << outarv[z].first << ">-<" << outarv[z].second << ">; ";
          arq << endl << endl;
        }
        else
        {
          arq << "porém não é um dos top K elementos." << endl << endl;
          outarv = arvoreb(heap2);
          arq << "arvore binaria: " << endl << endl;
          for (long unsigned int z=0; z<outarv.size(); z++)
            arq << "<" << outarv[z].first << ">-<" << outarv[z].second << ">; ";
          arq << endl << endl;
          outarv = arvavl(heap2);
          arq << "arvore AVL: " << endl << endl;
          for (long unsigned int z=0; z<outarv.size(); z++)
            arq << "<" << outarv[z].first << ">-<" << outarv[z].second << ">; ";
          arq << endl << endl;
          outarv = arvorehuff(heap2);
          arq << "arvore Huffman: " << endl << endl;
          for (long unsigned int z=0; z<outarv.size(); z++)
            arq << "<" << outarv[z].first << ">-<" << outarv[z].second << ">; ";
          arq << endl << endl;
        }
        
      }
      else
        arq << "Não está presente no texto " << i + 1 << "." << endl << endl;
    }
    arq.close();
  }
}

void Output()
{
  ofstream outt;
  string line;
  outt.open("dataset/output/output.txt");
  int n=0;

  for (long unsigned int i=0; i<termos.size(); i++)
  {
    n++;
    ifstream arq;
    arq.open("dataset/out" + to_string(n) + ".data");

    while (getline(arq, line))
      outt << line << endl;

    arq.close();

    string filename = "dataset/out" + to_string(n) + ".data";
    remove(filename.c_str());
  }
}
