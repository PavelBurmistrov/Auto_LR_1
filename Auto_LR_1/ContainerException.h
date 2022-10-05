#pragma once
#include "BaseException.h"
class ContainerException : public BaseException // Класс обработки исключений с контейнером
{
private:
	string text = "Error! Container exception!";
public:
	ContainerException(string _text) { this->text = _text; }
};