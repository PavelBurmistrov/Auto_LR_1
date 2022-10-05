#pragma once
#include <fstream>
#include "Patron.h"
#include "SoldCars.h"
#include <deque>
#include "AutoInStock.h";
#include <exception>
using namespace std;

template <class T>
class FileManager
{
private:
	ofstream fout;
	string path;
	ifstream fin;
	// Установка языка интерфейса
	void menka(int language, string *bmy, string *dt, string *pr)
	{
		if (language == 1)
		{
			*bmy = "Brand Model Year: ";
			*dt = "Date of purchase dd.mm.yy: ";
			*pr = "Price in BYN: ";
		}
		else {
			*bmy = "Марка Модель Год выпуска: ";
			*dt = "Дата покупки дд.мм.гг: ";
			*pr = "Стоимость в BYN: ";
		}
	}
public:
	
	FileManager(string path)
	{
		this->path = path;
		//fin.exceptions(ifstream::badbit | ifstream::failbit); // Специфика ифстрима
		try
		{
			this->fin.open(this->path); // Открытие файла
		}
		catch (const ifstream:: failure & ex)
		{
			cout << ex.what() << endl;
			cout << ex.code() << endl;
			cout << "File open error :(" << endl;
			system("pause");
		}
	}
	
	void read(deque<T> *patrons) // Чтение из файла
	{
		T p;
		while (this->fin >> p)
		{
			(*patrons).push_back(p);
		}
	}

	

	void WriteNewAutoInStock(int NumberOfAddedCars, deque<AutoInStock> cars, int VIN, int language) // Запись в файл авто в наличии с вводом
	{
		string bmy, dt, pr;
		menka(language, &bmy, &dt, &pr);
		fout.open(path, ofstream::app);
		if (!fout.is_open())
		{
			cout << "File not open!";
		}
		else
		{
			for (int count = 0; count < NumberOfAddedCars; count++)
			{
				cout << bmy; // Ввод информации по автомобилям
				cin >> cars[count].Brand >> cars[count].Model >> cars[count].Year;
				cout << dt;
				cin >> cars[count].Dayget >> cars[count].Monthget >> cars[count].YearOfPurchase;
				cout << pr;
				cin >> cars[count].ruble;
				cars[count].VIN = VIN++;
				fout << cars[count] << endl;
			}
			fout.close();  // Закрытие файла
		}
	}

	void write(T temp) // Запись в файл
	{
		fout.open(path, ofstream::app);
		if (!fout.is_open())
		{
			cout << "File not open!";
		}
		else
		{
			{
				fout << temp;
			}
		}
	}
	
	void writeDeque(deque<T> temp) // Запись дека в файл
	{
		fout.open(this->path);
		if (!fout.is_open())
		{
			cout << "File not open!";
		}
		else
		{
			for (int i = 0; i < temp.size(); i++)
			{
				fout << temp[i];
			}
		}
	}

	void close() // Закртытие файла
	{
		this->fin.close();
	}
};