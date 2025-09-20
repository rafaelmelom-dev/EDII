#include "grafos.hpp"
#include "../utils/utils.hpp"
#include <limits> // Necessário para numeric_limits

/// grafo - gerenciando vertices e arestas

Grafo::Grafo() { grafo = map<string, vector<pair<string, int>>>(); }

void Grafo::addVertice(string vertice) {
  grafo[vertice] = vector<pair<string, int>>();
}

void Grafo::removerVertice(string vertice) {
  grafo.erase(vertice);

  for (auto it = grafo.begin(); it != grafo.end(); ++it) {
    for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
      if (it2->first == vertice) {
        it->second.erase(it2);
        break;
      }
    }
  }
}

void Grafo::addAresta(string origem, string destino, int custo) {
  grafo[origem].push_back(make_pair(destino, custo));
}

void Grafo::removerAresta(string origem, string destino) {
  for (auto it = grafo[origem].begin(); it != grafo[origem].end(); ++it) {
    if (it->first == destino) {
      grafo[origem].erase(it);
      break;
    }
  }
}

void Grafo::printAdjacencias() {
  for (const auto &par : grafo) {
    cout << par.first << "-> ";
    for (const auto &adj : par.second) {
      cout << "(" << adj.first << ", " << adj.second << ") ";
    }
    cout << endl;
  }
}

map<string, vector<pair<string, int>>> Grafo::estrutura() { return grafo; }

bool Grafo::temVertice(string vertice) { return grafo.count(vertice) > 0; }

// módulo 1 - reconstruindo e mostrando o grafo
ReconsGrafo::ReconsGrafo()
    : narrativa(
          "Ford aponta para uma lacuna gritante no mapa. \"Olhe aqui! Todo "
          "mundo sabe que há uma rota comercial direta entre 'Santraginus V', "
          "famoso por seu solo rico em minerais para chá, e o "
          "'Frogstar B'. Sem essa rota, nossos cálculos de caminho ficarão "
          "completamente errados. Terráqueo, use a interface de baixo nível "
          "para adicionar manualmente a rota que falta. Os sensores indicam "
          "que a distância é de 7 parsecs.\"\n") {}

void ReconsGrafo::run() {
  Grafo grafo;
  grafo.addVertice("Magrathea");
  grafo.addAresta("Ponto de Partida", "Santraginus V", 4);
  grafo.addAresta("Ponto de Partida", "Nebulosa da Indiferença", 10);
  grafo.addAresta("Santraginus V", "Damogran", 5);
  grafo.addAresta("Frogstar B", "Magrathea", 9);
  grafo.addAresta("Nebulosa da Indiferença", "Damogran", 3);
  grafo.addAresta("Damogran", "Magrathea", 6);

  string vertice_origem;
  string vertice_destino;
  int valor;
  bool vertice_certo_adicionado = false;

  pretty_print(GREEN +
                   "Reconstruindo o Mapa Estelar (Modificação e Visualização "
                   "de Grafo) \n" +
                   RESET,
               20);
  pretty_print(narrativa, 20);

  while (!vertice_certo_adicionado) {
    cout << CYAN << "Digite o nome do planeta origem " << RESET << endl << "> ";
    getline(cin, vertice_origem);
    cout << CYAN << "Digite o nome do planeta destino " << RESET << endl
         << "> ";
    getline(cin, vertice_destino);
    cout << CYAN << "Digite também a distância entre os planetas " << RESET
         << endl
         << "> ";
    cin >> valor;
    cin.ignore();
    cout << endl;

    if ((vertice_origem == "Santraginus V" || vertice_origem == "Frogstar B") &&
        (vertice_destino == "Santraginus V" ||
         vertice_destino == "Frogstar B") &&
        valor == 7) {
      grafo.addAresta(vertice_origem, vertice_destino, valor);
      grafo.addAresta(vertice_destino, vertice_origem, valor);
      vertice_certo_adicionado = true;
    } else {
      pretty_print(
          "\nEssa entrada pode não ter o efeito desejado, talvez tenha que usar o nome do arquivo \
que Ford sugeriu.\n",
          20);
    }
  }

  pretty_print(
      GREEN +
          "\nMapa reconstruído com sucesso, agora podemos também visualizá-lo, "
          "para ficar mais fácil de interpretar, funciona da seguinte maneira "
          "(origem, destino, distância)!!!\n" +
          RESET,
      20);

  grafo.printAdjacencias();

  cout << endl;
  pretty_print(GREEN + "Fase completa com sucesso !" + RESET, 20);

  wait_enter();
}

