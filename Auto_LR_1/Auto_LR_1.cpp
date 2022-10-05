#include <iostream>
#include <locale.h>
#include "Auto.h"
#include "AutoInStock.h"
#include <fstream>
#include "Header.h"
#include "Header2.h"
#include "FileManager.h"
#include <Windows.h>
#include <conio.h>
using namespace std;
string men, autost, sold, all,total, canc0, clients, canc1, canc2, canc3, canc4, exitt, exec, viborst, soldmenu, lst, act, Lan, carl;


char Menu(int *op, int *opop1, int *opop2)  //  Функция отображения главного меню
{	
	char operation;
	cout << men <<"               ";                        cout << "                                 _____________/________                                \n";
	cout << "1-> " << autost << "          ";             cout << "                              /       /           |  \\           \n";
	cout << "2-> " << sold << "              ";				 cout << "	            ______/_______/____________|___\\_      $    \n";
	cout << "3-> " << all << "               ";					 cout << "		  #|            _ " << carl <<"  _       \\   $$\n";
	cout << "4-> " <<  total << "             ";					 cout << "		  #|_________________________________|$$$$\n";
	cout << "5-> " << clients << "                                    \\___/               \\___/         \n";
	if (*op >= 100 && *opop1 == 1)  // Если последняя операция была добавлением авто в наличии, вывести подсказку
		cout << canc1;
	else if (*op >= 100 && *opop1 == 3) // Если последняя операция была удаление авто в наличии, вывести подсказку
		cout << canc2;
	else if (*op > 0 && *op < 100 && *opop2 == 1) // Если последняя операция была добавлением клиента-авто, вывести подсказку
		cout << canc3;
	else if (*op > 0 && *op < 100 && *opop2 == 2) // Если последняя операция была удалением клиента-авто, вывести подсказку
		cout << canc4;
	else cout << "6-> " << canc0 << "\n";
	cout << "7-> " << Lan << "\n";
	cout << exitt;
	cout << exec;	
	cin >> operation;  // Ввод выбора операции
	if (operation > '8' || operation < '0') system("CLS"); // Очистка консоли при некорректном вводе
	return operation;  // Возврат введенной операции
}

int width = 15;
int height = 1;
int x = 0;
int y = 0;
string dd = "                                _____________/________                         ";
string cc = "\n                               /       /           |  \\           \n";
string pp = "		        ______/_______/____________|___\\_      $    \n";
string mm = "		      #|            _            _       \\   $$\n";
string kk = "		      #|_________________________________|$$$$\n";
string ll ="                            \\___/              \\___/ \n";

enum eDirection { STOP = 0, LEFT, RIGHT};
eDirection dir;
void Input()
{
	if (_kbhit)
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;  break;
		case 'd':
			dir = RIGHT; break;
		case 'q':
			dir = STOP; break;
		}
	}
}

void logic()
{
	switch (dir)
	{
	case LEFT: x-=3; break;
	case RIGHT: x+=3; break;
	}
}

