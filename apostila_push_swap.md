# Apostila Push Swap — Material de Estudo

*Escrito no papel de um mentor sênior de Engenharia de Software da 42. Este material ensina os conceitos, algoritmos e decisões de projeto necessários para implementar o push_swap do zero — ele não entrega a solução pronta.*

---

## Sumário

1. O que é o Push Swap
2. Entendendo o problema
3. Operações obrigatórias
4. Conceitos de C necessários
5. Estruturas de dados
6. Organização do projeto
7. Fluxo completo do programa
8. Parsing
9. Algoritmos
10. Estratégia de implementação
11. Função por função
12. Complexidade
13. Testes
14. Debug
15. Erros comuns
16. Roadmap de estudo

---

## Capítulo 1 — O que é o Push Swap

### O objetivo do projeto

Push_swap pede um programa que recebe uma lista de inteiros na linha de comando e imprime, na saída padrão, a **menor sequência possível de instruções** que ordena essa lista de forma ascendente, usando apenas duas pilhas (`a` e `b`) e um conjunto fechado de 11 operações.

Não é "ordenar" no sentido comum (você não escolhe o algoritmo que quiser e chama `qsort`). É ordenar **dentro de um modelo de custo diferente**: cada operação (`sa`, `pb`, `ra`, etc.) custa exatamente "1 unidade", independente de quantos elementos a pilha tem. Isso muda completamente o que "eficiente" significa aqui.

### Que problema ele resolve (pedagogicamente)

Na maioria das disciplinas de algoritmos, você aprende complexidade olhando para *tempo de CPU* (comparações, trocas). No push_swap, a métrica de custo é **o número de operações emitidas**, não o tempo que seu código C leva para decidir o que fazer. Isso força você a pensar em algoritmos de um jeito novo: seu programa em C pode gastar quanto tempo quiser pensando (contar, escanear, comparar o quanto precisar), mas o que sai impresso — a receita de operações — precisa ser curta.

Essa distinção é o cerne pedagógico do projeto: ele separa "complexidade do meu código" de "complexidade da solução que meu código produz".

### Por que existe na 42

A 42 usa push_swap como o primeiro grande desafio algorítmico do currículo comum, normalmente logo após libft e get_next_line. Até esse ponto, os projetos são principalmente sobre "traduzir uma spec em C corretamente". Push_swap é o primeiro que exige:

- Desenhar uma estrutura de dados própria (pilha).
- Comparar múltiplas estratégias algorítmicas e justificar a escolha.
- Lidar com um espaço de entrada que vai de 2 a 500+ números, onde a estratégia ingênua (que funciona para 3 números) explode para 500.

### Habilidades que o projeto desenvolve

- Modelagem de estruturas de dados (lista encadeada como pilha).
- Raciocínio sobre complexidade em um modelo de custo não convencional.
- Depuração de algoritmos que são fáceis de escrever errado de forma sutil (o programa roda, não trava, mas ordena errado ou usa operações demais).
- Design modular em C puro, sem bibliotecas externas de estrutura de dados.

### Como o avaliador analisa o projeto

Numa defesa (peer-evaluation) típica de push_swap, o avaliador costuma:

1. Pedir para rodar com poucos números (3, 5) e conferir a saída manualmente.
2. Rodar com 100 e 500 números aleatórios e contar quantas operações saíram (comparando com os limites esperados).
3. Testar entradas inválidas: letras, `INT_MAX + 1`, duplicados, lista vazia.
4. Pedir para explicar, ao vivo, por que o algoritmo escolhido tem a complexidade alegada — inclusive pedindo para modificar algo na hora.
5. Verificar memória (com `valgrind` ou `leaks`) e crash em casos extremos (0 argumentos, 1 argumento).

### O que reprova um projeto

- O programa trava, dá segfault, ou double free — mesmo em um caso extremo raramente testado.
- A saída não ordena de fato a pilha `a` (verificado programaticamente pelo checker).
- Memory leak detectado.
- Normas de formatação (Norminette) violadas — em muitas escolas, isso zera o projeto inteiro, mesmo que o código funcione perfeitamente.
- Não conseguir explicar o próprio código na arguição (isso é considerado tão grave quanto um bug).

### Resumo do capítulo

Push_swap não é "implementar um sort". É desenhar, a partir de operações restritas, a sequência mais curta possível que leva uid uma pilha desordenada a um estado ordenado — e depois defender, com propriedade, por que sua escolha de algoritmo é boa.

### Perguntas de revisão

1. Por que "número de operações emitidas" é uma métrica de custo diferente de "tempo de execução do seu programa em C"?
2. Cite duas coisas que fazem um push_swap ser reprovado mesmo funcionando "na maior parte dos casos".
3. Por que a defesa oral é parte da avaliação, e não só rodar o binário?

### Exercícios

1. Sem escrever código, liste de cabeça as 11 operações permitidas (você vai precisar delas de cor).
2. Pesquise (não implemente ainda) o que é "operation count" versus "time complexity" e escreva, com suas palavras, a diferença.

---

## Capítulo 2 — Entendendo o problema

### O conceito das duas pilhas

Você tem duas pilhas, `a` e `b`. No início, `a` tem todos os números (em alguma ordem, desordenada), e `b` está vazia. O objetivo é terminar com `a` ordenada ascendente (menor no topo) e `b` vazia de novo.

```
Início:                 Objetivo:
a: [5, 2, 8, 1]         a: [1, 2, 5, 8]
b: []                   b: []
```

`b` funciona como uma "área de trabalho temporária" — você tira elementos de `a`, mexe neles em `b`, e devolve para `a` na ordem certa.

### Por que "só pilha" (e não array, não fila)

Uma pilha só permite acesso ao topo. Você não pode "pegar o terceiro elemento direto" — precisa girar (`rotate`) a pilha até ele estar no topo, ou tirar tudo o que está acima dele e guardar em algum lugar. Isso é uma **restrição deliberada**: ela impede que você resolva o problema com um algoritmo de ordenação de array clássico (como quicksort com índices aleatórios) e força você a pensar em termos de "sequência de movimentos válidos".

### Operações permitidas — por que essas e não outras

Repare que não existe uma operação "insira o elemento X na posição Y". Você só tem:
- Trocar os dois primeiros de uma pilha (`sa`/`sb`/`ss`).
- Mover o topo de uma pilha para o topo da outra (`pa`/`pb`).
- Girar a pilha inteira em um sentido (`ra`/`rb`/`rr`) ou no outro (`rra`/`rrb`/`rrr`).

Isso significa que qualquer "algoritmo de ordenação" que você conheça (bubble sort, insertion sort, quicksort...) precisa ser **traduzido** para essa linguagem de movimentos. A ideia central do curso é: pegue a *lógica* de um algoritmo clássico e reimplemente-a usando só rotação e transferência entre pilhas.

### Pensando como desafio de algoritmos

Uma boa forma de encarar o push_swap é: "eu tenho um algoritmo de ordenação em mente (ex: seleção do menor). Cada 'passo lógico' dele — comparar, mover — precisa virar uma ou mais dessas 11 operações. Quantas operações, no total, meu passo lógico vai custar?"

Exemplo mental (não é código, é raciocínio):
- "Escolher o menor elemento" → não custa nenhuma operação (é só *olhar* os valores, seu programa em C pode escanear a lista à vontade).
- "Trazer esse elemento para o topo" → custa `N` rotações, onde `N` é a distância dele até o topo.
- "Empurrar para a pilha `b`" → custa 1 operação (`pb`).

Esse tipo de contabilidade — "quantas operações reais essa ideia gera?" — é o que você vai fazer o tempo todo neste projeto.

### Exemplo ilustrado — girando uma pilha

```
a antes de 'ra':        a depois de 'ra':
┌───┐                    ┌───┐
│ 2 │ topo                │ 8 │ topo
├───┤                    ├───┤
│ 5 │                    │ 1 │
├───┤                    ├───┤
│ 8 │                    │ 2 │
├───┤                    ├───┤
│ 1 │                    │ 5 │
└───┘                    └───┘
```

`ra` pegou o topo (2) e o mandou para o fundo — todo mundo "subiu" uma posição.

### Resumo do capítulo

O problema não é "ordenar números" — é "traduzir uma estratégia de ordenação em uma sequência mínima de movimentos de pilha". A restrição de só ter acesso ao topo é o que torna o desafio interessante.

### Perguntas de revisão

1. Por que você não pode simplesmente "inserir na posição certa" como faria com um array?
2. O que a pilha `b` representa na sua estratégia mental?
3. Dado `a: [3, 1, 2]` (topo=3), quantas rotações (`ra`) você precisa para trazer o `2` ao topo?

### Exercícios

1. Desenhe (no papel, ASCII) o efeito de `rra` na pilha `a: [3, 1, 2]` (topo à esquerda).
2. Para `a: [4, 2, 1, 3]`, escreva à mão (sem código) uma sequência de operações que a ordene — não precisa ser a menor sequência, só uma que funcione.

---

## Capítulo 3 — Operações obrigatórias

Convenção usada nesta apostila: a pilha é escrita com o **topo à esquerda**. Ex.: `a: [3, 1, 2]` significa que `3` está no topo.

### `sa` — swap a

