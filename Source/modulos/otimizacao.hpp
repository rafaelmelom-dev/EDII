#ifndef OTIMIZACAO_H
#define OTIMIZACAO_H

#include "../utils/utils.hpp"
#include <string>
#include <memory>
#include <string>
#include <bits/stdc++.h>

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
  void codificarArvore(ArvoreBinaria& a, std::string& texto);
  std::unique_ptr<ArvoreBinaria> decodificarArvore(std::string texto, size_t& indice);
  void montarTabelaCodigos(ArvoreBinaria& a, std::string codigoAtual, std::map<char, std::string>& tabelaCodigos);
  void codificarTexto(ArvoreBinaria &a, std::string& texto, std::string& texto_codificado);
  void decodificarTexto(ArvoreBinaria &a, std::string &texto);

public:
  CompHuffman();
  void run();
  void comprimir(std::string texto);
  void descomprimir(std::string texto, int tree_size);
};

#endif
