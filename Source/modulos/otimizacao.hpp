#ifndef OTIMIZACAO_H
#define OTIMIZACAO_H

#include <bits/stdc++.h>
using namespace std;

class CompHuffman {
private:
  string mensagem_esperada;
  const string narrativa;

  struct ArvoreBinaria {
    int valor;
    char raiz;
    unique_ptr<ArvoreBinaria> esquerda;
    unique_ptr<ArvoreBinaria> direita;
  };
  unique_ptr<ArvoreBinaria> arvoreHuffman;
  void montarArvore(string texto);
  void codificarArvore(ArvoreBinaria &a, string &texto);
  unique_ptr<ArvoreBinaria> decodificarArvore(string texto,
                                                   size_t &indice);
  void montarTabelaCodigos(ArvoreBinaria &a, string codigoAtual,
                           map<char, string> &tabelaCodigos);
  void codificarTexto(ArvoreBinaria &a, string &texto,
                      string &texto_codificado);
  void decodificarTexto(ArvoreBinaria &a, string &texto);

public:
  CompHuffman();
  void run();
  void comprimir(string texto);
  void descomprimir(string texto, int tree_size);
};

class Hashing {
private:
  const string narrativa;
  const string mensagem_cod_esperada;
  const string mensagem_esperada;
  const string arvore_esperada;
  unsigned long stringParaIntChave(string chave_string);
  int funcaoMeioQuadrado(int chave, int digitos_tabela);
  int enlacamentoLimite(int chave, int digitos_tabela);

  struct Item {
    string chave;
    string desc;
  };

  void mostrarTabelaMeioQuadrado();
  void mostrarTabelaEnlacLimite();
  vector<Item> tabelaMeioQuadrado[100];
  vector<Item> tabelaEnlacLimite[100];

public:
  Hashing();
  void run();

  bool inserirMeioQuadrado(Item item);
  bool buscarMeioQuadrado(string chave, Item &item);

  bool inserirEnlacLimite(Item item);
  bool buscarEnlacLimite(string chave, Item &item);
};

#endif