- **O que faz:** troca os dois primeiros elementos do topo de `a`.
- **Não faz nada** se `a` tiver 0 ou 1 elemento.
- **Antes:** `a: [3, 1, 2]` → **Depois:** `a: [1, 3, 2]`
- **Complexidade (operação):** custa sempre 1, independente do tamanho de `a`.
- **Quando usar:** quando os dois primeiros elementos estão fora de ordem entre si e você precisa deles ordenados sem gastar uma rotação.

### `sb` — swap b

Idêntico a `sa`, mas em `b`.

### `ss`

- Executa `sa` e `sb` ao mesmo tempo (conta como **1** operação no total, não 2).
- Usado quando você sabe, de antemão, que precisa trocar o topo de ambas as pilhas simultaneamente (economiza 1 operação comparado a fazer `sa` e `sb` separado).

### `pa` — push a

- **O que faz:** tira o topo de `b` e coloca no topo de `a`.
- Não faz nada se `b` estiver vazia.
- **Antes:** `a: [2]`, `b: [5, 8]` → **Depois:** `a: [5, 2]`, `b: [8]`
- **Quando usar:** ao "devolver" elementos de `b` para `a`, geralmente depois que eles já estão na ordem certa em `b`.

### `pb` — push b

Idêntico a `pa`, na direção contrária: tira o topo de `a`, coloca no topo de `b`.

### `ra` — rotate a

- **O que faz:** o primeiro elemento vira o último (a pilha inteira "gira" para cima).
- **Antes:** `a: [1, 2, 3, 4]` → **Depois:** `a: [2, 3, 4, 1]`
- **Quando usar:** quando o elemento que você quer está a poucas posições **abaixo** do topo — rotacionar é mais barato que empilhar tudo em `b`.

### `rb` — rotate b

Igual a `ra`, mas em `b`.

### `rr`

`ra` e `rb` ao mesmo tempo (custa 1 operação).

### `rra` — reverse rotate a

- **O que faz:** o último elemento vira o primeiro (rotação no sentido contrário de `ra`).
- **Antes:** `a: [1, 2, 3, 4]` → **Depois:** `a: [4, 1, 2, 3]`
- **Quando usar:** quando o elemento que você quer está mais perto do **fundo** da pilha — é mais barato "descer" o fundo até o topo do que dar a volta inteira com `ra`.

### `rrb` — reverse rotate b

Igual a `rra`, em `b`.

### `rrr`

`rra` e `rrb` ao mesmo tempo (custa 1 operação).

### Tabela-resumo

| Operação | Efeito | Custo | Usada tipicamente para |
|---|---|---|---|
| `sa`/`sb`/`ss` | troca os 2 do topo | 1 | corrigir ordem local no topo |
| `pa`/`pb` | move topo entre pilhas | 1 | transferir um elemento já "pronto" |
| `ra`/`rb`/`rr` | topo → fundo | 1 | alcançar algo perto do topo |
| `rra`/`rrb`/`rrr` | fundo → topo | 1 | alcançar algo perto do fundo |

### A decisão mais importante deste capítulo

Toda vez que você precisa "trazer um elemento ao topo", existe uma escolha: rotacionar para frente (`ra`) ou para trás (`rra`)? A resposta é sempre: **escolha a direção com menos passos**. Se o elemento está na posição `p` (contando do topo, 0-indexado) de uma pilha de tamanho `n`, o custo de `ra` repetido é `p`, e o custo de `rra` repetido é `n - p`. Você compara os dois e usa o menor.

### Resumo do capítulo

As 11 operações formam um "alfabeto" fechado. Todo algoritmo de push_swap, no fim, é uma tradução de uma ideia de ordenação para uma sequência dessas 11 letras — e a arte está em minimizar quantas letras você usa.

### Perguntas de revisão

1. Por que `ss`, `rr` e `rrr` existem, já que dá pra obter o mesmo efeito combinando as operações simples?
2. Se um elemento está na posição 3 de uma pilha de 10 elementos (0-indexado, topo = posição 0), você usaria `ra` ou `rra` repetidas para trazê-lo ao topo? Por quê?
3. `pa` e `pb` fazem o quê exatamente com a pilha de origem — ela encolhe ou cresce?

### Exercícios

1. Para `a: [1, 2, 3, 4, 5]` (topo=1), quantas `ra` você precisa para trazer o `4` ao topo? E quantas `rra`? Qual é mais barato?
2. Escreva, em papel, o estado de `a` e `b` depois de: `a: [3, 1, 2]`, `b: []` → `pb`, `pb`, `sa`... continue e veja onde chega.

---

## Capítulo 4 — Conceitos de C necessários

Este capítulo lista os pré-requisitos de C do projeto. A ideia não é ensinar C do zero, mas apontar **exatamente onde e por que** cada conceito aparece dentro do push_swap.

### Ponteiros

Um ponteiro guarda o **endereço de memória** de uma variável, não o valor em si. No push_swap, ponteiros aparecem em toda parte porque a pilha é uma lista encadeada — cada nó "aponta" para o próximo.

```c
int valor = 10;
int *p = &valor; /* p guarda o endereço de 'valor' */
printf("%d", *p);  /* *p acessa o valor apontado: 10 */
```

### Ponteiro para ponteiro

Usado quando uma função precisa **modificar o próprio ponteiro** que o chamador tem (não só o que ele aponta). No push_swap, isso aparece toda vez que uma operação precisa trocar *qual nó é o topo da pilha* — se a função só recebesse `t_stack *pilha`, qualquer troca dentro dela seria local (perdida ao sair da função). Por isso as funções de operação normalmente recebem `t_stack **pilha`.

```c
void muda_topo(int **ponteiro_para_ponteiro)
{
	static int novo_valor = 42;
	*ponteiro_para_ponteiro = &novo_valor;
}
```

### Struct

Uma struct agrupa vários dados relacionados sob um único tipo. É como representamos um nó da pilha (valor + ponteiro para o próximo).

### Listas encadeadas

Uma sequência de nós onde cada um aponta para o próximo (não como um array, que fica contíguo na memória). É a estrutura natural para representar uma pilha cujo tamanho muda — ver Capítulo 5 para a comparação completa.

### Alocação dinâmica / malloc / free

`malloc` reserva memória em tempo de execução (o tamanho da entrada só é conhecido quando o programa já está rodando, então você não pode usar um array de tamanho fixo declarado em tempo de compilação). `free` devolve essa memória ao sistema. No push_swap, cada nó da pilha é alocado com `malloc` quando criado, e **todo** nó precisa ser liberado com `free` antes do programa terminar — inclusive em caminhos de erro.

### Vazamento de memória (memory leak)

Acontece quando você perde a referência a um bloco alocado sem ter dado `free` nele antes. No push_swap, o erro mais comum é: alocar os nós da pilha, e se ocorrer um erro de parsing no meio do caminho, esquecer de liberar o que já tinha sido alocado antes de dar `exit`.

### Manipulação de argumentos (argc / argv)

`argc` é a quantidade de argumentos recebidos, `argv` é o array de strings com cada argumento (`argv[0]` é o nome do programa). O push_swap recebe seus números via `argv`, então todo o parsing começa varrendo esse array.

### Conversão de strings (string → int)

Os argumentos chegam como `char *` (texto), e você precisa convertê-los para `int` **validando** no processo (rejeitar letras, símbolos, overflow). Isso é diferente de simplesmente usar `atoi`, que não sinaliza erro — ver Capítulo 8.

### Tratamento de erros

Toda entrada inválida deve ser detectada **antes** de você começar a gerar operações, e o programa deve terminar de forma limpa (sem vazar memória, sem crashar), normalmente imprimindo `Error` e saindo com um código de erro.

### Modularização

Dividir o programa em arquivos por responsabilidade (parsing, operações, algoritmos, utilitários) em vez de um único arquivo gigante. Facilita tanto a norma (limite de funções por arquivo) quanto a legibilidade.

### Arquivos `.c` e `.h`

`.h` declara (protótipos de funções, tipos, estruturas) — é o "contrato" que outros arquivos usam para saber o que existe. `.c` implementa. Cada `.c` inclui o `.h` para saber a assinatura das funções que usa de outros arquivos.

### Makefile

Automatiza a compilação: define como transformar os `.c` em um binário, quais flags de warning usar, e as regras padrão (`all`, `clean`, `fclean`, `re`) exigidas pela 42.

### Includes

`#include` insere o conteúdo de outro arquivo (geralmente um `.h`) antes da compilação. Includes mal geridos (arquivo incluído mas não usado, ou faltando guarda de inclusão dupla) são um erro comum de norma.

### Tipos de dados

`int` para os valores da pilha (a spec limita à faixa de `int`), `long` quando você precisa de uma faixa maior temporariamente (por exemplo, ao detectar overflow durante o parsing, antes de confirmar que cabe em `int`).

### Enum

Útil para representar um conjunto fixo de "modos" ou "categorias" com nomes legíveis em vez de números mágicos (por exemplo, qual estratégia de ordenação está ativa).

### typedef

Cria um apelido para um tipo, deixando o código mais legível (`t_stack` em vez de `struct s_stack` toda vez).

### Complexidade de funções

