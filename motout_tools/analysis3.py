import pandas as pd
import matplotlib.pyplot as plt
import os

# Create a dir to generated images
outputdir = "./images_analysis"
os.makedirs(outputdir, exist_ok=True)

# Loading csv
file_path = "info.csv"
df = pd.read_csv(file_path)

# Converting timestamp to legible datetime
df["Date_from_timestamp"] = pd.to_datetime(df["Timestamp"], unit="s")

# Creating new columns from datetime
df["Data"] = df["Date_from_timestamp"].dt.date
df["Hora"] = df["Date_from_timestamp"].dt.hour
df["Mes"] = df["Date_from_timestamp"].dt.month
df["Dia"] = df["Date_from_timestamp"].dt.day

# Counting occurrences of hours
contagem_ocorrencias = df.groupby(["Data", "Hora"]).size().unstack(fill_value=0)

# Plotting occurrences of hours in one day 
for dia in contagem_ocorrencias.index:
    plt.figure(figsize=(12, 6))
    plt.bar(contagem_ocorrencias.columns, contagem_ocorrencias.loc[dia], color='skyblue', edgecolor='black')
    
    plt.title(f'Continuidade de Ocorrências para o Dia {dia}')
    plt.xlabel('Hora do Dia')
    plt.ylabel('Número de Ocorrências')
    plt.xticks(range(24))  # Mostrar todas as horas
    plt.grid(axis='y')
    plt.tight_layout()
    plt.savefig(os.path.join(outputdir, f"continuidade_ocorrencias_{dia}.png"))

# Counting occurrences of days
contagem_ocorrencias = df.groupby(["Mes", "Dia"]).size().unstack(fill_value=0)

# Plotting occurrences of days in one month
for mes in contagem_ocorrencias.index:
    plt.figure(figsize=(12, 6))
    plt.bar(contagem_ocorrencias.columns, contagem_ocorrencias.loc[mes], color='skyblue', edgecolor='black')
    
    plt.title(f'Continuidade de Ocorrências para o Mês {mes}')
    plt.xlabel('Dia do Mês')
    plt.ylabel('Número de Ocorrências')
    plt.xticks(range(1, 32))  # Mostrar dias de 1 a 31
    plt.xlim(1, 31)  # Ajusta o limite do eixo x
    plt.grid(axis='y')
    plt.tight_layout()
    plt.savefig(os.path.join(outputdir, f"continuidade_ocorrencias_mes_{mes}.png"))
