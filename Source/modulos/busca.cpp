#include "busca.hpp"
#include "../utils/utils.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//// Etapa da busca sequencial

BuscaSequencial::BuscaSequencial()
    : log_caotico(
          {"vogon_poetry_collection_vol3.txt",
           "pan_galactic_gargle_blaster_recipe_DANGER.mix",
           "how_to_survive_a_vogon_poetry_reading.md",
           "infinite_improbability_drive_repair_manual_pg1.pdf",
           "list_of_planets_mistakenly_demolished.csv",
           "lint_from_my_pocket.data", "a_brief_history_of_the_towel.doc",
           "forty_two_meaning_of_life_theories.txt",
           "sector_index_magrathea.ref", "zaphod_beeblebrox_shopping_list.dat",
           "marvin_the_paranoid_android_complaint_log_987.log",
           "earth_demolition_order_form_XG27-B.pdf",
           "trillian_mouse_care_guide.txt"}),
      narrativa(
          "O diretório de arquivos do Guia é agora uma lista completamente desordenada de \
arquivos com nomes absurdos. Ford explica que, antes do caos, havia um arquivo mestre chamado " +
          GREEN + "sector_index_magrathea.ref" + RESET +
          ". Vocês precisam encontrá-lo nesta bagunça para \
ter um ponto de partida. Como a lista não tem ordem, a única maneira é verificar um por um.\n") {
}

void BuscaSequencial::run() {
  std::string input;
  bool indice_encontrado = false;

  pretty_print(GREEN + "A Pilha de Lixo Digital (Busca Sequencial) \n" + RESET,
               20);

  pretty_print(narrativa, 20);

  while (!indice_encontrado) {
    std::cout << CYAN << "Digite o nome do arquivo a ser buscado no log caótico"
              << RESET << std::endl
              << "> ";
    std::cin >> input;
    std::cin.get();
    std::cout << std::endl;

    indice_encontrado = busca(log_caotico, input);

    if (input != "sector_index_magrathea.ref" && indice_encontrado) {
      pretty_print(
          "\nEssa entrada pode não ter o efeito desejado, talvez tenha que usar o nome do arquivo \
que Ford sugeriu.",
          20);
      indice_encontrado = false;
    }
  }

  pretty_print(
      GREEN + "\nArquivos com os indíces de Magrathea foram encontrados!!!\n" +
          RESET,
      20);
  pretty_print(
      YELLOW +
          "UFA! Ainda bem que tinha poucos arquivos! A busca sequencial, arquivo \
por arquivo demora muito tendo uma complexidade de O(n) no pior dos casos!\n" +
          RESET,
      20);

  pretty_print(GREEN + "Fase completa com sucesso !" + RESET, 20);

  wait_enter();
}

bool BuscaSequencial::busca(std::vector<std::string> arquivos,
                            std::string nome_arquivo) {
  for (std::string log_item : log_caotico) {
    bool found = false;
    std::string text = "Verificando o arquivo: " + log_item;

    if (log_item == nome_arquivo) {
      text += GREEN + " ENCONTRADO"; // aqui poderia entrar um retorno do índice
      found = true;
    } else {
      text += RED + " Não é este!";
    }

    text += RESET;

    pretty_print(text, 20);

    if (found)
      return true;
  }

  pretty_print(CYAN + "Não foi achado nenhum arquivo com este nome!\n" + RESET,
               20);
  return false;
};

//// Etapa da busca binária

BuscaBinaria::BuscaBinaria()
    : setorArq({{101, "Sistema Estelar Frogstar"},
                {113, "Constelação do Chapéu de Pano"},
                {242, "Região do Grande Cavalo-Marinho Espacial"},
                {355, "Nebulosa da Indiferença Total"},
                {499, "Quadrante Algoliano do Sol Nascente"},
                {610, "Vórtice de Santraginus V"},
                {734, "Confins de Damogran"},
                {877, "Ponto de Acesso de Magrathea"}, // <- O ALVO
                {921, "Territórios de Squornshellous Zeta"},
                {998, "Anomalia Espaço-Temporal do Fim do Universo"}}),
      narrativa(
          "Sucesso! Ao abrir o sector_index_magrathea.ref, você encontra uma lista \
gigantesca de setores galácticos, cada um com um código numérico único. Felizmente, \
este índice específico manteve sua ordenação numérica. Ford se lembra de ter lido que \
o sistema de Magrathea está em um \"setor antigo e obscuro\", com o código " +
          GREEN + "877" + RESET +
          ". Procurar sequencialmente levaria tempo demais, e Zaphod está ficando impaciente. É preciso \
usar um método mais eficiente.\n") {}

