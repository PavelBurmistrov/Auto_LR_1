#pragma once
#include <iostream>
#include <string>
#include "Profit.h"
using namespace std;
class Auto : public Profit // ����� ���������� ����������� �� ������������ ������ �������
{
public:
	Auto();
	int VIN; // VIN ����
	string Brand; // ����� ����������
	string Model; // ������ ����������
	int Year; // ��� ������� ���������
};