// modulo 2 - encontrando caminhos
BuscaGrafo::BuscaGrafo()
    : narrativa(
          "Com o mapa minimamente reparado, surge um debate na ponte. Zaphod "
          "quer chegar logo, Ford quer a rota mais segura e Trillian quer "
          "explorar as opções. Isso gera três desafios de busca.\n") {}

void BuscaGrafo::run() {
  Grafo grafo;
  grafo.addVertice("Magrathea");
  grafo.addAresta("Ponto de Partida", "Santraginus V", 4);
  grafo.addAresta("Ponto de Partida", "Nebulosa da Indiferença", 10);
  grafo.addAresta("Santraginus V", "Damogran", 5);
  grafo.addAresta("Frogstar B", "Magrathea", 9);
  grafo.addAresta("Nebulosa da Indiferença", "Damogran", 3);
  grafo.addAresta("Damogran", "Magrathea", 6);
  grafo.addAresta("Santraginus V", "Frogstar B", 7);
  grafo.addAresta("Frogstar B", "Santraginus V", 7);

  pretty_print(
      GREEN + "Em Busca do Caminho Perfeito (Buscas em Grafo)\n" + RESET, 20);
  pretty_print(narrativa, 20);

  bfs_init(grafo, "Ponto de Partida", "Magrathea");
  dfs_init(grafo, "Nebulosa da Indiferença", "Damogran");
  dijkstra_init(grafo, "Ponto de Partida", "Magrathea");

  pretty_print(
      YELLOW +
          "Na nossa situação a busca utilizando BFS e Dijkstra nos levou "
          "a um mesmo caminho por um mesmo custo, mas em casos que temos "
          "muitos pontos interligados no grafo, podemos ter uma "
          "eficiência melhor com o algoritmo de dijkstra." +
          RESET,
      20);
  cout << endl;

  pretty_print(GREEN + "Fase completa com sucesso !" + RESET, 20);

  wait_enter();
}

void BuscaGrafo::dijkstra_init(Grafo &grafo, string origem, string destino) {
  if (!grafo.temVertice(origem)) {
    pretty_print(RED + "\nErro: O vértice de origem '" + origem +
                     "' não existe no grafo.\n" + RESET,
                 20);
    return;
  }
  if (!grafo.temVertice(destino)) {
    pretty_print(RED + "\nErro: O vértice de destino '" + destino +
                     "' não existe no grafo.\n" + RESET,
                 20);
    return;
  }

  pretty_print(
      GREEN +
          "Parte C: A Rota Mais Rápida e Segura (Algoritmo de Dijkstra) \n" +
          RESET,
      20);
  pretty_print("Ford finalmente intervém com sensatez. \"Ok, menos saltos é "
               "uma ideia, mas as distâncias importam! Cada parsec que "
               "viajamos consome combustível e aumenta nossa exposição. "
               "Precisamos encontrar a rota com o menor custo total—o caminho "
               "mais curto—de onde estamos até Magrathea.\"\n\n",
               20);
  pretty_print(
      YELLOW + "Executando a busca por Magrathea utilizando Dijkstra." + RESET,
      20);

  map<string, vector<pair<string, int>>> g = grafo.estrutura();
  map<string, int> custos;
  map<string, string> pred;
  priority_queue<pair<int, string>, vector<pair<int, string>>,
                 greater<pair<int, string>>>
      pq;
  bool caminho_encontrado = false;

  // Inicializar todos os custos como "infinito"
  for (auto const &[vertice, adjacencias] : g) {
    custos[vertice] = numeric_limits<int>::max();
  }

  custos[origem] = 0;
  pq.push({0, origem});

  while (!pq.empty()) {
    string atual = pq.top().second;
    pq.pop();
    if (atual == destino) {
      int custo = 0;

      caminho_encontrado = true;
      vector<string> path;
      string curr = destino;
      while (curr != origem) {
        path.push_back(curr);
        curr = pred[curr];
      }
      path.push_back(origem);
      reverse(path.begin(), path.end());

      custo = custos[destino];

      string path_str = "";
      for (size_t i = 0; i < path.size(); ++i) {
        path_str += path[i];
        if (i < path.size() - 1) {
          path_str += " -> ";
        }
      }
      pretty_print(GREEN + "Caminho encontrado: " + path_str +
                       " com custo de " + to_string(custo) + " parsecs \n" +
                       RESET,
                   20);
      break;
    };
    for (auto vizinho : g[atual]) {
      int novo_custo = custos[atual] + vizinho.second;
      if (novo_custo < custos[vizinho.first]) {
        custos[vizinho.first] = novo_custo;
        pred[vizinho.first] = atual;
        pq.push({custos[vizinho.first], vizinho.first});
      }
    }
  }

  if (!caminho_encontrado) {
    pretty_print(YELLOW + "Caminho não encontrado entre " + origem + " e " +
                     destino + ".\n" + RESET,
                 20);
  }
}

