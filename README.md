# Trabalho AEDS II - Sistema de Autocompletar e Sugestões de Palavras

# Descrição

Nesta segunda atividade de Algoritmos e Estrutura de Dados II, foi feito um programa usando a linguagem C++, que recebe 6 arquivos de texto (definidos como "text1.txt", "text2.txt", etc, para facilitar a implementação do algoritmo) e 1 arquivo "input.txt" que possui uma palavra em cada linha de texto, e todas as palavras serão usadas como termos de pesquisa do sistema criado nessa atividade.

Esse sistema vai verificar se cada palavra está presente em cada um dos textos obtidos, e se estiver, o sistema irá verificar se essa palavra é um dos top K elementos mais relevantes, e após isso irá apresentar esses top K itens (caso a palavra pesquisada seja um top K elemento, outra palavra será incluída nas top K na apresentação de sugestões).

Ao final do programa, será gerado um arquivo "output.txt" que apresenta os resultados de todas as palavras pesquisadas. Qualquer palavra que não seja uma stopword (palavra usada para ajudar na construção de sentenças como advérbio e preposição, irrelevante para o conjunto de resultados que engloba palavras que são importantes ao contexto do texto inteiro) pode ser incluída no arquivo "input.txt" para ser pesquisada no sistema. O sistema foi pré-definido para fornecer os resultados das 20 palavras mais relevantes em cada texto, porém essa quantidade também pode ser alterada.

## Objetivo

O sistema que apresenta o resultado das análises em cada pesquisa com três tipos de estrutura de dados (Árvore binária, Árvore AVL, Árvore de Huffman), tem objetivo de mostrar o que é relevante em cada texto e por meio da pesquisa identificar elementos no texto apresentando a sua frequência, ainda que seja ou não uma palavra relevante.

# Estruturas de Dados

## Árvore binária

Uma árvore binária é uma estrutura de dados onde cada nó (elemento) possui um conteúdo, e dois ponteiros, uma para o "filho" esquerdo e outra para o direito. Os "filhos" são as ramificações da árvore (daí o nome binária), e o conteúdo do primeiro elemento (topo ou raiz) serve de critério para a inserção de outros nós. Se o valor do item for menor que o da nó folha, vai para a esquerda, se for maior vai para a direita, e assim até encontrar um local vazio para ser armazenado. Como nessa atividade, o conteúdo da árvore são os Top K elementos, cada nó posssui uma pair de string (palavra) e int (frequência), e a frequência é o critério de inserção. Como pode ocorrer de palavras possuírem a mesma frequência, essa situação foi tratada considerando a inserção do filho esquerdo como menor ou igual, invés de menor.

