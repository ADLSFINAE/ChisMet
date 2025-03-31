import numpy as np
import matplotlib.pyplot as plt

# Параметры задачи
L = 1.0  # Длина стержня
T_end = 1.0  # Конечное время
alpha = 1.0  # Коэффициент теплопроводности
T1 = 150.0  # Температура на левом конце
T2 = 80.0  # Температура на правом конце
T0 = 0.0  # Начальная температура стержня

# Параметры сетки
N = 100  # Количество узлов по пространству
M = 100000  # Количество шагов по времени
h = L / N  # Шаг по пространству
tau = T_end / M  # Шаг по времени

# Проверка устойчивости схемы
y = (T_end * (N**2)) / M
print(y)
if y > 0.5:
    raise ValueError("Схема неустойчива! Уменьшите шаг по времени.")

# Инициализация сетки
T = np.zeros((N + 1, M + 1))
T[:, 0] = T0  # Начальное условие
T[0, :] = T1  # Граничное условие на левом конце
T[-1, :] = T2  # Граничное условие на правом конце

# Реализация явной разностной схемы
for n in range(M):
    for i in range(1, N):
        T[i, n + 1] = (1 - 2*y)*T[i][n] + y*(T[i - 1][n] + T[i + 1][n])

# Построение графиков
x_values = np.linspace(0, L, N + 1)
t_values = np.linspace(0, T_end, M + 1)

# График распределения температуры на разных временных слоях
plt.figure(figsize=(10, 6))
for n in range(0, M + 1, M // 10):
    plt.plot(x_values, T[:, n], label=f"t={t_values[n]:.2f}")
plt.xlabel('x')
plt.ylabel('Температура T(x, t)')
plt.title('Распределение температуры по длине стержня')
plt.legend()
plt.grid()
plt.show()

# График температуры в центральном узле
central_node = N // 2
plt.figure(figsize=(10, 6))

plt.plot(t_values, T[central_node, :], label="Центральный узел", color='red')
plt.xlabel('Время t')
plt.ylabel('Температура T(x, t)')
plt.title('Температура в центральном узле')
plt.legend()
plt.grid()
plt.show()