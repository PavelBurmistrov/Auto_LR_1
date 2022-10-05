#pragma once
class Profit // Класс прибыли
{
public :
	virtual double profit() = 0; // Рассчет прибыли
	//virtual double EmountOfExpenses() = 0;
	double SellingPrice; // Цена продажи автомобиля
};