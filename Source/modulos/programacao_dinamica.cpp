#include "programacao_dinamica.hpp"
#include "../utils/utils.hpp"
#include <bits/stdc++.h>

using namespace std;

// Etapa da mochila 0/1

Mochila01::Mochila01()
    : narrativa("O guarda apresenta uma lista de itens e um pequeno contêiner. "
                "Cada item tem um peso (ou tamanho) e um valor de "
                "sobrevivência atribuído. Você não pode levar \"metade\""
                " de um gerador de oxigênio. É tudo ou nada. Ford está "
                "paralisado pelo medo (e pela péssima poesia Vogon tocando ao "
                "fundo). A decisão é sua.\n") {}

void Mochila01::run() {
  // populando o vetor de itens de sobrevivência
  itens.push_back({"Mini Gerador de Oxigênio (2h)", 3, 80});
  itens.push_back({"Nutri-pasta Sintética (3 dias)", 4, 100});
  itens.push_back({"Kit de Reparo de Furos no Traje", 2, 50});
  itens.push_back({"Sinalizador de Socorro Sub-Etha", 1, 30});
  itens.push_back({"Manual 'Como Sobreviver no Vácuo por 30s'", 5, 70});
  itens.push_back({"Foto de um Gatinho para Moral", 1, 25});

  string input;
  bool input_correto = false;

  pretty_print(
      GREEN + "O Dilema da Sobrevivência (Problema da Mochila 0/1) \n" + RESET,
      20);

  pretty_print(narrativa, 20);

  while (!input_correto) {

    cout << "++++ Itens de Sobrevivência ++++" << endl;
    cout << "nome  |  " << "peso  |  " << "valor de sobrevivência" << endl;
    for (auto &it : itens) {
      cout << it.nome << " | " << it.peso << " | " << it.valor_sobrevivencia
           << endl;
    }
    cout << "++++ Fim ++++" << endl << endl;

    cout << CYAN
         << "Digite \"calcular\", para que o sistema calcule a melhor "
            "combinação possível, visto que temos uma capacidade limitada (10 "
            "unidades)."
         << RESET << endl
         << "> ";
    cin >> input;
    cin.get();
    cout << endl;

    vector<vector<int>> tabela(itens.size() + 1, vector<int>(11, 0));
    if (calcularItens(itens, tabela, 10)) {
      cout << "Itens escolhidos: " << endl;

      int c = 10;
      int total = 0;

      for (int i = itens.size(); i > 0 && c > 0; i--) {
        if (tabela[i][c] != tabela[i - 1][c]) {
          cout << itens[i - 1].nome << endl;
          total += itens[i - 1].peso;
          c -= itens[i - 1].peso;
        }
      }

      cout << "Com capacidade total de: " << total << endl << endl;
    } else {
      cout << RED << "Não foi possível calcular os itens." << RESET << endl;
    }

    if (input == "calcular") {
      input_correto = true;
    } else {
      pretty_print("\nSem usar o sistema para calcular, você pode não levar "
                   "coisas importantes que poderiam ser carregadas.",
                   20);
    }
  }

  pretty_print(GREEN + "\nOs melhores itens possíveis foram coletados" + RESET,
               20);
  pretty_print(
      YELLOW +
          "\nNa tarefa onde temos os itens fracionados, o problema é simples, "
          "pegando os itens com razões mais importantes, e fracionando para "
          "até a capacidade total, mas em problemas binários, levo ou não "
          "certo item, a complexidade aumenta, dado que esse é um problema "
          "combinatório. Então como solução eficiente temos o algoritmo de "
          "programação dinâmica, com complexidade de O(n * p), sendo n, a "
          "quantidade de itens, e p, a capacidade máxima da mochila." +
          RESET,
      20);
  pretty_print(GREEN + "\nFase completa com sucesso!" + RESET, 20);
  wait_enter();
}

bool Mochila01::calcularItens(vector<ItemSobrevivencia> &itens,
                              vector<vector<int>> &tabela, int capacidade) {
  if (itens.empty())
    return false;
  if (tabela.empty())
    return false;
  if (tabela.size() != (itens.size() + 1))
    return false;
  if (tabela[0].size() != (capacidade + 1))
    return false;

  for (int i = 1; i <= itens.size(); i++) {
    for (int j = 1; j <= capacidade; j++) {
      int peso = itens[i - 1].peso;
      int valor = itens[i - 1].valor_sobrevivencia;

      if (peso <= j) {
        tabela[i][j] = max(tabela[i - 1][j], valor + tabela[i - 1][j - peso]);
      } else {
        tabela[i][j] = tabela[i - 1][j];
      }
    }
  }

  return true;
}
