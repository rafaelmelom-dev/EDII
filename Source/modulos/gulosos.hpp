#ifndef GULOSOS_HPP
#define GULOSOS_HPP

#include <bits/stdc++.h>

using namespace std;

// Algoritmos Gulosos

class MochilaFracionaria {
private:
  const string narrativa;
  struct Item {
      string nome;
      double peso;
      double valor;
  };
  vector<Item> itens;

public:
  MochilaFracionaria();
  void run();
  bool calcularItens(vector<Item>& itens, vector<double>& x, double capacidade);
};

class EscalonamentoIntervalos {
private:
  const string narrativa;
  struct Tarefa {
      string descricao;
      int inicio;
      int fim;
  };
  vector<Tarefa> tarefas;

public:
  EscalonamentoIntervalos();
  void run();
  bool calcularTarefas(vector<Tarefa>& tarefas, vector<int>& x);
};

class Troco {
private:
  const string narrativa;
  vector<int> moedas;

public:
  Troco();
  void run();
  bool calcularTroco(int valor, vector<int>& moedas, vector<int>& troco);
};

#endif
