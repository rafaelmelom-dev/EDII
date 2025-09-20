#include "gulosos.hpp"
#include "../utils/utils.hpp"
#include <bits/stdc++.h>

using namespace std;

// Etapa da mochila fracionária

MochilaFracionaria::MochilaFracionaria()
    : narrativa(
          "Ford joga uma mochila em seu colo. \"Temos exatamente 60 segundos! "
          "Pegue o que for mais valioso! Não precisa pegar o item inteiro, "
          "apenas enfie o máximo que puder aí dentro!\". Você olha ao redor, "
          "vendo itens de valor sentimental e prático. Sua mochila tem uma "
          "capacidade de peso limitada (15kg), e você precisa decidir o que "
          "levar.\n") {}

void MochilaFracionaria::run() {
  // populando o vetor de itens a serem recuperados durante o fim do mundo
  itens.push_back((Item){"Notebook antigo com os seus projetos", 2.5, 80});
  itens.push_back((Item){"Garrafa de Água filtrada", 1.5, 45});
  itens.push_back((Item){"Kit de Primeiros Socorros", 2.0, 50});
  itens.push_back((Item){"Saco de Ração de emergência", 5.0, 120});
  itens.push_back((Item){"Coleção de livros de ficção científica", 10.0, 150});
  itens.push_back((Item){"A Toalha", 0.5, 1000});
  itens.push_back((Item){"Panela de ferro da sua avó", 4.0, 40});

  string input;
  bool input_correto = false;

  pretty_print(
      GREEN + "A Pilhagem Desesperada (Problema da Mochila Fracionária) \n" +
          RESET,
      20);

  pretty_print(narrativa, 20);

  while (!input_correto) {

    cout << "++++ Itens ++++" << endl;
    cout << "nome  |  " << "peso  |  " << "valor" << endl;
    for (auto &it : itens) {
      cout << it.nome << " | " << it.peso << " | " << it.valor << endl;
    }
    cout << "++++ Fim ++++" << endl << endl;

    cout << CYAN
         << "Digite \"calcular\", para que o sistema calcule a melhor "
            "combinação possível, visto que temos pouco tempo."
         << RESET << endl
         << "> ";
    cin >> input;
    cin.get();
    cout << endl;

    vector<double> x(itens.size());

    if (calcularItens(itens, x, 15)) {
      cout << "++++ Itens calculados ++++" << endl;
      cout << "nome  |  " << "peso  |  " << "valor  |  "
           << "porcentagem a pegar" << endl;
      for (int i = 0; i < itens.size(); i++) {
        cout << itens[i].nome << " | " << itens[i].peso << " | "
             << itens[i].valor << "  |  " << x[i] << endl;
      }
      cout << "++++ Fim ++++" << endl << endl;
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

  pretty_print(
      GREEN +
          "\nOs melhores itens possíveis foram coletados, agora "
          "começa a aventura, você está pronto para enfrentar o fim do mundo." +
          RESET,
      20);
  pretty_print(
      YELLOW +
          "\nO algoritmo guloso é simples, mas resolve bem o problema da "
          "mochila fracionária, e com tempo de O(n), que é aceitável." +
          RESET,
      20);
  pretty_print(GREEN + "\nFase completa com sucesso!" + RESET, 20);
  wait_enter();
}

bool MochilaFracionaria::calcularItens(vector<Item> &itens, vector<double> &x,
                                       double capacidade) {
  // saindo da função caso não consiga calcular
  if (x.size() != itens.size())
    return false;
  if (x.size() == 0)
    return false;
  if (capacidade <= 0)
    return false;

  // colocando em ordem crescente
  sort(itens.begin(), itens.end(), [](const Item &a, const Item &b) {
    return a.valor / a.peso > b.valor / b.peso;
  });

  for (int i = 0; i < itens.size(); i++) {
    if (capacidade >= itens[i].peso) {
      capacidade -= itens[i].peso;
      x[i] = 1;
    } else {
      x[i] = capacidade / itens[i].peso;
      capacidade = 0;
    }
  }

  return true;
}

// Etapa do escalonamento de intervalos
EscalonamentoIntervalos::EscalonamentoIntervalos()
    : narrativa("Com a mochila nas costas, Ford lhe entrega um datapad com uma "
                "lista de tarefas urgentes. \"Eu preparei uma lista, mas não "
                "dá pra fazer tudo! Escolha as tarefas para concluirmos o "
                "máximo de coisas possível antes de sairmos daqui!\". Cada "
                "tarefa tem um tempo de início e um tempo de fim.\n") {}

void EscalonamentoIntervalos::run() {
  // populando o vetor de tarefas
  tarefas.push_back((Tarefa){"Ligar sinalizador de carona galáctico", 0, 10});
  tarefas.push_back(
      (Tarefa){"Enviar e-mail de despedida para a família", 5, 25});
  tarefas.push_back((Tarefa){"Desligar o gás da casa", 20, 30});
  tarefas.push_back(
      (Tarefa){"Baixar a Wikipédia inteira (compactada)", 15, 45});
  tarefas.push_back((Tarefa){"Achar as chaves do carro (por hábito)", 28, 40});
  tarefas.push_back((Tarefa){"Tomar uma última xícara de chá", 42, 55});
  tarefas.push_back((Tarefa){"Pegar o peixinho dourado", 50, 58});

  string input;
  bool input_correto = false;

  pretty_print(GREEN +
                   "A Agenda do Apocalipse (Problema do Escalonamento de "
                   "Intervalos) \n" +
                   RESET,
               20);

  pretty_print(narrativa, 20);

  while (!input_correto) {
    cout << "++++ Tarefas ++++" << endl;
    for (auto &it : tarefas) {
      cout << it.descricao << " (" << it.inicio << " - " << it.fim << ")"
           << endl;
    }
    cout << "++++ Fim ++++" << endl << endl;

    cout << CYAN
         << "Digite \"calcular\", para que o sistema calcule a melhor "
            "combinação possível, visto que temos que realizar o máximo de "
            "coisas o possível."
         << RESET << endl
         << "> ";
    cin >> input;
    cin.get();
    cout << endl;

    vector<int> x(tarefas.size());
    if (calcularTarefas(tarefas, x)) {
      cout << "Tarefas selecionadas:" << endl;
      for (int i = 0; i < x.size(); i++) {
        if (x[i] == 1) {
          cout << tarefas[i].descricao << endl;
        }
      }
      cout << endl;
    }

    if (input == "calcular") {
      input_correto = true;
    } else {
      pretty_print(
          "\nSem usar o sistema para calcular, você pode estar "
          "fazendo algumas coisas, que podem ser úteis ou não. Tente o cálculo "
          "do sistema, assim  você pode ter uma melhor otimização",
          20);
    }
  }

  pretty_print(
      GREEN +
          "\nFoi selecionado a quantidade máxima de tarefas, agora conseguimos "
          "fazer o máximo de coisas em um tempo mais curto" +
          RESET,
      20);
  pretty_print(
      YELLOW +
          "\nOutra aplicação interessante para o algoritmo guloso, escalonando "
          "intervalos, sem sobrepô-los, também com complexidade de O(n)." +
          RESET,
      20);
  pretty_print(GREEN + "\nFase completa com sucesso!" + RESET, 20);
  wait_enter();
}

bool EscalonamentoIntervalos::calcularTarefas(vector<Tarefa> &tarefas,
                                              vector<int> &x) {
  if (tarefas.empty())
    return false;
  if (tarefas.size() != x.size())
    return false;

  // ordenando para as tarefas com um fim mais próximo
  sort(tarefas.begin(), tarefas.end(),
       [](const Tarefa &a, const Tarefa &b) { return a.fim < b.fim; });

  int fim0 = -1;
  for (int i = 0; i < tarefas.size(); i++) {
    if (tarefas[i].inicio > fim0) {
      x[i] = 1;
      fim0 = tarefas[i].fim;
    } else {
      x[i] = 0;
    }
  }

  return true;
}

// Etapa do problema do Troco

Troco::Troco()
    : narrativa("No último minuto, Ford aponta para uma máquina de vendas na "
                "esquina. \"Precisamos de um 'Tradutor Universal Babel Fish'! "
                "Custa 37 créditos!\". Ele joga um punhado de moedas de várias "
                "denominações galácticas em sua mão. \"A máquina não dá troco "
                "e odeia muitas moedas. Use o mínimo possível!\".\n") {}

void Troco::run() {
  moedas = {1, 2, 5, 10, 20};
  int valor = 37;

  string input;
  bool input_correto = false;

  pretty_print(
      GREEN + "O Troco para o Fim do Mundo (Problema do Troco) \n" + RESET, 20);

  pretty_print(narrativa, 20);

  while (!input_correto) {
    cout << "Moedas do sistema monetário galático: ";
    for (auto moeda : moedas) {
      cout << moeda << " ";
    }
    cout << endl;

    cout << CYAN
         << "Digite \"calcular\", para que o sistema calcule o troco correto, "
            "já que não queremos que a máquina fique com o nosso troco."
         << RESET << endl
         << "> ";
    cin >> input;
    cin.get();
    cout << endl;

    vector<int> x;
    if (calcularTroco(valor, moedas, x)) {
      cout << "Moedas usadas: ";
      for (auto moeda : x) {
        cout << moeda << " ";
      }
      cout << endl;
    }

    if (input == "calcular") {
      input_correto = true;
    } else {
      pretty_print("\nSem usar o sistema para calcular, você pode demorar para "
                   "calcular eficientemente o troco.",
                   20);
    }
  }

  pretty_print(
      GREEN +
          "\nFoi selecionado a menor quantidade de moedas para o pagamanto." +
          RESET,
      20);
  pretty_print(
      YELLOW +
          "\nApesar de tempo de complexidade aceitável, o algoritmo guloso, "
          "para o problema do troco não é ótimo. No nosso caso o sistema "
          "monetário galático foi bem projetado, mas se não tivesse certas "
          "opções, o algoritmo guloso não poderia chegar em uma solução ótima, "
          "visto isso, seu uso depende do ambiente." +
          RESET,
      20);
  pretty_print(GREEN + "\nFase completa com sucesso!" + RESET, 20);
  wait_enter();
}

bool Troco::calcularTroco(int valor, vector<int> &moedas, vector<int> &troco) {
  if (moedas.empty())
    return false;
  if (valor <= 0)
    return false;
  troco = {};

  sort(moedas.begin(), moedas.end(), greater<int>());
  int n = moedas.size();
  int i = 0;
  while (valor > 0 && i < n) {
    if (moedas[i] <= valor) {
      troco.push_back(moedas[i]);
      valor -= moedas[i];
    } else {
      i++;
    }
  }
  return true;
}
