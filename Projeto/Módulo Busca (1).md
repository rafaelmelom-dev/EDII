### Escopo

O módulo de busca é compreendido pelos arquivos `busca.cpp` e `busca.hpp`, dentro da pasta de `modulos`, (Todos os códigos estão separados na pasta Source).

### Arquitetura

Para cada algoritmo do módulo de busca foi feito uma classe, com atributos necessários para a lógica do programa como a narrativa, e alguns dados internos a serem processados pelo algoritmo, mas o essencial está contido no método chamado `busca()`, que foi feito para cada algoritmo, no projeto em questão, os dados apenas são mostrados na tela, sem um uso muito adequado (onde uma busca retornaria uma posição onde foi encontrado o elemento).

Bom, o método `busca()`, contém a lógica do algoritmo e o método `run()`, só serve para organizar o programa e chamar o método de `busca` com a entrada do usuário.

### Complexidade

**Busca Sequencial**: tem uma complexidade de O(1) no melhor caso quando o elemento é o primeiro da estrutura usada para procura, mas chega a O(n) em seu pior caso, quando o elemento é o último.

**Busca Binária**: tem uma complexidade também de O(1) no melhor dos casos quando o elemento é o primeiro da árvore, mas pode chegar a uma complexidade de O(log n), sendo ótima para problemas em que tenha algum sistema de ordenação. Essa complexidade de O(log n) acontece porque na pesquisa binária, metade das opções é excluída da pesquisa a cada avanço do nó.

**Busca Rabin Karp**: no melhor dos casos, onde o hash (módulo com número primo), só bate uma vez, e temos apenas uma verificação, temos uma complexidade de O(n + m), mas se tivermos um hash com muitas colisões, poderemos chegar a uma complexidade de O(n * m), acontecendo verificações e todos os subtextos. Entende-se por **n** o tamanho do texto a ser usado na pesquisa, e **m** o tamanho do subtexto a ser procurado.