#pragma once
#include <iostream>
#include <string>
#include "Profit.h"
using namespace std;
class Auto : public Profit // Класс автомобиля наследуется от абстрактного класса прибыли
{
public:
	Auto();
	int VIN; // VIN авто
	string Brand; // Марка автомобиля
	string Model; // Модель автомобиля
	int Year; // Год выпуска автомобил
};