#pragma once
#include "BaseException.h"
#include "Patron.h"
class InputException : public BaseException // ����� ��������� ���������� �����
{
private:
	string text = "Error! Input exception!";
public:
	InputException(string _text) { this->text = _text; }
	string what() // ��������� �� ������
	{
		return this->text;
	}
	void ChangeDate(int carnumber, Patron *p); // ��������� ����
	void UpperCase(Patron *p); // �������� ����� � ������� �������
};