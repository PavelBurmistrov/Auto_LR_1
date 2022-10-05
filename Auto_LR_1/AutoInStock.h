#pragma once
#include "Auto.h"
#include <deque>
#include "Profit.h"
#include <fstream>
#include <iostream>
using namespace std;
class AutoInStock : public Auto // ����� ����������� � ������� ����������� �� ������ ����������
{
private:
	int DayOfPurchase;
	int MonthOfPurchase;
	deque<AutoInStock> SortByCost(deque<AutoInStock> cars); // ���������� ���� �� ���� �� �����������
	deque<AutoInStock> SortByCost2(deque<AutoInStock> cars); // ���������� ���� �� ���� �� ��������
	deque<AutoInStock> sortbyBrand(deque<AutoInStock> cars); // ���������� ���� �� ����� �� �����������
	deque<AutoInStock> sortbyBrand2(deque<AutoInStock> cars); // ���������� ���� �� ����� �� ��������
	deque<AutoInStock> SortListOfCars(deque<AutoInStock> cars); // ���������� ����������� �� �.�. �� ������������
	deque<AutoInStock> SortListOfCars2(deque<AutoInStock> cars); // ���������� ����������� �� �.�.�� ��������
	deque<AutoInStock> SortByPurchase(deque<AutoInStock> cars); // ���������� ���� �� ���� ������� �� �����������
	deque<AutoInStock> SortByPurchase2(deque<AutoInStock> cars);  // ���������� ���� �� ���� ������� �� ��������
public:
	friend ofstream& operator << (ofstream &out, const AutoInStock &car); // ������ �� ����� ���� � �������
	friend ifstream& operator >> (ifstream& in, AutoInStock& car); // ���� � ���� �����������
	friend ostream& operator < (ostream &out, AutoInStock &cars); // ����� ����������� �� �����
	void Cout(deque<AutoInStock> cars); // ����� ���� �� �����
	double ConverterFromRubleToDollar(); // ��������� �� BYN � �������
	int NumberOfAddedCars(int language); // ���������� ����������� ����
	void DeleteCar(int * indexofremovecar, int language); // �������� ����������
	void add_car_to_AutoInStock(int NumberOfAddedCars, deque<AutoInStock> cars, int language); // ���������� ����������
	void CancelLastActionStock(int opop1, int numbercars, int indexofremovecar); // ������ ���������� �������� (����������, ��������)
	void GetInfoFromFile(int language); // ��������� ���������� �� �����, �����, ����������
	void DisplTotalProfit(); // ����� ������� �� ������ ������� �������
	double profit() override
	{
		return (0 - ruble); 
	} // ������� �������
	void Dayset(int Day); // ���� 
	int Dayget; // ���� ������� ����
	int Monthget; // ���� ������� ����
	int YearOfPurchase; // ���� ������� ����
	int Year; // ���� ������� ����
	double Ruble; // ���� ������� ����
	double ruble;	// ���� ������� ����
	AutoInStock(double ruble) // ����������� � ���������� - ����
	{
		Ruble = ruble;
	}
	AutoInStock(string Brand, string Model) // ����������� 
	{
		this->Brand = Brand;
		this->Model = Model;
	}
	AutoInStock() : Auto() // ����������� �� ���������
	{
	}
	void Display()
	{
		cout << "Price with spare parts BYN: " << Ruble << endl;
	}
};