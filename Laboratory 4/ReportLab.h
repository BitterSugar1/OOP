#pragma once
#include "LaboratoryWorks.h"

class ReportLab : public LaboratoryWorks
{
private:
    bool* reports; // Динамический массив для отметок о сдаче отчетов
    int reportsSubmitted; // Количество сданных отчетов

public:
    // Конструктор
    ReportLab(const char* discipline, int totalWorks);

    // Конструктор копирования
    ReportLab(const ReportLab& other);

    // Деструктор
    ~ReportLab();

    // Метод для сдачи отчета
    void submitReport(int workNumber);

    // Переопределенный метод вывода информации
    void printStatus() const;

    // Оператор присваивания
    ReportLab& operator=(const ReportLab& other);

    // Геттеры
    int getReportsSubmitted() const;
    int getReportsRemaining() const;
    bool isReportSubmitted(int workNumber) const;
};
