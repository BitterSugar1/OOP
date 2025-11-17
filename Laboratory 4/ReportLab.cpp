#include "ReportLab.h"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <iomanip>

// Конструктор ReportLab
ReportLab::ReportLab(const char* discipline, int totalWorks)
    : LaboratoryWorks(discipline, totalWorks),
    reportsSubmitted(0) {
    reports = new bool[totalWorks];
    for (int i = 0; i < totalWorks; ++i) {
        reports[i] = false;
    }
}

// Конструктор копирования ReportLab
ReportLab::ReportLab(const ReportLab& other)
    : LaboratoryWorks(other),
    reportsSubmitted(other.reportsSubmitted) {
    reports = new bool[totalWorks];
    for (int i = 0; i < totalWorks; ++i) {
        reports[i] = other.reports[i];
    }
}

// Деструктор ReportLab
ReportLab::~ReportLab() {
    delete[] reports;
}

// Геттер для количества сданных отчетов
int ReportLab::getReportsSubmitted() const {
    return reportsSubmitted;
}

// Геттер для количества оставшихся отчетов
int ReportLab::getReportsRemaining() const {
    return completedWorks - reportsSubmitted;
}

// Метод для сдачи отчета
void ReportLab::submitReport(int workNumber) {
    if (workNumber < 1 || workNumber > totalWorks) {
        throw std::out_of_range("Ошибка: номер работы вне допустимого диапазона");
    }

    int index = workNumber - 1;

    // Проверяем, сдана ли работа (имеет оценку)
    if (grades[index] == 0) {
        throw std::invalid_argument("Ошибка: работа должна быть сначала сдана и оценена");
    }

    // Проверяем, не сдан ли отчет уже
    if (reports[index]) {
        throw std::invalid_argument("Ошибка: отчет по этой работе уже сдан");
    }

    reports[index] = true;
    reportsSubmitted++;
}

// Проверка сдан ли отчет по работе
bool ReportLab::isReportSubmitted(int workNumber) const {
    if (workNumber < 1 || workNumber > totalWorks) {
        throw std::out_of_range("Ошибка: номер работы вне допустимого диапазона");
    }
    return reports[workNumber - 1];
}

// Переопределенный метод вывода информации
void ReportLab::printStatus() const {
    std::cout << "Дисциплина: " << getDiscipline() << std::endl;
    std::cout << "Исполнитель: " << getExecutor() << std::endl;
    std::cout << "Общее количество лабораторных работ: " << totalWorks << std::endl;
    std::cout << "Количество сданных работ: " << completedWorks << std::endl;
    std::cout << "Количество сданных отчетов: " << reportsSubmitted << std::endl;
    std::cout << "Отчетов осталось сдать: " << (completedWorks - reportsSubmitted) << std::endl;
    std::cout << "Текущий средний балл: " << std::fixed << std::setprecision(2) << getCurrentAverage() << std::endl;
    std::cout << "Время выполнения: " << getExecutionTime() << " часов" << std::endl;

    // Вывод детальной информации о сданных работах и отчетах
    if (completedWorks > 0) {
        std::cout << "Детали по сданным работам и отчетам:" << std::endl;
        for (int i = 0; i < totalWorks; ++i) {
            if (grades[i] != 0) {
                std::cout << "  Работа " << (i + 1)
                    << " - Оценка: " << grades[i]
                    << ", Сложность: " << getExecutionTime() // difficulties недоступен, используем доступные поля
                    << ", Отчет: " << (reports[i] ? "Сдан" : "Не сдан") << std::endl;
            }
        }
    }
    std::cout << "------------------------" << std::endl;
}

// Оператор присваивания для ReportLab
ReportLab& ReportLab::operator=(const ReportLab& other) {
    if (this != &other) {
        // Вызываем оператор присваивания базового класса
        LaboratoryWorks::operator=(other);

        // Освобождаем старую память
        delete[] reports;

        // Копируем данные производного класса
        reportsSubmitted = other.reportsSubmitted;

        // Выделяем новую память и копируем массив отчетов
        reports = new bool[totalWorks];
        for (int i = 0; i < totalWorks; ++i) {
            reports[i] = other.reports[i];
        }
    }
    return *this;
}
