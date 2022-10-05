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

ofstream& operator << (ofstream &out, const AutoInStock &car) // ������ �� ����� ����������� � �������
{
	out << car.Brand << " " << car.Model << " " << car.Year << " " <<
		car.Dayget << " " << car.Monthget << " " << car.YearOfPurchase << " " << car.ruble << " " << car.VIN << endl;
	return out;
}

ifstream& operator >> (ifstream& in, AutoInStock& car) // ������ ���� � ������� � ����
{
	in >> car.Brand >> car.Model >> car.Year >> car.Dayget >> car.Monthget >> car.YearOfPurchase >> car.ruble >> car.VIN;
	if (!in)
	{
		car = AutoInStock();
	}
	return in;
}

ostream& operator < (ostream &out, AutoInStock &cars) // ����� ���������� � �������
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

double AutoInStock :: ConverterFromRubleToDollar() // ��������������� BYN � �������
{
	double dollar = ruble / 2.59;
	return dollar;
}

int AutoInStock::NumberOfAddedCars(int language)  // ���� ���������� ����������� ����
{
	int NumberOfAddedCars = 0;
	string num = "Number of added cars: ";
	if (language == 2) num = "���������� ����������� ����: ";

	do
	{
		cout << num;
		cin >> NumberOfAddedCars;
		if (NumberOfAddedCars < 0) system("CLS");
	} while (NumberOfAddedCars < 0);
	return NumberOfAddedCars;
}

void AutoInStock::DeleteCar(int *indexofremovecar, int language) // �������� ���������� �� ������
{
	AutoInStock autom;
	deque <AutoInStock> cars;
	FileManager<AutoInStock> f("AutoInStock.txt");
	int numberToDelete;
	string lst = "\t\t\t\t\t\tAuto list\n";
	string car = "Car number to delete: ";
	if (language == 2)
	{
		car = "����� ���� ��� ��������: ";
	}
	f.read(&cars); // ������ ������ ����������� �� �����
	auto iter = cars.begin(); // ������������� ��������� �� ������ ������
	cout << lst;
	autom.Cout(cars); // ����� ������ ���� � �������
	cout << car;
	do
	{   
		cin >> numberToDelete; // ���� ������ ���� ��� ��������
	} while (numberToDelete < 1 || numberToDelete > cars.size());
	FileManager<AutoInStock> W("Basket.txt");
	W.write(cars[numberToDelete - 1]); // ������ ���������� ���������� � �������
	cars.erase(iter + numberToDelete - 1); // �������� ����������
	f.writeDeque(cars); // ������ ������ ���� � ����
	cars.clear(); // ������� ������
	(*indexofremovecar) = numberToDelete - 1; // ���������� ������ ���������� ����
}

void AutoInStock::add_car_to_AutoInStock(int NumberOfAddedCars, deque <AutoInStock> cars, int language) // ���������� ����������� � ������ "� �������" 
{
	string was = "Car was added!";
	if (language == 2)
		if (NumberOfAddedCars > 1)
			was = "���������� ��� ��������!"; else was = "���������� ���� ���������!";
	deque <AutoInStock> carsa;
	FileManager<AutoInStock> f("AutoInStock.txt");
	int vin = 1, von = 1; // ������������� VIN ����
	f.read(&carsa); // ������ ������ ���� �� �����
	if (!carsa.empty()) // ���� ������ �� ����
		vin = ++carsa[carsa.size() - 1].VIN; // ���������������� VIN ���� ������ �� 1 ���������� 
	deque <Patron> patrons;
	FileManager<Patron> Q("SoldCars.txt");
	Q.read(&patrons); // ������ �������� �� �����
	if (!patrons.empty())
		von = ++patrons[patrons.size() - 1].cars[patrons[patrons.size() - 1].NumberOfCars - 1].VIN; // �������� VIN
	int max = von;
	if (vin > von) max = vin; // ���� VIN ���������� ���� � ������� � > ���������� ���� ���������������� ������������
	f.WriteNewAutoInStock(NumberOfAddedCars, cars, max, language); // ������ ���� � �������
	cout << was << endl;
	system("pause");
}

