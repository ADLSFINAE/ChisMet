import numpy as np
import matplotlib.pyplot as plt
from math import sin, pi, acos

class PoissonSolver:
    def __init__(self):
        self.n = 101  # Количество узлов сетки
        self.l = 1.0   # Длина струны
        self.h0 = self.l / (self.n - 1)  # Шаг по пространству
        self.tau = 0.25 * self.h0 ** 2   # Шаг по времени
        self.E = 1e-6   # Критерий сходимости
        self.pi = acos(-1)  # Число π

    def source_function(self, x, n):
        """Функция источника (правая часть уравнения)"""
        return sin(self.pi * n * x / self.l)

    def solve(self):
        """Решение уравнения Пуассона"""
        # Инициализация массивов
        y = np.zeros(self.n)  # Текущее решение
        y_new = np.zeros(self.n)  # Новое решение
        
        t = 0.0  # Текущее время
        iteration = 0  # Счетчик итераций
        
        # Создаем фигуру для графиков
        plt.figure(figsize=(12, 8))
        
        while True:
            # Граничные условия (закрепленные концы)
            y_new[0] = 0
            y_new[-1] = 0
            
            # Обновление решения во внутренних точках
            for i in range(1, self.n - 1):
                x = i * self.h0
                y_new[i] = y[i] + self.tau * (
                    (y[i-1] - 2*y[i] + y[i+1]) / (self.h0**2) - self.source_function(x, 3)
                )
            
            # Проверка сходимости
            max_diff = np.max(np.abs(y_new - y))
            
            # Сохранение промежуточных результатов для графиков
            if abs(t - 0.0) < self.tau/2:
                plt.plot(np.linspace(0, self.l, self.n), y_new.copy(), label=f't = {t:.4f}')
            if abs(t - 0.01) < self.tau/2:
                plt.plot(np.linspace(0, self.l, self.n), y_new.copy(), label=f't = {t:.4f}')
            if abs(t - 0.02) < self.tau/2:
                plt.plot(np.linspace(0, self.l, self.n), y_new.copy(), label=f't = {t:.4f}')
            if abs(t - 0.03625) < self.tau/2:
                plt.plot(np.linspace(0, self.l, self.n), y_new.copy(), label=f't = {t:.4f}')
            
            # Обновление решения
            y = y_new.copy()
            t += self.tau
            iteration += 1
            
            # Условие выхода
            if max_diff < self.E:
                break
        
        # Настройка и отображение графика
        plt.title("Решение уравнения Пуассона в разные моменты времени", fontsize=14)
        plt.xlabel("Координата x", fontsize=12)
        plt.ylabel("Температура u(x,t)", fontsize=12)
        plt.legend()
        plt.grid(True)
        plt.show()
        
        print(f"Решение сошлось за {iteration} итераций")
        print(f"Финальное время: {t:.5f}")
        
        return y

def convergence_study():
    """Исследование сходимости при разных N"""
    n_values = range(10, 40, 2)  # Более частый шаг
    mid_point_values = []
    
    for n in n_values:
        solver = PoissonSolver()
        solver.n = n
        solver.h0 = solver.l / (n - 1)
        solver.tau = 0.1 * solver.h0**2  # Уменьшен шаг по времени для устойчивости
        
        y = np.zeros(n)
        y_new = np.zeros(n)
        E = 1e-6
        
        for _ in range(10000):  # Фиксированное число итераций
            y_new[0] = 0
            y_new[-1] = 0
            
            for i in range(1, n - 1):
                x = i * solver.h0
                y_new[i] = y[i] + solver.tau * (
                    (y[i-1] - 2*y[i] + y[i+1]) / (solver.h0**2) - solver.source_function(x, 3)
                )
            
            if np.max(np.abs(y_new - y)) < E:
                break
            y = y_new.copy()
        
        mid_point_values.append(y[n//2])
    
    # Построение графика
    plt.figure(figsize=(12, 6))
    plt.plot(n_values, mid_point_values, 'bo-', label='Численное решение')
    plt.title("Сходимость решения в точке x=0.5", fontsize=14)
    plt.xlabel("Число узлов сетки N", fontsize=12)
    plt.ylabel("u(0.5)", fontsize=12)
    plt.legend()
    plt.grid(True)
    plt.show()

# Запуск в Google Colab
if __name__ == "__main__":
    print("Исследование сходимости:")
    convergence_study()
    
    print("\nРешение уравнения Пуассона:")
    solver = PoissonSolver()
    final_solution = solver.solve()