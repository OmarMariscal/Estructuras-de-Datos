import numpy as np
import matplotlib.pyplot as plt
from math import sqrt

def compute_regression(x, y, show_plot=True):
    x = np.array(x, dtype=float)
    y = np.array(y, dtype=float)
    if x.size != y.size:
        raise ValueError("x e y deben tener la misma longitud.")
    n = x.size
    if n < 2:
        raise ValueError("Se necesitan al menos 2 puntos para ajustar una recta.")
    
    x_bar = x.mean()
    y_bar = y.mean()
    
    Sxx = np.sum((x - x_bar)**2)
    Syy = np.sum((y - y_bar)**2)
    Sxy = np.sum((x - x_bar)*(y - y_bar))
    
    b1 = Sxy / Sxx
    b0 = y_bar - b1 * x_bar
    
    y_pred = b0 + b1 * x
    residuals = y - y_pred
    SSE = np.sum(residuals**2)
    SSR = np.sum((y_pred - y_bar)**2)
    SST = Syy
    
    s2 = SSE / (n - 2) if n > 2 else float('nan')
    se_b1 = sqrt(s2 / Sxx) if n > 2 else float('nan')
    se_b0 = sqrt(s2 * (1.0/n + x_bar**2 / Sxx)) if n > 2 else float('nan')
    
    r = Sxy / sqrt(Sxx * Syy) if Sxx>0 and Syy>0 else float('nan')
    r_squared = r**2 if not np.isnan(r) else float('nan')
    
    results = {
        'n': n,
        'slope': float(b1),
        'intercept': float(b0),
        'r': float(r),
        'r_squared': float(r_squared),
        'SSE': float(SSE),
        'SSR': float(SSR),
        'SST': float(SST),
        'se_slope': float(se_b1) if not np.isnan(se_b1) else None,
        'se_intercept': float(se_b0) if not np.isnan(se_b0) else None
    }
    
    print("Modelo de regresión lineal simple (mínimos cuadrados)")
    print(f"n = {n}")
    print(f"Ecuación: ŷ = {b0:.6f} + {b1:.6f} x")
    print(f"Coeficiente de correlación r = {r:.6f}")
    print(f"R² = {r_squared:.6f}")
    print(f"SSE (suma de residuos al cuadrado) = {SSE:.6f}")
    if n > 2:
        print(f"Varianza estimada del error s² = {s2:.6f}")
        print(f"Error estándar de la pendiente (se_b1) = {se_b1:.6f}")
        print(f"Error estándar del intercepto (se_b0) = {se_b0:.6f}")
    else:
        print("No hay grados de libertad suficientes para estimar errores estándar (n <= 2).")
    
    if show_plot:
        plt.figure(figsize=(7,5))
        plt.scatter(x, y)
        xs = np.linspace(x.min(), x.max(), 200)
        ys = b0 + b1 * xs
        plt.plot(xs, ys)
        plt.xlabel("x")
        plt.ylabel("y")
        plt.title("Ajuste por regresión lineal (mínimos cuadrados)")
        plt.grid(True)
        plt.show()
    
    return results

# --- Ejemplo de uso ---
x_ejemplo = [1.93,1.95,1.78,1.64,1.54,1.32,2.12,1.88,1.70,1.58,2.47,2.37,2.00,1.77,1.62,2.77,2.47,2.24,1.32,1.26,1.21,2.26,2.04,1.88]
y_ejemplo = [4.4,5.3,4.5,4.5,3.7,2.8,6.1,4.9,4.9,4.1,7.0,6.7,5.2,4.7,4.2,6.0,5.8,5.2,3.5,3.2,2.9,5.3,5.1,4.6]
res = compute_regression(x_ejemplo, y_ejemplo, show_plot=True)
