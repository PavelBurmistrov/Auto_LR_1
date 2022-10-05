#include "AutoInStock.h"
#include "Patron.h"
#include "FileManager.h"
#include <vector>

void AutoInStock::Dayset(int Day) 
{
	if (Day < 1 || Day > 31)
		cout << "Error!";
	DayOfPurchase = Day;
}

ofstream& operator << (ofstream &out, const AutoInStock &car) // Чтение из файла автомобилей в наличии
{
	out << car.Brand << " " << car.Model << " " << car.Year << " " <<
		car.Dayget << " " << car.Monthget << " " << car.YearOfPurchase << " " << car.ruble << " " << car.VIN << endl;
	return out;
}

ifstream& operator >> (ifstream& in, AutoInStock& car) // Запись авто в наличии в файл
{
	in >> car.Brand >> car.Model >> car.Year >> car.Dayget >> car.Monthget >> car.YearOfPurchase >> car.ruble >> car.VIN;
	if (!in)
	{
		car = AutoInStock();
	}
	return in;
}

ostream& operator < (ostream &out, AutoInStock &cars) // Вывод автомобиля в наличии
{
	string c, m;
	int dl = cars.Brand.length() + cars.Model.length();
	if (cars.Dayget < 10)  c = "0"; else c = "";
	if (cars.Monthget < 10)  m = ".0"; else m = ".";
	out  << "|"<<cars.VIN;
	if (cars.VIN < 10) out << "    ";
	if (cars.VIN > 9) out << "   ";
	out << "|" << cars.Brand;
	for (int i = 0; i < 17 - cars.Brand.length(); i++) out << " ";
	out <<"|" << cars.Model;
	for (int i = 0; i < 12 - cars.Model.length(); i++)
		out << " ";
	out << "|" << cars.Year << "       "
		"|" << c << cars.Dayget << m << cars.Monthget
		<< "." << cars.YearOfPurchase << "         |BYN: " << cars.ruble; 
	if (cars.ruble < 1000) dl = 7;
	if (cars.ruble > 1000) dl = 6;
	if (cars.ruble > 10000) dl = 5;
	if (cars.ruble > 100000) dl = 4;
	if (cars.ruble > 1000000) dl = 3;
	for (int i = 0; i < dl; i++) out << " ";
	out << " |$" << cars.ConverterFromRubleToDollar() << endl;
	return out;
}

double AutoInStock :: ConverterFromRubleToDollar() // Конвертирование BYN в доллары
{
	double dollar = ruble / 2.59;
	return dollar;
}

int AutoInStock::NumberOfAddedCars(int language)  // Ввод количества добавленных авто
{
	int NumberOfAddedCars = 0;
	string num = "Number of added cars: ";
	if (language == 2) num = "Количество добавляемых авто: ";

	do
	{
		cout << num;
		cin >> NumberOfAddedCars;
		if (NumberOfAddedCars < 0) system("CLS");
	} while (NumberOfAddedCars < 0);
	return NumberOfAddedCars;
}

void AutoInStock::DeleteCar(int *indexofremovecar, int language) // Удаление автомобиля из списка
{
	AutoInStock autom;
	deque <AutoInStock> cars;
	FileManager<AutoInStock> f("AutoInStock.txt");
	int numberToDelete;
	string lst = "\t\t\t\t\t\tAuto list\n";
	string car = "Car number to delete: ";
	if (language == 2)
	{
		car = "Номер авто для удаления: ";
	}
	f.read(&cars); // Чтение списка автомобилей из файла
	auto iter = cars.begin(); // Инициализация итератора на начало списка
	cout << lst;
	autom.Cout(cars); // Вывод списка авто в наличии
	cout << car;
	do
	{   
		cin >> numberToDelete; // Ввод номера авто для удаления
	} while (numberToDelete < 1 || numberToDelete > cars.size());
	FileManager<AutoInStock> W("Basket.txt");
	W.write(cars[numberToDelete - 1]); // Запись удаленного автомобиля в корзину
	cars.erase(iter + numberToDelete - 1); // Удаление автомобиля
	f.writeDeque(cars); // Запись списка авто в файл
	cars.clear(); // Очистка списка
	(*indexofremovecar) = numberToDelete - 1; // Запоминаем индекс удаленного авто
}