Cada função no C do seu projeto tem um custo (quantas vezes ela itera, quantas vezes chama outra função). Isso é diferente da complexidade *do algoritmo de push_swap em si* (contada em operações emitidas) — são dois níveis de análise que não devem ser confundidos (ver Capítulo 1).

### Resumo do capítulo

Nenhum conceito aqui é exclusivo do push_swap — mas o projeto é onde eles se juntam pela primeira vez: ponteiro duplo para mutar o topo da pilha, lista encadeada para representar a pilha, parsing rigoroso de `argv`, e organização modular disciplinada pela Norma.

### Perguntas de revisão

1. Por que uma função que "troca o topo da pilha" normalmente recebe `t_stack **` e não `t_stack *`?
2. Qual a diferença entre um vazamento de memória e um "uso depois de liberar" (use-after-free)?
3. Por que você não pode usar um array de tamanho fixo para guardar a pilha `a`?

### Exercícios

1. Escreva uma função pequena e isolada (não relacionada ao push_swap) que recebe `int **p` e faz `*p` apontar para um novo `int` alocado com `malloc`. Teste que ela funciona.
2. Explique com suas palavras por que `atoi("99999999999")` é perigoso e o que você usaria no lugar.

---

## Capítulo 5 — Estruturas de dados

### As três opções

| Critério | Array | Lista simplesmente encadeada | Lista duplamente encadeada |
|---|---|---|---|
| Alocação | um bloco contíguo, precisa saber o tamanho antes (ou realocar) | um nó por elemento, cresce/encolhe fácil | um nó por elemento, cresce/encolhe fácil |
| Acesso ao topo | O(1) via índice | O(1) via ponteiro de topo | O(1) via ponteiro de topo |
| `rotate` (topo→fundo) | precisa deslocar todos os elementos, ou usar índice circular | O(n) para achar o fim, O(1) para religar ponteiros | O(1) se você mantém ponteiro para o fim |
| `reverse rotate` (fundo→topo) | fácil com índice circular, complicado sem | O(n) para achar o penúltimo nó | O(1) com ponteiro para o fim e ponteiro `prev` |
| Complexidade de implementação | baixa se o tamanho é fixo; média com realocação | baixa/média | média/alta (mais ponteiros para manter consistentes) |
| Risco de bugs | baixo (sem ponteiros) | médio (esquecer de religar `next`) | alto (esquecer de religar `prev` ou `next`) |

### Vantagens e desvantagens, uma a uma

**Array**
- Vantagem: acesso a qualquer posição é O(1) direto, sem percorrer nada.
- Desvantagem: rotacionar significa fisicamente mover todos os elementos (ou implementar um buffer circular com índices, o que adiciona complexidade conceitual sem necessidade aqui, já que o tamanho da pilha muda a cada `pa`/`pb`).
- No contexto do push_swap: como o tamanho de `a` e `b` muda toda hora (elementos migram de um lado para o outro), você precisaria realocar constantemente — não é natural.

**Lista simplesmente encadeada**
- Vantagem: inserir/remover no topo é O(1); crescer/encolher é natural (é exatamente o que `pa`/`pb` fazem).
- Desvantagem: para "reverse rotate" (mover o *último* elemento para o topo), você precisa percorrer a lista inteira para achar o penúltimo nó (custa O(n) em tempo de C — não em operações emitidas, lembre-se da distinção do Capítulo 1).
- No contexto do push_swap: é a escolha mais comum e mais equilibrada.

**Lista duplamente encadeada**
- Vantagem: com um ponteiro para o último nó, tanto `rotate` quanto `reverse rotate` ficam O(1) em tempo de C.
- Desvantagem: mais um ponteiro (`prev`) para manter correto em toda operação — mais chance de bug sutil (achar que religou tudo e esquecer um lado).
- No contexto do push_swap: ganha performance de C, mas isso raramente importa (n ≤ 500), então o custo extra de complexidade de implementação geralmente não compensa.

### Qual costuma ser a melhor escolha, e por quê

Para o push_swap, a lista **simplesmente encadeada** costuma ser a melhor escolha na prática: ela modela naturalmente o crescimento/encolhimento da pilha (`pa`/`pb` viram literalmente "tirar da frente de uma lista e colocar na frente da outra"), e o custo extra de "achar o fim" para `reverse rotate` é em **tempo de execução do seu C**, não em operações emitidas — e como `n` é no máximo algumas centenas, isso nunca é um gargalo real. Você só consideraria lista duplamente encadeada se estivesse otimizando para milhões de elementos, o que não é o caso aqui.

### Resumo do capítulo

A escolha da estrutura de dados não muda a complexidade *do algoritmo em operações* — ela muda o quão fácil é implementar cada operação corretamente em C. Lista simplesmente encadeada é o ponto de equilíbrio certo para este projeto.

### Perguntas de revisão

1. Por que array não é uma boa escolha aqui, mesmo sendo O(1) para acesso indexado?
2. O que uma lista duplamente encadeada ganha em troca de mais complexidade de implementação?
3. O custo de "achar o fim da lista" para implementar `reverse rotate" conta para a complexidade do algoritmo push_swap (em operações)? Por quê?

### Exercícios

1. Desenhe (ASCII) uma lista simplesmente encadeada de 4 nós e mostre, com setas, o que muda ao fazer um "rotate" (topo vira fundo).
2. Sem escrever a operação completa, descreva em texto o algoritmo para implementar `reverse rotate` numa lista simplesmente encadeada (que ponteiros você precisa rastrear ao percorrer).

---

## Capítulo 6 — Organização do projeto

### Estrutura de diretórios sugerida

```
push_swap/
├── Makefile
├── includes/
│   └── push_swap.h
├── src/
│   ├── main.c
│   ├── parser/
│   │   ├── parse_args.c
│   │   └── validate.c
│   ├── stack/
│   │   ├── stack_new.c
│   │   ├── stack_utils.c
│   │   └── stack_ops.c
│   ├── operations/
│   │   ├── ops_a.c
│   │   ├── ops_b.c
│   │   └── ops_double.c
│   ├── sorting/
│   │   ├── sort_small.c
│   │   └── sort_big.c
│   └── utils/
│       └── ft_helpers.c
├── libft/            (se seu projeto permitir usá-la)
├── checker/          (bônus, programa separado)
└── tests/
    └── (scripts de teste, não fazem parte do binário)
```

### Para que serve cada pasta

- **`includes/`** — o(s) `.h` do projeto: declarações de tipos (`t_stack`), protótipos de todas as funções públicas. É o "índice" do projeto — qualquer pessoa devia entender a estrutura de dados só lendo esse arquivo.
- **`src/parser/`** — tudo relacionado a interpretar `argv`: converter strings em inteiros, validar, detectar duplicados, popular a pilha `a` inicial.
- **`src/stack/`** — criação de nós, funções genéricas de manipulação de lista (que tanto `a` quanto `b` usam).
- **`src/operations/`** — a implementação literal das 11 operações da spec. Cada uma imprime seu próprio nome e mexe na(s) pilha(s).
- **`src/sorting/`** — a lógica de decisão: qual estratégia usar, e a orquestração de operações que ela gera.
- **`src/utils/`** — pequenas funções auxiliares (ex.: as reimplementações mínimas de `strlen`, conversões, escrita — já que muitas vezes você não pode usar libc além do estritamente permitido pela spec).
- **`checker/`** — o programa bônus que valida uma sequência de operações contra uma pilha inicial (não faz parte do binário `push_swap`).
- **`tests/`** — scripts (shell/python) para gerar entradas aleatórias e checar corretude/contagem de operações — não compilam junto com o projeto, são ferramentas de apoio.

### Quem chama quem (visão de alto nível)

```
main()
  └─> parse_args()          (parser/)
        └─> valida e monta a lista ligada inicial (stack/)
  └─> escolhe_estrategia()   (sorting/)
        └─> chama operações  (operations/)
              └─> cada operação imprime + chama funções genéricas de lista (stack/)
  └─> libera memória e retorna
```

### Dependências entre módulos

- `operations/` depende de `stack/` (para manipular a lista), mas **não** depende de `sorting/` nem de `parser/`.
- `sorting/` depende de `operations/` (para emitir os movimentos) e de `stack/` (para consultar o estado atual).
- `parser/` depende de `stack/` (para criar os nós) e de `utils/` (para conversão de string).
- `main.c` é o único arquivo que conhece todos os módulos — ele os orquestra, mas não implementa lógica de negócio.

Esse desenho evita dependência circular: `stack/` não sabe que `operations/` existe, `operations/` não sabe que `sorting/` existe. Isso deixa cada camada testável isoladamente.

### Diagrama de arquitetura

```
        ┌──────────────┐
        │    main.c    │
        └──────┬───────┘
     ┌─────────┼──────────┐
     ▼         ▼          ▼
┌─────────┐┌─────────┐┌──────────┐
│ parser  ││ sorting ││ (saída)  │
└────┬────┘└────┬────┘└──────────┘
     │          │
     ▼          ▼
