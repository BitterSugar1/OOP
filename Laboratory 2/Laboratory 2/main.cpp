#include <iostream>
#include "LaboratoryWorks.h"

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

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "Лабораторная работа №2: Учет сдачи лабораторных работ\n" << std::endl;

    // Запуск всех тестов
    testNormalCase();
    testErrorCases();
    testCopyAndAssignment();
    testCompleteWorkflow();

    std::cout << "\nТестирование завершено!" << std::endl;

    return 0;
}