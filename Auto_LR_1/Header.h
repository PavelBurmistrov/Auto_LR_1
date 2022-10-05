#pragma once
#include <iostream>
using namespace std;

int AutoinStockMenu(int operation, int*, int); // Функция вызова меню авто в наличии
int language = 0;

void menu(int language, string *menu, string *autost, string *sold, string *all, string *clients, string *total, string *canc0, string*canc1, string *canc2, 
	string *canc3, string *canc4, string *exitt, string *exec, string *viborst, string *soldmenu, string *lst, string *act, string *lan, string *carl) // Установка языка
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
		*menu = "\tМеню";
		*autost =  "Авто в наличии ";
		*sold =    "Проданные авто ";
		*all =     "Все автомобили ";
		*clients = "Клиенты        ";
		*total =   "Общая прибыль  ";
		*canc0 = "Отмена последнего действия";
		*canc1 = "6-> Отмена последнего действия ( Последнее действие: добавление авто в наличии )\n";
		*canc2 = "6-> Отмена последнего действия ( Последнее действие: удаление авто в наличии )\n";
		*canc3 = "6-> Отмена последнего действия ( Последнее действие: добавление клиента-авто )\n";
		*canc4 = "6-> Отмена последнего действия ( Последнее действие: удаление клиента-авто )\n";
		*exitt = "0-> Выйти\n";
		*exec = "Выполнить: ";
		*viborst = "1->Добавить авто\t2->Удалить авто\n3->Список автомобилей\t0->Выйти в меню\n";
		*soldmenu = "1->Добавить клиент-авто\t   2->Удалить клиента\n3->Список клиент-авто\t   4->Проданные авто\t0->Выход в меню\n";
		*lst = "Список";
		*act = "Необходимо выполнить действие!\n";
		*lan = "Изменить язык на: Английский";
		*carl = "Автосалон";
			break;
	case 0:
		return;
	}
	system("CLS");
}