void BuscaGrafo::dfs_init(Grafo &grafo, string origem, string destino) {
  if (!grafo.temVertice(origem)) {
    pretty_print(RED + "\nErro: O vértice de origem '" + origem +
                     "' não existe no grafo.\n" + RESET,
                 20);
    return;
  }
  if (!grafo.temVertice(destino)) {
    pretty_print(RED + "\nErro: O vértice de destino '" + destino +
                     "' não existe no grafo.\n" + RESET,
                 20);
    return;
  }

  pretty_print(GREEN +
                   "Parte B: Explorando uma Rota Desconhecida (Busca em "
                   "Profundidade - DFS) \n" +
                   RESET,
               20);
  pretty_print(
      "Trillian nota uma anomalia. \"Há leituras de energia estranhas vindo "
      "das profundezas da 'Nebulosa da Indiferença'. Antes de nos "
      "comprometermos com uma rota, podemos verificar se existe um caminho que "
      "passa por lá até 'Damogran'? Quero ver se essa rota é viável.\"\n\n",
      20);
  pretty_print(YELLOW +
                   "Executando a busca para verificar um caminho entre a "
                   "Nebulosa da Indiferença e Damogran utilizando DFS." +
                   RESET,
               20);
  map<string, vector<pair<string, int>>> g = grafo.estrutura();
  map<string, bool> visitados;
  int achado = 0;

  for (auto it = g.begin(); it != g.end(); ++it) {
    visitados[it->first] = false;
  }

  dfs(g, origem, destino, visitados, achado);

  if (!achado) {
    pretty_print(GREEN + "Caminho não encontrado!\n" + RESET, 20);
  }
}

void BuscaGrafo::dfs(map<string, vector<pair<string, int>>> &g, string origem,
                     string destino, map<string, bool> &visitados,
                     int &achado) {
  if (origem == destino) {
    pretty_print(GREEN + "Caminho encontrado!\n" + RESET, 20);
    achado = 1;
    return;
  }

  visitados[origem] = true;

  for (auto vizinho : g[origem]) {
    if (!visitados[vizinho.first]) {
      dfs(g, vizinho.first, destino, visitados, achado);
    }
  }
}