void BuscaBinaria::run() {
  int input;
  bool setor_encontrado = false;

  pretty_print(GREEN + "Navegando pelos Setores Estelares (Busca Binária) \n" +
                   RESET,
               20);

  pretty_print(narrativa, 20);

  while (!setor_encontrado) {
    std::cout << CYAN
              << "Digite o código do setor a ser procurado dentro do arquivo "
                 "de índices"
              << RESET << std::endl
              << "> ";
    std::cin >> input;
    std::cin.get();
    std::cout << std::endl;

    setor_encontrado = busca(setorArq, input, 0, setorArq.size());

    if (input != 877 && setor_encontrado) {
      pretty_print(
          "\nEsse id pode não ter o efeito desejado, talvez tenha que u"
          "sar o id sugerido por Ford.",
          0);
      setor_encontrado = false;
    }
  }

  pretty_print(GREEN +
                   "\nO setor foi encontrado com sucesso, e ele corresponde a "
                   "Magrathea, parece que agora estamos perto!!!\n" +
                   RESET,
               20);
  pretty_print(
      YELLOW +
          "Com os índices ordenados, foi bem mais fácil acharmos o setor com o identificador sugerido,\
 com a Busca Binária, temos a complexidade de O(log n) em seu pior caso!!!\n" +
          RESET,
      20);

  pretty_print(GREEN + "Fase completa com sucesso !" + RESET, 20);

  wait_enter();
}

bool BuscaBinaria::busca(std::vector<SetorInfo> setores, int id_setor,
                         int ind_esq, int ind_dir) {
  if (ind_esq > ind_dir) {
    pretty_print(
        CYAN + "Não foi achado nenhum setor com este id!\n" + RESET, 20);
    return false;
  }

  int meio = (ind_esq + ind_dir) / 2;

  std::string res =
      "Verificando o setor: ID: " + std::to_string(setores[meio].id) +
      " - Nome: " + setores[meio].name;

  if (setores[meio].id == id_setor) {
    res += GREEN + " ENCONTRADO" + RESET;
    pretty_print(res, 20);
    return true;
  } else if (setores[meio].id > id_setor) {
    res += RED + " Não é este (é menor que esse)" + RESET;
    pretty_print(res, 20);
    return busca(setores, id_setor, ind_esq, meio - 1);
  } else {
    res += RED + " Não é este (é maior que esse)" + RESET;
    pretty_print(res, 20);
    return busca(setores, id_setor, meio + 1, ind_dir);
  }
}

//// Etapa da busca em texto (Rabin karp)

BuscaRabinKarp::BuscaRabinKarp()
    : arquivo_log(
          "Stardate 41999. O replicador de alimentos produziu novamente algo que se assemelha a um peixe, mas com o gosto \
sutil de desespero. Tenho saudades de um bom sanduíche. Marvin passou por aqui hoje, disse que as estrelas são apenas pontos de \
luz insignificantes em um vazio existencial. Isso não ajudou meu humor. Ah, sim, o trabalho. Finalizamos a calibração dos fiordes \
daquele continente na Noruega. O cliente ficou satisfeito, mas se esqueceu de nos pagar. Típico. O computador central insiste em \
tocar 'Stairway to Heaven' ao contrário. Anotação para a gerência: precisamos de uma atualização de software. Onde eu coloquei \
aquelas malditas coordenadas? Ah, aqui estão, no meio das minhas reclamações. COORDS::{Lat:42.0, Lon:-21.0, Dep:Sub-Etha}. Tenho \
que lembrar de não misturar anotações pessoais com dados de navegação. Enfim, hora do chá. Espero que hoje não tenha gosto de sapato molhado."),
      narrativa(
          "O \"Ponto de Acesso de Magrathea\" (877) leva a um único arquivo: um log de texto massivo. Parece ser o diário de bordo \
de um antigo capitão de uma nave de construção Magratheana. O arquivo está cheio de reclamações sobre a qualidade do chá, \
pensamentos filosóficos e relatos mundanos. Trillian sugere que as coordenadas planetárias em logs antigos eram sempre prefixadas \
com o marcador " +
          GREEN + "COORDS::" + RESET +
          ". Vocês precisam varrer o texto e encontrar essa substring para "
          "extrair as coordenadas exatas.\n") {}

