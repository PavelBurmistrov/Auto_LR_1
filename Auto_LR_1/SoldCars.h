#pragma once
#include "Auto.h"
class SoldCars : public Auto // ����� ��������� ����������� ����������� �� ������ �����������
{
private:
	int DayOfPurchase; // ���� ������� 
	int MonthOfPurchase; 
public:
	double profit() override // ������� ������ � ������� ����������
	{
		return (this->ruble - this->firstPrice);
	}
	double firstPrice; // ��������� ���� � ����������
	int BuyDay; // ���� ������� ���� ��������
	int BuyMonth; // ���� ������� ���� ��������
	int BuyYear; // ���� ������� ���� ��������
	int Dayget; // ���� ������� �����������
	int Monthget; // ���� ������� �����������
	int YearOfPurchase; // ���� ������� �����������
	int Year; // ��� ������� ����������
	double ruble; // ��������� ������� ����������
	double ConverterFromRubleToD(); // ��������� �� BYN � �������
};