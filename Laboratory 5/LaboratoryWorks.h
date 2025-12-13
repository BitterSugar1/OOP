#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include "IPrintable.h"

// Шаблонный класс: T — тип оценки (int или double)
template<typename T>
class LaboratoryWorks : public IPrintable
{
protected:
    static const int MIN_WORKS = 1;
    static const int MAX_WORKS = 20;
    static const int MIN_GRADE = 1;
    static const int MAX_GRADE = 10;
    static const int MIN_DIFFICULTY = 1;
    static const int MAX_DIFFICULTY = 5;

    char* discipline = nullptr;
    char* executor = nullptr;

    T currentAverage;        //  Теперь шаблонный тип
    double executionTime;

    int totalWorks;
    int completedWorks;

    T* grades = nullptr;     //  Теперь шаблонный массив
    int* difficulties = nullptr;

    // Проверки
    void validateGrade(T grade) const {
        if (grade < MIN_GRADE || grade > MAX_GRADE)
            throw std::out_of_range("Оценка вне диапазона");
    }

    void validateDifficulty(int difficulty) const {
        if (difficulty < MIN_DIFFICULTY || difficulty > MAX_DIFFICULTY)
            throw std::out_of_range("Сложность вне диапазона");
    }

    void validateWorkNumber(int workNumber) const {
        if (workNumber < 1 || workNumber > totalWorks)
            throw std::out_of_range("Неверный номер работы");
        if (grades[workNumber - 1] != 0)
            throw std::invalid_argument("Работа уже сдана");
    }

    // Пересчёт среднего балла
    void recalculateAverage() {
        if (completedWorks == 0) {
            currentAverage = T(0);
            return;
        }

        T sum = 0;
        for (int i = 0; i < totalWorks; i++)
            sum += grades[i];

        currentAverage = sum / completedWorks;
    }

public:
    LaboratoryWorks(const char* discipline, int totalWorks);
    LaboratoryWorks(const char* discipline, int totalWorks, double executionTime, const char* executor);

    LaboratoryWorks(const LaboratoryWorks& other);
    virtual ~LaboratoryWorks();

    // Сдача работы
    void submitWork(int workNumber, T grade, int difficulty);

    // Геттеры
    T getCurrentAverage() const { return currentAverage; }

    // Интерфейсные методы
    virtual void submitReport(int workNumber) = 0;
    virtual bool isReportSubmitted(int workNumber) const = 0;
    virtual int getReportsSubmitted() const = 0;
    virtual int getReportsRemaining() const = 0;

    virtual void printStatus() const override;
};

