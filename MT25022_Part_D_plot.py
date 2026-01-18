#!/usr/bin/env python3

# MT25022_Part_D_plot.py
# Python script to plot the metrics from MT25022_Part_D_CSV.csv
# Generates plots for CPU%, Mem, IO vs NumWorkers for each function and program.
# AI-generated with assistance from GitHub Copilot.
# Roll number: MT25022

import matplotlib.pyplot as plt
import pandas as pd

# Read the CSV
df = pd.read_csv('MT25022_Part_D_CSV.csv')

# For each function, plot for A and B
functions = ['cpu', 'mem', 'io']
metrics = ['CPU%', 'Mem', 'IO']

for func in functions:
    fig, axes = plt.subplots(1, 3, figsize=(15, 5))
    fig.suptitle(f'Performance Metrics for {func.upper()} Function')
    
    for i, metric in enumerate(metrics):
        ax = axes[i]
        for prog in ['A', 'B']:
            subset = df[(df['Program'] == prog) & (df['Function'] == func)]
            ax.plot(subset['NumWorkers'], subset[metric], label=f'Program {prog}', marker='o')
        ax.set_xlabel('Number of Workers')
        ax.set_ylabel(metric)
        ax.set_title(f'{metric} vs Workers ({func})')
        ax.legend()
        ax.grid(True)
    
    plt.tight_layout()
    plt.savefig(f'MT25022_Part_D_{func}_plot.png')
    plt.savefig(f'MT25022_Part_D_{func}_plot.pdf')
    plt.show()

print("Plots generated: MT25022_Part_D_{cpu,mem,io}_plot.png and .pdf")