void AutoInStock::add_car_to_AutoInStock(int NumberOfAddedCars, deque <AutoInStock> cars, int language) // Добавление автомобилей в спикок "В наличии" 
{
	string was = "Car was added!";
	if (language == 2)
		if (NumberOfAddedCars > 1)
			was = "Автомобиль был добавлен!"; else was = "Автомобили были добавлены!";
	deque <AutoInStock> carsa;
	FileManager<AutoInStock> f("AutoInStock.txt");
	int vin = 1, von = 1; // Инициализация VIN авто
	f.read(&carsa); // Чтение списка авто из файла
	if (!carsa.empty()) // Если список не пуст
		vin = ++carsa[carsa.size() - 1].VIN; // Инициализировать VIN авто больше на 1 имеющегося 
	deque <Patron> patrons;
	FileManager<Patron> Q("SoldCars.txt");
	Q.read(&patrons); // Чтение клиентов из файла
	if (!patrons.empty())
		von = ++patrons[patrons.size() - 1].cars[patrons[patrons.size() - 1].NumberOfCars - 1].VIN; // Проверка VIN
	int max = von;
	if (vin > von) max = vin; // Если VIN последнего авто в наличии Ю > проданного авто инициализировать максимальным
	f.WriteNewAutoInStock(NumberOfAddedCars, cars, max, language); // Запись авто в наличии
	cout << was << endl;
	system("pause");
}

