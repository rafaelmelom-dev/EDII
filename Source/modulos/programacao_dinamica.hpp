#ifndef PROGRAMACAO_DINAMICA_HPP
#define PROGRAMACAO_DINAMICA_HPP

#include <bits/stdc++.h>
using namespace std;

class Mochila01 {
private:
  const string narrativa;
  struct ItemSobrevivencia {
      string nome;
      int peso;
      int valor_sobrevivencia;
  };
  vector<ItemSobrevivencia> itens;

public:
  Mochila01();
  void run();
  bool calcularItens(vector<ItemSobrevivencia>& itens, vector<vector<int>>& tabela, int capacidade);
};

#endif