void AutoInStock::DisplTotalProfit() // ����� ����� �������
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
	case 1: // ������� ����� ������� �� ������������ �����
	{
		int year, month;
		double fullprofit = 0;
		system("CLS");
		cout << "\t\tMonthly profit\n";
		cout << "Choose the year: "; cin >> year; // ���� ���� 
		cout << "Choose the month: "; cin >> month; // ���� ������
		deque <Patron> patrons;
		FileManager<Patron> f("SoldCars.txt");
		f.read(&patrons); // ������ �������� �� �����
		for (int i = 0; i < patrons.size(); i++)
		{
			for (int j = 0; j < patrons[i].NumberOfCars; j++)
				if (year == patrons[i].cars[j].YearOfPurchase && month == patrons[i].cars[j].Monthget)
					fullprofit += patrons[i].cars[j].profit(); // ����� ���� ��������� �� ������������ �����
		}
		cout << "Profit for the month: " << fullprofit << " BYN" << endl;
		for (int i = 0; i < patrons.size(); i++)
		{
			for (int j = 0; j < patrons[i].NumberOfCars; j++)
				if (year == patrons[i].cars[j].YearOfPurchase && month == patrons[i].cars[j].Monthget)
					cout << patrons[i]; // ����� �������, �������� ���� � ����������� �����
		}
		if (fullprofit == 0) // ���� ������� == 0, ������� ���������
		{
			cout << "Empty :(((\n";
		}
		system("pause");
	}
	break;
	case 2: // ������� ����� ������� �� ������������ ���
	{
		int year;
		double fullprofit = 0;
		system("CLS");
		cout << "\t\tAnnual profit\n";
		cout << "Choose the year: "; cin >> year; // ���� ����
		deque <Patron> patrons;
		FileManager<Patron> f("SoldCars.txt");
		f.read(&patrons); // ������ �������� �� �����
		for (int i = 0; i < patrons.size(); i++) // ����� ���� ��������� �� ������������ ���
		{
			for (int j = 0; j < patrons[i].NumberOfCars; j++)
				if (year == patrons[i].cars[j].YearOfPurchase)
					fullprofit += patrons[i].cars[j].profit();
		}
		cout << "Profit for the year: " << fullprofit << " BYN" << endl;
		for (int i = 0; i < patrons.size(); i++) // ����� ���� ��������� �� ������������ ���
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
	case 3: // ������� ����� ������� �� ������������ ��� + ������ + ������ ������
	{
		int year;
		vector <int> months = { 0,0,0,0,0,0,0,0,0,0,0,0 }; // ������ ������� �� �����
		int max = months[0];
		vector<string> mon = { "Jan.","Feb.","Mar.","Apr.","May.","Jun.","Jul.","Aug.","Sep.","Oct.","Nov.","Dec." }; // �������� �������
		double fullprofit = 0;
		system("CLS");
		cout << "\t\tAnnual profit\n";
		cout << "Choose the year: "; cin >> year; // ����� ����
		deque <Patron> patrons;
		FileManager<Patron> f("SoldCars.txt");
		f.read(&patrons); // ������ �������� �� �����
		int maxi = patrons[0].cars[0].profit(), numi = 0;
		for (int i = 0; i < patrons.size(); i++)
		{
			for (int j = 0; j < patrons[i].NumberOfCars; j++) // ����� ���� ��������� �� ������������ ����� ���
				if (year == patrons[i].cars[j].YearOfPurchase)
				{
					if (patrons[i].cars[j].profit() > maxi)
					{
						maxi = patrons[i].cars[j].profit(); // ����� ����������� �������� ������
						numi = i;
					}
					months[patrons[i].cars[j].Monthget - 1] += patrons[i].cars[j].profit(); // ���������� ������� �� �����
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
			if (months[i] < 0) cout << "->" << months[i]; // ����� �� ����� ������� ������
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
		cout << patrons[numi]; // ����� ������ ������ �� ���
		f.close();
		system("pause");
	} break;
	default: return;
	}
	return;
}

deque <AutoInStock> AutoInStock:: SortByCost(deque <AutoInStock> cars) // ���������� ����������� �� ���� �� ��������
{
	AutoInStock b;
	for (int i = 0; i < cars.size(); i++)
	{
		for (int j = 0; j < cars.size() - 1; j++)
			if (cars[j].ruble < cars[j + 1].ruble) swap(cars[j], cars[j + 1]);
	}
	return cars;
}
deque <AutoInStock> AutoInStock::SortByCost2(deque <AutoInStock> cars) // ���������� ����������� �� ���� �� �����������
{
	AutoInStock b;
	for (int i = 0; i < cars.size(); i++)
	{
		for (int j = 0; j < cars.size() - 1; j++)
			if (cars[j].ruble > cars[j + 1].ruble)	swap(cars[j], cars[j + 1]);
	}
	return cars;
}
deque<AutoInStock> AutoInStock::sortbyBrand(deque<AutoInStock> cars) // ���������� �� ����� �� �����������
{
	for (int i = 0; i < cars.size() - 1; i++)
		for (int j = i + 1; j < cars.size(); j++)
		{
			if (strcmp(cars[i].Brand.c_str(), cars[j].Brand.c_str()) > 0) swap(cars[i], cars[j]);
		}
	return cars;
}
deque<AutoInStock> AutoInStock::sortbyBrand2(deque<AutoInStock> cars) // ���������� �� ����� �� ��������
{
	for (int i = 0; i < cars.size() - 1; i++)
		for (int j = i + 1; j < cars.size(); j++)
		{
			if (strcmp(cars[i].Brand.c_str(), cars[j].Brand.c_str()) < 0) swap(cars[i], cars[j]);
		}
	return cars;
}

deque <AutoInStock> AutoInStock::SortListOfCars(deque <AutoInStock> cars) // ���������� ���� �� ���� ������� �� �����������
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
deque <AutoInStock> AutoInStock::SortListOfCars2(deque <AutoInStock> cars) // ���������� ���� �� ���� ������� �� ��������
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


void AutoInStock::Cout(deque <AutoInStock> cars) // ����� ������ ���� � �������
{
	cout << "^� ^VIN  ^Brand            ^Model       ^Year       ^Purchase dd.mm.yy  ^Cost BYN        ^Cost Dollar" << endl;
		int i = 1;
		for (auto iter = cars.begin(); iter != cars.end(); iter++)
		{
			cout << "|" << i << " ";
			i++;
			cout < *iter;
		}
}

deque <AutoInStock> AutoInStock::SortByPurchase(deque <AutoInStock> cars) // ���������� ������ "���� � �������" �� ���� ������� ���������� ����������� �� �����������
{
	AutoInStock b;
	for (int i = 0; i < cars.size(); i++)
	{
		for (int j = 0; j < cars.size() - 1; j++)
			if (cars[j].YearOfPurchase < cars[j + 1].YearOfPurchase) // ��������� �� ����
				swap(cars[j], cars[j + 1]);
			else if (cars[j].YearOfPurchase == cars[j + 1].YearOfPurchase) // ���� ��� ��������, ��������� �� ������
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
deque <AutoInStock> AutoInStock::SortByPurchase2(deque <AutoInStock> cars) // ���������� ������ "���� � �������" �� ���� ������� ���������� ����������� �� ��������
{
	AutoInStock b;
	for (int i = 0; i < cars.size(); i++)
	{
		for (int j = 0; j < cars.size() - 1; j++)
			if (cars[j].YearOfPurchase > cars[j + 1].YearOfPurchase) // ��������� �� ����
				swap(cars[j], cars[j + 1]);
			else if (cars[j].YearOfPurchase == cars[j + 1].YearOfPurchase) // ���� ��� ��������, ��������� �� ������
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

void AutoInStock::CancelLastActionStock(int opop1, int numbercars, int indexofremovecar) // ������ ���������� ��������
{
	if (opop1 == 1) // ������ ���������� ����������
	{
		deque <AutoInStock> cars;
		FileManager<AutoInStock> f("AutoInStock.txt");
		f.read(&cars); // ������ ����������� � ������� �� �����
		for (int kol = 0; kol < numbercars; kol++)
		{
			cars.pop_back(); // �������� ����������� �����������
		}
		f.writeDeque(cars); // ������ ����������� ������
		cars.clear();
	}
	else if (opop1 == 3) // ������ �������� ���� � �������
	{
		FileManager<AutoInStock> r("Basket.txt");
		deque <AutoInStock> cars;
		r.read(&cars); // ������ ���� �� �������
		deque <AutoInStock> carsa;
		FileManager<AutoInStock> f("AutoInStock.txt");
		f.read(&carsa); // ������ ���� � �������
		auto iter = carsa.begin() + indexofremovecar; // ������������� ������� �� ��������� �������
		carsa.insert(iter, cars[cars.size() - 1]); // ������� ���������� ����������
		f.writeDeque(carsa); // ������ � ����
		cars.pop_back(); // �������� ���� �� �������
		r.writeDeque(cars); // ������ ������. ������ � �������
	}
}

void AutoInStock::GetInfoFromFile(int language) // ������ ���������� �� ����� �����, ����������
{
	system("CLS");
	deque <AutoInStock> cars;
	FileManager<AutoInStock> f("AutoInStock.txt");
	f.read(&cars); // ������ ����������� � ������ �� �����
	string lst = "\t\t\t\t\tAuto list\n";
	string sort = "Sort by:    1->Year    2->Purchase date    3->Cost    4->Brand    0->Exit to the Menu\n";
	string sor = "Sort: ";
	if (language == 2)
	{
		lst = "\t\t\t\t\t������ �����������\n";
		sort = "����������� ��:    1->����    2->���� �������    3->���������    4->�����    0->����� � ����\n";
		sor = "�����������: ";
	}
	cout << lst;
	Cout(cars); // ����� ������ ��������
	int year = 2, pur = 2, cost = 2, brand = 2;
	do
	{
		cout << sort; // ����� ���������� ������ ����
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
				cars = SortListOfCars(cars); // ���������� ����������� �� �.�. �� ������������
			else cars = SortListOfCars2(cars); // ���������� ����������� �� �.�.�� ��������
			year++;
			system("CLS");
			cout << lst;
			Cout(cars);
			break;
		case 2:
			if (pur % 2 == 0)
				cars = SortByPurchase(cars); // ���������� ���� �� ���� ������� �� �����������
			else cars = SortByPurchase2(cars); // ���������� ���� �� ���� ������� �� ��������
			pur++;
			system("CLS");
			cout << lst;
			Cout(cars);
			break;
		case 3:
			if (cost % 2 == 0)
				cars = SortByCost(cars); // ���������� ���� �� ���� �� �����������
			else cars = SortByCost2(cars); // ���������� ���� �� ���� �� ��������
			cost++;
			system("CLS");
			cout << lst;
			Cout(cars);
			break;
		case 4:
			if (brand % 2 == 0)
				cars = sortbyBrand(cars); // ���������� ���� �� ����� �� �����������
			else cars = sortbyBrand2(cars); // ���������� ���� �� ����� �� ��������
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