void AutoInStock::DisplTotalProfit() // Вывод общей прибыли
{
	int choose;
	cout << "\t\tTotal profit\n";
	cout << "1->Monthly profit\n";
	cout << "2-> Profit for the year\n";
	cout << "3-> Statistics for the year\n";
	cout << "Your choice: ";
	cin >> choose;
	switch (choose)
	{
	case 1: // Подсчет общей прибыли за определенный месяц
	{
		int year, month;
		double fullprofit = 0;
		system("CLS");
		cout << "\t\tMonthly profit\n";
		cout << "Choose the year: "; cin >> year; // Ввод года 
		cout << "Choose the month: "; cin >> month; // Ввод месяца
		deque <Patron> patrons;
		FileManager<Patron> f("SoldCars.txt");
		f.read(&patrons); // Чтение клиентов из файла
		for (int i = 0; i < patrons.size(); i++)
		{
			for (int j = 0; j < patrons[i].NumberOfCars; j++)
				if (year == patrons[i].cars[j].YearOfPurchase && month == patrons[i].cars[j].Monthget)
					fullprofit += patrons[i].cars[j].profit(); // Поиск авто проданных за определенный месяц
		}
		cout << "Profit for the month: " << fullprofit << " BYN" << endl;
		for (int i = 0; i < patrons.size(); i++)
		{
			for (int j = 0; j < patrons[i].NumberOfCars; j++)
				if (year == patrons[i].cars[j].YearOfPurchase && month == patrons[i].cars[j].Monthget)
					cout << patrons[i]; // Вывод клиенов, купивших авто в запрошенный месяц
		}
		if (fullprofit == 0) // Если прибыль == 0, вывести сообщение
		{
			cout << "Empty :(((\n";
		}
		system("pause");
	}
	break;
	case 2: // Подсчет общей прибыли за определенный год
	{
		int year;
		double fullprofit = 0;
		system("CLS");
		cout << "\t\tAnnual profit\n";
		cout << "Choose the year: "; cin >> year; // Ввод года
		deque <Patron> patrons;
		FileManager<Patron> f("SoldCars.txt");
		f.read(&patrons); // Чтение коиентов из файла
		for (int i = 0; i < patrons.size(); i++) // Поиск авто проданных за определенный год
		{
			for (int j = 0; j < patrons[i].NumberOfCars; j++)
				if (year == patrons[i].cars[j].YearOfPurchase)
					fullprofit += patrons[i].cars[j].profit();
		}
		cout << "Profit for the year: " << fullprofit << " BYN" << endl;
		for (int i = 0; i < patrons.size(); i++) // Поиск авто проданных за определенный год
		{
			for (int j = 0; j < patrons[i].NumberOfCars; j++)
				if (year == patrons[i].cars[j].YearOfPurchase)
					cout << patrons[i];
		}
		if (fullprofit == 0) 
		{
			cout << "Empty :(((\n";
		}
		system("pause");
	}break;
	case 3: // Подсчет общей прибыли за определенный год + график + лучшая сделка
	{
		int year;
		vector <int> months = { 0,0,0,0,0,0,0,0,0,0,0,0 }; // Массив прибыли за месяц
		int max = months[0];
		vector<string> mon = { "Jan.","Feb.","Mar.","Apr.","May.","Jun.","Jul.","Aug.","Sep.","Oct.","Nov.","Dec." }; // Названия месяцев
		double fullprofit = 0;
		system("CLS");
		cout << "\t\tAnnual profit\n";
		cout << "Choose the year: "; cin >> year; // Выбор года
		deque <Patron> patrons;
		FileManager<Patron> f("SoldCars.txt");
		f.read(&patrons); // Чтение клиентов из файла
		int maxi = patrons[0].cars[0].profit(), numi = 0;
		for (int i = 0; i < patrons.size(); i++)
		{
			for (int j = 0; j < patrons[i].NumberOfCars; j++) // Поиск авто проданных за определенный месяц год
				if (year == patrons[i].cars[j].YearOfPurchase)
				{
					if (patrons[i].cars[j].profit() > maxi)
					{
						maxi = patrons[i].cars[j].profit(); // Поиск максимально выгодной сделки
						numi = i;
					}
					months[patrons[i].cars[j].Monthget - 1] += patrons[i].cars[j].profit(); // Добавление прибыли за месяц
					if (months[patrons[i].cars[j].Monthget - 1] > max) max = months[patrons[i].cars[j].Monthget - 1];
				}
		}
		cout << "BYN, '#' - One thousand     '.' - One hundred \n";
		for (int i = 0; i < max / 1000 + 10; i++)
			cout << "_";
		cout << endl;
		for (int i = 0; i < 12; i++)
		{
			cout << mon[i] << "|";
			if (months[i] < 0) cout << "->" << months[i]; // Вывод на экран графика продаж
			else
				for (int j = 0; j < months[i] / 1000; j++)
					cout << "#";
			if (months[i] % 1000 > 0)
				for (int k = 0; k < months[i] % 1000 / 100; k++) cout << ".";
			if (months[i] > 0)
				cout << " <-" << months[i];
			cout << endl;
		}
		cout << "\n\t\t!Best deal of " << year << "!\n";
		cout << patrons[numi]; // Вывод лучшей сделки за год
		f.close();
		system("pause");
	} break;
	default: return;
	}
	return;
}

deque <AutoInStock> AutoInStock:: SortByCost(deque <AutoInStock> cars) // Сортировка автомобилей по цене по убыванию
{
	AutoInStock b;
	for (int i = 0; i < cars.size(); i++)
	{
		for (int j = 0; j < cars.size() - 1; j++)
			if (cars[j].ruble < cars[j + 1].ruble) swap(cars[j], cars[j + 1]);
	}
	return cars;
}
deque <AutoInStock> AutoInStock::SortByCost2(deque <AutoInStock> cars) // Сортировка автомобилей по цене по возрастанию
{
	AutoInStock b;
	for (int i = 0; i < cars.size(); i++)
	{
		for (int j = 0; j < cars.size() - 1; j++)
			if (cars[j].ruble > cars[j + 1].ruble)	swap(cars[j], cars[j + 1]);
	}
	return cars;
}
deque<AutoInStock> AutoInStock::sortbyBrand(deque<AutoInStock> cars) // Сортировка по марке по возрастанию
{
	for (int i = 0; i < cars.size() - 1; i++)
		for (int j = i + 1; j < cars.size(); j++)
		{
			if (strcmp(cars[i].Brand.c_str(), cars[j].Brand.c_str()) > 0) swap(cars[i], cars[j]);
		}
	return cars;
}
deque<AutoInStock> AutoInStock::sortbyBrand2(deque<AutoInStock> cars) // Сортировка по марке по убыванию
{
	for (int i = 0; i < cars.size() - 1; i++)
		for (int j = i + 1; j < cars.size(); j++)
		{
			if (strcmp(cars[i].Brand.c_str(), cars[j].Brand.c_str()) < 0) swap(cars[i], cars[j]);
		}
	return cars;
}

