#pragma once
#include <string>
class LaboratoryWorks
{
private:
	// Статические константы
	static const int MIN_WORKS = 1;
	static const int MAX_WORKS = 20;
	static const int MIN_GRADE = 1;
	static const int MAX_GRADE = 10;		// Оценки
	static const int MIN_DIFFICULTY = 1;
	static const int MAX_DIFFICULTY = 5;	// Сложность

	// Приватные поля класса
	char* discipline = nullptr;          // Название дисциплины
	int totalWorks;                      // Общее количество лабораторных работ
	int completedWorks;                  // Количество сданных работ
	int* grades = nullptr;               // Динамический массив оценок
	int* difficulties = nullptr;         // Динамический массив сложностей
	double currentAverage;               // Текущий средний балл

	// Приватные методы для валидации
	void validateGrade(int grade) const;
	void validateDifficulty(int difficulty) const;
	void validateWorkNumber(int workNumber) const;
	void recalculateAverage(); // Пересчет среднего балла

public:
#pragma region shadow_constructor
	// Конструктор с параметром
		//LaboratoryWorks(const char* const discipline, int totalWorks)
		//	: 
		//	discipline(nullptr),
		//	totalWorks(totalWorks),
		//	completedWorks(0),
		//	grades(nullptr),
		//	difficulties(nullptr),
		//	currentAverage(0.0)
		//{
		//	if (discipline == nullptr) {
		//		throw std::exception("Ошибка: название дисциплины не может быть пустым!"); 
		//	}

		//	if (strlen(discipline) == 0) {
		//		throw std::exception("Ошибка: название дисциплины не может быть пустым!");
		//	}

		//	for (int i = 0; strlen(discipline); ++i) {
		//		throw std::exception(""); 
		//	}

		//	if (totalWorks < MIN_WORKS || totalWorks > MAX_WORKS) {
		//		throw std::exception("Ошибка: количество лабораторных работ выходит за пределы!");
		//	}

		//	// Дисциплина и тотал воркс проверка

		//	this->discipline = new char[strlen(discipline) + 1] {0};
		//	strcpy_s();
		//}
#pragma endregion

	 // Конструктор с параметрами
	LaboratoryWorks(const char* discipline, int totalWorks);

	// Конструктор копирования
	LaboratoryWorks(const LaboratoryWorks& other);
	
	// Деструктор
	~LaboratoryWorks();

	// Селекторы (геттеры)
	const char* getDiscipline() const { return discipline; }
	int getTotalWorks() const { return totalWorks; }
	int getCompletedWorks() const { return completedWorks; }
	double getCurrentAverage() const { return currentAverage; }

	// Публичные методы
	void submitWork(int workNumber, int grade, int difficulty);
	void printStatus() const; // Вывод информации о состоянии

	// Оператор присваивания
	LaboratoryWorks& operator=(const LaboratoryWorks& other);
};