#pragma once
#include <iostream>
#include <string>
#include "Profit.h"
#include "SoldCars.h"
#include <fstream>
#include <deque>
using namespace std; // Класс клиентов, наследуется от класса проданных автомобилей
class Patron : public SoldCars
{ 
private:
	int n;
	void InputClient(Patron * p, int language); // Метод ввода данных клиента
	void InputDate(Patron * p, int kol); // Метод ввода даты продажи автомобиля
	deque <Patron> SearchByClient(deque<Patron>* patrons, int); // Поиск клиентов по ФИ (ФИ - фамилия имя клиента)
	deque <Patron> SearchByBrand(deque<Patron>* patrons, int); // Поиск по марки авто
	deque <Patron> SearchByYear(deque<Patron>* patrons, int); // Поиск по году выпуска автомобиля
	deque<Patron> SearchBy(int operation, deque<Patron> patrons, int language); // Метод выбора поиска
public:
	friend ifstream& operator >> (ifstream& in, Patron &patrons); // Запись клиента в файл
	friend ofstream& operator << (ofstream &out, const Patron &patrons); // Чтение клиента из файла
	friend ostream& operator << (ostream &out, const Patron &patrons); // Вывод клиента-авто на экран
	friend ostream& operator >= (ostream &out, const Patron &patrons); // Вывод клиента на экран
	friend ostream& operator -= (ostream &out, const Patron &patrons); // Вывод проданного автомобиля на экран
	void add_car_to_SoldCars(int * undo, int language); // Добавление клиента, проданного авто
	int DeleteCarSold(int language); // Удаление клиента-авто
	void CancelLastActionSold(int operation, int index, int delnumb); // Отмена последнего действия
	void DisplaySoldCars(int language); // Вывод списка проданных авто
	void GetInfoFromFileSold(int language); // Вывод на экран списка клиент-авто
	Patron ChangeInfo(deque<Patron>* patrons, int * numberer, int language); // Изменение информации о клиенте-авто
	string SerName; // Фамилия клиента
	string Name; // Имя
	string Patronymic; // Отчество
	string Adress; // Адресс
	int NumberOfCars; // Количество автомобилей клиента
	SoldCars *cars; // Автомобили пренадлежащие клиенту
	void Metod(int i) // Выыделение памяти для массива автомобилей
	{
		this->n = i;
		cars = new SoldCars[n];
	}
	~Patron() 
	{
		//delete cars;
	}
};