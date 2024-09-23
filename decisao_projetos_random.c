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

// Função para aplicar a "parentização" (otimização das decisões)
double parentizarDecisao(Projeto p, int criterios[]) {
    double score = 0.0;
    printf("Percurso das decisoes para %s:\n", p.nome);

    for (int i = 0; i < 4; i++) {
        int criterio = criterios[i];
        int resposta = 0;
        double pontuacao = 0;

        switch (criterio) {
            case 0: resposta = p.roi; printf(" - ROI: %s\n", resposta ? "Sim" : "Nao"); break;
            case 1: resposta = p.orcamento; printf(" - Orcamento: %s\n", resposta ? "Sim" : "Nao"); break;
            case 2: resposta = p.riscos; printf(" - Riscos: %s\n", resposta ? "Sim" : "Nao"); break;
            case 3: resposta = p.alinhamento; printf(" - Alinhamento Estrategico: %s\n", resposta ? "Sim" : "Nao"); break;
        }

        // Usa memoização para calcular o score sem recalcular subproblemas
        pontuacao = calcularCriterio(criterio, resposta);
        score += pontuacao;

        // Exibe o valor da pontuação para o critério atual
        if (pontuacao > 0) {
            printf("   -> Pontuacao adicionada: %.2f\n", pontuacao);
        } else {
            printf("   -> Nenhuma pontuacao adicionada.\n");
        }
    }

    printf("Score final de %s: %.2f\n\n", p.nome, score);
    return score;
}

// Função para avaliar os projetos e selecionar o melhor
void avaliarProjetos(Projeto projetos[], int numProjetos, int criterios[]) {
    Projeto *melhorProjeto = &projetos[0];  // Inicializa com o primeiro projeto
    
    for (int i = 0; i < numProjetos; i++) {
        // Aplica a ordem dos critérios parentizados
        projetos[i].score = parentizarDecisao(projetos[i], criterios);
        
        // Verifica se o projeto atual tem um score melhor
        if (projetos[i].score > melhorProjeto->score) {
            melhorProjeto = &projetos[i];
        }
    }
    
    printf("O melhor projeto e: %s com um score de %.2f\n", melhorProjeto->nome, melhorProjeto->score);
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
    
    // Definindo a ordem de parentização (otimização) dos critérios
    int criterios[] = {0, 1, 2, 3};  // Ordem: ROI, Orçamento, Riscos, Alinhamento

    // Avaliando os projetos e selecionando o melhor
    avaliarProjetos(projetos, 3, criterios);
    
    return 0;
}
