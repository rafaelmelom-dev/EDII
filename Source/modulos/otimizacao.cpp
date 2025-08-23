#include "otimizacao.hpp"
#include "../utils/utils.hpp"
#include <bits/stdc++.h>

using namespace std;

bool cmp(const pair<char, int> &a, const pair<char, int> &b) {
  if (a.second == b.second) {
    return (int)a.first > (int)b.first;
  }

  return a.second < b.second;
}

void CompHuffman::montarArvore(string texto) {
  map<char, int> letras_freq;

  // calculando a frequência das letras
  for (char c : texto) {
    try {
      letras_freq.at(c) += 1;
    } catch (const out_of_range &ex) {
      letras_freq[c] = 1;
    }
  }

  vector<pair<char, int>> freqs;

  for (auto &elemento : letras_freq) {
    freqs.push_back(elemento);
  }

  sort(freqs.begin(), freqs.end(), cmp);
  vector<unique_ptr<ArvoreBinaria>> arvore_freqs;

  // criando um vetor de arvores
  for (auto &elemento : freqs) {
    auto b = make_unique<ArvoreBinaria>();
    b->valor = elemento.second;
    b->raiz = elemento.first;
    arvore_freqs.push_back(move(b));
  }

  // ordenando e juntando essas arvores
  while (arvore_freqs.size() > 1) {
    unique_ptr<ArvoreBinaria> filha_esquerda = move(arvore_freqs[0]);
    unique_ptr<ArvoreBinaria> filha_direita = move(arvore_freqs[1]);

    auto no = make_unique<ArvoreBinaria>();
    no->valor = filha_esquerda->valor + filha_direita->valor;
    no->raiz = '\0';
    no->esquerda = move(filha_esquerda);
    no->direita = move(filha_direita);

    arvore_freqs.erase(arvore_freqs.begin());
    arvore_freqs.erase(arvore_freqs.begin());

    bool inserido = false;
    for (size_t i = 0; i < arvore_freqs.size(); ++i) {
      if (arvore_freqs[i]->valor > no->valor) {
        arvore_freqs.insert(arvore_freqs.begin() + i, move(no));
        inserido = true;
        break;
      }
    }

    if (!inserido) {
      arvore_freqs.push_back(move(no));
    }
  }

  this->arvoreHuffman = move(arvore_freqs[0]);
};

void CompHuffman::codificarArvore(ArvoreBinaria &a, string &texto) {
  if (!a.esquerda && !a.direita) {
    texto += "1";
    texto += bitset<8>((int)a.raiz).to_string();
    return;
  }

  texto += "0";

  codificarArvore(*a.esquerda, texto);
  codificarArvore(*a.direita, texto);
}

unique_ptr<CompHuffman::ArvoreBinaria>
CompHuffman::decodificarArvore(string texto, size_t &indice) {
  char bit = texto[indice];
  indice++;

  if (bit == '1') {
    int num = 0;
    for (int i = 0; i < 8; ++i) {
      num <<= 1;
      num |= (texto[indice + i] - '0');
    }
    indice += 8;

    unique_ptr<ArvoreBinaria> b = make_unique<ArvoreBinaria>();
    b->raiz = (char)num;
    b->esquerda = nullptr;
    b->direita = nullptr;

    return b;
  } else {
    unique_ptr<ArvoreBinaria> b = make_unique<ArvoreBinaria>();
    b->raiz = '\0';

    b->esquerda = decodificarArvore(texto, indice);
    b->direita = decodificarArvore(texto, indice);

    return b;
  }
}