┌─────────┐┌────────────┐
│  stack  │◄┤ operations │
└─────────┘└────────────┘
```

### Como isso mapeia para o nosso projeto real

*[Nota adicionada após a implementação: a estrutura acima é a organização didática/genérica. No nosso projeto de fato, por causa do limite de "5 funções por arquivo" da Norma, optamos por uma pasta única (raiz do repositório) com vários arquivos pequenos e nomeados por responsabilidade, em vez de subpastas — o princípio de separação por módulo continua o mesmo, só a forma de expressar isso em diretórios que mudou.]*

```
push_swap/
├── Makefile
├── push_swap.h            (todos os protótipos e tipos)
├── main.c                 (orquestra tudo)
├── parse.c, parse_utils.c (parser + validação/tokenização)
├── stack.c, stack_utils.c (nó da pilha + operações genéricas)
├── ops_a.c, ops_b.c, ops_double.c (as 11 operações da spec)
├── disorder.c             (métrica de desordem)
├── sort_small.c           (casos n ≤ 5)
├── sort_selection.c       (estratégia O(n²) — "--simple")
├── sort_chunks_utils.c, sort_chunks.c (estratégia O(n·√n) — "--medium")
├── sort_radix.c           (estratégia O(n log n) — "--complex")
├── sort_adaptive.c        (escolhe entre as três acima)
├── bench.c                (saída do modo --bench)
└── io_utils.c             (escrita em fd, sem usar printf)
```

A relação de dependência entre esses arquivos é a mesma discutida acima (`stack`/`ops` não conhecem `sort_*`; `sort_*` conhece `ops` e `stack`; `main.c` é quem orquestra tudo) — só não está expressa em pastas separadas.

### Resumo do capítulo

Organizar por responsabilidade (parser, stack, operations, sorting, utils) mantém cada arquivo pequeno, testável e alinhado com o limite de funções por arquivo da Norma — e deixa claro, só pela estrutura de pastas, o fluxo de dependências do projeto.

### Perguntas de revisão

1. Por que `stack/` não deveria depender de `sorting/`?
2. Qual módulo é responsável por decidir "que operações emitir para ordenar"?
3. Por que separar `checker/` do binário principal do push_swap?

### Exercícios

1. Desenhe você mesmo (sem copiar o diagrama acima) a árvore de dependências do seu projeto, antes de escrever a primeira linha de código.
2. Liste, para cada pasta, pelo menos uma função que você espera que exista nela.

---

## Capítulo 7 — Fluxo completo do programa

### Do comando à primeira linha de saída

Vamos seguir `./push_swap 3 2 1` passo a passo.

```
$ ./push_swap 3 2 1
```

**Passo 1 — o shell chama `main(argc, argv)`**
`argc = 4` (`"push_swap"`, `"3"`, `"2"`, `"1"`), `argv[1..3]` são os números como texto.

**Passo 2 — `main` decide: sem argumentos suficientes?**
Se `argc < 2`, a spec diz para não imprimir nada e simplesmente retornar — não é erro, é "nada para ordenar".

**Passo 3 — parsing**
`main` chama algo como `parse_args(argc, argv, &pilha_a)`. Essa função:
- percorre cada `argv[i]`,
- valida se é um inteiro bem formado (Capítulo 8),
- verifica se cabe em `int` (sem overflow),
- verifica duplicados,
- se tudo certo, cria um nó e insere na lista `a`.
Se qualquer validação falhar, ela retorna erro.

**Passo 4 — tratamento de erro**
Se o parsing falhou, `main` imprime `"Error\n"` na saída de erro (`stderr`) e encerra — **sem vazar memória** do que já tinha sido alocado.

**Passo 5 — checagem trivial**
Antes de gastar qualquer operação, verifique se a pilha já está ordenada (para `3 2 1` não está). Se estivesse, o programa não imprime nada e termina.

**Passo 6 — escolha do algoritmo**
Com a pilha montada, o programa decide qual estratégia usar — para poucos elementos (2, 3, 4, 5) normalmente existe uma lógica dedicada; para muitos, um algoritmo genérico (Capítulo 9).

**Passo 7 — geração e impressão das operações**
Cada vez que o algoritmo decide "preciso girar" ou "preciso empilhar", ele chama a função daquela operação, que:
1. modifica a(s) pilha(s) internamente,
2. imprime o próprio nome (ex.: `"ra\n"`) em `stdout`.

Para `3 2 1`, uma sequência válida (não necessariamente a mínima) seria: `sa` (troca 3 e 2 → `2 3 1`), depois mover e reorganizar até chegar em `1 2 3`.

**Passo 8 — liberação de memória**
Depois que o algoritmo termina (pilha `a` ordenada, `b` vazia), todo nó alocado é liberado com `free`.

**Passo 9 — término**
`main` retorna `0` (sucesso).

### Fluxograma ASCII

```
        ┌───────────────────┐
        │   início (main)   │
        └─────────┬─────────┘
                   ▼
         ┌───────────────────┐
         │ argc < 2 ?         │──sim──► retorna (nada imprime)
         └─────────┬─────────┘
                   │ não
                   ▼
         ┌───────────────────┐
         │  parse + valida    │──erro──► imprime "Error", libera o que
         └─────────┬─────────┘           já foi alocado, encerra
                   │ ok
                   ▼
         ┌───────────────────┐
         │ já está ordenada?  │──sim──► libera e termina (sem imprimir)
         └─────────┬─────────┘
                   │ não
                   ▼
         ┌───────────────────┐
         │ escolhe algoritmo  │
         └─────────┬─────────┘
                   ▼
         ┌───────────────────┐
         │ gera operações     │──(cada operação imprime seu nome)
         │ (loop)             │
         └─────────┬─────────┘
                   ▼
         ┌───────────────────┐
         │ libera memória     │
         └─────────┬─────────┘
                   ▼
                 (fim)
```

### Resumo do capítulo

O fluxo tem uma ordem rígida: validar antes de tudo, checar se já está ordenado antes de gastar operações, só então decidir o algoritmo, gerar/imprimir operações, e por fim liberar tudo — inclusive nos caminhos de erro.

### Perguntas de revisão

1. Por que checar "já está ordenada" antes de escolher o algoritmo economiza operações?
2. O que deve acontecer com a memória já alocada se o parsing falhar no meio do caminho?
3. Em que exato momento uma operação "conta" como emitida — antes ou depois de imprimir seu nome?

### Exercícios

1. Desenhe seu próprio fluxograma (a mão, sem copiar) para o caso `argc == 1`.
2. Escreva, em pseudocódigo (não C), os passos de `main` na ordem certa, antes de implementar.

---

## Capítulo 8 — Parsing

### O que precisa ser validado

| Caso | Exemplo inválido | Por quê |
|---|---|---|
| Letras/símbolos misturados | `"12a"`, `"1.5"` | não é um inteiro válido |
| Apenas sinal, sem dígitos | `"-"`, `"+"` | não representa número nenhum |
| Overflow (maior que `INT_MAX`) | `"99999999999"` | não cabe em `int` |
| Underflow (menor que `INT_MIN`) | `"-99999999999"` | idem |
| Duplicados | `"3", "3"` | a spec proíbe valores repetidos |
| Entrada vazia | `argc == 1` | nada a ordenar, não é erro, só não imprime nada |
| Múltiplos sinais | `"--3"`, `"+-3"` | formato inválido |

**Nota sobre espaços dentro de um argumento — decisão deste projeto:** diferente do que uma primeira leitura da spec sugere, o nosso parser **aceita** múltiplos números dentro de um único `argv`, separados por espaço (ex.: `./push_swap "1 2 3"` funciona igual a `./push_swap 1 2 3`). Isso é feito por uma função tokenizadora (`read_next_token`, em `parse_utils.c`) que percorre a string caractere a caractere, ignora espaços entre números e extrai um "token" por vez, validando cada um individualmente com `my_atoi_strict`. Ou seja: "espaço" não é mais um caractere inválido por si só — ele é um **separador de token**, e cada token extraído passa pela mesma validação de sempre (dígitos, sinal, overflow). Um token vazio (só espaços, ou nenhum número entre eles) ainda é tratado como erro.

### Por que não basta usar `atoi`

`atoi` (da libc padrão) **não tem como sinalizar erro**: `atoi("abc")` retorna `0`, exatamente igual a `atoi("0")`. Você não consegue distinguir "o usuário digitou zero" de "o usuário digitou lixo". Por isso o parser do push_swap precisa de uma conversão **própria**, que:
1. rejeita explicitamente qualquer caractere que não seja dígito (exceto um sinal opcional no início),
2. acumula o valor em um tipo maior que `int` (como `long`) enquanto lê os dígitos,
3. compara contra `INT_MAX`/`INT_MIN` **antes** de fazer o cast final para `int` — nunca depois (se você deixar estourar um `int` primeiro, o comportamento já é indefinido).

### Exemplo isolado (conceito, não a solução do projeto)

Este exemplo ilustra *a ideia* de detectar overflow acumulando em `long` — não é a função completa do seu parser, que também precisa lidar com sinal, string vazia, etc.

```c
#include <limits.h>

int cabe_em_int(long valor)
{
	return (valor >= INT_MIN && valor <= INT_MAX);
}
```

A lição aqui: **sempre valide em um tipo com faixa maior antes de reduzir para o tipo final.**

### Exemplos válidos vs. inválidos

```
Válidos:              Inválidos:
"42"                   "42a"
"-17"                  "- 17"      (espaço separa "-" e "17" em dois
                                     tokens; "-" sozinho é inválido)