deque <AutoInStock> AutoInStock::SortListOfCars(deque <AutoInStock> cars) // Сортировка авто по году выпуска по возрастанию
{
	AutoInStock b;
	for (int i = 0; i < cars.size(); i++)
	{
		for (int j = 0; j < cars.size() - 1; j++)
			if (cars[j].Year < cars[j + 1].Year)
				swap(cars[j], cars[j + 1]);
	}
	return cars;
}
deque <AutoInStock> AutoInStock::SortListOfCars2(deque <AutoInStock> cars) // Сортировка авто по году выпуска по убыванию
{
	AutoInStock b;
	for (int i = 0; i < cars.size(); i++)
	{
		for (int j = 0; j < cars.size() - 1; j++)
			if (cars[j].Year > cars[j + 1].Year)
				swap(cars[j], cars[j + 1]);
	}
	return cars;
}


void AutoInStock::Cout(deque <AutoInStock> cars) // Вывод списка авто в наличии
{
	cout << "^№ ^VIN  ^Brand            ^Model       ^Year       ^Purchase dd.mm.yy  ^Cost BYN        ^Cost Dollar" << endl;
		int i = 1;
		for (auto iter = cars.begin(); iter != cars.end(); iter++)
		{
			cout << "|" << i << " ";
			i++;
			cout < *iter;
		}
}

deque <AutoInStock> AutoInStock::SortByPurchase(deque <AutoInStock> cars) // Сортировка списка "Авто в наличии" по дате покупки автомобиля автосалоном по возрастанию
{
	AutoInStock b;
	for (int i = 0; i < cars.size(); i++)
	{
		for (int j = 0; j < cars.size() - 1; j++)
			if (cars[j].YearOfPurchase < cars[j + 1].YearOfPurchase) // Сортируем по году
				swap(cars[j], cars[j + 1]);
			else if (cars[j].YearOfPurchase == cars[j + 1].YearOfPurchase) // Если год одинаков, сортируем по месяцу
			{
				if (cars[j].Monthget < cars[j + 1].Monthget)
					swap(cars[j], cars[j + 1]);
				else if (cars[j].Monthget == cars[j + 1].Monthget)
				{
					if (cars[j].Dayget < cars[j + 1].Dayget)
						swap(cars[j], cars[j + 1]);
				}
			}
	}
	return cars;
}
deque <AutoInStock> AutoInStock::SortByPurchase2(deque <AutoInStock> cars) // Сортировка списка "Авто в наличии" по дате покупки автомобиля автосалоном по убыванию
{
	AutoInStock b;
	for (int i = 0; i < cars.size(); i++)
	{
		for (int j = 0; j < cars.size() - 1; j++)
			if (cars[j].YearOfPurchase > cars[j + 1].YearOfPurchase) // Сортируем по году
				swap(cars[j], cars[j + 1]);
			else if (cars[j].YearOfPurchase == cars[j + 1].YearOfPurchase) // Если год одинаков, сортируем по месяцу
			{
				if (cars[j].Monthget > cars[j + 1].Monthget)
					swap(cars[j], cars[j + 1]);
				else if (cars[j].Monthget == cars[j + 1].Monthget)
				{
					if (cars[j].Dayget > cars[j + 1].Dayget)
						swap(cars[j], cars[j + 1]);
				}
			}
	}
	return cars;
}

