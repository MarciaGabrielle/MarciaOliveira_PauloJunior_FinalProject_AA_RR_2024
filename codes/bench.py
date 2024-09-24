import pandas as pd
import tkinter as tk
from tkinter import ttk

# Função para exibir a tabela em uma janela gráfica
def exibir_tabela(df):
    # Criar a janela principal
    root = tk.Tk()
    root.title("Tempos de Execução")

    # Criar um widget Treeview para exibir a tabela
    tree = ttk.Treeview(root)

    # Definir as colunas
    tree['columns'] = list(df.columns)
    tree['show'] = 'headings'  # Ocultar a coluna de índices padrão

    # Definir os títulos das colunas
    for col in df.columns:
        tree.heading(col, text=col)

    # Inserir os dados na tabela
    for index, row in df.iterrows():
        tree.insert("", "end", values=list(row))

    # Colocar a tabela na janela
    tree.pack(expand=True, fill='both')

    # Iniciar a interface gráfica
    root.mainloop()

# Carregar o arquivo CSV
df = pd.read_csv('tempos_execucao.csv')

# Exibir a tabela em uma janela gráfica
exibir_tabela(df)
