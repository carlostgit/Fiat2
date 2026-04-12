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

        styles = ['-', '--', ':', '-.']
        for idx, col in enumerate(option_cols):
            y = [row.get(col, 0.0) for row in data]
            label = col.replace(f"_{person}", "")
            # Alternar estilos para facilitar distinción si se solapan
            style = styles[idx % len(styles)]
            line, = axes[row_idx, 1].plot(y, marker='.', markersize=4, linestyle=style, 
                                   label=label, alpha=0.8, linewidth=1.5)
            
            # Etiqueta al final de la evolución
            if len(y) > 0:
                axes[row_idx, 1].text(len(y) - 0.5, y[-1], label, color=line.get_color(), 
                                      fontsize=8, va='center', fontweight='bold')

        axes[row_idx, 1].set_title(f"Desglose de Opciones - {person}", fontsize=14, fontweight='bold')
        axes[row_idx, 1].set_ylabel("Cantidad")
        axes[row_idx, 1].grid(True, linestyle='--', alpha=0.5)
        if len(option_cols) > 5:
            axes[row_idx, 1].legend(bbox_to_anchor=(1.02, 1), loc='upper left', fontsize='x-small')
        else:
            axes[row_idx, 1].legend(loc='best', fontsize='x-small')

    plt.xlabel("Iteración")
    fig.tight_layout()
    plt.savefig("market_complete_evolution.png")
    print("Gráfico completo con balance de mercado guardado en market_complete_evolution.png")
    
    # Leyenda interactiva
    enable_interactive_legend(fig)
    
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

def plot_all_initial_conditions(initial_csv, curves_csv):
    if not os.path.exists(initial_csv) or not os.path.exists(curves_csv):
        return False
    
    # 1. Leer datos iniciales
    initial_data = []
    with open(initial_csv, 'r') as f:
        initial_data = list(csv.DictReader(f))
    persons_init = [row['Person'] for row in initial_data]
    products = [h for h in initial_data[0].keys() if h != 'Person']

    # 2. Leer curvas
    curves_data = []
    with open(curves_csv, 'r') as f:
        curves_data = list(csv.DictReader(f))
    persons_curves = sorted(list(set(row['Person'] for row in curves_data)))

    num_persons = len(persons_curves)
    total_rows = num_persons + 1
    fig, axes = plt.subplots(total_rows, 1, figsize=(14, 5 * total_rows))

    # --- SUBPLOT 0: Cantidades iniciales (Bar Chart) ---
    ax_init = axes[0]
    x = range(len(persons_init))
    width = 0.8 / len(products)
    for i, product in enumerate(products):
        amounts = [float(row[product]) for row in initial_data]
        ax_init.bar([pos + i * width for pos in x], amounts, width, label=product)
    
    ax_init.set_xticks([pos + (len(products)-1)*width/2 for pos in x])
    ax_init.set_xticklabels(persons_init)
    ax_init.set_title("Condiciones Iniciales: Posesión de Productos por Persona", fontsize=14, fontweight='bold')
    ax_init.set_ylabel("Cantidad inicial")
    ax_init.legend()
    ax_init.grid(axis='y', linestyle='--', alpha=0.7)

    # --- SUBPLOTS 1 a N: Curvas por persona ---
    import numpy as np
    q_range = np.linspace(0, 15, 100)
    def calculate_satisfaction(q, pref0, maxsat):
        if maxsat == 0: return 0.0
        return maxsat * (1.0 - (1.0 / (q * pref0 / maxsat + 1.0)))

    # Mapeo de estilos por tipo
    line_styles = {
        'Option': '-',      # Solid
        'SupplCombo': '--', # Dashed
        'ComplCombo': ':'   # Dotted
    }

    for i, person in enumerate(persons_curves):
        ax_curr = axes[i + 1]
        person_data = [row for row in curves_data if row['Person'] == person]
        
        for idx, row in enumerate(person_data):
            subject = row['Subject']
            sType = row.get('Type', 'Option')
            pref0 = float(row['PreferenceAt0'])
            maxsat = float(row['MaximumSatisf'])
            
            style = line_styles.get(sType, '-')
            y = [calculate_satisfaction(q, pref0, maxsat) for q in q_range]
            
            # Añadir marcadores (markevery para no saturar con 100 puntos)
            line, = ax_curr.plot(q_range, y, label=f"{subject} ({sType})", 
                         linestyle=style, marker='.', markersize=6, markevery=8,
                         linewidth=2.0, alpha=0.7)
            
            # Etiqueta al final de la curva
            ax_curr.text(q_range[-1] + 0.2, y[-1], subject, color=line.get_color(), 
                         fontsize=8, va='center', fontweight='bold')
        
        ax_curr.set_title(f"Configuración de Satisfacción - {person}", fontsize=14, fontweight='bold')
        ax_curr.set_xlabel("Cantidad (Quantity)")
        ax_curr.set_ylabel("Satisfacción")
        ax_curr.set_xlim(0, 18) # Dejar espacio para etiquetas
        # Leyenda más pequeña y fuera del gráfico
        ax_curr.legend(bbox_to_anchor=(1.02, 1), loc='upper left', fontsize='x-small')
        ax_curr.grid(True, linestyle='--', alpha=0.4)

    plt.tight_layout()
    plt.savefig("initial_state_complete.png")
    print("Dashboard inicial guardado en initial_state_complete.png")
    
    # Hacer la leyenda interactiva si es posible
    enable_interactive_legend(fig)
    
    plt.show()
    return True

def enable_interactive_legend(fig):
    """Habilita que se puedan ocultar/mostrar líneas clicando en la leyenda"""
    artist_to_line = {}
    
    for ax in fig.axes:
        leg = ax.get_legend()
        if not leg: continue
        
        orig_lines = ax.get_lines()
        # En el caso de Satisfaction Curves, puede haber textos extra (labels finales)
        # que no queremos que interfieran con la lógica de la leyenda clicable 
        # a menos que los mapeemos también.
        
        leg_lines = leg.get_lines()
        leg_texts = leg.get_texts()
        
        for i, (leg_line, leg_text) in enumerate(zip(leg_lines, leg_texts)):
            if i < len(orig_lines):
                orig_line = orig_lines[i]
                
                # Configurar ambos (línea y texto) como pickers
                for artist in [leg_line, leg_text]:
                    artist.set_picker(True)
                    if hasattr(artist, 'set_pickradius'):
                        artist.set_pickradius(5) # Radio más pequeño para precisión
                    artist_to_line[artist] = (orig_line, leg_line, leg_text)

    def on_pick(event):
        artist = event.artist
        if artist not in artist_to_line:
            return
        
        orig_line, leg_line, leg_text = artist_to_line[artist]
        visible = not orig_line.get_visible()
        orig_line.set_visible(visible)
        
        # Efecto visual en la leyenda
        alpha = 1.0 if visible else 0.2
        leg_line.set_alpha(alpha)
        leg_text.set_alpha(alpha)
        
        fig.canvas.draw()

    fig.canvas.mpl_connect('pick_event', on_pick)

if __name__ == "__main__":
    # Intentar graficar condiciones iniciales si existen (Dashboard Unificado)
    plot_all_initial_conditions("initial_conditions.csv", "satisfaction_curves.csv")

    if len(sys.argv) > 1:
        plot_market_adjustment(sys.argv[1])
    else:
        if not plot_market_adjustment("log_market_adjustment.csv"):
            plot_market_adjustment("satisfaction_test.csv")
