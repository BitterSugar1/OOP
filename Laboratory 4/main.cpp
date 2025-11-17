#include <iostream>
#include "LaboratoryWorks.h"
#include "ReportLab.h"

// Функция для тестирования нормального случая работы
void testNormalCase()
{
    std::cout << "=== Тестирование нормального случая ===" << std::endl;

    try {
        // Создание объекта для учета работ по ООП
        LaboratoryWorks manager("Объектно-Ориентированное Программирование", 5);

        // Сдача нескольких работ
        manager.submitWork(1, 8, 3);
        manager.submitWork(2, 9, 4);
        manager.submitWork(3, 7, 2);

        // Вывод текущего состояния
        manager.printStatus();
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
};

// Функция для тестирования различных ошибок
void testErrorCases() {
    std::cout << "\n=== Тестирование обработки ошибок ===" << std::endl;

    // Тест пустого названия дисциплины
    try {
        LaboratoryWorks manager("", 5);
    }
    catch (const std::exception& e) {
        std::cerr << "Тест пустого названия: " << e.what() << std::endl;
    }

    // Тест недопустимого количества работ
    try {
        LaboratoryWorks manager("Математика", 0);
    }
    catch (const std::exception& e) {
        std::cerr << "Тест количества работ: " << e.what() << std::endl;
    }

    // Тест недопустимой оценки
    try {
        LaboratoryWorks manager("Физика", 3);
        manager.submitWork(1, 15, 2);
    }
    catch (const std::exception& e) {
        std::cerr << "Тест оценки: " << e.what() << std::endl;
    }

    // Тест недопустимого номера работы
    try {
        LaboratoryWorks manager("Химия", 3);
        manager.submitWork(5, 8, 3);
    }
    catch (const std::exception& e) {
        std::cerr << "Тест номера работы: " << e.what() << std::endl;
    }

    // Тест двойной сдачи одной работы
    try {
        LaboratoryWorks manager("Информатика", 3);
        manager.submitWork(1, 8, 3);
        manager.submitWork(1, 9, 4); // Попытка сдать ту же работу еще раз
    }
    catch (const std::exception& e) {
        std::cerr << "Тест двойной сдачи: " << e.what() << std::endl;
    }
}

// Функция для тестирования копирования и присваивания
void testCopyAndAssignment() {
    std::cout << "\n=== Тестирование копирования и присваивания ===" << std::endl;

    try {
        // Создание оригинального объекта
        LaboratoryWorks original("Алгоритмы и структуры данных", 4);
        original.submitWork(1, 9, 4);
        original.submitWork(2, 8, 3);

        std::cout << "Оригинальный объект:" << std::endl;
        original.printStatus();

        // Тестирование конструктора копирования
        LaboratoryWorks copy(original);
        std::cout << "Скопированный объект:" << std::endl;
        copy.printStatus();

        // Тестирование оператора присваивания
        LaboratoryWorks assigned("Временный", 2);
        assigned = original;
        std::cout << "Присвоенный объект:" << std::endl;
        assigned.printStatus();

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка при копировании: " << e.what() << std::endl;
    }
}

// Функция для демонстрации полного цикла сдачи работ
void testCompleteWorkflow() {
    std::cout << "\n=== Тестирование полного цикла сдачи ===" << std::endl;

    try {
        LaboratoryWorks manager("Базы данных", 3);

        std::cout << "Начальное состояние:" << std::endl;
        manager.printStatus();

        // Последовательная сдача всех работ
        manager.submitWork(1, 7, 2);
        std::cout << "После сдачи работы 1:" << std::endl;
        manager.printStatus();

        manager.submitWork(2, 9, 4);
        std::cout << "После сдачи работы 2:" << std::endl;
        manager.printStatus();

        manager.submitWork(3, 8, 3);
        std::cout << "После сдачи работы 3:" << std::endl;
        manager.printStatus();

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка в рабочем процессе: " << e.what() << std::endl;
    }
}

// Функция для тестирования перегруженных операторов
void testOverloadedOperators() {
    std::cout << "\n=== Тестирование перегруженных операторов ===" << std::endl;

    try {
        // Создание объектов с использованием перегруженного конструктора
        LaboratoryWorks lab1("ООП", 5, 12.5, "Иванов Иван");
        LaboratoryWorks lab2("Базы данных", 3, 8.0); // Исполнитель по умолчанию

        std::cout << "Использование оператора <<:" << std::endl;
        std::cout << lab1;
        std::cout << lab2;

        // Тестирование оператора += (внутри класса)
        std::cout << "Добавление времени выполнения (5 часов):" << std::endl;
        lab1 += 5.0;
        std::cout << lab1 << "\r";

        // Тестирование внешнего оператора +=
        double totalTime = 0.0;
        totalTime += lab1;
        totalTime += lab2;
        std::cout << "Общее затраченное время на все задачи: " << totalTime << " часов" << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка при тестировании операторов: " << e.what() << std::endl;
    }
}

// Остальные тестовые функции остаются без изменений...

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "Лабораторная работа №3: Перегрузка методов и операторов\n" << std::endl;

    // Запуск всех тестов
    testNormalCase();
    testErrorCases();
    testCopyAndAssignment();
    testCompleteWorkflow();
    testOverloadedOperators(); // Новая тестовая функция

    std::cout << "\nТестирование завершено!" << std::endl;

    return 0;
}