void BuscaGrafo::bfs_init(Grafo &grafo, string origem, string destino) {
  if (!grafo.temVertice(origem)) {
    pretty_print(RED + "\nErro: O vértice de origem '" + origem +
                     "' não existe no grafo.\n" + RESET,
                 20);
    return;
  }
  if (!grafo.temVertice(destino)) {
    pretty_print(RED + "\nErro: O vértice de destino '" + destino +
                     "' não existe no grafo.\n" + RESET,
                 20);
    return;
  }

  pretty_print(
      GREEN + "Parte A: A Rota com Menos Paradas (Busca em Largura - BFS) \n" +
          RESET,
      20);
  pretty_print(
      "Zaphod está impaciente. \"Chega de análise! Qual é o caminho "
      "com o menor número de saltos? Menos paradas, menos chances de "
      "encontrar Vogons ou, pior, de ficar sem bebida! Não me importo "
      "com a distância, só quero saltar o mínimo de vezes possível!\"\n\n",
      20);
  pretty_print(
      YELLOW + "Executando a busca por Magrathea utilizando BFS." + RESET, 20);

  map<string, vector<pair<string, int>>> g = grafo.estrutura();
  map<string, string> pred;
  map<string, bool> visitados;
  queue<string> q;

  visitados[origem] = true;
  q.push(origem);

  bool caminho_encontrado = false;

  while (!q.empty()) {
    string atual = q.front();
    q.pop();

    if (atual == destino) {
      int custo = 0;

      caminho_encontrado = true;
      vector<string> path;
      string curr = destino;
      while (curr != origem) {
        path.push_back(curr);
        curr = pred[curr];
      }
      path.push_back(origem);
      reverse(path.begin(), path.end());

      for (auto it = path.begin(); it != path.end() - 1; ++it) {
        for (auto it2 = g[*it].begin(); it2 != g[*it].end(); ++it2) {
          if (it2->first == *next(it)) {
            custo += it2->second;
            break;
          }
        }
      }

      string path_str = "";
      for (size_t i = 0; i < path.size(); ++i) {
        path_str += path[i];
        if (i < path.size() - 1) {
          path_str += " -> ";
        }
      }
      pretty_print(GREEN + "Caminho encontrado: " + path_str +
                       " com custo de " + to_string(custo) + " parsecs \n" +
                       RESET,
                   20);
      break;
    }

    for (auto &it : g[atual]) {
      if (grafo.temVertice(it.first) && !visitados[it.first]) {
        visitados[it.first] = true;
        pred[it.first] = atual;
        q.push(it.first);
      }
    }
  }

  if (!caminho_encontrado) {
    pretty_print(YELLOW + "Caminho não encontrado entre " + origem + " e " +
                     destino + ".\n" + RESET,
                 20);
  }
}

// modulo 3 - algoritmos variados
AlgGrafos::AlgGrafos()
    : narrativa(
          "Ao chegar na órbita de Magrathea, vocês descobrem que o planeta "
          "está protegido por sistemas automatizados antigos e enigmáticos. "
          "Para pousar, é preciso interagir com esses sistemas.\n") {}

void AlgGrafos::run() {
  pretty_print(
      GREEN + "Superando as Defesas de Magrathea (Algoritmos Avançados)\n" +
          RESET,
      20);
  pretty_print(narrativa, 20);

  colorir();
  ordTop();
  agm();

  pretty_print(YELLOW +
                   "Como esses algoritmos funcionam em casos muito "
                   "específicos, nós abordamos apenas seu funcionamento." +
                   RESET,
               20);
  cout << endl;

  pretty_print(GREEN + "Fase completa com sucesso !" + RESET, 20);

  wait_enter();
}

