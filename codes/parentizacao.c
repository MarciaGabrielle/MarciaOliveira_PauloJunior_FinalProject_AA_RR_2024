#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

double memo[4][2];  // Tabela de memoização para armazenar resultados

// Função para calcular e armazenar os resultados dos critérios usando memoização
double calcularCriterio(int criterio, int resposta) {
    if (memo[criterio][resposta] != -1) {
        return memo[criterio][resposta];  // Retorna o valor já calculado
    }

    switch (criterio) {
        case 0: // ROI
            memo[criterio][resposta] = resposta == 1 ? PESO_ROI : 0;
            break;
        case 1: // Orçamento
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

// Função para aplicar a "parentização" e calcular a pontuação
double parentizarDecisao(Projeto p, int criterios[], char caminho[]) {
    double score = 0.0;

    for (int i = 0; i < 4; i++) {
        int criterio = criterios[i];
        int resposta = 0;
        double pontuacao = 0;

        switch (criterio) {
            case 0: resposta = p.roi; caminho[i] = resposta ? 'S' : 'N'; break;
            case 1: resposta = p.orcamento; caminho[i] = resposta ? 'S' : 'N'; break;
            case 2: resposta = p.riscos; caminho[i] = resposta ? 'S' : 'N'; break;
            case 3: resposta = p.alinhamento; caminho[i] = resposta ? 'S' : 'N'; break;
        }

        pontuacao = calcularCriterio(criterio, resposta);
        score += pontuacao;
    }

    caminho[4] = '\0';  // Adiciona o terminador de string
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
    double score1 = parentizarDecisao(p, criterios1, caminho);
    double score2 = parentizarDecisao(p, criterios2, caminho);
    double score3 = parentizarDecisao(p, criterios3, caminho);

    // Retorna o maior score entre as diferentes ordens
    double maior_score = score1;
    if (score2 > maior_score) maior_score = score2;
    if (score3 > maior_score) maior_score = score3;

    return maior_score;
}

// Função para embaralhar os projetos
void embaralharProjetos(Projeto projetos[], int numProjetos) {
    for (int i = numProjetos - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Projeto temp = projetos[i];
        projetos[i] = projetos[j];
        projetos[j] = temp;
    }
}

// Função para avaliar os projetos e encontrar o melhor
void avaliarProjetos(Projeto projetos[], int numProjetos) {
    Projeto *melhorProjeto = &projetos[0];

    for (int i = 0; i < numProjetos; i++) {
        projetos[i].score = testarParentizacao(projetos[i]);

        if (projetos[i].score > melhorProjeto->score) {
            melhorProjeto = &projetos[i];
        }
    }

    // Exibe os resultados
    for (int i = 0; i < numProjetos; i++) {
        printf("\n%s - ROI: %d, Orçamento: %d, Riscos: %d, Alinhamento: %d => Score = %.2f\n",
               projetos[i].nome, projetos[i].roi, projetos[i].orcamento,
               projetos[i].riscos, projetos[i].alinhamento, projetos[i].score);
    }
    printf("\nO melhor projeto é: %s com um score de %.2f\n", melhorProjeto->nome, melhorProjeto->score);
}

// Função para medir o tempo de execução
double medirTempoExecucao(Projeto projetos[], int numProjetos) {
    clock_t inicio, fim;
    double tempo_gasto;

    inicio = clock(); // Início da medição
    avaliarProjetos(projetos, numProjetos); // Avaliação dos projetos
    fim = clock(); // Fim da medição

    tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC; // Tempo em segundos
    return tempo_gasto;
}

int main() {
    srand(time(0));

    // Abrindo o arquivo CSV para salvar os tempos de execução
    FILE *fp = fopen("tempos_execucao.csv", "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    // Escrevendo o cabeçalho no arquivo CSV
    fprintf(fp, "Execucao,Tempo (segundos)\n");

    for (int i = 0; i < 4; i++) {
        memo[i][0] = -1;
        memo[i][1] = -1;
    }

    Projeto projetos[16];

    for (int i = 0; i < 16; i++) {
        projetos[i].roi = (i & 8) ? 1 : 0;
        projetos[i].orcamento = (i & 4) ? 1 : 0;
        projetos[i].riscos = (i & 2) ? 1 : 0;
        projetos[i].alinhamento = (i & 1) ? 1 : 0;
    }

    char projectNames[16][50] = {
        "Projeto A", "Projeto B", "Projeto C", "Projeto D",
        "Projeto E", "Projeto F", "Projeto G", "Projeto H",
        "Projeto I", "Projeto J", "Projeto K", "Projeto L",
        "Projeto M", "Projeto N", "Projeto O", "Projeto P"
    };

    for (int i = 0; i < 16; i++) {
        snprintf(projetos[i].nome, 50, "%s", projectNames[i]);
    }

    // Realizar várias execuções para coletar dados de tempo
    for (int exec = 0; exec < 10; exec++) { // Execute 10 vezes, por exemplo
        embaralharProjetos(projetos, 16);   // Embaralha a lista de projetos
        double tempo = medirTempoExecucao(projetos, 16);  // Mede o tempo

        // Escrevendo a execução e o tempo no arquivo CSV
        fprintf(fp, "%d,%.6f\n", exec + 1, tempo);

        // Exibindo o tempo de execução no console
        printf("Execução %d: Tempo = %.6f segundos\n", exec + 1, tempo);
    }

    // Fechando o arquivo CSV
    fclose(fp);

    printf("Tempos de execução salvos em 'tempos_execucao.csv'\n");

    return 0;
}
