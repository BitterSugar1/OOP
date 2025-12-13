#include <iostream>
#include "LaboratoryWorks.h"
#include "ReportLab.h"

// Функция для тестирования нормального случая работы
void testNormalCase()
{
    std::cout << "=== Тестирование нормального случая ===" << std::endl;
    try {
        // Теперь указываем тип оценки — int
        ReportLab<int> manager("Объектно-Ориентированное Программирование", 5);

        manager.submitWork(1, 8, 3);
        manager.submitWork(2, 9, 4);
        manager.submitWork(3, 7, 2);

        manager.printStatus();
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

// Функция для тестирования различных ошибок
void testErrorCases() {
    std::cout << "\n=== Тестирование обработки ошибок ===" << std::endl;

    try {
        ReportLab<int> manager("", 5);
    }
    catch (const std::exception& e) {
        std::cerr << "Тест пустого названия: " << e.what() << std::endl;
    }

    try {
        ReportLab<int> manager("Математика", 0);
    }
    catch (const std::exception& e) {
        std::cerr << "Тест количества работ: " << e.what() << std::endl;
    }

    try {
        ReportLab<int> manager("Физика", 3);
        manager.submitWork(1, 15, 2);
    }
    catch (const std::exception& e) {
        std::cerr << "Тест оценки: " << e.what() << std::endl;
    }

    try {
        ReportLab<int> manager("Химия", 3);
        manager.submitWork(5, 8, 3);
    }
    catch (const std::exception& e) {
        std::cerr << "Тест номера работы: " << e.what() << std::endl;
    }

    try {
        ReportLab<int> manager("Информатика", 3);
        manager.submitWork(1, 8, 3);
        manager.submitWork(1, 9, 4);
    }
    catch (const std::exception& e) {
        std::cerr << "Тест двойной сдачи: " << e.what() << std::endl;
    }
}

// Функция для тестирования копирования и присваивания
void testCopyAndAssignment() {
    std::cout << "\n=== Тестирование копирования и присваивания ===" << std::endl;
    try {
        ReportLab<int> original("Алгоритмы и структуры данных", 4);
        original.submitWork(1, 9, 4);
        original.submitWork(2, 8, 3);

        std::cout << "Оригинальный объект:" << std::endl;
        original.printStatus();

        ReportLab<int> copy(original);
        std::cout << "Скопированный объект:" << std::endl;
        copy.printStatus();

        ReportLab<int> assigned("Временный", 2);
        assigned = original;

        std::cout << "Присвоенный объект:" << std::endl;
        assigned.printStatus();
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка при копировании: " << e.what() << std::endl;
    }
}

void testCompleteWorkflow() {
    std::cout << "\n=== Тестирование полного цикла сдачи ===" << std::endl;
    try {
        ReportLab<int> manager("Базы данных", 3);

        std::cout << "Начальное состояние:" << std::endl;
        manager.printStatus();

        manager.submitWork(1, 7, 2);
        manager.printStatus();

        manager.submitWork(2, 9, 4);
        manager.printStatus();

        manager.submitWork(3, 8, 3);
        manager.printStatus();
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка в рабочем процессе: " << e.what() << std::endl;
    }
}

void testOverloadedOperators() {
    std::cout << "\n=== Тестирование перегруженных операторов ===" << std::endl;
    try {
        ReportLab<int> lab1("ООП", 5, 12.5, "Иванов Иван");
        ReportLab<int> lab2("Базы данных", 3, 8.0);

        std::cout << lab1;
        std::cout << lab2;

        lab1 += 5.0;
        std::cout << lab1;

        double totalTime = 0.0;
        totalTime += lab1;
        totalTime += lab2;

        std::cout << "Общее время: " << totalTime << " часов" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void testPolymorphism() {
    std::cout << "\n=== Тестирование полиморфизма ===" << std::endl;

    try {
        LaboratoryWorks<int>* labs[3] = {
            new ReportLab<int>("ООП", 3),
            new ReportLab<int>("Базы данных", 4),
            new ReportLab<int>("Алгоритмы", 2)
        };

        for (int i = 0; i < 3; i++) {
            labs[i]->submitWork(1, 8 + i, 3);
            labs[i]->submitReport(1);

            if (i == 1) {
                labs[i]->submitWork(2, 9, 4);
                labs[i]->submitReport(2);
            }
            labs[i]->printStatus();
        }

        for (int i = 0; i < 3; i++)
            delete labs[i];
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void testIPrintable() {
    std::cout << "\n=== Тестирование интерфейса IPrintable ===" << std::endl;

    try {
        IPrintable* arr[3] = {
            new ReportLab<int>("ООП", 3, 10.5, "Иванов"),
            new ReportLab<int>("Базы данных", 4, 8.0, "Петров"),
            new ReportLab<int>("Алгоритмы", 2, 15.2, "Сидорова")
        };

        for (int i = 0; i < 3; i++) {
            arr[i]->printStatus();
        }

        for (int i = 0; i < 3; i++)
            delete arr[i];
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    testNormalCase();
    testErrorCases();
    testCopyAndAssignment();
    testCompleteWorkflow();
    testOverloadedOperators();
    testPolymorphism();
    testIPrintable();

    std::cout << "\nТестирование завершено!\n";
    return 0;
}