void AlgGrafos::colorir() {
  pretty_print(
      GREEN +
          "Parte A: Sincronizando Frequências de Escudo (Coloração de Grafo "
          "com Welsh-Powell)\n" +
          RESET,
      20);
  pretty_print(
      "Uma rede de satélites defensivos envolve o planeta. Para passar, "
      "a \" Coração de Ouro\" precisa modular seus escudos. Cada satélite "
      "opera em uma frequência, e "
      "satélites que podem se comunicar diretamente (adjacentes) não podem "
      "usar a mesma frequência para evitar interferência. Vocês têm um número "
      "limitado de moduladores de frequência. Qual o número mínimo de "
      "frequências necessárias para que a rede opere sem conflitos?\n\n",
      20);
  pretty_print(YELLOW +
                   "Executando o algoritmo de coloração Welsh-Powell para as "
                   "zonas de Magrathea." +
                   RESET,
               20);

  map<string, vector<string>> grafo;
  grafo["A"] = {"B", "C", "D"};
  grafo["B"] = {"A", "C"};
  grafo["C"] = {"A", "B", "D"};
  grafo["D"] = {"A", "C", "E"};
  grafo["E"] = {"D"};

  string texto = "\nRepresentação do grafo de zonas para coloração:\n";
  for (const auto &entry : grafo) {
    texto += "  " + entry.first + " -> ";
    for (size_t i = 0; i < entry.second.size(); ++i) {
      texto += entry.second[i];
      if (i < entry.second.size() - 1) {
        texto += ", ";
      }
    }
    texto += "\n";
  }
  pretty_print(GREEN + texto + RESET, 20);

  map<string, int> graus;
  for (const auto &p : grafo) {
    graus[p.first] = p.second.size();
  }

  vector<pair<int, string>> vertices_ordenados;
  for (const auto &p : graus) {
    vertices_ordenados.push_back({p.second, p.first});
  }

  sort(vertices_ordenados.rbegin(), vertices_ordenados.rend());

  map<string, int> cores;
  int maximo_cores = 0;

  for (const auto &e : vertices_ordenados) {
    string vertice = e.second;

    if (cores.find(vertice) == cores.end()) {
      set<int> cores_usadas_vizinhos;
      for (const string &vizinho : grafo[vertice]) {
        if (cores.count(vizinho)) {
          cores_usadas_vizinhos.insert(cores[vizinho]);
        }
      }

      int cor_atual = 1;

      while (cores_usadas_vizinhos.count(cor_atual)) {
        cor_atual++;
      }
      cores[vertice] = cor_atual;
      if (cor_atual > maximo_cores) {
        maximo_cores = cor_atual;
      }
    }
  }

  string result_str = "\nResultados da coloração Welsh-Powell: \n";
  for (const auto &p : cores) {
    result_str += "  Zona " + p.first + ": Cor " + to_string(p.second) + "\n";
  }
  result_str +=
      "\nNúmero total de cores utilizadas: " + to_string(maximo_cores);
  pretty_print(GREEN + result_str + RESET, 20);
  cout << endl;
}

void AlgGrafos::ordTop() {
  pretty_print(GREEN +
                   "Parte B: A Sequência de Ativação do Portal (Ordenação "
                   "Topológica)\n" +
                   RESET,
               20);
  pretty_print(
      "O acesso final é através de um portal de energia. Para ativá-lo, uma "
      "série de relés de energia deve ser ligada em uma ordem específica. "
      "Alguns relés dependem de outros para serem ativados. O painel mostra um "
      "diagrama de dependências, mas não a ordem linear. Vocês precisam "
      "encontrar a sequência correta de ativação.\n\n",
      20);
  pretty_print(
      YELLOW +
          "Executando o algoritmo de Kahn para determinar a sequência de "
          "ativação dos relés." +
          RESET,
      20);

  map<string, vector<string>> grafo_top;
  grafo_top["Relé_Alfa"] = {"Relé_Beta", "Relé_Gama"};
  grafo_top["Relé_Beta"] = {"Relé_Delta"};
  grafo_top["Relé_Gama"] = {"Relé_Delta"};
  grafo_top["Relé_Delta"] = {"Relé_Épsilon"};
  grafo_top["Relé_Épsilon"] = {};

  string texto = "\nRepresentação do grafo de relés para ordenação topológica:\n";
  for (const auto &entry : grafo_top) {
    texto += "  " + entry.first + " -> ";
    for (size_t i = 0; i < entry.second.size(); ++i) {
      texto += entry.second[i];
      if (i < entry.second.size() - 1) {
        texto += ", ";
      }
    }
    texto += "\n";
  }
  pretty_print(GREEN + texto + RESET, 20);

  set<string> vertices;
  for (const auto &p : grafo_top) {
    vertices.insert(p.first);
    for (const string &neighbor : p.second) {
      vertices.insert(neighbor);
    }
  }

  map<string, int> vertices_graus;
  for (const string &vertice : vertices) {
    vertices_graus[vertice] = 0;
  }

  for (auto const &[u, neighbors] : grafo_top) {
    for (const string &v : neighbors) {
      vertices_graus[v]++;
    }
  }

  queue<string> q;
  for (auto const &[vertice, grau] : vertices_graus) {
    if (grau == 0) {
      q.push(vertice);
    }
  }

  vector<string> ordem_topologica;
  while (!q.empty()) {
    string u = q.front();
    q.pop();
    ordem_topologica.push_back(u);

    for (const string &v : grafo_top[u]) {
      vertices_graus[v]--;
      if (vertices_graus[v] == 0) {
        q.push(v);
      }
    }
  }

  string result_str =
      "\nOrdem de inicialização dos relés (Ordenação Topológica Kahn): \n";
  if (ordem_topologica.size() == vertices.size()) {
    for (size_t i = 0; i < ordem_topologica.size(); ++i) {
      result_str += ordem_topologica[i];
      if (i < ordem_topologica.size() - 1) {
        result_str += " -> ";
      }
    }
  } else {
    result_str +=
        "Um ciclo foi detectado no grafo, ordenação topológica não é possível.";
  }

  pretty_print(GREEN + result_str + RESET, 20);
  cout << endl;
}

