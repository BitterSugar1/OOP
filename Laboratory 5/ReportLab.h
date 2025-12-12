#pragma once
#include "LaboratoryWorks.h"
class ReportLab : public LaboratoryWorks
{
private:
    bool* reports; // Динамический массив для отметок о сдаче отчетов
    int reportsSubmitted; // Количество сданных отчетов

public:

    // Конструкторы
    ReportLab(const char* discipline, int totalWorks);
    ReportLab(const char* discipline, int totalWorks, double executionTime, const char* executor = "Unknown");
    
    // Конструктор копирования
    ReportLab(const ReportLab& other);

    // Деструктор
    ~ReportLab();

    // Метод для сдачи отчета
    void submitReport(int workNumber) override;

    // Переопределенный метод вывода информации
    virtual void printStatus() const override;

    // Оператор присваивания
    ReportLab& operator=(const ReportLab& other);

    // Геттеры
    int getReportsSubmitted() const override;
    int getReportsRemaining() const override;
    bool isReportSubmitted(int workNumber) const override;
};