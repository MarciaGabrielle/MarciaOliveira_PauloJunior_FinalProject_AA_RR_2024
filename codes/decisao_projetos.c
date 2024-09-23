#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definindo os pesos dos critérios
#define PESO_ROI 0.35
#define PESO_ORCAMENTO 0.30
#define PESO_RISCOS 0.15
#define PESO_ALINHAMENTO 0.20

// Estrutura para representar um projeto
typedef struct Projeto {
    char nome[50];
    int roi;        // 1 para sim, 0 para não
    int orcamento;  // 1 para sim, 0 para não
    int riscos;     // 1 para sim, 0 para não
    int alinhamento;// 1 para sim, 0 para não
    double score;   // Pontuação calculada com base nos pesos
} Projeto;

// Memoização: tabela para armazenar os resultados parciais
double memo[4][2];  // [critério][sim/não] => [0 para não, 1 para sim]

// Função para gerar valores aleatórios 0 ou 1 para os critérios
void randomizarProjeto(Projeto* p, char* nome) {
    p->roi = rand() % 2;          // Gera 0 ou 1
    p->orcamento = rand() % 2;    // Gera 0 ou 1
    p->riscos = rand() % 2;       // Gera 0 ou 1
    p->alinhamento = rand() % 2;  // Gera 0 ou 1
    snprintf(p->nome, 50, "%s", nome); // Define o nome do projeto
}

// Função para calcular e armazenar os resultados dos critérios usando memoização
double calcularCriterio(int criterio, int resposta) {
    // Verifica se o valor já foi calculado (memoização)
    if (memo[criterio][resposta] != -1) {
        return memo[criterio][resposta];  // Retorna o valor já calculado
    }

    // Caso contrário, calcula o valor e armazena
    switch (criterio) {
        case 0: // ROI
            memo[criterio][resposta] = resposta == 1 ? PESO_ROI : 0;
            break;
        case 1: // Orcamento
            memo[criterio][resposta] = resposta == 1 ? PESO_ORCAMENTO : 0;
            break;
        case 2: // Riscos
            memo[criterio][resposta] = resposta == 1 ? PESO_RISCOS : 0;
            break;
        case 3: // Alinhamento
            memo[criterio][resposta] = resposta == 1 ? PESO_ALINHAMENTO : 0;
            break;
    }
    return memo[criterio][resposta];
}

// Função para aplicar a "parentização" (ordem de critérios) e calcular a pontuação
double parentizarDecisao(Projeto p, int criterios[], char caminho[]) {
    double score = 0.0;
    
    // Percorre os critérios na ordem especificada
    for (int i = 0; i < 4; i++) {
        int criterio = criterios[i];
        int resposta = 0;
        double pontuacao = 0;

        // Verifica o critério atual e avalia o "Sim" ou "Não"
        switch (criterio) {
            case 0: resposta = p.roi; caminho[i] = resposta ? 'S' : 'N'; break;
            case 1: resposta = p.orcamento; caminho[i] = resposta ? 'S' : 'N'; break;
            case 2: resposta = p.riscos; caminho[i] = resposta ? 'S' : 'N'; break;
            case 3: resposta = p.alinhamento; caminho[i] = resposta ? 'S' : 'N'; break;
        }

        // Calcula a pontuação para o critério atual
        pontuacao = calcularCriterio(criterio, resposta);
        score += pontuacao;
    }

    caminho[4] = '\0';  // Adiciona o terminador de string ao caminho
    return score;
}

// Função para testar diferentes "ordens de parentização" (critérios)
double testarParentizacao(Projeto p) {
    char caminho[5];  // String para armazenar o caminho (Sim ou Não) percorrido

    // Define diferentes ordens de avaliação (simulando diferentes parentizações)
    int criterios1[] = {0, 1, 2, 3};  // Ordem: ROI, Orçamento, Riscos, Alinhamento
    int criterios2[] = {1, 0, 3, 2};  // Ordem: Orçamento, ROI, Alinhamento, Riscos
    int criterios3[] = {2, 1, 0, 3};  // Ordem: Riscos, Orçamento, ROI, Alinhamento

    // Testa todas as ordens e calcula os scores
    printf("Testando diferentes parentizações para %s:\n", p.nome);
    
    double score1 = parentizarDecisao(p, criterios1, caminho);
    printf("Caminho (ROI-Orçamento-Riscos-Alinhamento): %s => Score = %.2f\n", caminho, score1);

    double score2 = parentizarDecisao(p, criterios2, caminho);
    printf("Caminho (Orçamento-ROI-Alinhamento-Riscos): %s => Score = %.2f\n", caminho, score2);

    double score3 = parentizarDecisao(p, criterios3, caminho);
    printf("Caminho (Riscos-Orçamento-ROI-Alinhamento): %s => Score = %.2f\n", caminho, score3);

    // Retorna o maior score entre as diferentes ordens
    double maior_score = score1;
    if (score2 > maior_score) maior_score = score2;
    if (score3 > maior_score) maior_score = score3;

    return maior_score;
}

// Função para avaliar os projetos e selecionar o melhor
void avaliarProjetos(Projeto projetos[], int numProjetos) {
    Projeto *melhorProjeto = &projetos[0];  // Inicializa com o primeiro projeto

    // Testa cada projeto e encontra o melhor
    for (int i = 0; i < numProjetos; i++) {
        projetos[i].score = testarParentizacao(projetos[i]);  // Testa diferentes parentizações
        
        // Verifica se o projeto atual tem um score melhor
        if (projetos[i].score > melhorProjeto->score) {
            melhorProjeto = &projetos[i];
        }
    }

    // Exibe os resultados e o melhor projeto
    for (int i = 0; i < numProjetos; i++) {
        printf("\n%s: Score final = %.2f\n", projetos[i].nome, projetos[i].score);
    }
    printf("\nO melhor projeto é: %s com um score de %.2f\n", melhorProjeto->nome, melhorProjeto->score);
}

int main() {
    // Inicializando o gerador de números aleatórios
    srand(time(0));

    // Inicializa a tabela de memoização com valores "não calculados" (-1)
    for (int i = 0; i < 4; i++) {
        memo[i][0] = -1;
        memo[i][1] = -1;
    }

    // Definindo três projetos com respostas aleatórias para os critérios
    Projeto projetos[3];
    randomizarProjeto(&projetos[0], "Projeto A");
    randomizarProjeto(&projetos[1], "Projeto B");
    randomizarProjeto(&projetos[2], "Projeto C");
    
    // Avaliando os projetos e selecionando o melhor
    avaliarProjetos(projetos, 3);
    
    return 0;
}