![av_bin](https://github.com/vramoscabral/Sistema-de-Autocompletar-e-Sugestoes-de-Palavras/assets/127407951/096c63ee-0774-42f0-8905-da013a30102b)
exemplo de árvore binária

## AVL

Recebe esse nome por conta de seus criadores Adelson Velsky e Landis. Também é uma árvore binária, mas com um diferencial, ela é balanceada. O problema da árvore binária comum é o fato de apenas inserir itens sem balancear árvore tornando a pesquisa menos custosa. Um exemplo disso é quando a cada vez que um item for inserido, seu valor é menor. Na inserção da árvore comum, ela vai ser ramificada só pela esquerda, sem nenhum "filho direito", o que acaba fazendo com que a árvore tenha o comportamento de uma lista encadeada, onde um item aponta para o outro. No propósito da árvore em se ramificar e tornar mais fácil a pesquisa, era necessário que ela fosse balanceada para resolver esse problema.


![avltree](https://github.com/vramoscabral/Sistema-de-Autocompletar-e-Sugestoes-de-Palavras/assets/127407951/f23fb224-e49c-474d-83d6-8a5f91d7dd70)
exemplo de avl

## Implementação

- Primeiramente, o programa vai abrir o arquivo "stopwords.txt", e armazená-los em um vector de stop words, para ao longo da execução do código, o programa desconsiderar as stopwords para elementar as palavras mais frequentes, e também vai abrir o "input.txt" e salvar cada palavra num vector de termos de pesquisa para facilitar a implementação e não precisar abrir esse arquivo a cada pesquisa.
- Cada um dos textos da pasta texts, vai ser aberto e no loop de leitura das palavras, elas vão sendo armazenadas como chaves (arrays) de uma hash (no caso, unordered_map). Cada hash será armazenada em um vector de hash, totalizando 6 hashs por serem 6 textos. Cada termo da hash terá a palavra como chave e a sua frequência (string, int).
- Depois disso, é criado um heap (priority_queue) contendo string e int para cada uma das hashs, e nelas serão armazenadas as top K palavras mais relevantes. As 6 heaps serão armazenadas em um vector de heapsoriginais, que vão servir de base para a operação de pesquisa. Aqui também terá um vector de palavras topK+1, porque essa palavra depois da última vai ser utilizada na operação de pesquisa para substituir a palavra que for encontrada no heap.
- Então será percorrido o vector de termos, pra que cada palavra seja pesquisada. Cada palavra vai ser pesquisada nos 6 textos e seus resultados irão pro output. Inicialmente é verificado se a palavra está ou não no texto, se ela estiver então será verificado se a palavra está no heap top K ou não. Se estiver, essa palavra vai ser removida do heap e a topK + 1 será inserida, caso contrário a heap original se mantém. Quando a palavra está no texto, após as verificações, a heap modificada ou original vai gerar três árvores (binária, AVL e Huffman), e seus resultados irão ao output. Depois que cada palavra for analisada, o código encerra. Nada é printado no terminal, apenas no arquivo "output.txt"
- Em cada arquivo de implementação das 3 árvores, foi usado uma struct para representar o conteúdo e os ponteiros de cada Nó, e uma classe para a árvore e suas operações.

## Arquivos

* ```main.cpp```: Arquivo e função principal do código;
* ```metodo.hpp```, ```arvore.hpp```, ```avl.hpp```, ```huffman.hpp```: Declaração das funções utilizadas;
* ```metodo.cpp```, ```arvore.cpp```, ```avl.cpp```, ```huffman.cpp```: Implementação das funções descritas no arquivo hpp;
* ```text1.txt```, ```text2.txt```, ```text3.txt```, ```text4.txt```, ```text5.txt```, ```text6.txt```: Arquivo dos textos de base para o mapeamento e pesquisa;
* ```stopwords.txt```: Arquivo com as stopwords a serem desconsideradas do mapeamento de palavras;
* ```input.txt```: Arquivo com as palavras que serão procuradas nos textos;
* ```output.txt```: Arquivo com os resultados das operações desse programa (é gerado na compilação e execução, se mudarem o define e os termos do input, seu conteúdo será modificado);
* ```Makefile```: Automatiza o processo de compilação;

## Funções

```metodo.cpp```

* ```void stopwords_termos()```: A primeira função que executada na main, abre o arquivo das stopwords e armazena todas em um vector de string (vector<string> stopword), e também abre o input e armazena as palavras em vector<string> termos;
* ```bool ehstopword(string word)```: Função booleana que recebe uma palavra que está sendo verificada na função de mapeamento e retorna se ela é ou não uma stop word;
* ```void mapeamento()```: É a função responsável por colocar todas as palavras na hash. Com um loop for de 6 iterações, pois cada hash é montada a partir de um texto e é adicionada ao vector<unordered_map<string, int>> wordtxtsCounts (vector de hashs). Inicialmente é aberto o arquivo de texto e depois começa um loop do tipo while para fazer a leitura, e essa função deixa todas as palavras em letra mínuscula e são retiradas pontuações como "(", ")", ".", "-". A palavra em questão vai ser testada, se não for vazia e nem stopword, é colocada como array do heap e o int de contagem é incrementado.
* ```void topKitens()```: Após o mapeamento pra pegar todas as palavras das 6 hashs, entra em um loop para montar as 6 heaps e salvá-las em vector<priority_queue<Item>> heapsoriginais, (Item é uma struct de string, int, e o operador de ordem crescente). Em cada iteração um loop até K(no caso 20) é iniciado para colocar os primeiros itens que estão na hash, sejam eles os maiores ou não, e então um novo loop é iniciado, e este vai percorrer palavra por palavra e comparar o contador de cada uma com a palavra da heap que apareceu menos. Se a palavra do loop tiver maior contador, a palavra com menos contagem é removida do heap e é substituída. A cada iteração de inserção de palavra na heap, a palavra que sai é atríbuida ao elemento topK+1, ao final da inserção o item de K+1 maior valor de frequência é inserido em extern vector<pair<string, int>> topKplus1;
* ```void pesquisatermos()```: Nessa função é iniciado um loop que vai até o tamanho do vector de termos (ou seja, a quantidade de palavras do input), e é aberto um arquivo de output pra cada palavra para o registrar o resultado da pesquisa, e a cada iteração, cada palavra entra em um loop para ser analisada nos 6 textos. Primeiramente a palavra é procurada na hash do texto a ser iterado, se não estiver, é printado no output que a palavra não está no texto e o próximo texto é chamado. Se a palavra estiver no texto, ela vai ser procurada na heap original daquele texto, se for uma das top K palavras, a palavra é retirada do heap de top K e é colocado a top K+1. Caso contrário a heap se mantém, e é printado no output que a palavra está (ou não) na heap e a sua frequência. Após isso a heap modificada ou original irá ser levada às três árvores do algoritmo (binária, AVL e Huffman), e após as operações de cada árvore, pega um vector com a árvore em pré-ordem para ser printado no output específico de cada palavra.
* ```void Output()```: Última função chamada na main. Cada palavra gerou um arquivo outN.data, de 1 até N(quantidade de termos de pesquisa), e essa função é responsável por juntar dentro de um único arquivo output.txt, todas as informações que foram geradas pelas operações desse sistema e armazenadas anteriormente nos arquivos output específicos. Todos os arquivos output temporários gerados durante a execução são removidos.

```arvore.cpp```

* ```void arvorebinsert(pair<string, int> item)```: Função que recebe cada item da heap de maneira individual e insere na árvore binária. Usando o int da pair como critério de inserção.
* ```vector<pair<string, int>> arvoreb(priority_queue<Item> heap)```: Função fora da classe que é responsável por receber diretamente da função pesquisatermos() do metodo.cpp a heap que é inserida na árvore binária. Também chama a função de pegar a pré-Ordem da árvore e de remover a árvore, ao final retorna o vector da pré-Ordem.

```avl.cpp```

```huffman.cpp```

## Exemplos da execução


## Conclusão

Esse sistema se mostra eficiente em mostrar ao usuário o que há de mais importante e relevante em cada texto, além de permitir que sejam colocadas quantas palavras forem necessárias para serem procuradas em cada um dos textos, e que seja definida a quantidade de palavras mais relevantes a serem mostradas na análise.

## Compilação e Execução

Esse código possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |


# Contato

✉️ <i>vramoscabral2020@gmail.com</i>
