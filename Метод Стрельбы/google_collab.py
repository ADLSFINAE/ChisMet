import numpy as np
import matplotlib.pyplot as plt

# Функция, задающая ОДУ второго порядка
def f(x, y, dy):
    return y  # Уравнение y'' = y

# Метод Рунге-Кутта 4-го порядка для системы ОДУ
def runge_kutta_4(f, x0, y0, dy0, h, n):
    x = np.zeros(n + 1)
    y = np.zeros(n + 1)
    dy = np.zeros(n + 1)
    
    x[0] = x0
    y[0] = y0
    dy[0] = dy0
    
    for i in range(n):
        k1_y = dy[i]
        k1_dy = f(x[i], y[i], dy[i])
        
        k2_y = dy[i] + 0.5 * h * k1_dy
        k2_dy = f(x[i] + 0.5 * h, y[i] + 0.5 * h * k1_y, dy[i] + 0.5 * h * k1_dy)
        
        k3_y = dy[i] + 0.5 * h * k2_dy
        k3_dy = f(x[i] + 0.5 * h, y[i] + 0.5 * h * k2_y, dy[i] + 0.5 * h * k2_dy)
        
        k4_y = dy[i] + h * k3_dy
        k4_dy = f(x[i] + h, y[i] + h * k3_y, dy[i] + h * k3_dy)
        
        y[i + 1] = y[i] + (h / 6) * (k1_y + 2 * k2_y + 2 * k3_y + k4_y)
        dy[i + 1] = dy[i] + (h / 6) * (k1_dy + 2 * k2_dy + 2 * k3_dy + k4_dy)
        x[i + 1] = x[i] + h
    
    return x, y

# Метод дихотомии для нахождения y'(0)
def dichotomy_method(f, a, b, ya, yb, h, tol=1e-6, max_iter=100):
    def error_function(dy0):
        # Решаем задачу Коши с текущим y'(a)
        x, y = runge_kutta_4(f, a, ya, dy0, h, int((b - a) / h))
        return y[-1] - yb  # Ошибка на правой границе

    # Начальные границы для y'(0)
    dy0_left = -10.0  # Левая граница
    dy0_right = 10.0  # Правая граница

    # Проверка, что функция меняет знак на интервале
    if error_function(dy0_left) * error_function(dy0_right) >= 0:
        raise ValueError("Функция не меняет знак на заданном интервале.")

    # Итерации метода дихотомии
    for _ in range(max_iter):
        dy0_mid = (dy0_left + dy0_right) / 2  # Середина интервала
        error_mid = error_function(dy0_mid)

        # Проверка на сходимость
        if abs(error_mid) < tol:
            return dy0_mid

        # Сужаем интервал
        if error_function(dy0_left) * error_mid < 0:
            dy0_right = dy0_mid
        else:
            dy0_left = dy0_mid

    raise ValueError("Метод дихотомии не сошелся!")

# Метод стрельбы с использованием метода дихотомии
def shooting_method(f, a, b, ya, yb, h, tol=1e-6, max_iter=100):
    # Находим y'(0) методом дихотомии
    dy0 = dichotomy_method(f, a, b, ya, yb, h, tol, max_iter)
    
    # Решаем задачу Коши с найденным y'(0)
    return runge_kutta_4(f, a, ya, dy0, h, int((b - a) / h))

# Параметры задачи
a = 0.0  # Начало интервала
b = 1.0  # Конец интервала
ya = 0.0  # Граничное условие на левом конце
yb = 1.0  # Граничное условие на правом конце
h = 0.1  # Шаг

# Решение методом стрельбы
x, y = shooting_method(f, a, b, ya, yb, h)

# Аналитическое решение
C1 = (yb - ya * np.exp(-b)) / (np.exp(b) - np.exp(-b))
C2 = ya - C1
y_analytical = C1 * np.exp(x) + C2 * np.exp(-x)

# Построение графиков
plt.figure(figsize=(10, 10))
plt.plot(x, y_analytical, label="Аналитическое решение", color='red')
plt.plot(x, y, label="Метод стрельбы (дихотомия)", color='blue', linestyle='--')
plt.xlabel('x')
plt.ylabel('y(x)')
plt.title('Решение краевой задачи методом стрельбы с дихотомией')
plt.legend()
plt.grid()
plt.show()