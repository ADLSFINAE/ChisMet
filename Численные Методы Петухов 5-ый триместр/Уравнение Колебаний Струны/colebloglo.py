import numpy as np
import matplotlib.pyplot as plt
from math import pi, sin, cos

class Hyper:
    def __init__(self):
        self.n = 101
        self.l = 1
        self.h0 = self.l / (self.n - 1)
        self.c = 0.1
        self.tau = 0.01
        self.pi = pi
        self.t0 = 100
        self.k = self.c**2 * self.tau**2 / self.h0**2
    
    def dalamb(self):
        y0 = np.zeros(self.n)
        y = np.zeros(self.n)
        y1 = np.zeros(self.n)
        T = []
        
        t = 0
        
        # Initial conditions
        for i in range(self.n):
            x = i * self.h0
            y0[i] = y[i] - self.tau * sin(self.pi * 3 * x / self.l)
        
        y0[0] = y0[-1] = 0
        y[0] = y[-1] = 0
        y1[0] = y1[-1] = 0
        
        # Prepare figure for time snapshots
        plt.figure(figsize=(12, 8))
        
        while abs(t - self.t0) > self.tau / 2:
            if abs(t - 0) < self.tau / 2:
                plt.plot(np.linspace(0, self.l, self.n), y1, label=f't = {t:.1f}')
            if abs(t - 2.1) < self.tau / 2:
                plt.plot(np.linspace(0, self.l, self.n), y1, label=f't = {t:.1f}')
            if abs(t - 5.5) < self.tau / 2:
                plt.plot(np.linspace(0, self.l, self.n), y1, label=f't = {t:.1f}')
            if abs(t - 7.8) < self.tau / 2:
                plt.plot(np.linspace(0, self.l, self.n), y1, label=f't = {t:.1f}')
            
            # Update solution
            for i in range(1, self.n - 1):
                y1[i] = 2 * y[i] - y0[i] + self.k * (y[i+1] - 2*y[i] + y[i-1])
            
            y0, y = y, y1.copy()
            t += self.tau
            T.append(y[self.n // 2])
        
        # Plot time snapshots
        plt.title("Решение уравнения колебаний струны в разные моменты времени")
        plt.xlabel("x")
        plt.ylabel("u(x,t)")
        plt.legend()
        plt.grid()
        plt.show()
        
        # Plot time evolution at middle point
        plt.figure(figsize=(12, 6))
        plt.plot(np.arange(0, t-self.tau, self.tau), T)
        plt.title("Эволюция решения в средней точке струны")
        plt.xlabel("Время t")
        plt.ylabel("u(L/2,t)")
        plt.grid()
        plt.show()
        
        print(f"Расчет завершен в t = {t}")

if __name__ == "__main__":
    solver = Hyper()
    solver.dalamb()