#include <iostream>
#include "modulos/busca.hpp"
#include "modulos/otimizacao.hpp"


void menu () {
    int opt;

    do {
        clean_screen();
        std::cout << GREEN << "+++ História Interativa do Guia do Mochileiro dos Algoritmos +++" << RESET << std::endl;
        std::cout << "[1] Busca de Dados (O guia bagunçado e a busca por Magrathea)" << std::endl;
        std::cout << "[2] Otimização de Recursos (Sussurros no Vácuo e a Tabela de Dispersão Vogon)" << std::endl;
        std::cout << "[3] Sair" << std::endl << std::endl;

        std::cout << CYAN << "Digite a opção desejada" << RESET << std::endl << "> ";
        std::cin >> opt;
        std::cin.get();
        std::cout << std::endl << std::endl;

        switch (opt) {
        case 1: {
            // Narrativa geral da fase de busca
            pretty_print(GREEN + "O guia bagunçado e a busca por Magrathea\n\n" + RESET, 20);
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
um planeta que provavelmente nem quer ser encontrado.\n\n", 20);
            // etapa: busca sequencial
            BuscaSequencial bSeq;
            // etapa: busca binária
            BuscaBinaria bBin;
            // etapa: busca em texto (rabin karp)
            BuscaRabinKarp bRabKarp;
            bSeq.run();
            std::cout << std::endl << std::endl;
            bBin.run();
            std::cout << std::endl << std::endl;
            bRabKarp.run();
            std::cout << std::endl << std::endl;

            pretty_print("Ao extrair a string COORDS::{Lat:42.0, Lon:-21.0, Dep:Sub-Etha}, você a entrega a \
Zaphod. Ele digita as coordenadas no painel da nave com um sorriso maníaco. A Coração de Ouro estremece, as \
luzes piscam e o Motor de Improbabilidade Infinita se prepara para o próximo salto. Vocês estão a caminho de \
Magrathea, mas Ford Prefect nota transmissões Vogons se aproximando. \"Rápido!\", ele diz. \"Precisamos comprimir \
nossas próximas comunicações para não sermos detectados!\"./n/n", 20);

            pretty_print(CYAN + "Módulo de busca de dados finalizado com sucesso!!!" + RESET, 20);

            std::cout << std::endl << std::endl;

            wait_enter();
            break;
            }
        case 2: {
            // Narrativa geral da fase de otimização
            pretty_print(GREEN + "Sussurros no Vazio e a Fúria Vogon\n\n" + RESET, 20);
            pretty_print("Com as coordenadas de Magrathea inseridas, a Coração de Ouro salta pelo espaço. O alívio, no \
entanto, dura pouco. Um alarme estridente ecoa pela ponte. Ford Prefect aponta para o scanner de longo alcance, \
seu rosto pálido. \"São eles! Uma frota de construção Vogon. Eles nos seguiram!\"\n\n\
Trillian analisa os dados. \"Eles estão escaneando todas as frequências de comunicação. Se transmitirmos qualquer \
coisa, eles vão triangular nossa posição em segundos.\" Zaphod, pela primeira vez, parece preocupado. \"Não podemos \
simplesmente ficar em silêncio! Preciso coordenar nosso próximo movimento com... contatos.\"\n\n\
É então que Arthur Dent, segurando seu exemplar do Guia, tem uma ideia. \"No Guia diz que civilizações primitivas \
usavam 'códigos' para esconder mensagens. E se... e se nós 'espremêssemos' a nossa mensagem para que ela parecesse \
ruído aleatório para os scanners deles?\" Ford completa o raciocínio: \"Compressão! Brilhante, terráqueo! Se comprimirmos \
a mensagem, ela será menor, mais rápida de enviar e, sem o dicionário de descompressão, será indecifrável para os Vogons!\"\n\n", 20);
            // etapa: compressao
            CompHuffman cHuff;
            // etapa: hashing


            cHuff.run();


            pretty_print("Ao buscar e exibir com sucesso os dados que você mesmo inseriu, o painel de controle da nave pisca em verde \
com uma mensagem: \"LOG REGISTRADO. TRANSMISSÃO AUTORIZADA.\" Zaphod dá um tapa de comemoração nas suas costas. A mensagem \
comprimida e sua chave de decodificação são enviadas em uma transmissão ultrarrápida. Momentos depois, a resposta chega. \"Aproximação \
final é um labirinto de rotas espaciais antigas e fluxos de detritos. Vocês precisarão calcular o caminho mais rápido, mas também considerar \
paradas para reabastecer... e pegar aquelas toalhas.\"", 20);
            break;
        }
        case 3:
            exit(0);
        default:
            std::cout << "Opção inválida. Tente novamente." << std::endl;

            wait_enter();
        }
    } while (opt != 3);
}

int main (int argc, char** argv) {
    menu();

    return 0;
};