void CompHuffman::montarTabelaCodigos(
    ArvoreBinaria &a, string codigoAtual,
    map<char, string> &tabelaCodigos) {
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

void CompHuffman::codificarTexto(ArvoreBinaria &a, string &texto,
                                 string &texto_codificado) {
  map<char, string> codigos;
  texto_codificado = "";

  montarTabelaCodigos(*this->arvoreHuffman, "", codigos);

  for (char c : texto) {
    texto_codificado += codigos.at(c);
  }
}

void CompHuffman::decodificarTexto(ArvoreBinaria &a, string &texto) {
  string bits_codificados = texto;
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
é:" + GREEN +
          "\"Encontramos Magrathea. Precisamos de uma toalha extra e chá. "
          "Atrasem os Vogons. Zaphod.\"" +
          RESET + ". Para que os scanners \
Vogons não a identifiquem como linguagem, você precisa transformá-la em uma sequência de bits o mais curta e \
indecifrável possível. A única maneira de fazer isso eficientemente é analisando a frequência de cada caractere e \
construindo uma árvore de Huffman para gerar códigos de bits de tamanho variável.\n") {
}

void CompHuffman::run() {
  string input;
  bool mensagem_esperada_input = false;

  pretty_print(GREEN + "O Código de Huffman (Compressão de Dados) \n" + RESET,
               20);

  pretty_print(narrativa, 20);

  while (!mensagem_esperada_input) {
    cout << CYAN << "Digite o texto a ser comprimido" << RESET << endl
              << "> ";
    getline(cin, input);
    cout << endl;

    comprimir(input);

    if (input == mensagem_esperada) {
      mensagem_esperada_input = true;
    } else {
      pretty_print(
          "\nEssa mensagem pode não ter o efeito desejado, talvez tenha que usar a mensagem redigida \
por Zaphod.",
          20);
    }
  }

  pretty_print(GREEN +
                   "Texto comprimido com sucesso, e mensagem prestes a ser "
                   "enviada!!!\n" +
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

void CompHuffman::comprimir(string texto) {
  string texto_codificado;
  string texto_arvore;
  stringstream res;
  montarArvore(texto);

  codificarTexto(*this->arvoreHuffman, texto, texto_codificado);
  codificarArvore(*this->arvoreHuffman, texto_arvore);

  res << CYAN << "Sequência de bits depois da compressão -> " << RESET
      << texto_codificado << endl;

  res << endl
      << CYAN << "Sequência de bits da árvore codificada -> " << RESET
      << texto_arvore << endl;

  res << YELLOW << "O texto original tinha " << texto.length() * 8
      << "bits e o texto comprimido \
tem " << texto_codificado.length()
      << "bits sem a árvore de decodificação." << endl;
  res << "Tendo uma redução de " << setprecision(2)
      << ((float)texto_codificado.length() / (float)(texto.length() * 8)) * 100
      << "% no tamanho da mensagem.\n" + RESET;

  pretty_print(res.str(), 5);
};

void CompHuffman::descomprimir(string texto, int tree_size) {
  string texto_decodificado =
      texto.substr(tree_size, texto.length() - tree_size);

  size_t ind = 0;
  this->arvoreHuffman = decodificarArvore(texto.substr(0, tree_size), ind);

  decodificarTexto(*this->arvoreHuffman, texto_decodificado);

  cout << texto_decodificado << endl;
};

////// HASHING

int contarDigitos(long numero) {
  int c = 0;
  int resto;

  while (numero > 0) {
    resto = numero % 10;
    numero /= 10;
    c++;
  }

  return c;
}

Hashing::Hashing()
    : narrativa(
          "Você conseguiu! A mensagem de Zaphod foi brilhantemente transformada em uma sequência compacta de bits. \
Mas, antes de transmiti-la, Ford Prefect o interrompe. \"Espere aí, macaco sem pelos! Nesta nave, você não envia nem um 'oi' sem \
registrar no log de bordo. O Motor de Improbabilidade já bagunçou nossos sistemas uma vez; cada operação precisa ser indexada e armazenada \
de forma que possamos encontrá-la instantaneamente. Se não, ela se perde para sempre no caos.\"\n\n\
Ele aponta para um terminal que exibe uma estrutura de dados peculiar. \"Este é o log principal da nave. É uma tabela hash. Tudo que importa \
está aí. Antes de enviar sua mensagem, você precisa inserir nela uma referência para o texto original, a mensagem comprimida e, o mais importante, \
a árvore de decodificação de Huffman. Sem registrar a árvore, nossa mensagem será tão inútil para nosso contato quanto para os Vogons.\"\n\n"),
      mensagem_cod_esperada(
          "00111110001110101110100010100010101111110111010011010011100111101110101011010011111110001\
100001010011010101110011010001010100101111110111010011010001011001010001111111001110101001110011001001111110111\
011100000110010001010111011100101110101111110000111011000001011000000100010101110011100111101011110100110100110\
0111011011111101000110010000101001011011001000111111110000100000"),
      mensagem_esperada("Encontramos Magrathea. Precisamos de uma toalha extra "
                        "e chá. Atrasem os Vogons. Zaphod."),
      arvore_esperada(
          "00001001011100101100100010111100010111010100010111000010110110001011010011010110\
100010101011010101000001010011011010001010010111010010111001010110000100000101000001111000011101101110\
101110011100100000001011001010101100011011010000110110011101011011110101101101101101000") {
}

void Hashing::run() {

  // inserções
  inserirMeioQuadrado(
      (Item){"status_motor_improbabilidade", "Ocioso (perigosamente)"});
  inserirMeioQuadrado((Item){
      "estoque_cha_nutrimatico",
      "Substituído por algo quase, mas não exatamente, diferente de chá"});
  inserirMeioQuadrado(
      (Item){"ultima_reclamacao_marvin",
             "A porta suspirou para mim. Odeio portas felizes."});
  inserirMeioQuadrado(
      (Item){"protocolo_de_emergencia", "Não entre em pânico."});
  inserirMeioQuadrado(
      (Item){"proprietario_registrado", "Zaphod Beeblebrox (roubado)"});
  inserirMeioQuadrado(
      (Item){"reparos_necessarios",
             "Consertar o dispensador de petiscos que insulta o usuário"});
  inserirMeioQuadrado((Item){"senha_wifi", "toalha123"});

  inserirEnlacLimite(
      (Item){"status_motor_improbabilidade", "Ocioso (perigosamente)"});
  inserirEnlacLimite((Item){
      "estoque_cha_nutrimatico",
      "Substituído por algo quase, mas não exatamente, diferente de chá"});
  inserirEnlacLimite(
      (Item){"ultima_reclamacao_marvin",
             "A porta suspirou para mim. Odeio portas felizes."});
  inserirEnlacLimite((Item){"protocolo_de_emergencia", "Não entre em pânico."});
  inserirEnlacLimite(
      (Item){"proprietario_registrado", "Zaphod Beeblebrox (roubado)"});
  inserirEnlacLimite(
      (Item){"reparos_necessarios",
             "Consertar o dispensador de petiscos que insulta o usuário"});
  inserirEnlacLimite((Item){"senha_wifi", "toalha123"});

  string input;
  bool mensagem_esperada_input = false;
  bool msg_original_input = false;
  bool msg_comprimida_input = false;
  bool arvore_decodificada_input = false;

  pretty_print(GREEN + "O Log de Bordo da Coração de Ouro (Hashing) \n" + RESET,
               20);

  pretty_print(narrativa, 20);

  while (!msg_original_input) {
    cout << CYAN << "INSERINDO O TEXTO DA CHAVE: msg_original_magrathea"
              << RESET << endl;
    cout << CYAN << "Digite o texto da mensagem original da fase anterior"
              << RESET << endl
              << "> ";
    getline(cin, input);
    cout << endl;

    if (input == mensagem_esperada) {
      msg_original_input = true;

      inserirMeioQuadrado((Item){"msg_original_magrathea", input});
      inserirEnlacLimite((Item){"msg_original_magrathea", input});
      pretty_print("\nMensagem inserida com sucesso\n", 20);
    } else {
      pretty_print(
          "\nEssa mensagem pode não ter o efeito desejado, talvez tenha que usar a mensagem redigida \
por Zaphod.",
          20);
    }
  }

  while (!msg_comprimida_input) {
    cout << CYAN << "INSERINDO O TEXTO DA CHAVE: msg_comprimida_bits"
              << RESET << endl;
    cout << CYAN
              << "Digite os bits da mensagem comprimida da fase anterior"
              << RESET << endl
              << "> ";
    getline(cin, input);
    cout << endl;

    if (input == mensagem_cod_esperada) {
      msg_comprimida_input = true;

      inserirMeioQuadrado((Item){"msg_comprimida_bits", input});
      inserirEnlacLimite((Item){"msg_comprimida_bits", input});
      pretty_print("\nMensagem inserida com sucesso\n", 20);
    } else {
      pretty_print(
          "\nEssa mensagem pode não ter o efeito desejado, talvez tenha que usar a sequência de bits \
que representa a mensagem da questão anterior",
          20);
    }
  }

  while (!arvore_decodificada_input) {
    cout << CYAN
              << "INSERINDO O TEXTO DA CHAVE: arvore_decodificacao_huffman"
              << RESET << endl;
    cout << CYAN << "Digite os bits da árvore gerada na fase anterior"
              << RESET << endl
              << "> ";
    getline(cin, input);
    cout << endl;

    if (input == arvore_esperada) {
      arvore_decodificada_input = true;

      inserirMeioQuadrado((Item){"arvore_decodificacao_huffman", input});
      inserirEnlacLimite((Item){"arvore_decodificacao_huffman", input});
      pretty_print("\nMensagem inserida com sucesso\n", 20);
    } else {
      pretty_print(
          "\nEssa mensagem pode não ter o efeito desejado, talvez tenha que usar a sequência de bits \
que representa a árvore de Huffman da questão anterior",
          20);
    }
  }

  pretty_print(CYAN + "Tabelas em seus estados atuais: \n\n" + RESET, 20);

  mostrarTabelaMeioQuadrado();
  cout << endl << endl;
  mostrarTabelaEnlacLimite();
  cout << endl << endl;

  Item item;
  while (input != "q") {
    cout << CYAN
              << "Digite alguma chave para procurar seu valor, e 'q' para "
                 "prosseguir..."
              << RESET << endl
              << "> ";
    getline(cin, input);
    cout << endl;

    if (input != "q") {

      if (buscarMeioQuadrado(input, item)) {
        cout << GREEN << "Tabela Meio Quadrado: " << RESET << item.desc
                  << endl;
      } else {
        cout << GREEN << "Tabela Meio Quadrado: " << RESET
                  << "Chave não existe" << endl;
      }

      if (buscarEnlacLimite(input, item)) {
        cout << GREEN << "Tabela Enlaçamento Limite: " << RESET
                  << item.desc << endl;
      } else {
        cout << GREEN << "Tabela Enlaçamento Limite: " << RESET
                  << "Chave não existe" << endl;
      }
    }

    cout << endl << endl;
  }

  pretty_print(
      GREEN + "Todos os textos necessários foram inseridos com sucesso!!!\n" +
          RESET,
      20);
  pretty_print(
      YELLOW +
          "As tabelas hashing são uma maneira de tornar o acesso ao armazenamento mais rápido, já que \
não presisamos percorrer toda ela, por conta das chaves e valores. Logo sua complexidade vai depender \
apenas da quantidade de colisões. Já que teremos O(n) no pior caso, sendo n o tamanho da maior lista \
gerada como um tratamento às colisões. E no melhor caso O(1) quando se tem apenas um elemento no índice \
daquela tabela\n" +
          RESET,
      20);

  pretty_print(GREEN + "Fase completa com sucesso !" + RESET, 20);

  wait_enter();
}

void Hashing::mostrarTabelaMeioQuadrado() {
  int i = 0;
  int lot = 0;

  cout << "Tabela Meio Quadrado:" << endl;

  for (vector vet : tabelaMeioQuadrado) {
    if (!vet.empty()) {
      for (Item &it : vet) {
        cout << GREEN << it.chave << ": " << RESET << it.desc << RED
                  << " (" << i << ")" << RESET << endl;
      }
      lot++;
    }
    i++;
  }

  if (lot == 0) {
    cout << "Tabela Meio Quadrado vazia\n" << endl;
  }
}

void Hashing::mostrarTabelaEnlacLimite() {
  int i = 0;
  int lot = 0;

  cout << "Tabela Enlacamento Limite:" << endl;

  for (vector vet : tabelaEnlacLimite) {
    if (!vet.empty()) {
      for (Item &it : vet) {
        cout << GREEN << it.chave << ": " << RESET << it.desc << RED
                  << " (" << i << ")" << RESET << endl;
      }
      lot++;
    }
    i++;
  }

  if (lot == 0) {
    cout << "Tabela Enlacamento Limite vazia\n" << endl;
  }
}

unsigned long Hashing::stringParaIntChave(string chave_string) {
  unsigned long hash = 5381;

  for (char c : chave_string) {
    hash = ((hash << 5) + hash) + c;
  }

  return hash;
};

int Hashing::funcaoMeioQuadrado(int chave, int digitos_tabela) {
  unsigned long quadrado = (unsigned long)chave * (unsigned long)chave;
  int digitosChaveQuad = contarDigitos(quadrado);
  int meio = 0;

  for (int i = 0; i < ((digitosChaveQuad - digitos_tabela) / 2); i++) {
    quadrado /= 10;
  }

  for (int i = 0; i < digitos_tabela; i++) {
    meio += (quadrado % 10) * pow(10, i);
    quadrado /= 10;
  }

  return meio;
}

bool Hashing::inserirMeioQuadrado(Item item) {
  int chave = stringParaIntChave(item.chave);
  chave = funcaoMeioQuadrado(chave, 2);

  if (tabelaMeioQuadrado[chave].empty()) {
    tabelaMeioQuadrado[chave].push_back(move(item));

    return true;
  }

  auto it = lower_bound(
      tabelaMeioQuadrado[chave].begin(), tabelaMeioQuadrado[chave].end(), item,
      [](const Item &a, const Item &b) { return a.chave < b.chave; });

  if (it != tabelaMeioQuadrado[chave].end() && (*it).chave == item.chave) {
    return false;
  }

  tabelaMeioQuadrado[chave].insert(it, item);

  return true;
}

bool Hashing::buscarMeioQuadrado(string chave, Item &item) {
  int chaveCod = stringParaIntChave(chave);
  chaveCod = funcaoMeioQuadrado(chaveCod, 2);

  if (tabelaMeioQuadrado[chaveCod].empty()) {
    return false;
  }

  for (Item &it : tabelaMeioQuadrado[chaveCod]) {
    if (it.chave == chave) {
      item = move(it);
      return true;
    }
  }

  return false;
}

int Hashing::enlacamentoLimite(int chave, int digitos_tabela) {
  while (contarDigitos(chave) % digitos_tabela !=
         0) { // se a chave tem numero de digitos congruente a
              // digitos_tabela, iremos multiplicar por 10,
              // para ser mais simples de dividirmos as partes
    chave *= 10;
  }

  string chave_string = to_string(chave);
  int digitosChave = contarDigitos(chave);
  int valor = 0;

  for (int j = 0; j < digitos_tabela; j++) {
    int coluna = 0;

    for (int i = 0; i < (digitosChave / digitos_tabela); i++) {
      if (i % 2 == 0) {
        coluna += chave_string[digitos_tabela * i + (digitos_tabela - 1 - j)] -
                  '0'; // acessando o elemento correto
      } else {
        coluna += chave_string[digitos_tabela * i + j] -
                  '0'; // acessando o elemento correto
      }
    }

    valor *= 10;
    valor += coluna % 10; // tirando o bit 'carry'
  }

  return valor;
}

bool Hashing::inserirEnlacLimite(Item item) {
  int chave = stringParaIntChave(item.chave);
  chave = enlacamentoLimite(chave, 2);

  if (tabelaEnlacLimite[chave].empty()) {
    tabelaEnlacLimite[chave].push_back(move(item));

    return true;
  }

  auto it = lower_bound(
      tabelaEnlacLimite[chave].begin(), tabelaEnlacLimite[chave].end(), item,
      [](const Item &a, const Item &b) { return a.chave < b.chave; });

  if (it != tabelaEnlacLimite[chave].end() && (*it).chave == item.chave) {
    return false;
  }

  tabelaEnlacLimite[chave].insert(it, item);

  return true;
}

bool Hashing::buscarEnlacLimite(string chave, Item &item) {
  int chaveCod = stringParaIntChave(chave);
  chaveCod = enlacamentoLimite(chaveCod, 2);

  if (tabelaEnlacLimite[chaveCod].empty()) {
    return false;
  }

  for (Item &it : tabelaEnlacLimite[chaveCod]) {
    if (it.chave == chave) {
      item = move(it);
      return true;
    }
  }

  return false;
}
