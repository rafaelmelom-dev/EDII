#ifndef GRAFOS_H
#define GRAFOS_H

#include <bits/stdc++.h>

using namespace std;

// gerenciando grafos
class Grafo {
private:
  map<string, vector<pair<string, int>>> grafo;

public:
  Grafo();
  void addVertice(string vertice);
  void removerVertice(string vertice);
  void addAresta(string origem, string destino, int custo);
  void removerAresta(string origem, string destino);
  void printAdjacencias();
  bool temVertice(string vertice);
  map<string, vector<pair<string, int>>> estrutura();
};

// modulo 1 - reconstruindo o grafo
class ReconsGrafo {
private:
  const string narrativa;

public:
  ReconsGrafo();
  void run();
};

// modulo 2 - busca em grafo
class BuscaGrafo {
private:
  const string narrativa;

public:
  BuscaGrafo();
  void run();
  void dijkstra_init(Grafo &grafo, string origem, string destino);
  void dfs_init(Grafo &grafo, string origem, string destino);
  void dfs(map<string, vector<pair<string, int>>> &g, string origem,
           string destino, map<string, bool> &visitados, int &achado);
  void bfs_init(Grafo &grafo, string origem, string destino);
};

// modulo 3 - algoritmos variados
class AlgGrafos {
private:
  const string narrativa;

public:
  AlgGrafos();
  void run();
  void colorir();
  void ordTop();
  void agm();
};

#endif
