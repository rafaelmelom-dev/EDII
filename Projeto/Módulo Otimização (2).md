### Escopo

O módulo de otimização é compreendido pelos arquivos `otimizacao.cpp` e `otimizacao.hpp`, dentro da pasta `modulos`.(Todos os códigos estão separados na pasta Source)

### Arquitetura

Para o algoritmo de compressão foi criada uma classe chamada `CompHuffman`, assim como o módulo de busca contém os atributos necessários para a história. Além de conter também o algoritmo principal, o algoritmo de Huffman.

Com isso a classe `CompHuffman` acabou ficando um pouco mais complexa, todos os dados foram tratados como string a fim de mostrá-los, mas em um exemplo real poderíamos ter uma estrutura que pudesse ocupar menos espaço, como uma variável booleana, já que o algoritmo de Huffman só contém bits 0 e 1. Mas enfim, temos uma função para montar a árvore (`montarArvore`), para montar a tabela de códigos (`montarTabelaCodigos`) e para transformar o texto com os códigos (`codificarTexto`), além da função `comprimir`, que basicamente utiliza todas as anteriores, para comprimir um texto. Essas funções, exceto a `montarArvore`, contém sua inversa, para descomprimirmos um texto, mas essa parte ainda não foi abordada no programa.

Para o algoritmo de hashing foi criada uma classe chamada `Hashing`. Contendo os atributos necessários para o funcionamento. Os elementos específicos para o Hashing foram duas tabelas, de tamanho 100, cada uma com uma função diferente, uma para a função `Meio Quadrado` e outra para a função `Enlaçamento Limite`. E para cada uma dessas tabelas teremos funções para inserir, buscar e mostrar toda a tabela, para que o Hashing funcione como o esperado foi criado uma estrutura chamada `Item`, que é o tipo que é guardado na tabela Hash, o tipo tem duas strings, uma é a `chave`, base para o índice onde será adicionado, e outra é a `desc`, o texto relacionado a chave.

### Complexidade

**Algoritmo de Huffman**: A complexidade de Huffman é O(n), sendo n o número de caracteres do texto submetido a compressão. Por mais que o algoritmo percorra uma árvore (complexidade de O(log n)), a complexidade para contar as frequências de cada letra é maior, sendo O(n).

**Hashing**: Sem pensar na complexidade de cada função, o Hashing vai ter complexidade de O(n), no máximo, sendo n o tamanho da maior lista gerada a partir das colisões acontecidas. E o O(1) no melhor caso, quando o valor daquela chave ainda não tem colisões.

**Função Meio Quadrado**: Algo por volta de O(n/2), sendo n a quantidade de dígitos da chave.

**Enlaçamento Limite**: Algo por volta de O(n), sendo n a quantidade de dígitos da chave.


