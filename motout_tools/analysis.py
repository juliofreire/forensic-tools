import pandas as pd
import matplotlib.pyplot as plt
import os
import sys

# Create a dir to generated images
outputdir = "./images_analysis"
os.makedirs(outputdir, exist_ok=True)
debug = 0

# Loading csv
if len(sys.argv) != 2:
    print(f"Usage {sys.argv[0]}: Provide only the csv to read.")
    exit()
print(len(sys.argv))
file_path = sys.argv[1] 
df = pd.read_csv(file_path)

print("Date" in df.columns)
print(df.head())

if("Timestamp" in df.columns or "timestamp" in df.columns):
    # Converting timestamp to legible datetime
    df["Date_from_timestamp"] = pd.to_datetime(df["Timestamp"], unit="s")

    # Creating new columns from datetime
    df["Data"] = df["Date_from_timestamp"].dt.date
    df["Hora"] = df["Date_from_timestamp"].dt.hour
    df["Ano"] = df["Date_from_timestamp"].dt.year
    df["Mes"] = df["Date_from_timestamp"].dt.month
    df["Dia"] = df["Date_from_timestamp"].dt.day

elif("Date" in df.columns or "date" in df.columns):
    print("PROGRAMA DE DATE")
    df["Data_from_date"] = pd.to_datetime(df["Date"])
    # Creating new columns from datetime
    df["Data"] = df["Data_from_date"].dt.date
    df["Ano"] =  df["Data_from_date"].dt.year
    df["Mes"] =  df["Data_from_date"].dt.month
    df["Dia"] =  df["Data_from_date"].dt.day
    df["Hora"] = df["Data_from_date"].dt.hour


if debug==0:
    # Counting occurrences of hours
    contagem_ocorrencias = df.groupby(["Data", "Channel", "Hora"]).size().unstack(fill_value=0)
    # Plotting occurrences of hours in one day 
    for dia in contagem_ocorrencias.index:
        plt.figure(figsize=(12, 6))
        plt.bar(contagem_ocorrencias.columns, contagem_ocorrencias.loc[dia], color='skyblue', edgecolor='black')
        
        plt.title(f'Continuidade de Ocorrências para o Dia {dia[0]} no canal {dia[1]}')
        plt.xlabel('Hora do Dia')
        plt.ylabel('Número de Ocorrências')
        plt.xticks(range(24))  # Mostrar todas as horas
        plt.grid(axis='y')
        plt.tight_layout()
        plt.savefig(os.path.join(outputdir, f"continuidade_ocorrencias_{dia[0]}_channel{dia[1]}.png"))

    # Counting occurrences of days
    contagem_ocorrencias = df.groupby(["Mes", "Channel", "Dia"]).size().unstack(fill_value=0)

    # Plotting occurrences of days in one month
    for mes in contagem_ocorrencias.index:
        plt.figure(figsize=(12, 6))
        plt.bar(contagem_ocorrencias.columns, contagem_ocorrencias.loc[mes], color='skyblue', edgecolor='black')
        
        plt.title(f'Continuidade de Ocorrências para o Mês {mes[0]} no canal {mes[1]},')
        plt.xlabel('Dia do Mês')
        plt.ylabel('Número de Ocorrências')
        plt.xticks(range(1, 32))  # Mostrar dias de 1 a 31
        plt.xlim(1, 31)  # Ajusta o limite do eixo x
        plt.grid(axis='y')
        plt.tight_layout()
        plt.savefig(os.path.join(outputdir, f"continuidade_ocorrencias_mes_{mes[0]}_channel{mes[1]}.png"))

    # Counting occurrences of months
    contagem_ocorrencias = df.groupby(["Ano", "Channel", "Mes"]).size().unstack(fill_value=0)

    # Plotting occurrences of months in one year
    for ano in contagem_ocorrencias.index:
        plt.figure(figsize=(12, 6))
        plt.bar(contagem_ocorrencias.columns, contagem_ocorrencias.loc[ano], color='skyblue', edgecolor='black')
        
        plt.title(f'Continuidade de Ocorrências para o Ano {ano[0]} no canal {ano[1]}')
        plt.xlabel('Mes do Ano')
        plt.ylabel('Número de Ocorrências')
        plt.xticks(range(1, 13))  # Mostrar dias de 1 a 31
        plt.xlim(1, 12)  # Ajusta o limite do eixo x
        plt.grid(axis='y')
        plt.tight_layout()
        plt.savefig(os.path.join(outputdir, f"continuidade_ocorrencias_ano_{ano[0]}_channel{ano[1]}.png"))
