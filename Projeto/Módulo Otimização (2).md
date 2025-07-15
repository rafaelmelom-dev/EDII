### Escopo

O módulo de otimização é compreendido pelos arquivos `otimizacao.cpp` e `otimizacao.hpp`, dentro da pasta `modulos`.(Todos os códigos estão separados na pasta Source)

### Arquitetura

Para o algoritmo de compressão foi criada uma classe chamada `CompHuffman`, assim como o módulo de busca contém os atributos necessários para a história. Além de conter também o algoritmo principal, o algoritmo de Huffman.

Com isso a classe `CompHuffman` acabou ficando um pouco mais complexa, todos os dados foram tratados como string a fim de mostrá-los, mas em um exemplo real poderíamos ter uma estrutura que pudesse ocupar menos espaço, como uma variável booleana, já que o algoritmo de Huffman só contém bits 0 e 1. Mas enfim, temos uma função para montar a árvore (`montarArvore`), para montar a tabela de códigos (`montarTabelaCodigos`) e para transformar o texto com os códigos (`codificarTexto`), além da função `comprimir`, que basicamente utiliza todas as anteriores, para comprimir um texto. Essas funções, exceto a `montarArvore`, contém sua inversa, para descomprimirmos um texto, mas essa parte ainda não foi abordada no programa.
