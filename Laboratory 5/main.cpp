#include <iostream>
#include "LaboratoryWorks.h"
#include "ReportLab.h"
// Функция для тестирования нормального случая работы
void testNormalCase()
{
    std::cout << "=== Тестирование нормального случая ===" << std::endl;
    try {
        // Создание объекта для учета работ по ООП
        ReportLab manager("Объектно-Ориентированное Программирование", 5);
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
        ReportLab manager("", 5);
    }
    catch (const std::exception& e) {
        std::cerr << "Тест пустого названия: " << e.what() << std::endl;
    }
    // Тест недопустимого количества работ
    try {
        ReportLab manager("Математика", 0);
    }
    catch (const std::exception& e) {
        std::cerr << "Тест количества работ: " << e.what() << std::endl;
    }
    // Тест недопустимой оценки
    try {
        ReportLab manager("Физика", 3);
        manager.submitWork(1, 15, 2);
    }
    catch (const std::exception& e) {
        std::cerr << "Тест оценки: " << e.what() << std::endl;
    }
    // Тест недопустимого номера работы
    try {
        ReportLab manager("Химия", 3);
        manager.submitWork(5, 8, 3);
    }
    catch (const std::exception& e) {
        std::cerr << "Тест номера работы: " << e.what() << std::endl;
    }
    // Тест двойной сдачи одной работы
    try {
        ReportLab manager("Информатика", 3);
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
        ReportLab original("Алгоритмы и структуры данных", 4);
        original.submitWork(1, 9, 4);
        original.submitWork(2, 8, 3);
        std::cout << "Оригинальный объект:" << std::endl;
        original.printStatus();
        // Тестирование конструктора копирования
        ReportLab copy(original);
        std::cout << "Скопированный объект:" << std::endl;
        copy.printStatus();
        // Тестирование оператора присваивания
        ReportLab assigned("Временный", 2);
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
        ReportLab manager("Базы данных", 3);
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
        ReportLab lab1("ООП", 5, 12.5, "Иванов Иван");
        ReportLab lab2("Базы данных", 3, 8.0); // Исполнитель по умолчанию
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

void testPolymorphism() {
    std::cout << "\n=== Тестирование полиморфизма и абстрактных классов ===" << std::endl;
    try {
        LaboratoryWorks* labs[3] = {
            new ReportLab("ООП", 3),
            new ReportLab("Базы данных", 4),
            new ReportLab("Алгоритмы", 2)
        };

        // Сдача работ и отчетов полиморфно
        for (int i = 0; i < 3; ++i) {
            labs[i]->submitWork(1, 8 + i, 3);
            labs[i]->submitReport(1);
            if (i == 1) {
                labs[i]->submitWork(2, 9, 4);
                labs[i]->submitReport(2);
            }
            labs[i]->printStatus();
        }

        // Освобождение памяти
        for (int i = 0; i < 3; ++i) {
            delete labs[i];
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void testIPrintable() {
    std::cout << "\n=== Тестирование интерфейса IPrintable ===" << std::endl;
    try {
        // Создаем массив указателей на интерфейс IPrintable
        IPrintable* printables[3] = {
            new ReportLab("ООП", 3, 10.5, "Иванов Иван"),
            new ReportLab("Базы данных", 4, 8.0, "Петров Петр"),
            new ReportLab("Алгоритмы", 2, 15.2, "Сидорова Анна")
        };

        std::cout << "Демонстрация полиморфизма через интерфейс IPrintable:" << std::endl;
        std::cout << "=====================================================" << std::endl;

        // Полиморфный вызов метода printStatus() через интерфейс
        for (int i = 0; i < 3; ++i) {
            std::cout << "Объект " << (i + 1) << " через IPrintable:" << std::endl;
            printables[i]->printStatus();  // Вызовется реализация из ReportLab
            std::cout << std::endl;
        }

        // Демонстрация работы с разными типами через один интерфейс
        std::cout << "Обход всех объектов через единый интерфейс:" << std::endl;
        std::cout << "===========================================" << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << ">>> Вывод статуса объекта " << (i + 1) << ":" << std::endl;
            printables[i]->printStatus();
        }

        // Освобождение памяти через виртуальный деструктор IPrintable
        for (int i = 0; i < 3; ++i) {
            delete printables[i];
        }

        std::cout << "Тестирование интерфейса завершено успешно!" << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка при тестировании интерфейса IPrintable: " << e.what() << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Лабораторная работа №5: Абстрактные классы и интерфейсы\n" << std::endl;
    // Запуск всех тестов
    testNormalCase();
    testErrorCases();
    testCopyAndAssignment();
    testCompleteWorkflow();
    testOverloadedOperators();
    testPolymorphism();
    std::cout << "\nТестирование завершено!" << std::endl;
    return 0;
}
