#pragma once
#include <iostream>

class ILaboratoryWork {
public:
    virtual ~ILaboratoryWork() = default;

    // Чисто виртуальные методы интерфейса
    virtual void printStatus() const = 0;
    virtual const char* getDiscipline() const = 0;
    virtual int getTotalWorks() const = 0;
    virtual int getCompletedWorks() const = 0;
    virtual double getCurrentAverage() const = 0;
    virtual double getExecutionTime() const = 0;
    virtual const char* getExecutor() const = 0;

    // Виртуальный оператор []
    virtual int operator[](int index) const = 0;

    // Виртуальные методы для работы с работами
    virtual void submitWork(int workNumber, int grade, int difficulty) = 0;
};