void BuscaRabinKarp::run() {
  std::string input;
  bool texto_encontrado = false;

  pretty_print(
      GREEN + "O Diário de Bordo Perdido (Busca em Texto - Rabin Karp) \n" +
          RESET,
      20);

  pretty_print(narrativa, 20);

  while (!texto_encontrado) {
    std::cout << CYAN
              << "Digite algum bloco de texto para ser procurado no arquivo "
                 "encontrado"
              << RESET << std::endl
              << "> ";
    std::cin >> input;
    std::cin.get();
    std::cout << std::endl;

    texto_encontrado = busca(arquivo_log, input, 256, 101);

    if ((input != "COORDS" && input != "COORDS::") && texto_encontrado) {
      pretty_print(
          "\nEsse texto pode não ter o efeito desejado, talvez tenha que usar a convenção \
sugerida por Trillian.",
          20);
      texto_encontrado = false;
    }
  }

  pretty_print(GREEN +
                   "\nO texto encontrado pode ajudar a encontrarmos o lugar "
                   "exato onde se encontra Magrathea!!!\n" +
                   RESET,
               20);
  pretty_print(
      YELLOW +
          "A busca em texto, utilizando o algoritmo de Rabin Karp, tem uma complexidade variável de O(n + m), pensando \
no melhor caso, onde o texto irá ser comparado apenas uma vez, e assim é achado, mas podemos ter também o pior caso, onde a \
complexidade pode ser aumentada para O(n * m), por conta das colisões, considerando neste caso que irão ser comparados todos \
os subtextos que se encontram no texto!!!\n" +
          RESET,
      20);

  pretty_print(GREEN + "Fase completa com sucesso !" + RESET, 20);

  wait_enter();
}

bool BuscaRabinKarp::busca(std::string texto, std::string subtexto, int d,
                           int q) {
  // calculando n e m
  int n = texto.length();
  int m = subtexto.length();

  // calculando h
  int h = 1;
  for (int i = 1; i < m; i++) {
    h = (h * d) % q;
  }

  // calculando a hash do padrao e do subtexto inicial
  int p = 0;
  int t = 0; // t0

  for (int i = 0; i < m; i++) {
    p = (d * p + int(subtexto[i])) % q;
    t = (d * t + int(texto[i])) % q;
  }

  for (int s = 0; s < (n - m + 1); s++) {
    if (s % 20 == 0) {
      std::stringstream res;
      res << MAGENTA << std::setprecision(2) << ((float)s / (float)n * 100)
          << "% do texto já foi vasculhado." << RESET;
      pretty_print(res.str(), 10);
    }

    if (p == t) {
      if (subtexto == texto.substr(s, m)) {
        std::string res_final =
            "\n" + GREEN + "PARTE DO TEXTO FOI ENCONTRADO" + RESET;
        pretty_print(res_final, 20);

        pretty_print(
            YELLOW + "CONTEXTO -> " + MAGENTA + "..." +
                texto.substr(std::max(0, s - 40), std::min(m + 80, n - s)) +
                "..." + RESET,
            20);

        return true;
      }
    }

    if (s < n - m) {
      t = (d * (t - int(texto[s]) * h) + int(texto[s + m])) % q;
    }

    if (t < 0) {
      t += q;
    }
  }

  return false;
}
