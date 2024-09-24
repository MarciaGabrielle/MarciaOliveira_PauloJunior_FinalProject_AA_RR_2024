# Algoritmo de Parentização - Projeto Final de Análise de Algoritmos

Este repositório contém o código do projeto final da disciplina de **Análise de Algoritmos** com o tema **Algoritmo de Parentização**. O objetivo do projeto é resolver o problema de **Tomada de decisão** utilizando técnicas de otimização baseadas em programação dinâmica.

## Estrutura do Repositório

- **/codes**: Contém os códigos-fonte implementados em C e python para a solução do problema proposto utilizando o Algoritmo de Parentização.
- **/docs**: Contém o relatório referente ao projeto.
- **/slides**: Contém os slides referente ao projeto.

## Algoritmo de Parentização

O algoritmo de parentização resolve o problema da melhor forma de multiplicar uma sequência de matrizes, minimizando o número total de multiplicações escalares. Este é um problema clássico em otimização, frequentemente utilizado para demonstrar a eficiência de algoritmos de programação dinâmica.

## Como Rodar o Projeto

### Pré-requisitos

- Um compilador C (ex: GCC).
- Um terminal para compilar e rodar o código.
- Sistema operacional compatível (Linux, MacOS, ou Windows com WSL).

### Passo a Passo para Compilar e Rodar

1. **Clone o repositório:**
   ```bash
   git clone https://github.com/MarciaGabrielle/MarciaOliveira_PauloJunior_FinalProject_AA_RR_2024.git

2. **Compile o código em C:**
   ```bash
   gcc -o parentizacao parentizacao.c

3. **Execute o programa em C para gerar um CSV com os tempos de execução:**
    ```bash
    ./parentizacao

4. **Após gerar o CSV execute o codigo em Python para gerar a tabela e analisar os tempos de execução:**
    ```bash
    python bench.py