void draw()
{
	system("CLS");
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i == y && j == x)
			{
				
				cout << dd;
				cout << cc;
				cout << pp;
				cout << mm;
				cout << kk;
				cout << ll;
			}

			else cout << " ";
		}
		cout << endl;
	}
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	setlocale(LC_ALL, "Russian");
	int op = 0; // Инициализируем переменную нулем, если не было совершеной операций
	AutoInStock automibile;
	Patron p;
	language = 0;
	cout << "Choose Language \\ Выберите язык\n";  // Меню выбора языка
	cout << "1->English\n";
	cout << "2->Русский\n";
	cout << "0->Exit \\ Выйти\n";
	cout << "Excecute \\ Выполнить: ";
	do {
		cin >> language;  // Выбор языка интерфейса
	} while (language < 0 || language > 2); // Пока некорректный ввод выбора языка
	if (language == 0) return 0; // Выход из программы
	system("CLS");
	int operation1 = 0, numbercars = 0, opop1 = 0, indexofremovecar = -1, operation2 = 0, opop2 = 0, undo = -1, delnumb = -1; // Объявление переменных
	do {
		menu(language, &men, &autost, &sold, &all, &total, &clients, &canc0, &canc1, &canc2, &canc3, &canc4, &exitt, &exec,
			&viborst, &soldmenu, &lst, &act, &Lan, &carl); // Вызов функции установки языка интерфейса
		char operation;
		do
		{
			operation = Menu(&op, &opop1, &opop2); // Вызов функции отображения меню
		} while (operation > '8' || operation < '0');  // Пока некорректный ввод
		system("CLS");
		
		switch (operation) 
		{
		case '1': // Меню автомобилей в наличии
			do
			{
				do
				{
					cout << "\t\t\t" << autost << "\n"; // Вывод пунктов меню на выбранном языке
					cout << viborst;
					cout << exec;
					cin >> operation1;  // Выбор операции
					if (operation1 > 4 || operation1 < 0) system("CLS");
				} while (operation1 > 4 || operation1 < 0); // Пока некорректный ввод
				if (operation1 == 1)
					numbercars = AutoinStockMenu(operation1, &indexofremovecar, language); 
				else AutoinStockMenu(operation1, &indexofremovecar, language); // Вызов функции выполнения действий с автомобилями в наличии (добавление, удаление и т.д.)
				system("CLS");
				if (operation1 == 1) // Если была произведена операция с авто в наличии, запомнить номер операции для отмены последнего действия
				{
					opop1 = 0; op = 0;
					opop1 = 1;  op += 100;
				}
				else if (operation1 == 2) // Если была произведена операция с клиентами-авто, запомнить номер операции для отмены последнего действия
				{
					opop1 = 0; op = 0;
					opop1 = 3; op += 100;
				}
			} while (operation1 != 0); // Пока не выход из программы 
			break;
		case '8' :
			while (true)
			{
				draw();
				Input();
				logic();
				//system("CLS");
			}
			break;
		case '2': // Меню клиентов, проданных авто
			do
			{
				do
				{
					cout << "\t\t" << sold << endl;
					cout << soldmenu;
					cout << exec;
					cin >> operation2;  // Выбор операции
					if (operation2 > 4 || operation2 < 0) system("CLS");  
				} while (operation2 > 4 || operation2 < 0); // Пока некорректный ввод
				SoldCarsMenuSold(operation2, &undo, &delnumb, language); // Вызов функции выполнения действий с клинтами-авто (добавление, удаление и т.д.)
				system("CLS");
				if (operation2 == 1) // Если была произведена операция с клиентом-авто, запомнить номер операции для отмены последнего действия
				{
					opop2 = 0; op = 0;
					opop2 = 1; op++;
				}
				else if (operation2 == 2) // Если была произведена операция с клиентом-авто, запомнить номер операции для отмены последнего действия
				{
					opop2 = 0; op = 0;
					opop2 = 2; op++;
				}
			} while (operation2 != 0); // Пока не выход из программы
			break;
		case '3': // Вывод на экран всех автомобилей
		{
			deque <Patron> patrons;  
			FileManager<Patron> f("SoldCars.txt");
			f.read(&patrons); // Считывание с файла в дек клиентов
			system("CLS");
			if (language == 1) // Если выбран английский язык
			cout << "----------------------------------" << "Sold Cars" << "-----------------------------------------------------\n";
			else cout << "--------------------------------" << "Проданные авто" << "----------------------------------------------------\n";
			cout << "^VIN  ^Brand            ^Model       ^Year       ^Purchase dd.mm.yy  ^Cost BYN        ^Cost Dollar" << endl;
			for (auto itera = patrons.begin(); itera != patrons.end(); itera++)
				cout >= *itera; // Вывод на экран список проданных авто
			f.close(); // Закрытие файла

			if (language == 1)
				cout << "--------------------------------" << "Auto in Stock" << "----------------------------------------------------\n";
			else cout << "--------------------------------" << "Авто в наличии" << "----------------------------------------------------\n";
			deque <AutoInStock> cars;
			FileManager<AutoInStock> S("AutoInStock.txt");
			S.read(&cars); // Считывание из файла в дек автомобилей в наличии
			for (auto itera = cars.begin(); itera != cars.end(); itera++) 
				cout < *itera; // Вывод на экран автомобилей в наличии
			system("pause");
		}
		break;
		case '4': // Вывод списка клиентов автосалона
		{

			deque <Patron> patrons;
			FileManager<Patron> f("SoldCars.txt");
			f.read(&patrons); // Считывание из файла в дек клиентов авто
			system("CLS");
			cout << "\t\t" << lst << "\n"; int i = 1;
			for (auto itera = patrons.begin(); itera != patrons.end(); itera++)
			{
				cout << "№ " << i << " ";
				i++;
				cout -= *itera; // Вывод на экран список проданных авто
			}
			system("pause");
		}
		break;
		case '5':  // Общая прибыль за определенный период
			automibile.DisplTotalProfit(); break; // Вызов функции меню общей прибыли
		case '0': return 0;
		case '6':
		{
			if (op == 0)
			{
				cout << act;
				system("pause"); break;
			}
			else if (op >= 100) // Если последнее действие было связано с автомобилями в наличии, то 
				automibile.CancelLastActionStock(opop1, numbercars, indexofremovecar); // Вызвать функцию отмены последнего действия с авто в наличии
			else if (op > 0 && op < 100) // Если последнее действие было связано с клиентами-авто, то
				p.CancelLastActionSold(opop2, undo, delnumb);  // Вызвать метод отмены последнего действия с клиентами-авто
			op = 0; opop1 = 0; opop2 = 0;
		}     break;
		case '7': // Изменение языка интерфейса
			if (language == 1) language = 2; 
			else if (language == 2) language = 1;
			break;
		}
		system("CLS");
	} while (true);  // Выполнять до принужденного выхода (case 0: ...)
	return 0;
}