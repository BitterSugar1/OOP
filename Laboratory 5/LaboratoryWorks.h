// LaboratoryWorks.h
#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include "IPrintable.h"

class LaboratoryWorks : public IPrintable
{
private:
    // Статические константы
    static const int MIN_WORKS = 1;
    static const int MAX_WORKS = 20;
    static const int MIN_GRADE = 1;
    static const int MAX_GRADE = 10; // Оценки
    static const int MIN_DIFFICULTY = 1;
    static const int MAX_DIFFICULTY = 5; // Сложность


    // Приватные поля класса
    char* discipline = nullptr; // Название дисциплины
    double currentAverage; // Текущий средний балл
    double executionTime; // Время выполнения (в часах)
    char* executor = nullptr; // Исполнитель работ


    // Приватные методы для валидации
    void validateGrade(int grade) const;
    void validateDifficulty(int difficulty) const;
    void validateWorkNumber(int workNumber) const;
    void recalculateAverage(); // Пересчет среднего балла

protected:
    int totalWorks; // Общее количество лабораторных работ
    int completedWorks; // Количество сданных работ
    int* grades = nullptr; // Динамический массив оценок
    int* difficulties = nullptr; // Динамический массив сложностей

public:
    // Конструкторы
    LaboratoryWorks(const char* discipline, int totalWorks);
    LaboratoryWorks(const char* discipline, int totalWorks, double executionTime, const char* executor = "Unknown");
    
    // Конструктор копирования
    LaboratoryWorks(const LaboratoryWorks& other);

    // Деструктор
    virtual ~LaboratoryWorks();

    // Селекторы (геттеры)
    const char* getDiscipline() const { return discipline; }
    int getTotalWorks() const { return totalWorks; }
    int getCompletedWorks() const { return completedWorks; }
    double getCurrentAverage() const { return currentAverage; }
    double getExecutionTime() const { return executionTime; }
    const char* getExecutor() const { return executor; }

    // Модификаторы (сеттеры)
    void setExecutionTime(double time) { executionTime = time; }
    void setExecutor(const char* newExecutor);

    // Публичные методы
    void submitWork(int workNumber, int grade, int difficulty);
    virtual void printStatus() const; // Вывод информации о состоянии

    // Абстрактные методы для интерфейса отчетов
    virtual void submitReport(int workNumber) = 0;
    virtual bool isReportSubmitted(int workNumber) const = 0;
    virtual int getReportsSubmitted() const = 0;
    virtual int getReportsRemaining() const = 0;

    // Операторы
    LaboratoryWorks& operator=(const LaboratoryWorks& other);
    LaboratoryWorks& operator+=(double additionalTime); // Добавление времени выполнения

    // Дружественные операторы
    friend std::ostream& operator<<(std::ostream& out, const LaboratoryWorks& labWork);
};
// Внешний оператор для расчета общего времени
double& operator+=(double& sum, const LaboratoryWorks& labWork);
