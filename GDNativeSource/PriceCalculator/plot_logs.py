#!/usr/bin/env python3
import csv
import matplotlib.pyplot as plt
import os
import sys

def plot_market_adjustment(file_path):
    if not os.path.exists(file_path):
        return False

    data = []
    try:
        with open(file_path, 'r') as f:
            reader = csv.DictReader(f)
            for row in reader:
                clean_row = {}
                for k, v in row.items():
                    if k and v:
                        try:
                            clean_row[k] = float(v)
                        except ValueError:
                            pass
                if clean_row:
                    data.append(clean_row)
    except Exception as e:
        print(f"Error leyendo CSV {file_path}: {e}")
        return False

    if not data:
        return False

    headers = list(data[0].keys())
    
    # Caso 1: Test de componentes de satisfacción
    if "Amount" in headers and "Total" in headers:
        plot_satisfaction_test(data)
        return True

    # Caso 2: Evolución por persona, precios y trade (Market Adjustment)
    persons = set()
    for h in headers:
        if h.startswith("Satisfaction_"):
            persons.add(h.replace("Satisfaction_", ""))
    
    if not persons:
        return False

    persons = sorted(list(persons))
    num_persons = len(persons)
    products = get_product_names(headers)
    
    # Filas: 1 para precios + 1 para trade + 1 por cada persona
    total_rows = num_persons + 2
    fig, axes = plt.subplots(total_rows, 2, figsize=(15, 6 * total_rows), squeeze=False)
    
    # --- FILA 0: Evolución de Precios de Productos ---
    ax_prices = plt.subplot(total_rows, 1, 1)
    price_cols = [h for h in headers if h.startswith("Price_")]
    if price_cols:
        for col in price_cols:
            y = [row.get(col, 0.0) for row in data]
            label = col.replace("Price_", "")
            ax_prices.plot(y, marker='s', markersize=3, label=label)
        ax_prices.set_title("Evolución de Precios de Productos", fontsize=16, fontweight='bold')
        ax_prices.set_ylabel("Precio")
        ax_prices.grid(True, linestyle='--', alpha=0.7)
        ax_prices.legend(loc='upper left')

    # Ocultamos los axes originales correspondientes
    axes[0, 0].set_visible(False)
    axes[0, 1].set_visible(False)

    # --- FILA 1: Evolución de Trade (Exceso/Falta) ---
    ax_trade = plt.subplot(total_rows, 1, 2)
    trade_cols = [h for h in headers if h.startswith("MarketTrade_")]
    if trade_cols:
        for col in trade_cols:
            y = [row.get(col, 0.0) for row in data]
            label = col.replace("MarketTrade_", "")
            ax_trade.plot(y, marker='o', markersize=3, label=label)
        ax_trade.axhline(0, color='black', linestyle='-', alpha=0.5)
        ax_trade.set_title("Evolución de Demanda y Exceso (mapSumOfTradeAndExcessTrade)", fontsize=16, fontweight='bold')
        ax_trade.set_ylabel("Balance (Exceso Demanda > 0)")
        ax_trade.grid(True, linestyle='--', alpha=0.7)
        ax_trade.legend(loc='upper left')
    
    axes[1, 0].set_visible(False)
    axes[1, 1].set_visible(False)

    # --- FILAS RESTANTES: Una por persona ---
    for i, person in enumerate(persons):
        row_idx = i + 2
        
        # 1. Gráfico de Satisfacción (Izquierda)
        sat_col = f"Satisfaction_{person}"
        satisfaction = [row.get(sat_col, 0.0) for row in data]
        
        axes[row_idx, 0].plot(satisfaction, color='blue', linewidth=3, label='Satisfacción Total')
        axes[row_idx, 0].set_title(f"Satisfacción - {person}", fontsize=14, fontweight='bold')
        axes[row_idx, 0].set_ylabel("Nivel")
        axes[row_idx, 0].grid(True, linestyle='--', alpha=0.7)
        axes[row_idx, 0].legend()

        # 2. Gráfico de Opciones Individuales (Derecha)
        person_cols = [h for h in headers if h.endswith(f"_{person}") and not h.startswith("Satisfaction_")]
        
        option_cols = []
        for col in person_cols:
            is_product = False
            for prod in products:
                if col == f"{prod}_{person}":
                    is_product = True
                    break
            if not is_product:
                option_cols.append(col)

        for col in option_cols:
            y = [row.get(col, 0.0) for row in data]
            label = col.replace(f"_{person}", "")
            axes[row_idx, 1].plot(y, marker='.', markersize=4, label=label)

        axes[row_idx, 1].set_title(f"Desglose de Opciones - {person}", fontsize=14, fontweight='bold')
        axes[row_idx, 1].set_ylabel("Cantidad")
        axes[row_idx, 1].grid(True, linestyle='--', alpha=0.7)
        if len(option_cols) > 5:
            axes[row_idx, 1].legend(bbox_to_anchor=(1.05, 1), loc='upper left', fontsize='small')
        else:
            axes[row_idx, 1].legend()

    plt.xlabel("Iteración")
    plt.tight_layout()
    plt.savefig("market_complete_evolution.png")
    print("Gráfico completo con balance de mercado guardado en market_complete_evolution.png")
    plt.show()
    return True

def get_product_names(headers):
    return [h.replace("Price_", "") for h in headers if h.startswith("Price_")]

def plot_satisfaction_test(data):
    amounts = [row.get("Amount", 0.0) for row in data]
    cols = ["Individual", "Supplementary", "Complementary", "Total"]
    
    plt.figure(figsize=(10, 6))
    for col in cols:
        if col in data[0]:
            y = [row.get(col, 0.0) for row in data]
            plt.plot(amounts, y, label=col, linewidth=2)
            
    plt.title("Componentes de la Satisfacción vs Cantidad de Opciones")
    plt.xlabel("Cantidad (Amount)")
    plt.ylabel("Satisfacción")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig("satisfaction_test_plot.png")
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) > 1:
        plot_market_adjustment(sys.argv[1])
    else:
        if not plot_market_adjustment("log_market_adjustment.csv"):
            plot_market_adjustment("satisfaction_test.csv")
