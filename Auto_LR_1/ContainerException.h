#pragma once
#include "BaseException.h"
class ContainerException : public BaseException // ����� ��������� ���������� � �����������
{
private:
	string text = "Error! Container exception!";
public:
	ContainerException(string _text) { this->text = _text; }
};