#pragma once
#include <iostream>
#include <string>
#include "Profit.h"
#include "SoldCars.h"
#include <fstream>
#include <deque>
using namespace std; // ����� ��������, ����������� �� ������ ��������� �����������
class Patron : public SoldCars
{ 
private:
	int n;
	void InputClient(Patron * p, int language); // ����� ����� ������ �������
	void InputDate(Patron * p, int kol); // ����� ����� ���� ������� ����������
	deque <Patron> SearchByClient(deque<Patron>* patrons, int); // ����� �������� �� �� (�� - ������� ��� �������)
	deque <Patron> SearchByBrand(deque<Patron>* patrons, int); // ����� �� ����� ����
	deque <Patron> SearchByYear(deque<Patron>* patrons, int); // ����� �� ���� ������� ����������
	deque<Patron> SearchBy(int operation, deque<Patron> patrons, int language); // ����� ������ ������
public:
	friend ifstream& operator >> (ifstream& in, Patron &patrons); // ������ ������� � ����
	friend ofstream& operator << (ofstream &out, const Patron &patrons); // ������ ������� �� �����
	friend ostream& operator << (ostream &out, const Patron &patrons); // ����� �������-���� �� �����
	friend ostream& operator >= (ostream &out, const Patron &patrons); // ����� ������� �� �����
	friend ostream& operator -= (ostream &out, const Patron &patrons); // ����� ���������� ���������� �� �����
	void add_car_to_SoldCars(int * undo, int language); // ���������� �������, ���������� ����
	int DeleteCarSold(int language); // �������� �������-����
	void CancelLastActionSold(int operation, int index, int delnumb); // ������ ���������� ��������
	void DisplaySoldCars(int language); // ����� ������ ��������� ����
	void GetInfoFromFileSold(int language); // ����� �� ����� ������ ������-����
	Patron ChangeInfo(deque<Patron>* patrons, int * numberer, int language); // ��������� ���������� � �������-����
	string SerName; // ������� �������
	string Name; // ���
	string Patronymic; // ��������
	string Adress; // ������
	int NumberOfCars; // ���������� ����������� �������
	SoldCars *cars; // ���������� ������������� �������
	void Metod(int i) // ���������� ������ ��� ������� �����������
	{
		this->n = i;
		cars = new SoldCars[n];
	}
	~Patron() 
	{
		//delete cars;
	}
};