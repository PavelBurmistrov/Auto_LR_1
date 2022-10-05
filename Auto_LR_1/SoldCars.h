#pragma once
#include "Auto.h"
class SoldCars : public Auto // Класс проданных автомобилей наследуется от класса автомобилей
{
private:
	int DayOfPurchase; // Дата продажи 
	int MonthOfPurchase; 
public:
	double profit() override // Подсчет выгоды с продажи автомобиля
	{
		return (this->ruble - this->firstPrice);
	}
	double firstPrice; // Стоимость авто в автосалоне
	int BuyDay; // Дата покупки авто клиентом
	int BuyMonth; // Дата покупки авто клиентом
	int BuyYear; // Дата покупки авто клиентом
	int Dayget; // Дата покупки автосалоном
	int Monthget; // Дата покупки автосалоном
	int YearOfPurchase; // Дата покупки автосалоном
	int Year; // Год выпуска автомобиля
	double ruble; // Стоимость продажи автомобиля
	double ConverterFromRubleToD(); // Конвертер из BYN в Доллары
};