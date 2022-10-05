#pragma once
#include "BaseException.h"
#include "Patron.h"
class InputException : public BaseException // Класс обработки исключений ввода
{
private:
	string text = "Error! Input exception!";
public:
	InputException(string _text) { this->text = _text; }
	string what() // Сообщение об ошибке
	{
		return this->text;
	}
	void ChangeDate(int carnumber, Patron *p); // Изменение даты
	void UpperCase(Patron *p); // Поднятие буквы в верхний регистр
};