#pragma once
#include <iostream>
using namespace std;

int AutoinStockMenu(int operation, int*, int); // ������� ������ ���� ���� � �������
int language = 0;

void menu(int language, string *menu, string *autost, string *sold, string *all, string *clients, string *total, string *canc0, string*canc1, string *canc2, 
	string *canc3, string *canc4, string *exitt, string *exec, string *viborst, string *soldmenu, string *lst, string *act, string *lan, string *carl) // ��������� �����
{
	switch (language)
	{
	case 1:
		*menu = "\tMenu";
		*autost =  "Auto in stock  ";
		*sold =    "Sold cars      ";
		*all =     "All cars       ";
		*clients = "Clients        ";
		*total =   "Total profit   ";
		*canc0 = "Cancel the last action";
		*canc1 = "6-> Cancel the last action ( Last action was add car in stock )\n";
			*canc2 = "6-> Cancel the last action ( Last action was remove car in stock )\n";
			*canc3 = "6-> Cancel the last action ( Last action was add client-car in sold cars )\n";
			*canc4 = "6-> Cancel the last action ( Last action was remove client-car in sold cars )\n";
			*exitt = "0-> Exit\n";
			*exec = "Execute: ";
			*viborst = "1->Add car\t2->Remove car\n3->Auto list\t0->Exit to the Menu\n";
			*soldmenu = "1->Add client-cars\t2->Remove patron\t\n3->Client-car list\t4->Sold cars\t0->Exit to the Menu\n";
			*lst = "list";
			*act = "Take action first!\n";
			*lan = "Change language to: Russian";
			*carl = "Auto Show";
		break;
	case 2:
		*menu = "\t����";
		*autost =  "���� � ������� ";
		*sold =    "��������� ���� ";
		*all =     "��� ���������� ";
		*clients = "�������        ";
		*total =   "����� �������  ";
		*canc0 = "������ ���������� ��������";
		*canc1 = "6-> ������ ���������� �������� ( ��������� ��������: ���������� ���� � ������� )\n";
		*canc2 = "6-> ������ ���������� �������� ( ��������� ��������: �������� ���� � ������� )\n";
		*canc3 = "6-> ������ ���������� �������� ( ��������� ��������: ���������� �������-���� )\n";
		*canc4 = "6-> ������ ���������� �������� ( ��������� ��������: �������� �������-���� )\n";
		*exitt = "0-> �����\n";
		*exec = "���������: ";
		*viborst = "1->�������� ����\t2->������� ����\n3->������ �����������\t0->����� � ����\n";
		*soldmenu = "1->�������� ������-����\t   2->������� �������\n3->������ ������-����\t   4->��������� ����\t0->����� � ����\n";
		*lst = "������";
		*act = "���������� ��������� ��������!\n";
		*lan = "�������� ���� ��: ����������";
		*carl = "���������";
			break;
	case 0:
		return;
	}
	system("CLS");
}