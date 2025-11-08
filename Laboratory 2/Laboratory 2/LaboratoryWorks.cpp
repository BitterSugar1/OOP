#include "LaboratoryWorks.h"
#include <iostream>
#include <cstring>
#include <stdexcept>

// Конструктор с параметрами
LaboratoryWorks::LaboratoryWorks(const char* discipline, int totalWorks)
    : discipline(nullptr),
    totalWorks(totalWorks),
    completedWorks(0),
    grades(nullptr),
    difficulties(nullptr),
    currentAverage(0.0) {

    // Валидация входных данных
    if (discipline == nullptr || strlen(discipline) == 0) {
        throw std::invalid_argument("Ошибка: название дисциплины не может быть пустым");
    }

    if (totalWorks < MIN_WORKS || totalWorks > MAX_WORKS) {
        throw std::out_of_range("Ошибка: недопустимое количество лабораторных работ");
    }

    // Выделение памяти для названия дисциплины
    this->discipline = new char[strlen(discipline) + 1];
    strcpy_s(this->discipline, strlen(discipline) + 1, discipline);

    // Выделение памяти для массивов
    grades = new int[totalWorks];
    difficulties = new int[totalWorks];

    // Инициализация массивов нулевыми значениями
    for (int i = 0; i < totalWorks; ++i) {
        grades[i] = 0;
        difficulties[i] = 0;
    }
}

// Конструктор копирования
LaboratoryWorks::LaboratoryWorks(const LaboratoryWorks& other)
    : discipline(nullptr),
    totalWorks(other.totalWorks),
    completedWorks(other.completedWorks),
    grades(nullptr),
    difficulties(nullptr),
    currentAverage(other.currentAverage) {

    // Копирование названия дисциплины
    discipline = new char[strlen(other.discipline) + 1];
    strcpy_s(discipline, strlen(other.discipline) + 1, other.discipline);

    // Выделение памяти и копирование массивов
    grades = new int[totalWorks];
    difficulties = new int[totalWorks];

    for (int i = 0; i < totalWorks; ++i) {
        grades[i] = other.grades[i];
        difficulties[i] = other.difficulties[i];
    }
}

// Деструктор - освобождение динамической памяти
LaboratoryWorks::~LaboratoryWorks() {
    delete[] discipline;
    delete[] grades;
    delete[] difficulties;
}

// Валидация оценки
void LaboratoryWorks::validateGrade(int grade) const {
    if (grade < MIN_GRADE || grade > MAX_GRADE) {
        throw std::out_of_range("Ошибка: оценка должна быть в диапазоне от 1 до 10");
    }
}

// Валидация сложности
void LaboratoryWorks::validateDifficulty(int difficulty) const {
    if (difficulty < MIN_DIFFICULTY || difficulty > MAX_DIFFICULTY) {
        throw std::out_of_range("Ошибка: сложность должна быть в диапазоне от 1 до 5");
    }
}

// Валидация номера работы
void LaboratoryWorks::validateWorkNumber(int workNumber) const {
    if (workNumber < 1 || workNumber > totalWorks) {
        throw std::out_of_range("Ошибка: номер работы вне допустимого диапазона");
    }

    // Проверка, не сдана ли работа уже
    if (grades[workNumber - 1] != 0) {
        throw std::invalid_argument("Ошибка: эта работа уже была сдана");
    }
}

// Пересчет среднего балла
void LaboratoryWorks::recalculateAverage() {
    if (completedWorks == 0) {
        currentAverage = 0.0;
        return;
    }

    double sum = 0.0;
    for (int i = 0; i < totalWorks; ++i) {
        if (grades[i] != 0) {
            sum += grades[i];
        }
    }

    currentAverage = sum / completedWorks;
}

// Метод для внесения информации о сданной работе
void LaboratoryWorks::submitWork(int workNumber, int grade, int difficulty) {
    // Валидация всех входных параметров
    validateWorkNumber(workNumber);
    validateGrade(grade);
    validateDifficulty(difficulty);

    // Запись данных в массивы
    grades[workNumber - 1] = grade;
    difficulties[workNumber - 1] = difficulty;
    if (grades[workNumber - 1] == 0) {
        completedWorks++;
    }

    // Пересчет среднего балла
    recalculateAverage();
}

// Метод вывода информации о состоянии сдачи работ
void LaboratoryWorks::printStatus() const {
    std::cout << "Дисциплина: " << discipline << std::endl;
    std::cout << "Общее количество лабораторных работ: " << totalWorks << std::endl;
    std::cout << "Количество сданных работ: " << completedWorks << std::endl;
    std::cout << "Текущий средний балл: " << currentAverage << std::endl;

    // Вывод детальной информации о сданных работах
    if (completedWorks > 0) {
        std::cout << "Детали по сданным работам:" << std::endl;
        for (int i = 0; i < totalWorks; ++i) {
            if (grades[i] != 0) {
                std::cout << "  Работа " << (i + 1)
                    << " - Оценка: " << grades[i]
                    << ", Сложность: " << difficulties[i] << std::endl;
            }
        }
    }
    std::cout << "------------------------" << std::endl;
}

// Оператор присваивания
LaboratoryWorks& LaboratoryWorks::operator=(const LaboratoryWorks& other) {
    // Проверка на самоприсваивание
    if (this != &other) {
        // Освобождение старой памяти
        delete[] discipline;
        delete[] grades;
        delete[] difficulties;

        // Копирование полей
        totalWorks = other.totalWorks;
        completedWorks = other.completedWorks;
        currentAverage = other.currentAverage;

        // Выделение новой памяти и копирование данных
        discipline = new char[strlen(other.discipline) + 1];
        strcpy_s(discipline, strlen(other.discipline) + 1, other.discipline);

        grades = new int[totalWorks];
        difficulties = new int[totalWorks];

        for (int i = 0; i < totalWorks; ++i) {
            grades[i] = other.grades[i];
            difficulties[i] = other.difficulties[i];
        }
    }
    return *this;
}

