#pragma once
#include <iostream>
using namespace std;
class BaseException : public exception
{
protected:
	// объ€снение к исключению - общее дл€ всех производных классов
	string text;

public:
	// чиста€ виртуальна€ функци€, котора€ выводит текст исключени€
	virtual string what() = 0;
};