#include "modulos/busca.hpp"
#include "modulos/grafos.hpp"
#include "modulos/gulosos.hpp"
#include "modulos/otimizacao.hpp"
#include "modulos/programacao_dinamica.hpp"
#include "utils/utils.hpp"
#include <bits/stdc++.h>

using namespace std;

void menu() {
  int opt;

  do {
    clean_screen();
    cout << GREEN
         << "+++ História Interativa do Guia do Mochileiro dos Algoritmos +++"
         << RESET << endl;
    cout << "[1] Algoritmos Gulosos (O fim do mundo em cinco minutos)" << endl;
    cout << "[2] Programação Dinâmica (A lógica fria do vácuo)" << endl;
    cout << "[3] Busca de Dados (O guia bagunçado e a busca por Magrathea)"
         << endl;
    cout << "[4] Otimização de Recursos (Sussurros no Vácuo e a Tabela de "
            "Dispersão Vogon)"
         << endl;
    cout << "[5] Grafos (O Labirinto de Asteroides e a Rota para Magrathea)"
         << endl;
    cout << "[6] Sair" << endl << endl;

    cout << CYAN << "Digite a opção desejada" << RESET << endl << "> ";
    cin >> opt;
    cin.get();
    cout << endl << endl;

    switch (opt) {
    case 1: {
      pretty_print(GREEN + "O fim do mundo em cinco minutos\n\n" + RESET, 20);

      pretty_print(
          "Você está em sua casa, tranquilamente tomando uma xícara de chá, "
          "quando seu excêntrico amigo, Ford Prefect, arromba a porta. Ele "
          "está em pânico. \"Rápido! Pegue sua toalha! Os Vogons estão "
          "vindo!\", ele grita, apontando para o céu, onde uma gigantesca "
          "frota de naves amarelas paira ameaçadoramente. Um anúncio "
          "burocrático e ininteligível ecoa pela vizinhança, confirmando que a "
          "Terra será demolida para a construção de uma via expressa "
          "hiperespacial.\n\nO tempo é curtíssimo. Você precisa tomar decisões "
          "rápidas e eficientes para sobreviver. Cada segundo conta, e não há "
          "tempo para planejar a solução perfeita – apenas a que funciona "
          "agora.\n\n",
          20);

      // etapa: mochila fracionaria
      MochilaFracionaria mf;
      // etapa: escalonamento de intervalos
      EscalonamentoIntervalos ei;
      // etapa: troco
      Troco t;

      mf.run();
      cout << endl << endl;
      ei.run();
      cout << endl << endl;
      t.run();
      cout << endl << endl;

      pretty_print(
          "Ao conseguir o peixe Babel, vocês o inserem no ouvido. Segundos "
          "depois, um raio demolidor vaporiza sua rua. Vocês foram "
          "capturados.\n\n",
          20);

      pretty_print(
          CYAN + "Módulo de algoritmos gulosos finalizado com sucesso!!!" +
              RESET,
          20);

      cout << endl << endl;

      wait_enter();
      break;
    }
    case 2: {
      pretty_print(GREEN + "A lógica fria do vácuo\n\n" + RESET, 20);

      pretty_print(
          "Vocês estão em uma cela úmida e escura na nave Vogon. O guarda, uma "
          "criatura horrenda e burocrática chamada Prostetnic Vogon Jeltz, "
          "anuncia seu destino: serem ejetados no vácuo do espaço. No entanto, "
          "ele oferece um \"desafio de lógica\" como uma forma sádica de "
          "entretenimento.\n\n\"De acordo com o regulamento 37-B, subseção 9, "
          "prisioneiros podem receber um kit de sobrevivência. No entanto, o "
          "compartimento de carga do kit é... eficiente\", ele diz com um "
          "sorriso cruel. \"Vocês devem escolher a combinação de itens que "
          "maximize seu valor de sobrevivência. Os itens são indivisíveis. "
          "Escolham errado, e o vácuo parecerá um alívio.\"\n\nDiferente do "
          "pânico "
          "na Terra, aqui a decisão é calculada. Uma escolha errada significa "
          "o fim. A solução precisa ser perfeita.\n\n",
          20);

      // etapa: mochila 0/1
      Mochila01 m;

      m.run();
      cout << endl << endl;

      pretty_print(
          "Após sua implementação encontrar a combinação ótima (por exemplo: "
          "Gerador de Oxigênio, Nutri-pasta, Kit de Reparo e o Sinalizador), "
          "você arruma o kit. O guarda Vogon, impressionado contra a sua "
          "vontade, os arrasta para a câmara de ejeção. A porta se abre, e "
          "vocês são lançados na escuridão fria. O kit funciona! O oxigênio "
          "flui, o sinalizador pisca... mas o tempo está se esgotando. Quando "
          "tudo parece perdido, uma luz dourada brilhante e uma "
          "improbabilidade estatística de dois elevado a infinito para um "
          "acontece. Uma nave surge do nada e os resgata.\n\nVocês estão a "
          "bordo da Coração de Ouro, e a sua aventura está prestes a ficar "
          "muito, muito mais estranha.\n\n",
          20);

      pretty_print(
          CYAN + "Módulo de programação dinâmica finalizado com sucesso!!!" +
              RESET,
          20);

      cout << endl << endl;

      wait_enter();
      break;
    }
    case 3: {
      // Narrativa geral da fase de busca
      pretty_print(
          GREEN + "O guia bagunçado e a busca por Magrathea\n\n" + RESET, 20);
      pretty_print("Ao chegar na ponte de comando da Coração de Ouro, vocês \
são recebidos por Zaphod Beeblebrox, o presidente da galáxia. Exultante e caótico, ele \
anuncia seu grande plano: encontrar o lendário planeta de Magrathea. No entanto, a última \
ativação do Motor de Improbabilidade Infinita para escapar dos Vogons teve um efeito colateral \
desastroso: corrompeu completamente a base de dados local do \"Guia do Mochileiro das Galáxias\".\n\n\
Zaphod, impaciente, se vira para você e Ford Prefect. \"Ei, terráqueo! Você parece inteligente. \
E você, meu primo, deveria saber dessas coisas! O Guia é um lixo digital agora. Não consigo \
encontrar nada! Achem as coordenadas de Magrathea para mim, ou terei que apertar este botão de novo!\"\n\n\
Sua tarefa é mergulhar nos dados fragmentados e caóticos do Guia para encontrar as coordenadas. \
Marvin, o Androide Paranoico, observa de um canto, murmurando sobre a futilidade de procurar por \
um planeta que provavelmente nem quer ser encontrado.\n\n",
                   20);
      // etapa: busca sequencial
      BuscaSequencial bSeq;
      // etapa: busca binária
      BuscaBinaria bBin;
      // etapa: busca em texto (rabin karp)
      BuscaRabinKarp bRabKarp;
      bSeq.run();
      cout << endl << endl;
      bBin.run();
      cout << endl << endl;
      bRabKarp.run();
      cout << endl << endl;

      pretty_print(
          "Ao extrair a string COORDS::{Lat:42.0, Lon:-21.0, Dep:Sub-Etha}, você a entrega a \
Zaphod. Ele digita as coordenadas no painel da nave com um sorriso maníaco. A Coração de Ouro estremece, as \
luzes piscam e o Motor de Improbabilidade Infinita se prepara para o próximo salto. Vocês estão a caminho de \
Magrathea, mas Ford Prefect nota transmissões Vogons se aproximando. \"Rápido!\", ele diz. \"Precisamos comprimir \
nossas próximas comunicações para não sermos detectados!\".\n\n",
          20);

      pretty_print(CYAN + "Módulo de busca de dados finalizado com sucesso!!!" +
                       RESET,
                   20);

      cout << endl << endl;

      wait_enter();
      break;
    }
    case 4: {
      // Narrativa geral da fase de otimização
      pretty_print(GREEN + "Sussurros no Vazio e a Fúria Vogon\n\n" + RESET,
                   20);
      pretty_print(
          "Com as coordenadas de Magrathea inseridas, a Coração de Ouro salta pelo espaço. O alívio, no \
entanto, dura pouco. Um alarme estridente ecoa pela ponte. Ford Prefect aponta para o scanner de longo alcance, \
seu rosto pálido. \"São eles! Uma frota de construção Vogon. Eles nos seguiram!\"\n\n\
Trillian analisa os dados. \"Eles estão escaneando todas as frequências de comunicação. Se transmitirmos qualquer \
coisa, eles vão triangular nossa posição em segundos.\" Zaphod, pela primeira vez, parece preocupado. \"Não podemos \
simplesmente ficar em silêncio! Preciso coordenar nosso próximo movimento com... contatos.\"\n\n\
É então que Arthur Dent, segurando seu exemplar do Guia, tem uma ideia. \"No Guia diz que civilizações primitivas \
usavam 'códigos' para esconder mensagens. E se... e se nós 'espremêssemos' a nossa mensagem para que ela parecesse \
ruído aleatório para os scanners deles?\" Ford completa o raciocínio: \"Compressão! Brilhante, terráqueo! Se comprimirmos \
a mensagem, ela será menor, mais rápida de enviar e, sem o dicionário de descompressão, será indecifrável para os Vogons!\"\n\n",
          20);
      // etapa: compressao
      CompHuffman cHuff;
      // etapa: hashing
      Hashing hashing;

      cHuff.run();
      cout << endl << endl;

      hashing.run();
      cout << endl << endl;

      pretty_print(
          "Ao buscar e exibir com sucesso os dados que você mesmo inseriu, o painel de controle da nave pisca em verde \
com uma mensagem: \"LOG REGISTRADO. TRANSMISSÃO AUTORIZADA.\" Zaphod dá um tapa de comemoração nas suas costas. A mensagem \
comprimida e sua chave de decodificação são enviadas em uma transmissão ultrarrápida. Momentos depois, a resposta chega. \"Aproximação \
final é um labirinto de rotas espaciais antigas e fluxos de detritos. Vocês precisarão calcular o caminho mais rápido, mas também considerar \
paradas para reabastecer... e pegar aquelas toalhas.\"\n\n",
          20);
      pretty_print(
          CYAN + "Módulo de otimização de dados finalizado com sucesso!!!" +
              RESET,
          20);

      cout << endl << endl;

      wait_enter();
      break;
    }
    case 5: {
      // Narrativa geral da fase de busca
      pretty_print(GREEN +
                       "O Labirinto de Asteroides e a Rota para Magrathea\n\n" +
                       RESET,
                   20);
      pretty_print(
          "O salto termina abruptamente. Em vez da superfície serena de "
          "Magrathea, a tela principal da nave exibe um denso e caótico campo "
          "de asteroides, sistemas estelares instáveis e nebulosas "
          "traiçoeiras. Zaphod bate no painel. \"O que é isso?! Onde estão "
          "minhas praias pré-fabricadas e meus oceanos de encomenda?\"Trillian "
          "analisa os dados. \"Parece que as coordenadas nos levaram para a "
          "vizinhança de Magrathea, uma região conhecida como 'O Emaranhado de "
          "Horsehead'. O planeta está blindado, e a única forma de chegar lá é "
          "navegando por esta rede de rotas espaciais. Pior: o último salto "
          "parece ter corrompido parcialmente nosso mapa de navegação "
          "local.\"Ford Prefect abre o mapa estelar no terminal.\"Ela tem "
          "razão. O mapa é um grafo de pontos de "
          "interesse—planetas, estações espaciais, anomalias—conectados "
          "por rotas seguras. Mas algumas rotas óbvias sumiram, e os "
          "dados de perigo e distância estão uma bagunça. Precisamos "
          "consertar isso antes de nos movermos.\"\n\n",
          20);

      // etapa: grafo - manipulacao
      ReconsGrafo rg;
      // etapa: grafo - navegando
      BuscaGrafo bg;
      // etapa: grafo - avançado
      AlgGrafos ag;

      rg.run();
      cout << endl << endl;

      bg.run();
      cout << endl << endl;

      ag.run();
      cout << endl << endl;

      pretty_print("Com a rede de comunicação estabelecida, uma voz antiga e "
                   "calma ecoa pela ponte: \" Saudações,viajantes.Estivemos "
                   "esperando.Magrathea desperta.\" Vocês finalmente "
                   "conseguiram. Zaphod comemora, "
                   "enquanto Marvin apenas resmunga que agora o trabalho "
                   "de verdade vai começar. O caminho para os segredos "
                   "mais profundos da galáxia está aberto, preparando o "
                   "terreno para os próximos desafios do jogo.\n\n",
                   20);

      pretty_print(CYAN + "Módulo de grafos finalizado com sucesso!!!" + RESET,
                   20);

      cout << endl << endl;

      wait_enter();
      break;
    }
    case 6:
      exit(0);
    default:
      cout << "Opção inválida. Tente novamente." << endl;

      wait_enter();
    }
  } while (opt != 6);
}

int main(int argc, char **argv) {
  menu();

  return 0;
};
