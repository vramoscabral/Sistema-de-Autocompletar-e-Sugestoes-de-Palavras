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
- 
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

* ```void stopwords()```: A primeira função que executada na main, ela abre o arquivo das stopwords, e armazena todas em um vector de string (vector<string> stopword);
* ```bool ehstopword(string word)```: Função booleana que recebe uma palavra que está sendo verificada na função de mapeamento e retorna se ela é ou não uma stop word;
* ```void mapeamento()```: É a função responsável por colocar todas as palavras na hash. Inicialmente é aberto o arquivo de texto e depois começa um loop do tipo while para fazer a leitura, e essa função deixa todas as palavras em letra mínuscula e são retiradas pontuações como "(", ")", ".", "-". A palavra em questão vai ser testada, se não for vazia e nem stopword, é colocada como array do heap e o int de contagem é incrementado.
* ```void topKitens()```: Após o mapeamento e contagem de todas as palavras, um loop até 20 é iniciado para colocar os primeiros itens que estão na hash, sejam eles os maiores ou não, e então um novo loop é iniciado, e este vai percorrer palavra por palavra e comparar o contador de cada uma com a palavra da heap que apareceu menos. Se a palavra do loop tiver maior contador, a palavra com menos contagem é removida do heap e é substituída.
* ```void heapfinal()```: A função anterior usava um heap que ordenava os elementos crescentemente para facilitar as operações, essa função de heapfinal transfere os elementos da heap crescente e coloca em uma heap em ordem decrescente, e após isso é mostrado no terminal o resultado final de todas as operações do programa.

## Exemplos da execução


## Conclusão

O foco desse programa ao utilizar uma hash e posteriormente o heap, foi considerar as palavras (elementos) mais presentes no texto, logo o critério de comparação das operações foi o valor da contagem de vezes em que as palavras apareciam.

Esse programa permite que o usuário possa ter uma noção do que é mais relevante e crucial a fim de orientar no entendimento do texto todo e sobre o que ele trata.

## Compilação e Execução

Esse código possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |


# Contato

✉️ <i>vramoscabral2020@gmail.com</i>
