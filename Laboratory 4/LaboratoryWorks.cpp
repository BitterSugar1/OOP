#include "LaboratoryWorks.h"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <iomanip>

// Конструктор с параметрами (базовый)
LaboratoryWorks::LaboratoryWorks(const char* discipline, int totalWorks)
    : discipline(nullptr),
    totalWorks(totalWorks),
    completedWorks(0),
    grades(nullptr),
    difficulties(nullptr),
    currentAverage(0.0),
    executionTime(0.0),
    executor(nullptr)
{
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

    // Выделение памяти для исполнителя (по умолчанию)
    this->executor = new char[8];
    strcpy_s(this->executor, 8, "Unknown");

    // Выделение памяти для массивов
    grades = new int[totalWorks];
    difficulties = new int[totalWorks];

    // Инициализация массивов нулевыми значениями
    for (int i = 0; i < totalWorks; ++i) {
        grades[i] = 0;
        difficulties[i] = 0;
    }
}

// Перегруженный конструктор с временем выполнения и исполнителем
LaboratoryWorks::LaboratoryWorks(const char* discipline,
    int totalWorks,
    double executionTime,
    const char* executor)
    : discipline(nullptr),
    totalWorks(totalWorks),
    completedWorks(0),
    grades(nullptr),
    difficulties(nullptr),
    currentAverage(0.0),
    executionTime(executionTime),
    executor(nullptr)
{
    // Валидация входных данных
    if (discipline == nullptr || strlen(discipline) == 0) {
        throw std::invalid_argument("Ошибка: название дисциплины не может быть пустым");
    }

    if (totalWorks < MIN_WORKS || totalWorks > MAX_WORKS) {
        throw std::out_of_range("Ошибка: недопустимое количество лабораторных работ");
    }

    if (executionTime < 0) {
        throw std::invalid_argument("Ошибка: время выполнения не может быть отрицательным");
    }

    // Выделение памяти для названия дисциплины
    this->discipline = new char[strlen(discipline) + 1];
    strcpy_s(this->discipline, strlen(discipline) + 1, discipline);

    // Выделение памяти для исполнителя
    if (executor != nullptr && strlen(executor) > 0) {
        this->executor = new char[strlen(executor) + 1];
        strcpy_s(this->executor, strlen(executor) + 1, executor);
    }
    else {
        this->executor = new char[8];
        strcpy_s(this->executor, 8, "Unknown");
    }

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
    currentAverage(other.currentAverage),
    executionTime(other.executionTime),
    executor(nullptr)
{
    // Копирование названия дисциплины
    discipline = new char[strlen(other.discipline) + 1];
    strcpy_s(discipline, strlen(other.discipline) + 1, other.discipline);

    // Копирование исполнителя
    executor = new char[strlen(other.executor) + 1];
    strcpy_s(executor, strlen(other.executor) + 1, other.executor);

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
    delete[] executor;
}

// Установка исполнителя
void LaboratoryWorks::setExecutor(const char* newExecutor) {
    if (newExecutor == nullptr || strlen(newExecutor) == 0) {
        throw std::invalid_argument("Ошибка: имя исполнителя не может быть пустым");
    }

    delete[] executor;
    executor = new char[strlen(newExecutor) + 1];
    strcpy_s(executor, strlen(newExecutor) + 1, newExecutor);
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
    int index = workNumber - 1;
    if (grades[index] == 0) {
        completedWorks++;
    }
    grades[index] = grade;
    difficulties[index] = difficulty;

    // Пересчет среднего балла
    recalculateAverage();
}

// Метод вывода информации о состоянии сдачи работ
void LaboratoryWorks::printStatus() const {
    std::cout << "Дисциплина: " << discipline << std::endl;
    std::cout << "Исполнитель: " << executor << std::endl;
    std::cout << "Общее количество лабораторных работ: " << totalWorks << std::endl;
    std::cout << "Количество сданных работ: " << completedWorks << std::endl;
    std::cout << "Текущий средний балл: " << std::fixed << std::setprecision(2) << currentAverage << std::endl;
    std::cout << "Время выполнения: " << executionTime << " часов" << std::endl;

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
        delete[] executor;

        // Копирование полей
        totalWorks = other.totalWorks;
        completedWorks = other.completedWorks;
        currentAverage = other.currentAverage;
        executionTime = other.executionTime;

        // Выделение новой памяти и копирование данных
        discipline = new char[strlen(other.discipline) + 1];
        strcpy_s(discipline, strlen(other.discipline) + 1, other.discipline);

        executor = new char[strlen(other.executor) + 1];
        strcpy_s(executor, strlen(other.executor) + 1, other.executor);

        grades = new int[totalWorks];
        difficulties = new int[totalWorks];

        for (int i = 0; i < totalWorks; ++i) {
            grades[i] = other.grades[i];
            difficulties[i] = other.difficulties[i];
        }
    }
    return *this;
}

// Оператор += для добавления времени выполнения
LaboratoryWorks& LaboratoryWorks::operator+=(double additionalTime) {
    if (additionalTime < 0) {
        throw std::invalid_argument("Ошибка: добавляемое время не может быть отрицательным");
    }
    executionTime += additionalTime;
    return *this;
}

// Оператор << для вывода на консоль
std::ostream& operator<<(std::ostream& out, const LaboratoryWorks& labWork) {
    out << "=== Информация о лабораторных работах ===" << std::endl;
    out << "Дисциплина: " << labWork.discipline << std::endl;
    out << "Исполнитель: " << labWork.executor << std::endl;
    out << "Работ всего: " << labWork.totalWorks << std::endl;
    out << "Сдано работ: " << labWork.completedWorks << std::endl;
    out << "Средний балл: " << std::fixed << std::setprecision(2) << labWork.currentAverage << std::endl;
    out << "Затраченное время: " << labWork.executionTime << " часов" << std::endl;

    if (labWork.completedWorks > 0) {
        out << "Сданные работы:" << std::endl;
        for (int i = 0; i < labWork.totalWorks; ++i) {
            if (labWork.grades[i] != 0) {
                out << "  №" << (i + 1) << " - Оценка: " << labWork.grades[i]
                    << ", Сложность: " << labWork.difficulties[i] << std::endl;
            }
        }
    }
    out << "=======================================" << std::endl;
    return out;
}

// Внешний оператор += для расчета общего времени
double& operator+=(double& sum, const LaboratoryWorks& labWork) {
    sum += labWork.getExecutionTime();  // Используем геттер вместо прямого доступа
    return sum;
}
