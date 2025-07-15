#include "otimizacao.hpp"
#include "../utils/utils.hpp"
#include <bits/stdc++.h>
#include <bitset>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

bool cmp(const std::pair<char, int> &a, const std::pair<char, int> &b) {
  if (a.second == b.second) {
    return (int)a.first > (int)b.first;
  }

  return a.second < b.second;
}

void CompHuffman::montarArvore(std::string texto) {
  std::map<char, int> letras_freq;

  // calculando a frequência das letras
  for (char c : texto) {
    try {
      letras_freq.at(c) += 1;
    } catch (const std::out_of_range &ex) {
      letras_freq[c] = 1;
    }
  }

  std::vector<std::pair<char, int>> freqs;

  for (auto &elemento : letras_freq) {
    freqs.push_back(elemento);
  }

  std::sort(freqs.begin(), freqs.end(), cmp);
  std::vector<std::unique_ptr<ArvoreBinaria>> arvore_freqs;

  // criando um vetor de arvores
  for (auto &elemento : freqs) {
    auto b = std::make_unique<ArvoreBinaria>();
    b->valor = elemento.second;
    b->raiz = elemento.first;
    arvore_freqs.push_back(std::move(b));
  }

  // ordenando e juntando essas arvores
  while (arvore_freqs.size() > 1) {
    std::unique_ptr<ArvoreBinaria> filha_esquerda = std::move(arvore_freqs[0]);
    std::unique_ptr<ArvoreBinaria> filha_direita = std::move(arvore_freqs[1]);

    auto no = std::make_unique<ArvoreBinaria>();
    no->valor = filha_esquerda->valor + filha_direita->valor;
    no->raiz = '\0';
    no->esquerda = std::move(filha_esquerda);
    no->direita = std::move(filha_direita);

    arvore_freqs.erase(arvore_freqs.begin());
    arvore_freqs.erase(arvore_freqs.begin());

    bool inserido = false;
    for (size_t i = 0; i < arvore_freqs.size(); ++i) {
      if (arvore_freqs[i]->valor > no->valor) {
        arvore_freqs.insert(arvore_freqs.begin() + i, std::move(no));
        inserido = true;
        break;
      }
    }

    if (!inserido) {
      arvore_freqs.push_back(std::move(no));
    }
  }

  this->arvoreHuffman = std::move(arvore_freqs[0]);
};

void CompHuffman::codificarArvore(ArvoreBinaria &a, std::string &texto) {
  if (!a.esquerda && !a.direita) {
    texto += "1";
    texto += std::bitset<8>((int)a.raiz).to_string();
    return;
  }

  texto += "0";

  codificarArvore(*a.esquerda, texto);
  codificarArvore(*a.direita, texto);
}

std::unique_ptr<CompHuffman::ArvoreBinaria>
CompHuffman::decodificarArvore(std::string texto, size_t &indice) {
  char bit = texto[indice];
  indice++;

  if (bit == '1') {
    int num = 0;
    for (int i = 0; i < 8; ++i) {
      num <<= 1;
      num |= (texto[indice + i] - '0');
    }
    indice += 8;

    std::unique_ptr<ArvoreBinaria> b = std::make_unique<ArvoreBinaria>();
    b->raiz = (char)num;
    b->esquerda = nullptr;
    b->direita = nullptr;

    return b;
  } else {
    std::unique_ptr<ArvoreBinaria> b = std::make_unique<ArvoreBinaria>();
    b->raiz = '\0';

    b->esquerda = decodificarArvore(texto, indice);
    b->direita = decodificarArvore(texto, indice);

    return b;
  }
}

void CompHuffman::montarTabelaCodigos(
    ArvoreBinaria &a, std::string codigoAtual,
    std::map<char, std::string> &tabelaCodigos) {
  if (a.esquerda == nullptr && a.direita == nullptr) {
    tabelaCodigos[a.raiz] = codigoAtual;
  }

  if (a.esquerda != nullptr) {
    montarTabelaCodigos(*a.esquerda, codigoAtual + "0", tabelaCodigos);
  }
  if (a.direita != nullptr) {
    montarTabelaCodigos(*a.direita, codigoAtual + "1", tabelaCodigos);
  }
}