void AlgGrafos::agm() {
  pretty_print(GREEN +
                   "Parte C: O Mínimo Esforço de Comunicação (Árvore Geradora "
                   "Mínima)\n" +
                   RESET,
               20);
  pretty_print(
      "O portal está aberto, mas Magrathea ainda não responde. Marvin, com um "
      "suspiro, aponta: \"Para iniciar o contato, é necessário criar uma rede "
      "de comunicação de baixa energia entre os pontos de contato orbitais. A "
      "matriz de custos de energia para conectar cada par de pontos é "
      "conhecida. Devemos ativar apenas as conexões essenciais para interligar "
      "todos os pontos com o mínimo de energia gasta, ou o planeta considerará "
      "nosso esforço excessivo e fútil.\"\n\n",
      20);
  pretty_print(YELLOW +
                   "Executando o algoritmo de Kruskal para otimizar a rede de "
                   "energia de Magrathea." +
                   RESET,
               20);

  vector<tuple<int, string, string>> arestas;
  arestas.emplace_back(10, "P1", "P2");
  arestas.emplace_back(15, "P1", "P3");
  arestas.emplace_back(30, "P1", "P4");
  arestas.emplace_back(40, "P2", "P3");
  arestas.emplace_back(20, "P2", "P4");
  arestas.emplace_back(50, "P3", "P4");

  sort(arestas.begin(), arestas.end());

  map<string, string> parent;
  map<string, int> sz;

  set<string> vertices_set;
  for (const auto &aresta : arestas) {
    vertices_set.insert(get<1>(aresta));
    vertices_set.insert(get<2>(aresta));
  }

  for (const string &v : vertices_set) {
    parent[v] = v;
    sz[v] = 1;
  }

  function<string(string)> find_set = [&](string v) {
    if (v == parent[v])
      return v;
    return parent[v] = find_set(parent[v]);
  };

  auto union_sets = [&](string a, string b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
      if (sz[a] < sz[b])
        swap(a, b);
      parent[b] = a;
      sz[a] += sz[b];
      return true;
    }
    return false;
  };

  vector<tuple<string, string, int>> mst_arestas;
  int mst_custo_total = 0;

  for (const auto &aresta : arestas) {
    int weight = get<0>(aresta);
    string u = get<1>(aresta);
    string v = get<2>(aresta);

    if (union_sets(u, v)) {
      mst_arestas.emplace_back(u, v, weight);
      mst_custo_total += weight;
    }
  }

  string texto = "\nGrafo normal: \n";
  for (const auto &aresta : arestas) {
    texto += "  (" + get<1>(aresta) + ", " + get<2>(aresta) + ", " +
              to_string(get<0>(aresta)) + ")\n";
  }
  texto += "\n";

  string result_str = "\nÁrvore Geradora Mínima (Kruskal): \n";
  for (const auto &aresta : mst_arestas) {
    result_str += "  (" + get<0>(aresta) + ", " + get<1>(aresta) + ", " +
                  to_string(get<2>(aresta)) + ")\n";
  }
  result_str +=
      "\nCusto total da MST: " + to_string(mst_custo_total) + " parsecs\n";

  pretty_print(GREEN + texto + RESET, 20);
  pretty_print(GREEN + result_str + RESET, 20);
  cout << endl;
}
