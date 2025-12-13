#pragma once
#include "LaboratoryWorks.h"

template<typename T>
class ReportLab : public LaboratoryWorks<T>
{
private:
    bool* reports;
    int reportsSubmitted;

public:
    ReportLab(const char* discipline, int totalWorks)
        : LaboratoryWorks<T>(discipline, totalWorks), reportsSubmitted(0)
    {
        reports = new bool[totalWorks] {};
    }

    ReportLab(const char* discipline, int totalWorks, double time, const char* exec)
        : LaboratoryWorks<T>(discipline, totalWorks, time, exec), reportsSubmitted(0)
    {
        reports = new bool[totalWorks] {};
    }

    ~ReportLab() {
        delete[] reports;
    }

    void submitReport(int workNumber) override {
        if (workNumber < 1 || workNumber > this->totalWorks)
            throw std::out_of_range("Неверный номер работы");

        int idx = workNumber - 1;

        if (this->grades[idx] == 0)
            throw std::invalid_argument("Нельзя сдавать отчёт до сдачи работы");

        if (reports[idx])
            throw std::invalid_argument("Отчёт уже сдан");

        reports[idx] = true;
        reportsSubmitted++;
    }

    bool isReportSubmitted(int workNumber) const override {
        return reports[workNumber - 1];
    }

    int getReportsSubmitted() const override {
        return reportsSubmitted;
    }

    int getReportsRemaining() const override {
        return this->completedWorks - reportsSubmitted;
    }

    void printStatus() const override {
        LaboratoryWorks<T>::printStatus();
        std::cout << "Отчётов сдано: " << reportsSubmitted << "\n";
    }
};
