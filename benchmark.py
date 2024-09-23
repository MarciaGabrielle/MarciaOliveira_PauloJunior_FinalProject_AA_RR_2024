import matplotlib.pyplot as plt
import pandas as pd
import timeit
import random

# Função para simular o algoritmo C para benchmarking
def benchmark_algorithm():
    def randomizar_projeto(nome):
        return {
            'nome': nome,
            'roi': random.randint(0, 1),
            'orcamento': random.randint(0, 1),
            'riscos': random.randint(0, 1),
            'alinhamento': random.randint(0, 1)
        }

    def calcular_score(projeto):
        score = 0
        score += projeto['roi'] * 0.35
        score += projeto['orcamento'] * 0.30
        score += projeto['riscos'] * 0.15
        score += projeto['alinhamento'] * 0.20
        return score

    projetos = [randomizar_projeto(f'Projeto {chr(65+i)}') for i in range(3)]
    melhores_projetos = sorted(projetos, key=lambda p: calcular_score(p), reverse=True)
    return melhores_projetos[0]

# Função para rodar o benchmark
def rodar_benchmark(repeticoes):
    tempo_execucao = timeit.timeit(benchmark_algorithm, number=repeticoes)
    return tempo_execucao

# Números de execuções para teste
repeticoes_testadas = [100, 500, 1000, 5000, 10000]

# Armazenar os resultados
tempos_execucao = [rodar_benchmark(repeticoes) for repeticoes in repeticoes_testadas]

# Criar tabela com resultados
tabela_resultados = pd.DataFrame({
    'Número de Execuções': repeticoes_testadas,
    'Tempo de Execução (segundos)': tempos_execucao
})

# Figura 1: Gerar o gráfico
plt.figure(figsize=(10, 6))
plt.plot(repeticoes_testadas, tempos_execucao, marker='o', linestyle='-', color='b')
plt.xlabel('Número de Execuções')
plt.ylabel('Tempo de Execução (segundos)')
plt.title('Benchmark do Algoritmo - Tempo de Execução')
plt.grid(True)
plt.show()

# Figura 2: Exibir a tabela em uma janela separada
fig, ax = plt.subplots(figsize=(6, 3))
ax.axis('tight')
ax.axis('off')
table = ax.table(cellText=tabela_resultados.values, colLabels=tabela_resultados.columns, cellLoc='center', loc='center')

# Exibir a tabela
plt.title('Tabela de Benchmark')
plt.show()