void AutoInStock::CancelLastActionStock(int opop1, int numbercars, int indexofremovecar) // Отмена последнего действия
{
	if (opop1 == 1) // Отмена добавления автомобиля
	{
		deque <AutoInStock> cars;
		FileManager<AutoInStock> f("AutoInStock.txt");
		f.read(&cars); // Чтение автомобилей в наличии из файла
		for (int kol = 0; kol < numbercars; kol++)
		{
			cars.pop_back(); // Удаление необходимых автомобилей
		}
		f.writeDeque(cars); // Запись измененного списка
		cars.clear();
	}
	else if (opop1 == 3) // Отмена удаления авто в наличии
	{
		FileManager<AutoInStock> r("Basket.txt");
		deque <AutoInStock> cars;
		r.read(&cars); // Чтение авто из корзины
		deque <AutoInStock> carsa;
		FileManager<AutoInStock> f("AutoInStock.txt");
		f.read(&carsa); // Чтение авто в наличии
		auto iter = carsa.begin() + indexofremovecar; // Инициализация индекса на удаленный элемент
		carsa.insert(iter, cars[cars.size() - 1]); // Вставка удаленного автомобиля
		f.writeDeque(carsa); // Запись в файл
		cars.pop_back(); // Удаления авто из корзины
		r.writeDeque(cars); // Запись преобр. списка в корзину
	}
}

void AutoInStock::GetInfoFromFile(int language) // Чтение информации из файла вывод, сортировка
{
	system("CLS");
	deque <AutoInStock> cars;
	FileManager<AutoInStock> f("AutoInStock.txt");
	f.read(&cars); // Чтение автомобилей в налчии из файла
	string lst = "\t\t\t\t\tAuto list\n";
	string sort = "Sort by:    1->Year    2->Purchase date    3->Cost    4->Brand    0->Exit to the Menu\n";
	string sor = "Sort: ";
	if (language == 2)
	{
		lst = "\t\t\t\t\tСписок автомобилей\n";
		sort = "Сортировать по:    1->Году    2->Дате покупки    3->Стоимости    4->Марке    0->Выйти в меню\n";
		sor = "Сортировать: ";
	}
	cout << lst;
	Cout(cars); // Вывод списка объектов
	int year = 2, pur = 2, cost = 2, brand = 2;
	do
	{
		cout << sort; // Выбор сортировки списка авто
		int Number;
		do
		{
			cout << sor; cin >> Number;
		} while (Number < 0 || Number > 4);

		switch (Number)
		{
		case 0:return;
		case 1:
			if (year % 2 == 0)
				cars = SortListOfCars(cars); // Сортировка автомобилей по г.в. по возрастванию
			else cars = SortListOfCars2(cars); // Сортировка автомобилей по г.в.по убыванию
			year++;
			system("CLS");
			cout << lst;
			Cout(cars);
			break;
		case 2:
			if (pur % 2 == 0)
				cars = SortByPurchase(cars); // Сортировка авто по дате покупки по возрастанию
			else cars = SortByPurchase2(cars); // Сортировка авто по дате покупки по убыванию
			pur++;
			system("CLS");
			cout << lst;
			Cout(cars);
			break;
		case 3:
			if (cost % 2 == 0)
				cars = SortByCost(cars); // Сортировка авто по цене по возрастанию
			else cars = SortByCost2(cars); // Сортировка авто по цене по убыванию
			cost++;
			system("CLS");
			cout << lst;
			Cout(cars);
			break;
		case 4:
			if (brand % 2 == 0)
				cars = sortbyBrand(cars); // Сортировка авто по марке по возрастанию
			else cars = sortbyBrand2(cars); // Сортировка авто по марке по убыванию
			brand++;
			system("CLS");
			cout << lst;
			Cout(cars);
			break;
		default:
			break;
		}
	} while (true);
}