void CompHuffman::codificarTexto(ArvoreBinaria &a, std::string &texto,
                                 std::string &texto_codificado) {
  std::map<char, std::string> codigos;
  texto_codificado = "";

  montarTabelaCodigos(*this->arvoreHuffman, "", codigos);

  for (char c : texto) {
    texto_codificado += codigos.at(c);
  }
}

void CompHuffman::decodificarTexto(ArvoreBinaria &a, std::string &texto) {
  std::string bits_codificados = texto;
  texto.clear();

  ArvoreBinaria *no_atual = &a;
  size_t bit_indice = 0;

  while (bit_indice < bits_codificados.length()) {
    char bit = bits_codificados[bit_indice];
    bit_indice++;

    if (bit == '0') {
      no_atual = no_atual->esquerda.get();
    } else {
      no_atual = no_atual->direita.get();
    }

    if (no_atual->esquerda == nullptr && no_atual->direita == nullptr) {
      texto += no_atual->raiz;
      no_atual = &a;
    }
  }
}

CompHuffman::CompHuffman()
    : mensagem_esperada("Encontramos Magrathea. Precisamos de uma toalha extra "
                        "e chá. Atrasem os Vogons. Zaphod."),
      narrativa(
          "Zaphod redigiu uma mensagem urgente para um contato em um posto avançado próximo a Magrathea. A mensagem \
é:" + GREEN +  "\"Encontramos Magrathea. Precisamos de uma toalha extra e chá. Atrasem os Vogons. Zaphod.\"" + RESET + ". Para que os scanners \
Vogons não a identifiquem como linguagem, você precisa transformá-la em uma sequência de bits o mais curta e \
indecifrável possível. A única maneira de fazer isso eficientemente é analisando a frequência de cada caractere e \
construindo uma árvore de Huffman para gerar códigos de bits de tamanho variável.\n") {
}

void CompHuffman::run() {
  std::string input;
  bool mensagem_esperada_input = false;

  pretty_print(GREEN + "O Código de Huffman (Compressão de Dados) \n" + RESET,
               20);

  pretty_print(narrativa, 20);

  while (!mensagem_esperada_input) {
    std::cout << CYAN << "Digite o texto a ser comprimido"
              << RESET << std::endl
              << "> ";
    std::getline(std::cin, input);
    std::cout << std::endl;

    comprimir(input);

    if (input == mensagem_esperada) {
        mensagem_esperada_input = true;
    } else {
        pretty_print("\nEssa mensagem pode não ter o efeito desejado, talvez tenha que usar a mensagem redigida \
por Zaphod.", 20);
    }
  }

  pretty_print(
      GREEN + "Texto comprimido com sucesso, e mensagem prestes a ser enviada!!!\n" +
          RESET,
      20);
  pretty_print(
      YELLOW +
          "A economia na compressão parece ser pouca, mas a nossa mensagem também foi curta, a medida em que \
aumentamos o tamanho da mensagem, a compressão tem resultados melhores. Isso acontece por conta da árvore de decodificação, \
que querendo ou não ocupa algum espaço, e em mensagens pequenas, o algoritmo pode acabar aumentando o tamanho da mensagem!!!\n" +
          RESET,
      20);

  pretty_print(GREEN + "Fase completa com sucesso !" + RESET, 20);

  wait_enter();
};

void CompHuffman::comprimir(std::string texto) {
  std::string texto_codificado;
  std::stringstream res;
  montarArvore(texto);

  codificarTexto(*this->arvoreHuffman, texto, texto_codificado);


  res << CYAN << "Sequência de bits depois da compressão -> " << RESET << texto_codificado << std::endl;

  res << YELLOW << "O texto original tinha " << texto.length() * 8 << "bits e o texto comprimido \
tem " << texto_codificado.length() << "bits sem a árvore de decodificação." << std::endl;
  res << "Tendo uma redução de " << std::setprecision(2) << ((float)texto_codificado.length() / (float)(texto.length() * 8)) * 100 << "% no tamanho da mensagem.\n" + RESET;

  pretty_print(res.str(), 5);
};

void CompHuffman::descomprimir(std::string texto, int tree_size) {
  std::string texto_decodificado =
      texto.substr(tree_size, texto.length() - tree_size);

  size_t ind = 0;
  this->arvoreHuffman = decodificarArvore(texto.substr(0, tree_size), ind);

  decodificarTexto(*this->arvoreHuffman, texto_decodificado);

  std::cout << texto_decodificado << std::endl;
};