"0"                    "007"       (aceitável ou não? decida e documente
                                     sua regra — a spec não exige rejeitar
                                     zeros à esquerda, mas seja consistente)
"2147483647"           "2147483648" (estoura INT_MAX)
"1 2 3" (um só argv)   "1  " (token vazio ao final, tratado como erro)
```

### Duplicados — quando checar

Duplicados só fazem sentido depois que você já validou que o argumento é um inteiro válido — não dá para comparar `"3"` com `"03"` como texto (são iguais como número, diferentes como string). Ou seja: primeiro converta e valide todos, **depois** compare os valores inteiros entre si.

### Resumo do capítulo

Parsing robusto é sobre **rejeitar cedo e claramente**: qualquer ambiguidade (overflow, formato, duplicata) deve ser pega antes de qualquer operação ser gerada, e o erro deve ser sinalizado de forma inequívoca — nunca silenciosamente virar `0` como o `atoi` faz.

### Perguntas de revisão

1. Por que comparar contra `INT_MAX`/`INT_MIN` precisa acontecer *antes* de fazer o cast para `int`?
2. Por que `atoi` é perigoso para este projeto especificamente?
3. Em que ordem você deve validar formato e detectar duplicados? Por quê?

### Exercícios

1. Liste 5 strings de entrada (diferentes das listadas aqui) que você acha que testariam bem os limites do seu parser.
2. Sem código, escreva em português o algoritmo passo a passo para validar um único argumento (`char *`), incluindo onde ele pode "falhar cedo" (early return).

---

## Capítulo 9 — Algoritmos

### Casos pequenos primeiro

**2 números:** só existem duas possibilidades — já ordenado, ou trocado. Se trocado, um único `sa` resolve.

**3 números:** existem `3! = 6` permutações possíveis. Você pode mapear cada uma delas a uma sequência curta e fixa de operações (o pior caso de 3 elementos nunca precisa de mais de 2-3 operações). A ideia central: com poucos elementos, vale a pena **enumerar os casos** em vez de rodar um algoritmo genérico.

**4 números:** uma estratégia comum é tirar o menor elemento para `b` (usando a rotação mais barata) e resolver os 3 que sobraram em `a` com a lógica de 3 números, depois devolver o elemento de `b`.

**5 números:** mesma ideia — tire os dois menores para `b` (na ordem certa), resolva os 3 restantes, depois devolva.

Esse padrão ("tire o(s) menor(es) para `b`, resolva um caso menor conhecido, devolva") é uma técnica geral de redução: transformar um problema em uma instância menor de um problema que você já sabe resolver.

### Algoritmos para casos maiores

#### Radix Sort (adaptado)

**Ideia:** em vez de comparar valores diretamente, olhe para a representação em **bits** do rank de cada número (rank = posição que ele ocuparia numa lista ordenada, de 0 a n-1). Para cada bit, da posição menos significativa até a mais significativa, separe os elementos entre os que têm aquele bit 0 (vão para `b`) e os que têm bit 1 (ficam em `a`, "dando a volta" via rotação); depois devolva.

- **Vantagens:** custo previsível e independente da entrada (mesmo número de operações para o pior e o melhor caso, aproximadamente); fácil de justificar formalmente a complexidade.
- **Desvantagens:** conceitualmente menos intuitivo de explicar do que "achar o menor e mover".
- **Complexidade:** cerca de `O(n log n)` operações (uma passada por bit, `log₂(n)` bits).
- **Quando usar:** entradas grandes e/ou muito desordenadas, onde você quer uma garantia robusta de desempenho.

#### "Turk Algorithm" (variação popular usada por alunos da 42)

É essencialmente o mesmo princípio do radix sort acima, mas descrito de forma mais operacional: em vez de pensar em "bits", pensa-se em "quantos passes preciso dar até que todo elemento tenha sido movido para `b` na ordem certa, usando a menor quantidade de rotações por passe". Muita gente usa "Turk algorithm" como sinônimo de "radix sort aplicado ao push_swap" — a ideia de fundo é a mesma.

#### Chunk Sort (ordenação por blocos)

**Ideia:** divida o intervalo de valores em `k` faixas (por exemplo, `k ≈ √n`). Mova os elementos da primeira faixa (menores valores) para `b`, depois da segunda faixa, e assim por diante; ao final, devolva tudo para `a` na ordem certa.

- **Vantagens:** conceitualmente simples ("divida para conquistar" por faixa de valor).
- **Desvantagens:** a escolha de `k` (quantidade de blocos) afeta bastante o resultado, e garantir uma prova rigorosa de complexidade de pior caso é mais delicado do que parece à primeira vista.
- **Complexidade:** tipicamente perto de `O(n·√n)` operações, se bem calibrado.
- **Quando usar:** quando você quer uma estratégia intermediária entre a simplicidade do "achar o menor" e a rigidez do radix sort.

#### LIS — Longest Increasing Subsequence (maior subsequência crescente)

**Ideia:** ache a maior sequência de elementos que **já estão** na ordem relativa correta (não precisam ser contíguos). Esses elementos não precisam ser movidos entre si — só os que **não** fazem parte dessa subsequência precisam ser reposicionados.

- **Vantagens:** em entradas que já estão "quase ordenadas", identifica o mínimo de trabalho necessário — muito eficiente nesses casos.
- **Desvantagens:** achar a LIS tem seu próprio custo (algoritmo clássico O(n log n) em tempo de C) e a lógica de "mover só quem não está na subsequência" é mais complexa de implementar corretamente do que os métodos acima.
- **Complexidade:** depende de quão desordenada a entrada é — no melhor caso (quase ordenado), muito poucas operações; no pior caso, se aproxima de outras estratégias.
- **Quando usar:** como parte de uma estratégia adaptativa, quando você já mede o quão desordenada a entrada está e quer aproveitar entradas "fáceis".

### Tabela-resumo comparativa

| Algoritmo | Ideia central | Melhor cenário | Complexidade típica (operações) |
|---|---|---|---|
| Casos pequenos (2-5) | enumeração/redução | sempre (entradas pequenas) | constante |
| Radix / Turk | ordenar por bits do rank | entradas grandes, qualquer desordem | O(n log n) |
| Chunk sort | dividir por faixa de valor | entradas grandes, meio-termo | O(n·√n) |
| LIS | preservar o que já está ordenado | entradas quase ordenadas | varia (ótimo em bons casos) |

### O que este projeto realmente implementa

*[Nota adicionada após a implementação]* Das opções discutidas acima, o projeto implementa três, mais um "caso pequeno" dedicado — **LIS não foi implementado** (ficou como alternativa conhecida, não usada):

| Arquivo | Estratégia da tabela acima | Ideia real implementada |
|---|---|---|
| `sort_small.c` | técnica de redução (2-5 elementos) | `sort_2`/`sort_3` por comparação direta; 4 e 5 tiram o(s) menor(es) para `b`, resolvem 3, devolvem |
| `sort_selection.c` | "ingênuo" (achar o menor, mover, repetir) | é literalmente essa estratégia — usada quando `--simple` é pedido (para `n` até 100) |
| `sort_chunks.c` + `sort_chunks_utils.c` | Chunk sort | em vez de dividir por **faixa de valor**, divide pelo **rank** (posição que cada elemento ocuparia já ordenado) em `⌈√n⌉` grupos de tamanho igual — isso evita grupos desbalanceados que uma divisão por valor bruto poderia gerar em entradas com distribuição irregular |
| `sort_radix.c` | Radix / Turk | radix sort clássico sobre o rank, bit a bit, do menos para o mais significativo |
| `sort_adaptive.c` | — | dispatcher: mede `disorder` e escolhe entre as três acima pelos limiares 0.2 / 0.5 |

Repare que tanto `sort_chunks.c` quanto `sort_radix.c` dependem de um **rank pré-calculado** (campo `rank` dentro de `t_stack`, preenchido por `assign_ranks()`) em vez de comparar valores brutos — isso simplifica as contas de "em qual grupo/bit esse elemento cai" para um número pequeno (`0` a `n-1`), independente da faixa real dos valores de entrada (que pode incluir negativos, números bem espaçados, etc.).

### Resumo do capítulo

Não existe "o" algoritmo do push_swap — existe um leque de estratégias, cada uma melhor em um cenário. Alunos experientes costumam combinar mais de uma (ex.: casos pequenos com lógica dedicada, e um algoritmo tipo radix para o resto).

### Perguntas de revisão

1. Por que faz sentido tratar 2, 3, 4 e 5 elementos como "casos especiais" em vez de rodar um algoritmo genérico neles?
2. Qual é a diferença conceitual entre "chunk sort" e "radix sort" na forma como cada um decide o que mover para `b` primeiro?
3. Em que cenário o LIS se destaca em relação aos outros algoritmos?

### Exercícios

1. Sem implementar, escreva (em português) o passo a passo que você usaria para ordenar 4 números com a técnica de redução ("tire o menor, resolva 3, devolva").
2. Pesquise o que é "rank" de um elemento numa lista e explique, com suas palavras, por que ele é útil para o radix sort aplicado ao push_swap.

---

## Capítulo 10 — Estratégia de implementação

Divida o projeto em etapas pequenas, cada uma **testável isoladamente** antes de avançar.

**Etapa 1 — Estrutura das pilhas**
Defina a struct do nó e as funções básicas de lista (criar nó, adicionar, contar tamanho, imprimir para debug). Teste criando uma lista manualmente e imprimindo.

**Etapa 2 — Parser**
Implemente a validação de argumentos (Capítulo 8) sem se preocupar ainda com pilhas — só validar e converter strings, testando com casos válidos e inválidos.

**Etapa 3 — Ligação parser + pilha**
Junte as etapas 1 e 2: popular a pilha `a` a partir de `argv` validado.

**Etapa 4 — Operações**
Implemente as 11 operações (Capítulo 3), uma por vez, testando cada uma isoladamente (crie uma pilha pequena manualmente, aplique a operação, confira o resultado).

**Etapa 5 — Testes de operação**
Antes de seguir, monte um pequeno script (fora do binário) que aplica operações manualmente e confere se o estado bate com o esperado.

**Etapa 6 — Casos pequenos (2 e 3 números)**
Implemente a lógica para 2 e depois 3 números. É o primeiro "algoritmo de ordenação" completo do projeto — mantenha pequeno e testável.

**Etapa 7 — Casos pequenos (4 e 5 números)**
Estenda usando a técnica de redução (Capítulo 9).

**Etapa 8 — Checagem "já ordenado"**
Implemente a função que verifica se a pilha já está ordenada, para não gastar operações à toa.

**Etapa 9 — Algoritmo genérico (casos grandes)**
Escolha uma estratégia (Capítulo 9) e implemente para `n` arbitrário. Comece testando com poucos elementos (10, 20) antes de ir para 100 e 500.

**Etapa 10 — Contagem de operações e ajuste**
Rode com 100 e 500 números aleatórios repetidamente, meça quantas operações saem, e ajuste a estratégia se estiver muito acima do esperado.

**Etapa 11 — Liberação de memória e tratamento de erro**
Revise todos os caminhos (sucesso e erro) garantindo que tudo que foi `malloc`ado é `free`ado.

**Etapa 12 — Testes finais e Norma**
Rode a bateria de testes do Capítulo 13, rode a Norminette, e só então considere o mandatório pronto.

### Resumo do capítulo

Trabalhar em etapas pequenas e testáveis evita a armadilha mais comum do projeto: tentar escrever o algoritmo genérico direto, sem uma base sólida de operações testadas — o que torna qualquer bug muito mais difícil de localizar.

### Perguntas de revisão

1. Por que testar as 11 operações isoladamente antes de implementar qualquer algoritmo de ordenação?
2. Em que etapa faz sentido medir a contagem de operações pela primeira vez?
3. Por que deixar "liberação de memória" como uma etapa revisada no fim, e não só confiar que "cada malloc já tem seu free do lado"?

### Exercícios

1. Escreva seu próprio roteiro de etapas (pode ser igual ou diferente do sugerido), com uma frase de "critério de pronto" para cada uma.
2. Para a Etapa 4 (operações), escreva 3 casos de teste manuais (estado antes/depois) para `ra` e para `rra`.

---

## Capítulo 11 — Função por função

Esta é a lista de funções que **costumam** existir em implementações de push_swap — não é a lista definitiva do seu projeto, é um guia do que esperar.

### `init_stack()`
- **Responsabilidade:** inicializar o estado vazio de uma pilha (ponteiro para `NULL`, ou uma struct de contexto zerada).
- **Parâmetros:** normalmente nenhum, ou um ponteiro para a struct de contexto.
- **Retorno:** void, ou a estrutura inicializada.
- **Quem chama:** `main`, no começo.
- **Quem ela chama:** nada, ou `malloc` se já alocar algo inicial.
- **Pré-condição:** nenhuma.
- **Pós-condição:** pilha em estado consistente e vazio.

### `create_node()`
- **Responsabilidade:** alocar um novo nó com um valor.
- **Parâmetros:** o valor inteiro.
- **Retorno:** ponteiro para o nó criado (ou `NULL`/exit em falha de alocação).
- **Quem chama:** o parser, ao popular a pilha inicial.
- **Quem ela chama:** `malloc`.
- **Pré-condição:** valor já validado.
- **Pós-condição:** nó alocado, pronto para ser inserido na lista.

### `push()`
- **Responsabilidade:** implementar a lógica genérica de `pa`/`pb` (mover o topo de uma lista para o topo de outra).
- **Parâmetros:** ponteiro duplo para a lista de origem, ponteiro duplo para a de destino.
- **Retorno:** void.
- **Quem chama:** as funções específicas `op_pa`/`op_pb` (que além disso imprimem o nome da operação).
- **Quem ela chama:** nada além de manipulação de ponteiros.
- **Pré-condição:** nenhuma (deve lidar com origem vazia sem quebrar).
- **Pós-condição:** origem perde o topo (se tinha), destino ganha esse nó no topo.

### `rotate()` / `reverse_rotate()`
- **Responsabilidade:** implementar a lógica genérica de `ra`/`rra` (e suas variantes em `b`).
- **Parâmetros:** ponteiro duplo para a pilha.
- **Retorno:** void.
- **Quem chama:** as funções específicas de operação.
- **Quem ela chama:** nada além de manipulação de ponteiros.
- **Pré-condição:** nenhuma (deve lidar com 0 ou 1 elemento sem efeito).
- **Pós-condição:** o topo virou o fundo (ou vice-versa).

### `swap()`
- **Responsabilidade:** lógica genérica de `sa`/`sb`.
- **Parâmetros:** ponteiro duplo para a pilha.
- **Retorno:** void.
- **Pré-condição:** nenhuma (nenhum efeito se tiver menos de 2 elementos).
- **Pós-condição:** os dois primeiros nós trocaram de posição.

### `sort_three()` / `sort_five()`
- **Responsabilidade:** a lógica dedicada para os casos pequenos (Capítulo 9).
- **Parâmetros:** contexto com as duas pilhas.
- **Retorno:** void (efeito colateral: pilha `a` ordenada, operações impressas).
- **Quem chama:** a função de decisão de estratégia.
- **Quem ela chama:** as operações (`op_sa`, `op_ra`, etc.).
- **Pré-condição:** tamanho exato esperado (3 ou 5).
- **Pós-condição:** `a` ordenada, `b` vazia.

### `radix_sort()` (ou nome equivalente à estratégia escolhida)
- **Responsabilidade:** orquestrar o algoritmo genérico para `n` grande.
- **Parâmetros:** contexto com as duas pilhas.
- **Retorno:** void.
- **Quem chama:** a função de decisão de estratégia.
- **Quem ela chama:** operações, e possivelmente uma função auxiliar de cálculo de rank/bit.
- **Pré-condição:** `a` populada, `b` vazia.
- **Pós-condição:** `a` ordenada, `b` vazia.

### `parse_args()`
- **Responsabilidade:** ler `argv`, validar e popular a pilha `a`.
- **Parâmetros:** `argc`, `argv`, ponteiro para o contexto/pilha.
- **Retorno:** código de sucesso/erro.
- **Quem chama:** `main`.
- **Quem ela chama:** funções de validação, `create_node`.
- **Pré-condição:** `argc >= 2`.
- **Pós-condição:** pilha `a` populada (em caso de sucesso) ou erro sinalizado sem vazamento.

### `check_duplicates()`
- **Responsabilidade:** verificar se um valor já existe na pilha antes de inserir.
- **Parâmetros:** a pilha atual, o valor a checar.
- **Retorno:** booleano (existe ou não).
- **Quem chama:** `parse_args`.
- **Quem ela chama:** nada (percorre a lista comparando valores).
- **Pré-condição:** pilha em estado consistente.
- **Pós-condição:** nenhuma mudança de estado (é só consulta).

### `free_stack()`
- **Responsabilidade:** liberar todos os nós de uma pilha.
- **Parâmetros:** ponteiro duplo para a pilha.
- **Retorno:** void.
- **Quem chama:** `main`, no final (sucesso ou erro).
- **Quem ela chama:** `free`.
- **Pré-condição:** nenhuma (deve lidar com pilha já vazia).
- **Pós-condição:** ponteiro da pilha aponta para `NULL`, toda memória devolvida.

### Correspondência com os nomes reais do nosso código

*[Nota adicionada após a implementação]* Os nomes acima são genéricos, para ensinar o conceito. No nosso projeto, alguns ganharam nomes diferentes (mais alinhados ao vocabulário da spec) ou foram fundidos em uma função só. Tabela de correspondência:

| Nome genérico (neste capítulo) | Nome real no projeto | Onde |
|---|---|---|
| `init_stack()` | inline dentro de `parse_args()` (zera `data->a`, `data->b`, etc.) | `parse.c` |
| `create_node()` | `stack_new()` | `stack.c` |
| `push()` | `generic_push()` | `stack_utils.c` |
| `rotate()` / `reverse_rotate()` | `generic_rotate()` / `generic_reverse_rotate()` | `stack_utils.c` |
| `swap()` | `generic_swap()` | `stack_utils.c` |
| `sort_three()` / `sort_five()` | uma função só, `sort_small()`, que cobre `n` de 2 a 5 (usa as estáticas `sort_2`, `sort_3`, `find_min_pos`, `push_min_to_b` internamente) | `sort_small.c` |
| `radix_sort()` | `sort_radix()` (chama `assign_ranks()` e depois `radix_pass()` por bit) | `sort_radix.c` |
| `parse_args()` | `parse_args()` (nome igual) | `parse.c` |
| `check_duplicates()` | não existe separada — a checagem está embutida em `add_number()`, que já percorre a lista para inserir | `parse.c` |
| `free_stack()` | `stack_free()` | `stack.c` |

Um detalhe extra que não estava na lista genérica: o parser real também tem `process_arg()` e `read_next_token()` (`parse.c`/`parse_utils.c`), responsáveis por quebrar um único `argv` em vários números separados por espaço antes de validar cada um — conceito que não existia quando este capítulo foi escrito originalmente (ver Capítulo 8).

### Resumo do capítulo

Cada função deve ter uma responsabilidade única e clara — perceba como as funções "genéricas" (`push`, `rotate`, `swap`) são reaproveitadas tanto para `a` quanto para `b`, e como as funções "de operação" (`op_pa`, `op_ra`...) são finas camadas em cima delas, responsáveis só por imprimir o nome.

### Perguntas de revisão

1. Por que `push()` genérica recebe dois ponteiros duplos (origem e destino) em vez de ser escrita separadamente para cada direção?
2. O que `check_duplicates()` faz que `create_node()` não deveria fazer?
3. Por que `free_stack()` precisa lidar corretamente com uma pilha já vazia?

### Exercícios

1. Escreva a assinatura (só o protótipo, sem corpo) de cada função desta lista, decidindo você mesmo os tipos de parâmetro.
2. Para `rotate()`/`reverse_rotate()`, escreva em português (não código) a pré-condição e pós-condição para o caso de pilha com exatamente 1 elemento.

---

## Capítulo 12 — Complexidade

Lembre-se da distinção do Capítulo 1: aqui falamos de complexidade **em número de operações emitidas** (o que importa para a nota), não tempo de CPU do seu C.

### Tabela geral

| Estratégia | Complexidade (operações) | Quando é usada |
|---|---|---|
| Caso 2 elementos | O(1) | sempre que n=2 |
| Caso 3 elementos | O(1) (no máximo poucas operações fixas) | sempre que n=3 |
| Casos 4-5 (redução) | O(1) + custo do caso menor | n=4 ou n=5 |
| Ingênuo (achar o menor, mover, repetir) | O(n²) | didático, não recomendado para n grande |
| Chunk sort | O(n·√n) | tamanhos médios |
| Radix / Turk | O(n log n) | tamanhos grandes, qualquer desordem |
| LIS-based (adaptativo) | varia, ótimo se quase ordenado | entradas já parcialmente ordenadas |

### Por que o "ingênuo" é O(n²)

A estratégia "ache o menor elemento, traga ao topo, empurre para `b`, repita" custa, por elemento, até `n/2` rotações no pior caso (a distância média até o topo). Fazendo isso `n` vezes: `n × (n/2) ≈ O(n²)`. Para `n=500`, isso facilmente passa de 100 mil operações — muito acima do que a maioria das specs aceita.

### Por que radix é O(n log n)

Cada "passada" (uma por bit do rank) processa todos os `n` elementos uma vez: custo `O(n)` por passada. O número de bits necessários para representar ranks de `0` a `n-1` é `⌈log₂ n⌉`. Total: `O(n) × O(log n) = O(n log n)`.

### Como isso aparece no nosso código

*[Nota adicionada após a implementação]* A estratégia "ingênuo" da tabela não é só um exemplo didático aqui — é exatamente o que `sort_selection.c` implementa, e ela roda de verdade quando `--simple` é escolhido (para `n` até 100; acima disso o `main.c` troca por `sort_radix` para não gerar uma quantidade absurda de operações — vale conferir esse detalhe com atenção na arguição, já que a spec pede que cada flag force sua própria classe de complexidade "independente do tamanho da entrada"). Já `sort_chunks.c` mede o custo em cima do **rank** pré-calculado, não do valor bruto — isso ajuda a manter os `⌈√n⌉` grupos com tamanhos parecidos entre si, o que é a premissa por trás da conta `O(n·√n)`.

### Resumo do capítulo

A tabela acima é o seu "mapa mental" para justificar, na arguição, por que sua estratégia escolhida tem a complexidade que você alega — pratique explicar o "por quê" de cada linha, não só decorar o resultado.

### Perguntas de revisão

1. Por que a estratégia "ache o menor" degrada para O(n²) conforme `n` cresce?
2. De onde vem o fator `log n` na complexidade do radix sort aplicado aqui?
3. Por que "complexidade de operações" e "tempo de execução do programa em C" podem divergir completamente para o mesmo algoritmo?

### Exercícios

1. Calcule (à mão) uma estimativa de operações para a estratégia ingênua com `n=100`. Compare com o que a tabela de radix sugere.
2. Explique, com suas palavras, por que seria enganoso dizer "meu programa roda em menos de 1 segundo, então minha complexidade está boa" nesse projeto.

---

## Capítulo 13 — Testes

### Checklist — Parsing

- [ ] Entrada vazia (`argc == 1`) → não imprime nada, sai com sucesso.
- [ ] Um único argumento válido (`./push_swap 5`) → já ordenado, não imprime nada.
- [ ] Argumento não-numérico (`"abc"`) → `Error`.
- [ ] Argumento com sinal isolado (`"-"`, `"+"`) → `Error`.
- [ ] Overflow (`"2147483648"`) → `Error`.
- [ ] Underflow (`"-2147483649"`) → `Error`.
- [ ] Valor exatamente `INT_MAX` e `INT_MIN` → aceitos normalmente.
- [ ] Duplicados (`"3 3"`) → `Error`.
- [ ] Números passados como um único argumento com espaços (`"3 2 1"` entre aspas) — decida e teste seu comportamento.

### Checklist — Operações

- [ ] Cada uma das 11 operações testada isoladamente em pilha vazia (não deve travar).
- [ ] Cada uma testada em pilha com 1 elemento (não deve ter efeito, exceto onde já esperado).
- [ ] Cada uma testada em pilha com 2+ elementos, conferindo estado antes/depois manualmente.
- [ ] Operações combinadas (`ss`, `rr`, `rrr`) conferidas contra a combinação manual das simples.

### Checklist — Casos pequenos

- [ ] Todas as 2 permutações de 2 elementos.
- [ ] Todas as 6 permutações de 3 elementos.
- [ ] Amostra ampla de permutações de 4 e 5 elementos (testar todas as 120 de 5 é viável com um script).

### Checklist — Casos grandes

- [ ] 100 números aleatórios — conferir corretude e contar operações.
- [ ] 500 números aleatórios — idem.
- [ ] Repetir os testes de 100 e 500 várias vezes com seeds diferentes (o pior caso pode não aparecer na primeira tentativa).

### Checklist — Casos especiais de entrada

- [ ] Lista já ordenada ascendente.
- [ ] Lista ordenada descendente (pior caso de desordem).
- [ ] Lista quase ordenada (poucos elementos fora do lugar).
- [ ] Apenas 1 número.
- [ ] Números negativos misturados com positivos.

### Como validar corretude automaticamente

Escreva um script (fora do projeto C, em shell ou Python) que:
1. gera uma lista aleatória,
2. roda seu `push_swap` com essa lista, capturando a saída de operações,
3. **simula** cada operação sobre a lista original (sem chamar seu binário de novo),
4. confere se o resultado final está ordenado.

Isso é exatamente o papel do `checker` (bônus), mas você pode (e deve) ter uma versão de teste própria, mesmo sem fazer o bônus.

### Resumo do capítulo

Testar push_swap não é só "rodar e ver se não trava" — é conferir corretude (ordenou mesmo?) e desempenho (quantas operações?) em várias categorias de entrada, incluindo casos que "quase nunca acontecem" mas que um avaliador vai testar de propósito.

### Perguntas de revisão

1. Por que testar a mesma quantidade de elementos (100, 500) várias vezes com entradas diferentes, em vez de uma vez só?
2. Por que "lista ordenada descendente" é interessante de testar especificamente?
3. Qual é a diferença entre testar corretude e testar desempenho (contagem de operações)?

### Exercícios

1. Escreva (em pseudocódigo, não precisa ser o script final) os passos de um script de teste automático como descrito acima.
2. Liste 3 categorias de teste que você acha que a maioria dos alunos esquece de testar.

---

## Capítulo 14 — Debug

### Ferramentas e o que cada uma revela

**`printf` (ou uma macro de debug)**
Uso mais simples: imprimir o estado da pilha em pontos-chave (ex.: antes e depois de cada operação) para uma entrada pequena, e comparar manualmente com o que você esperava.

**`gdb`**
Depurador interativo — permite pausar a execução (breakpoints), inspecionar variáveis, e navegar pela pilha de chamadas no momento de um crash. Essencial para descobrir **onde exatamente** um segmentation fault acontece (o `backtrace` do gdb mostra a cadeia de funções até o ponto do crash).

**`valgrind` (Linux)**
Detecta vazamentos de memória (blocos alocados e nunca liberados) e acessos inválidos (ler/escrever memória que não deveria). Rode com `--leak-check=full` para relatório detalhado de cada vazamento, incluindo onde a memória foi alocada.

**`leaks` (macOS)**
Equivalente ao valgrind para macOS — detecta vazamentos de memória em um processo.

### Como identificar cada tipo de problema

**Segmentation fault**
Geralmente é acesso a um ponteiro inválido — `NULL` não checado, ou um ponteiro "solto" (apontando para memória já liberada). O `gdb` com `backtrace` mostra exatamente a linha.

**Double free**
Acontece quando `free` é chamado duas vezes no mesmo endereço. Sintoma clássico: crash ao liberar memória, às vezes com uma mensagem específica do alocador. Valgrind aponta isso diretamente ("Invalid free()").

**Invalid read / invalid write**
Ler ou escrever em um endereço fora dos limites de um bloco alocado (ex.: acessar `nó->next->next` quando `nó->next` já era `NULL`). Valgrind sinaliza a linha exata.

**Memory leak**
Bloco alocado (`malloc`) do qual você perdeu toda referência sem dar `free`. No push_swap, os lugares mais comuns são: nós de pilha nunca liberados após um erro de parsing, ou um nó "extra" criado antes de detectar que o valor era duplicado.

### Estratégia geral de debug

1. Reduza o caso que falha ao **menor exemplo possível** (se falha com 500 números, tente achar uma entrada de 4-5 números que reproduza o mesmo bug).
2. Adicione impressões de estado (ou use `gdb`) nesse caso reduzido.
3. Compare o estado real com o que você esperava, operação por operação.
4. Rode valgrind/leaks **sempre**, mesmo quando "parece que está tudo certo" — vazamentos não travam o programa, então passam despercebidos sem a ferramenta.

### Resumo do capítulo

Debugar push_swap é, na maior parte das vezes, sobre encontrar o menor caso que reproduz o bug e usar as ferramentas certas (gdb para crashes, valgrind/leaks para memória) em vez de adivinhar olhando o código todo de uma vez.

### Perguntas de revisão

1. Por que reduzir o caso de falha ao menor exemplo possível acelera o debug?
2. Qual ferramenta você usaria para descobrir a linha exata de um segmentation fault?
3. Por que um vazamento de memória pode passar despercebido sem ferramentas como valgrind?

### Exercícios

1. Escreva um pequeno programa isolado (não relacionado ao push_swap) que aloca um nó e propositalmente esquece de liberá-lo; rode com valgrind e leia o relatório.
2. Descreva, em português, o que você esperaria ver no `backtrace` do gdb para um segmentation fault causado por acessar `->next` de um ponteiro `NULL`.

---

## Capítulo 15 — Erros comuns

### 1. Confundir complexidade de operações com complexidade de tempo de C
Como discutido no Capítulo 1/12 — alunos frequentemente acham que "meu código roda rápido" prova que a estratégia é boa. Evite: sempre meça em **operações emitidas**, não em tempo de relógio.

### 2. Esquecer de escolher a rotação mais barata
Usar sempre `ra` (nunca `rra`) mesmo quando o elemento está mais perto do fundo dobra o custo desnecessariamente. Evite: sempre compare as duas distâncias antes de decidir a direção (Capítulo 3).

### 3. Vazar memória em caminhos de erro
É comum liberar tudo certinho no caminho de sucesso, mas esquecer que um `return` de erro no meio do parsing também precisa liberar o que já foi alocado. Evite: trate a liberação de memória como parte do **contrato de erro**, não um detalhe do caminho feliz.

### 4. Não tratar pilha vazia ou de 1 elemento nas operações genéricas
Uma operação `rotate` que assume "sempre tem pelo menos 2 elementos" vai crashar em algum caso de borda que o avaliador vai testar de propósito. Evite: toda operação deve verificar explicitamente os casos de 0 e 1 elemento.

### 5. `atoi` para converter os argumentos
Como discutido no Capítulo 8, `atoi` não sinaliza erro. Evite: escreva sua própria conversão validada.

### 6. Duplicar lógica entre `a` e `b`
Escrever `rotate_a()` e `rotate_b()` como cópias quase idênticas, em vez de uma função genérica que recebe qual pilha manipular. Evite: parametrize por ponteiro duplo (Capítulo 4/11) e reaproveite.

### 7. Ignorar a Norma até o fim
Escrever o projeto inteiro e só rodar a Norminette na véspera da entrega. Muitas violações (função grande demais, muitas variáveis, arquivo com funções demais) exigem refatoração estrutural, não só ajuste cosmético — deixar para o fim é caro. Evite: rode a Norminette desde as primeiras funções.

### 8. Testar só com poucos números
Validar manualmente com 3-5 números e nunca rodar com 100/500 antes da entrega. Evite: automatize testes com entradas grandes desde cedo (Capítulo 13).

### 9. Não entender o próprio algoritmo o suficiente para explicá-lo
Copiar uma estratégia (de um vídeo, de um colega) sem entender por completo o "porquê" de cada parte. Isso aparece imediatamente na arguição, quando pedem para explicar ou modificar algo ao vivo.

### Resumo do capítulo

A maioria dos erros comuns não é "não saber escrever C" — é atalhos tomados sob pressão de tempo: pular casos de borda, adiar a Norma, não testar em escala, ou não internalizar de verdade a lógica do algoritmo escolhido.

### Perguntas de revisão

1. Por que "meu código roda rápido" não é evidência de uma boa estratégia de push_swap?
2. Dê um exemplo concreto de um caminho de erro onde memória pode vazar se você não prestar atenção.
3. Por que deixar a Norminette para o final costuma ser mais caro do que rodá-la desde o início?

### Exercícios

1. Revise (mentalmente ou no papel) seu plano de implementação e aponte em quais etapas você corre mais risco de cometer cada um destes erros.
2. Escolha um dos erros desta lista e escreva, com suas palavras, uma "regra pessoal" para não cometê-lo.

---

## Capítulo 16 — Roadmap de estudo

Um cronograma sugerido — ajuste ao seu ritmo, mas mantenha a ordem (cada dia depende do anterior).

**Dia 1 — Fundamentos**
Revisar ponteiros, ponteiro duplo, structs e listas encadeadas (Capítulo 4). Implementar, fora do contexto do push_swap, uma lista encadeada simples com inserção e impressão.

**Dia 2 — Modelo do problema**
Ler os Capítulos 1-3 com atenção. Sem código: escrever à mão a sequência de operações para ordenar 2-3 exemplos pequenos.

**Dia 3 — Estrutura e organização**
Definir a struct da pilha, decidir a estrutura de pastas (Capítulos 5-6), criar o esqueleto de arquivos e o Makefile.

**Dia 4 — Parser**
Implementar e testar exaustivamente a validação de argumentos (Capítulo 8), sem se preocupar ainda com pilhas.

**Dia 5 — Operações (parte 1)**
Implementar `sa`, `sb`, `ss`, `pa`, `pb`. Testar cada uma isoladamente.

**Dia 6 — Operações (parte 2)**
Implementar `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`. Testar cada uma isoladamente.

**Dia 7 — Casos pequenos**
Implementar e testar exaustivamente os casos de 2 e 3 números (todas as permutações).

**Dia 8 — Casos pequenos, continuação**
Implementar e testar 4 e 5 números via redução.

**Dia 9 — Estudo dos algoritmos grandes**
Sem codar ainda: estudar a fundo radix/Turk e chunk sort (Capítulo 9), fazendo exemplos no papel com 8-16 números.

**Dia 10 — Implementação do algoritmo genérico**
Implementar a estratégia escolhida para `n` arbitrário, testando incrementalmente (10, 20, 50 números).

**Dia 11 — Escala e medição**
Testar com 100 e 500 números repetidamente, medir operações, comparar com os limites esperados, ajustar se necessário.

**Dia 12 — Robustez**
Revisar toda a liberação de memória e tratamento de erros (Capítulo 15, itens 3-4). Rodar valgrind/leaks em todos os cenários.

**Dia 13 — Norma e polimento**
Rodar a Norminette em todo o projeto, corrigir violações, revisar nomes de funções/variáveis.

**Dia 14 — Simulação de defesa**
Explicar o projeto inteiro em voz alta (ou para um colega) sem olhar o código — se travar em algum ponto, esse é exatamente o ponto que precisa de mais revisão antes da arguição real.

### Resumo do capítulo

O roteiro segue a mesma lógica do Capítulo 10: da estrutura mais simples para a mais complexa, sempre testando antes de avançar, e reservando tempo explícito para robustez, norma e a capacidade de **explicar** o projeto — não só fazê-lo funcionar.

### Perguntas de revisão

1. Por que o roadmap deixa "algoritmo genérico para n grande" só depois de dominar os casos pequenos?
2. Por que existe um dia inteiro dedicado a "simular a defesa" antes da entrega?
3. Se você tivesse menos dias disponíveis, quais etapas você jamais cortaria, e por quê?

### Exercícios finais

1. Adapte este roadmap ao seu calendário real (quantos dias você tem até a entrega?) sem remover nenhuma etapa — só redistribua o tempo.
2. Ao final de cada "dia" do seu roadmap, escreva uma frase de "critério de pronto" (como fizemos no Capítulo 10) antes de seguir para o próximo.
