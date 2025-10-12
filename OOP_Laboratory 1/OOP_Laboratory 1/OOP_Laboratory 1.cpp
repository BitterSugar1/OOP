#include <iostream>
#include <stdio.h>
#include "windows.h"

bool calcul_prime(int n)
{
	if (n <= 1) return 0; // не простые числа (меньше 1)
	if (n == 2) return 1; // 2 - простое число
	if (n % 2 == 0) return 0; // четные числа больше 2 не простые

	// Проверяем делители от 3 до квадратного корня из n
	for (int i = 3; i*i <= n; i += 2) {
		if (n % i == 0) {
			return 0; // нашли делитель - число не простое
		}
	}
		
	return 1; // делителей не найдено - число простое
}


int main()
{
	setlocale(LC_ALL, "Russian");

	int prime_num, count_prime_num = 0;

	printf("Введите последовательность целых положительных чисел (0 - конец):\n");

	while (1) 
	{
		while (getchar() != '\n');

		printf("Введите число: ");
		int argsc = scanf_s("%d", &prime_num); // Считываем с клавиатуры значение и присваиваем пер.
		
		// TODO проверить на количество аргументов
		if (argsc == 0)
		{
			printf("Ошибка: введите число в корректном формате!\n");
			continue;
		}
		
		// Проверяем, что число положительное (кроме 0)
		if (prime_num < 0)
		{
			printf("Ошибка: введите положительное число!\n");
			continue;
		}

		// Если введен 0 - выходим из цикла
		if (prime_num == 0)
		{
			break;
		}

		// Проверяем, является ли число простым
		if (calcul_prime(prime_num))
		{
			count_prime_num++; // Счетчик простых чисел
		}
	}

	printf("\nКоличество простых чисел в последовательности: %d\n", count_prime_num);

	// TODO задержка консоли
	Sleep(5000);
	return 0;
}
