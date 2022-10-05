#pragma once
#include "Auto.h"
#include <deque>
#include "Profit.h"
#include <fstream>
#include <iostream>
using namespace std;
class AutoInStock : public Auto // Класс автомобилей в наличии наследуется от класса автомобиля
{
private:
	int DayOfPurchase;
	int MonthOfPurchase;
	deque<AutoInStock> SortByCost(deque<AutoInStock> cars); // Сортировка авто по цене по возрастанию
	deque<AutoInStock> SortByCost2(deque<AutoInStock> cars); // Сортировка авто по цене по убыванию
	deque<AutoInStock> sortbyBrand(deque<AutoInStock> cars); // Сортировка авто по марке по возрастанию
	deque<AutoInStock> sortbyBrand2(deque<AutoInStock> cars); // Сортировка авто по марке по убыванию
	deque<AutoInStock> SortListOfCars(deque<AutoInStock> cars); // Сортировка автомобилей по г.в. по возрастванию
	deque<AutoInStock> SortListOfCars2(deque<AutoInStock> cars); // Сортировка автомобилей по г.в.по убыванию
	deque<AutoInStock> SortByPurchase(deque<AutoInStock> cars); // Сортировка авто по дате покупки по возрастанию
	deque<AutoInStock> SortByPurchase2(deque<AutoInStock> cars);  // Сортировка авто по дате покупки по убыванию
public:
	friend ofstream& operator << (ofstream &out, const AutoInStock &car); // Вывода из файла авто в наличии
	friend ifstream& operator >> (ifstream& in, AutoInStock& car); // Ввод в файл автомобилей
	friend ostream& operator < (ostream &out, AutoInStock &cars); // Вывод автомобилей на экран
	void Cout(deque<AutoInStock> cars); // Вывод авто на экран
	double ConverterFromRubleToDollar(); // Конвертер из BYN в Доллары
	int NumberOfAddedCars(int language); // Количество добавляемых авто
	void DeleteCar(int * indexofremovecar, int language); // Удаление автомобиля
	void add_car_to_AutoInStock(int NumberOfAddedCars, deque<AutoInStock> cars, int language); // Добавление автомобиля
	void CancelLastActionStock(int opop1, int numbercars, int indexofremovecar); // Отмена последнего дейтсвия (добавление, удаление)
	void GetInfoFromFile(int language); // Получение информации из файла, вывод, сортировка
	void DisplTotalProfit(); // Общая прибыль за разные периоды времени
	double profit() override
	{
		return (0 - ruble); 
	} // Подсчет прибыли
	void Dayset(int Day); // Дата 
	int Dayget; // Дата покупки авто
	int Monthget; // Дата покупки авто
	int YearOfPurchase; // Дата покупки авто
	int Year; // Дата покупки авто
	double Ruble; // Цена покупки авто
	double ruble;	// Цена покупки авто
	AutoInStock(double ruble) // Конструктор с аргументом - цена
	{
		Ruble = ruble;
	}
	AutoInStock(string Brand, string Model) // Конструктор 
	{
		this->Brand = Brand;
		this->Model = Model;
	}
	AutoInStock() : Auto() // Конструктор по умолчанию
	{
	}
	void Display()
	{
		cout << "Price with spare parts BYN: " << Ruble << endl;
	}
};