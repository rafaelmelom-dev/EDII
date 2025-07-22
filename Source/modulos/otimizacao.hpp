#ifndef OTIMIZACAO_H
#define OTIMIZACAO_H

#include "../utils/utils.hpp"
#include <bits/stdc++.h>
#include <memory>
#include <string>
#include <vector>

class CompHuffman {
private:
  std::string mensagem_esperada;
  const std::string narrativa;

  struct ArvoreBinaria {
    int valor;
    char raiz;
    std::unique_ptr<ArvoreBinaria> esquerda;
    std::unique_ptr<ArvoreBinaria> direita;
  };
  std::unique_ptr<ArvoreBinaria> arvoreHuffman;
  void montarArvore(std::string texto);
  void codificarArvore(ArvoreBinaria &a, std::string &texto);
  std::unique_ptr<ArvoreBinaria> decodificarArvore(std::string texto,
                                                   size_t &indice);
  void montarTabelaCodigos(ArvoreBinaria &a, std::string codigoAtual,
                           std::map<char, std::string> &tabelaCodigos);
  void codificarTexto(ArvoreBinaria &a, std::string &texto,
                      std::string &texto_codificado);
  void decodificarTexto(ArvoreBinaria &a, std::string &texto);

public:
  CompHuffman();
  void run();
  void comprimir(std::string texto);
  void descomprimir(std::string texto, int tree_size);
};

class Hashing {
private:
  const std::string narrativa;
  const std::string mensagem_cod_esperada;
  const std::string mensagem_esperada;
  const std::string arvore_esperada;
  unsigned long stringParaIntChave(std::string chave_string);
  int funcaoMeioQuadrado(int chave, int digitos_tabela);
  int enlacamentoLimite(int chave, int digitos_tabela);

  struct Item {
    std::string chave;
    std::string desc;
  };

  void mostrarTabelaMeioQuadrado();
  void mostrarTabelaEnlacLimite();
  std::vector<Item> tabelaMeioQuadrado[100];
  std::vector<Item> tabelaEnlacLimite[100];

public:
  Hashing();
  void run();

  bool inserirMeioQuadrado(Item item);
  bool buscarMeioQuadrado(std::string chave, Item &item);

  bool inserirEnlacLimite(Item item);
  bool buscarEnlacLimite(std::string chave, Item &item);
};

#endif
