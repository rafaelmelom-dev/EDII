### Escopo

O módulo de grafos é compreendido pelos arquivos `grafos.cpp` e `grafos.hpp`, dentro da pasta `modulos`.(Todos os códigos estão separados na pasta Source)

### Arquitetura

Para cada módulo presente na atividade temos uma classe correspondida, que é responsável pela narrativa e execução dos algoritmos. Tendo uma classe extra, usada nos módulos 1 e 2 para criar e gerenciar o grafo.

O módulo 1 é compreendido pela classe `ReconsGrafo`, onde temos sua narrativa que leva a uma atualização no grafo, mostrando que o programa é capaz de inserir novas informações no grafo.

Já o módulo 2 é compreendido pela classe `BuscaGrafo`, onde temos também a narrativa, mas nenhuma comunicação direta com usuário, mesmo os algoritmos tendo sentido na história.

Assim como o módulo 2, o módulo 3 não estabelece uma comunicação direta com o usuário. Ele é compreendido pela classe `AlgGrafos`, e possui três algoritmos visto no campo de grafos, o algoritmo de coloração, ordenação topológica e árvore geradora mínima.

### Complexidade

Apenas como uma nota rápida sobre complexidade nas buscas utilizando grafos.

**DFS e BFS:** BFS tem alta complexidade visto que ele irá visitar todos os seus vizinhos para prosseguir a próxima camada, e o DFS também pode atingir alta complexidade em dado contexto, mas ele continua sendo o caminho mais fácil. Ambos os algoritmos são muito dependentes dos vértices de origem e final da busca.

**Dijkstra:** Custo semelhante ao BFS, para ser executado, já que algumas diferenças que temos aqui é uma fila de prioridade e marcação de custos, mas o algoritmo de Dijkstra garante o menor custo de um vértice a outro.