#pragma once
#include <iostream>
using namespace std;
class BaseException : public exception
{
protected:
	// ���������� � ���������� - ����� ��� ���� ����������� �������
	string text;

public:
	// ������ ����������� �������, ������� ������� ����� ����������
	virtual string what() = 0;
};