**Projeto para:** Estruturas de Dados II
**Autor:** Rafael Moreira de Melo
**Entrega:** 23 de junho de 2025
### Tema  

**Título do projeto: O Guia Interativo do Mochileiro dos Algoritmos**

**Conceito geral:** O projeto é um jogo de aventura baseado em texto, ambientado no universo de "O Guia do Mochileiro das Galáxias". O jogador assume o papel do único sobrevivente à demolição da Terra e deve navegar por uma série de desafios e quebra-cabeças cósmicos. Diferente de uma simples ficção interativa, cada grande desafio do jogo é, na verdade, uma representação lúdica de um problema algorítmico complexo da ementa de Estruturas de Dados II.

### Justificativa  

A escolha do tema é decorrente de alguns fatores, mas o principal deles, é o gosto pessoal pelo tema, mas também pela **aventura** que a obra traz, além da **riqueza** de detalhes, que pode trazer uma boa imersão para uma opção de jogo interativo, sem contar as tantas regras que os Vogons seguem, o que traz boas possibilidades de desafios.

### Visão Geral das Funcionalidades

O software será uma aventura textual com as seguintes funcionalidades centrais:

- **Motor de Narrativa Interativa:** Uma interface baseada em texto que processa os comandos do jogador (ex: `olhar guia`, `ir para ponte`, `usar toalha em painel`), atualiza o estado do jogo e apresenta os desdobramentos da história.
- **Sistema de Desafios Modulares:** Cada grande arco da história corresponde a um tópico da ementa. A resolução de um desafio algorítmico destrava o próximo arco narrativo.
- **Árvore de Decisão com Ramificações Locais:** As escolhas do jogador terão consequências imediatas e poderão levar a diferentes desfechos dentro de um mesmo capítulo ou desafio. Falhas em um quebra-cabeça podem resultar em finais prematuros e cômicos (ex: ser ejetado no espaço, ser forçado a ouvir poesia Vogon eternamente), incentivando a rejogabilidade e a busca pela solução ótima.
- **O Guia (Banco de Dados Interativo):** O jogador poderá consultar o "Guia" a qualquer momento. As entradas do Guia não apenas fornecem contexto sobre o universo, mas também podem conter dicas (diretas ou indiretas) para a resolução dos desafios algorítmicos.

### Integração da Ementa

A princípio cada tópico da ementa vai ser como um capítulo da história, o intuito é que, ao final, quando os módulos forem se unindo, a história da obra poderá ser contada inteiramente. A história começa com a destruição da Terra.

**Algoritmos de Busca (Sequencial, Binária, Busca em Texto, Hashing)**
Após resgatados pela nave Coração de Ouro, o motor de improbabilidade infinita bagunçou completamente o Guia, agora você terá que vasculhar dados desorganizador, índices antigos semi-ordenados, e procurando informações exatas em grande volume de texto inútil, até achar as coordenadas do planeta secreto de Magrathea.

**Compressão de Dados (RLE, Huffman)**
Com os Vogons nos perseguindo teremos que ter mais cuidado. Teremos que implementar protocolos de comunicação com informações comprimidas, assim poderemos ter menos trabalho na transmissão e os Vogons não saberão o que estamos falando, visto de para a descompressão precisamos saber a codificação. 

**Grafos (Todos os subtópicos: Caminhos, Redes, Conexões, Fluxos, etc.)**
Rumo a Magrathea, por mais disfarçamos os Vogons, temos que nos adiantar e tentar chegar ao nosso destino rapidamente, sem demora, mas também poderemos precisar de algumas paradas, é muito importante manter nosso estoque de toalhas.

**Algoritmos Gulosos (Troco, Escalonamento de Intervalos, Mochila Fracionário)**
Após a nave Vogon chegar a Terra, momentos antes de destruí-la, Ford Prefect grita, sinalizando que o tempo é curto, e em meio ao pânico você terá que escolher o que salvar da sua casa. E não se esqueça de levar a sua toalha.

**Programação Dinâmica (Mochila 0/1, Multiplicação de Matrizes, LCS, etc.)**
Capturado pelos Vogons, você está prestes a ser jogado no espaço. Ford tem uma pequena mochila de sobrevivência com tamanho limitado, assim você terá que escolher uma combinação de itens ótimas, para aumentar as chances de sobreviver.

**Fluxo**
Inicialmente o fluxo foi pensando em uma ordem diferente da ementa, tendo a seguinte ordem para que faça sentido a história:
**Algoritmos gulosos** -> **Programação dinâmica** -> **Algoritmos de busca** -> **Compressão de dados** -> **Grafos**

### Tecnologia escolhidas

implementação será desenvolvida na linguagem **C++**. A interface será puramente textual (console), permitindo que o foco permaneça na narrativa e na resolução dos quebra-cabeças. Nenhuma biblioteca externa será necessária inicialmente, pois o objetivo é implementar as estruturas de dados e os algoritmos a partir do zero, conforme os requisitos da disciplina.