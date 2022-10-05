#include "Patron.h"
#include "InputException.h"
#include "AutoInStock.h"
#include "FileManager.h"

ifstream& operator >> (ifstream& in, Patron &patrons) // ������ ������� � ����
{
	in >> patrons.SerName >> patrons.Name >> patrons.Patronymic >> patrons.Adress >> patrons.NumberOfCars;
	patrons.Metod(patrons.NumberOfCars);
	for (int i = 0; i < patrons.NumberOfCars; i++)
		in >> patrons.cars[i].VIN >> patrons.cars[i].Brand >> patrons.cars[i].Model >> patrons.cars[i].Year >> patrons.cars[i].BuyDay >>
		 patrons.cars[i].BuyMonth >> patrons.cars[i].BuyYear >>
		patrons.cars[i].Dayget >>
		patrons.cars[i].Monthget >> patrons.cars[i].YearOfPurchase >>
		patrons.cars[i].ruble >> patrons.cars[i].firstPrice;
	if (!in)
	{
		patrons = Patron();
	}
	return in;
}

ofstream& operator << (ofstream &out, const Patron &patrons) // ������ ������� �� �����
{
	out << patrons.SerName << " " << patrons.Name << " " << patrons.Patronymic << " " << patrons.Adress
		<<  " " << patrons.NumberOfCars << endl;

	for (int i = 0; i < patrons.NumberOfCars; i++)
		out << patrons.cars[i].VIN << " " << patrons.cars[i].Brand << " " << patrons.cars[i].Model << " " << patrons.cars[i].Year << " "
		<< patrons.cars[i].BuyDay << " " << patrons.cars[i].BuyMonth << " " << patrons.cars[i].BuyYear << " " <<
		" " << patrons.cars[i].Dayget << " " <<
		patrons.cars[i].Monthget << " " << patrons.cars[i].YearOfPurchase << " " <<
		patrons.cars[i].ruble << " " << patrons.cars[i].firstPrice << endl;
	return out;
}

ostream& operator << (ostream &out, const Patron &patrons) // ����� ������� �� �����
{
	/*out << "Patron: " << patrons.SerName << " " << patrons.Name << " " << patrons.Patronymic << " \n" << "Adress: " << patrons.Adress
		<< "\nCars number: " << patrons.NumberOfCars << endl;*/
	out << "Client: " << patrons.SerName << " " << patrons.Name << " " << patrons.Patronymic;
	for (int i = 0; i < 35 - (patrons.SerName.length() + patrons.Name.length() + patrons.Patronymic.length()); i++) cout << " ";
	out << "Adress: " << patrons.Adress;
	for (int i = 0; i < 40 - patrons.Adress.length(); i++) cout << " ";
	out << "   Cars number: " << patrons.NumberOfCars << endl;
	string c, m;
	for (int i = 0; i < patrons.NumberOfCars; i++)
	{
		int dl = patrons.cars[i].Brand.length() + patrons.cars[i].Model.length();
		if (patrons.cars[i].Dayget < 10)  c = "0"; else c = "";
		if (patrons.cars[i].Monthget < 10)  m = ".0"; else m = ".";
		out << "->"<< patrons.cars[i].VIN << " " << patrons.cars[i].Brand << " " << patrons.cars[i].Model;
		for (int i = 0; i < 20 - dl; i++)
			out << " ";
		out << patrons.cars[i].Year << "\t"
			<< c << patrons.cars[i].Dayget << m << patrons.cars[i].Monthget
			<< "." << patrons.cars[i].YearOfPurchase << " \tBYN: " << patrons.cars[i].ruble << " Profit: BYN "
			<< patrons.cars[i].profit() << endl;
	}
	for (int i = 0; i < 120; i++)
		cout << "_";
	cout << endl;
	return out;
}

ostream& operator >= (ostream &out, const Patron &patrons) // ����� ��������� ����������� �� �����
{
	string c, m;
	for (int i = 0; i < patrons.NumberOfCars; i++)
	{
		int dl = patrons.cars[i].Brand.length() + patrons.cars[i].Model.length();
		if (patrons.cars[i].Dayget < 10)  c = "0"; else c = "";
		if (patrons.cars[i].Monthget < 10)  m = ".0"; else m = ".";
		out << "|";
		out << patrons.cars[i].VIN;
		if (patrons.cars[i].VIN < 10) out << "    ";
		if (patrons.cars[i].VIN > 9) out << "   ";
		out << "|" << patrons.cars[i].Brand;
		for (int count = 0; count < 17 - patrons.cars[i].Brand.length(); count++) out << " ";
		out << "|" << patrons.cars[i].Model;
		for (int icount = 0; icount < 12 - patrons.cars[i].Model.length(); icount++)
			out << " ";
		out << "|" << patrons.cars[i].Year << "       "
			"|" << c << patrons.cars[i].Dayget << m << patrons.cars[i].Monthget
			<< "." << patrons.cars[i].YearOfPurchase << "         |BYN: " << patrons.cars[i].ruble;
		if (patrons.cars[i].ruble < 1000) dl = 7;
		if (patrons.cars[i].ruble > 1000) dl = 6;
		if (patrons.cars[i].ruble > 10000) dl = 5;
		if (patrons.cars[i].ruble > 100000) dl = 4;
		if (patrons.cars[i].ruble > 1000000) dl = 3;
		for (int ic = 0; ic < dl; ic++) out << " ";
		out << " |$" << patrons.cars[i].ConverterFromRubleToD() << endl;
	}
	return out;

}

ostream& operator -= (ostream &out, const Patron &patrons) // ����� �������� �� �����
{
	/*out << "Patron: " << patrons.SerName << " " << patrons.Name << " " << patrons.Patronymic << " \n" << "Adress: " << patrons.Adress
		<< "\nCars number: " << patrons.NumberOfCars << endl;
	return out;*/

	out << "Client: "<< patrons.SerName << " " << patrons.Name << " " << patrons.Patronymic;
	for (int i = 0; i < 35 - (patrons.SerName.length() + patrons.Name.length() + patrons.Patronymic.length()); i++) cout << " ";
	out << "Adress: " << patrons.Adress;
		for (int i = 0; i < 40 - patrons.Adress.length(); i++) cout << " ";
		out << "   Cars number: " << patrons.NumberOfCars << endl;
	return out;
}

void Patron::InputClient(Patron *p, int language)  // ���� ������ �������
{
	string sec = "Patron's second name: ";
	string nm = "Patron's name: ";
	string pt = "Patron's patronymic: ";
	string adr = "Patron's adress: ";
	string num = "Number of patron's cars: ";
	if (language == 2)
	{
		sec = "������� �������: ";
		nm = "��� �������: ";
		pt = "�������� �������: ";
		adr = "�����: ";
		num = "���������� �����������: ";
	} 
	cout << sec; cin >> (*p).SerName; // ���� ��� �������
	cout << nm; cin >> (*p).Name;
	cout << pt; cin >> (*p).Patronymic;
	cout << adr; cin >> (*p).Adress; // ���� ������ �������
	cout << num; cin >> (*p).NumberOfCars;
	(*p).Metod((*p).NumberOfCars); // ��������� ������ ��� ������ ����������� �������
	if ((*p).SerName[0] >= 'a' && (*p).SerName[0] <= 'z' || (*p).SerName[0] >= '�' && (*p).SerName[0] <= '�'
		|| (*p).Name[0] >= 'a' && (*p).Name[0] <= 'z' || (*p).Name[0] >= '�' && (*p).Name[0] <= '�'
		|| (*p).Patronymic[0] >= 'a' && (*p).Patronymic[0] <= 'z' || (*p).Patronymic[0] >= '�' && (*p).Patronymic[0] <= '�')
		throw InputException("Lowercase letter"); // ���� ��� ������� � �������� �����, �������� �� ���������, ������ ����������
}

void Patron::InputDate(Patron *p, int kol)
{
	cin >> (*p).cars[kol].Dayget >> (*p).cars[kol].Monthget >> (*p).cars[kol].YearOfPurchase;
	if (!(*p).cars[kol].YearOfPurchase || !(*p).cars[kol].Dayget || !(*p).cars[kol].Monthget)
		throw InputException("�haracters entered incorrectly!"); // ������� ����������, ���� ���� ������� �����������
	if ((*p).cars[kol].YearOfPurchase < (*p).cars[kol].BuyYear ||
		((*p).cars[kol].YearOfPurchase == (*p).cars[kol].BuyYear && (*p).cars[kol].Monthget < (*p).cars[kol].BuyMonth) ||
		((*p).cars[kol].YearOfPurchase == (*p).cars[kol].BuyYear && (*p).cars[kol].Monthget == (*p).cars[kol].BuyMonth && (*p).cars[kol].Dayget < (*p).cars[kol].BuyDay))
		throw InputException("Date of sale before date of purchase!"); // ������� ����������, ���� ���� ������� ������ ���� ������� ����������
}

void Patron::add_car_to_SoldCars(int *undo, int language) // ���������� ����������� � ������ "� �������" 
{
	Patron p;
	try                     
	{
		InputClient(&p, language); // ����� ������� ����� ������ �������
	}
	catch (InputException &ex)  // ��������� ���������� ������ ����� �����, �������, ��������
	{
		cout << ex.what() << endl; // ����� ��������� �� ������
		ex.UpperCase(&p); // ����� ������ �������� ����� � ������� �������
	}
	for (int kol = 0; kol < p.NumberOfCars; kol++) // ���������� ����������� �������
	{

		deque <AutoInStock> carsa;
		FileManager<AutoInStock> f("AutoInStock.txt");
		f.read(&carsa); // ������ �� ����� ����������� � �������
		int numb = 0;
		if (carsa.empty()) // ���� ������ ���� � ������� ����, ������� ��������� �� ����
		{
			if (language == 2) cout << "������ ���� :(\n"; else
			cout << "list is empty :(\n";
			system("pause");
			return;
		}
		system("CLS");
		cout -= p; // ����� ��������� ������ �������
		for (auto iter = carsa.begin(); iter != carsa.end(); iter++)
			cout < *iter; // ����� ������ ���� � �������
		if (language == 2) cout << "������� VIN ����: "; else
		cout << "Enter car VIN: "; cin >> numb; // ���� VIN ����������
		int i = 0;
		while (numb != carsa[i].VIN) // ����� ���������� � ������ �� VIN
		{
			i++;
		}
		(*undo) = i; // ���������� ����� ���������� � ������ 
		{
			p.cars[kol].BuyDay = carsa[i].Dayget; // ����������� ���������� � ������� � ��������� ����
			p.cars[kol].BuyMonth = carsa[i].Monthget; // ������������� ���� ������� �����������
			p.cars[kol].BuyYear = carsa[i].YearOfPurchase; // ������������� ���� ������� �����������
			p.cars[kol].Brand = carsa[i].Brand; // ������������� ����� ����
			p.cars[kol].Model = carsa[i].Model; // ������������� ������ ����
			p.cars[kol].Year = carsa[i].Year; // ������������� ����  �������
			p.cars[kol].VIN = carsa[i].VIN; // ������������� VIN
			p.cars[kol].firstPrice = carsa[i].ruble; // ������������� ���� ������� �����������
		}
		if (language == 2) cout << "���� ������� ��.��.��: "; else
		cout << "Date of sale dd.mm.yy: ";
		try
		{
			InputDate(&p, kol); // �������� ������� ����������
		}
		catch (InputException &ex) // ��������� ���������� (���� ���� ������� ������ ���� �������)
		{
			cout << ex.what() << endl;
			ex.ChangeDate(kol, &p); // ��������� ���� 
		}
		catch (...)
		{
			cout << "Some error :(" << endl; // ���� �������� �������������� ��������
		}
		FileManager<AutoInStock> W("Basket.txt");
		W.write(carsa[i]); // ������ ���� � ������� � ����-�������
		auto iter = carsa.begin(); // ������������� ��������� �� ������ ������ ���� � �������
		carsa.erase(iter + i);     // �������� ���� � �������, ������� ���� �������
		f.writeDeque(carsa); // ������ ������ ����������� � ������� � ����
		if (language == 2) cout << "��������� � BYN: "; else 
		cout << "Price in BYN: ";
		cin >> p.cars[kol].ruble; // ���� ��������� ������� ����������
		FileManager<Patron> E("SoldCars.txt");
		deque <Patron> patrons;
		E.read(&patrons); // ������ �� ����� �������� - ����
		if (!patrons.empty()) // ������������� VIN ����
			p.cars[kol].VIN = patrons[patrons.size() - 1].cars[patrons[patrons.size() - 1].NumberOfCars - 1].VIN += (kol + 1);
		else p.cars[kol].VIN = carsa[carsa.size() - 1].VIN += kol;
	}
	FileManager<Patron> W("SoldCars.txt");
	W.write(p); // ������ �������-���� � ����
	if (language == 2) cout << "������ ��������! " << endl; else 
	cout << "Client was added!" << endl; // ����� ��������� ��������� ���������� �������-����
	system("pause");
}

int Patron::DeleteCarSold(int language) // �������� �������-���������� �� ������
{
	FileManager<Patron> f("SoldCars.txt");
	int numberToDelete, i = 1;
	deque <Patron> patrons;
	f.read(&patrons); // ������ �������� �� �����
	if (patrons.empty()) // ���� ������ ������ ������� ��������� 
	{
		if (language == 2) cout << "������ ���� :(\n"; else
		cout << "List is empty:(" << endl;
		system("pause");
		return 0;
	}
	for (auto itera = patrons.begin(); itera != patrons.end(); itera++)
	{
		cout << "|"<< i << "| ";
		cout << *itera; // ����� ������ �������� - ����
		i++;
	}
	if (language == 2) cout << "0->�����\n����� ���������� �������: "; else
	cout << "0->Exit \nPatron number to delete: ";
	i = 1;
	do
	{
		cin >> numberToDelete; // ���� ������ ������� ��� �������
		if (numberToDelete == 0) return 0;
	} while (numberToDelete < 1 || numberToDelete > patrons.size()); // ���� ���� ������������
	auto iterNumberToDelete = patrons.begin(); // ������������� ��������� ������ �������� - ����
	FileManager<Patron> W("BasketSoldCars.txt");
	W.write(patrons[numberToDelete - 1]); // ������ ���������� ������� � ����-�������
	iterNumberToDelete += (numberToDelete - 1); // ����������� ��������� �� ���������� �������
	patrons.erase(iterNumberToDelete);  // �������� ���������� �������
	system("CLS");

	if (patrons.empty()) // ���� ������ ����, ������� ��������� �� ����
	{ 
		if (language == 2) cout << "������ ���� :(\n"; else
			cout << "List is empty:(" << endl;
		system("pause"); return 0;
	}
	else
		for (auto itera = patrons.begin(); itera != patrons.end(); itera++)
		{
			cout <<"|"<< i << "| ";
			cout << *itera; // ����� ���������������� ������
			i++;
		}
	system("pause");								
	f.writeDeque(patrons); // ������ �������� � ����
	return numberToDelete - 1; // ���������� ������ ���������� �������
}

deque <Patron> Patron:: SearchByClient(deque<Patron> *patrons, int language) // ����� ������� �� ������� �����
{
	Patron p;
	deque <Patron> clients;
	string name = " ", secname = " "; int num = 1;
	if (language == 2)
	{
		cout << "�������: "; cin >> secname;
		cout << "���: "; cin >> name;
	}
	else
	{
		cout << "Sername: "; cin >> secname;
		cout << "Name: "; cin >> name;
	}
	system("CLS");
	auto iter = (*patrons).begin();
	for (iter = (*patrons).begin(); iter != (*patrons).end(); iter++)
		if (name == (*iter).Name && secname == (*iter).SerName) 
		{
			clients.push_back(*iter); // ���������� ������� �������� 
			cout << num << " "; // ����� ������� ��������
			num++;
			cout << *iter;
		}
	return clients;
}

deque <Patron> Patron::SearchByBrand(deque<Patron> *patrons, int language) // ����� �������� �� ����� ����������
{
	Patron p;
	string Brand = " ";
	deque <Patron> clients; int num = 1;
	if (language == 2) { cout << "�����: "; cin >> Brand; }
	else {
		cout << "Brand: "; cin >> Brand;
	}
	system("CLS");
	for (auto iter = (*patrons).begin(); iter != (*patrons).end(); iter++)
		for (int i = 0; i < (*iter).NumberOfCars; i++)
			if (Brand == (*iter).cars[i].Brand)
			{
				clients.push_back(*iter); // ���������� ������� �������� 
				cout << num << " "; // ����� ������� ��������
				num++;
				cout << *iter;
			}
	return clients;
}

deque <Patron> Patron::SearchByYear(deque <Patron> *patrons, int language) // ����� �� ���� ������� ����������
{
	Patron p;
	deque<Patron> clients;
	int Year = 0, num = 1;
	if (language == 2) { cout << "��� �������: "; cin >> Year; }
	else
	{
		cout << "Year: "; cin >> Year;
	}
	system("CLS");
	auto iter = (*patrons).begin(); // ������������� ��������� 
	for (auto iter = (*patrons).begin(); iter != (*patrons).end(); iter++)
		for (int i = 0; i < (*iter).NumberOfCars; i++)
			if (Year == (*iter).cars[i].Year)
			{
				clients.push_back(*iter); // ���������� ������� �������� 
				cout << num << " "; // ����� ������� ��������
				num++;
				cout << *iter;
			}
	return clients;
}

void Patron::DisplaySoldCars(int language) // ����� �� ����� ����� ��������� ����
{
	string sold = "SOLD CARS";
	if (language == 2) sold = "��������� ����������";
	deque <Patron> patrons;
	FileManager<Patron> f("SoldCars.txt");
	f.read(&patrons); 
	system("CLS");
	cout << "--------------------------------" << sold << "-------------------------------------------------------\n"; int i = 1;
	cout << "^VIN  ^Brand            ^Model       ^Year       ^Purchase dd.mm.yy  ^Cost BYN        ^Cost Dollar" << endl;
	for (auto itera = patrons.begin(); itera != patrons.end(); itera++)
	{
		cout >= *itera;
	}
	f.close(); // �������� �����
	system("pause");
}


void Patron::GetInfoFromFileSold(int language) // ��������� ���������� � ��������-����
{
	string lst = "\t\tlist\n";
	string ser = "Search by:    1->Client SN     2->Car Brand    3->Car year    0->Exit to the Menu\n";
	string sr = "Search: ";
	if (language == 2)
	{
		lst = "\t\t\t\t������\n";
		ser = "������ ��:    1->�.�. �������    2->����� ����    3->��� �������    0->����� � ����\n";
		sr = "������: ";
	}
	deque <Patron> patrons;
	deque <Patron> clients;
	Patron p;
	FileManager<Patron> f("SoldCars.txt");
	f.read(&patrons);
	system("CLS");
	cout << lst;
	auto itera = patrons.begin(); int count = 1;
	while (itera != patrons.end()) // ����� ������ ��������-����
	{
		cout << "|"<<count << "| ";
		count++;
		cout << *itera;
		itera++;
	}
	f.close(); // �������� �����
	cout << ser; // ����� ���������� ������ ����
	int Number = 0;
	do
	{
		cout << sr; cin >> Number;
	} while (Number < 0 || Number > 3);
	if (Number == 0) return;
	clients = SearchBy(Number, patrons, language); // ����� ������� ������ ��������
	int numberer = 0;
	p = ChangeInfo(&clients, &numberer, language); // ����� ������� ��������� ���������� �� ������� 
	auto iter = patrons.begin();
	for (iter = patrons.begin(); iter != patrons.end(); iter++) // ����� �� VIN ���� 
	{
		if (p.cars[0].VIN == (*iter).cars[0].VIN)
			break;
	}
	(*iter) = p;
	itera = patrons.begin();
	while (itera != patrons.end())
	{
		cout << *itera; // ����� ���������������� ������
		itera++;
	}
	system("pause");
	f.writeDeque(patrons); // ������ �������� � ����
}

void lang(int language, string *sel, string *ch, string *exec, string *cser, string *cnm, string *cpt, string *cadr, string *ser, string *nm,
	string *pt, string *adr, string *cto, string *inf, string *vin, string *cbr, string *cmd, string *cye, string *cpur, string *csal, string
 *dpur, string *dsal, string *brr, string *yearr, string *mdll, string *ddtd, string *ddsd, string *purpr, string *slprs) // ��������� �����
{
	switch (language)
	{
	case 1:
		*sel = "Select client: ";
		*ch = "Change: 1->Client   2->Car   0->Exit\n";
		*exec = "Excecute: ";
		*cser = "1-> Change Sername\n";
		*cnm = "2-> Change Name\n";
		*cpt = "3-> Change patronymic\n";
		*cadr = "4-> Change Adress\n";
		*ser = "Sername: ";
		*nm = "Name: ";
		*pt = "Patronymic: ";
		*adr = "Adress: ";
			*cto = " Change to-> ";
			*inf = "Info has been changed!\n";
			*vin = "Enter car VIN: ";
			*cbr = "1-> Change Brand\n";
			*cmd = "2-> Change Model\n";
			*cye = "3-> Change Year\n";
			*cpur = "4-> Change Date of purchase\n";
			*csal = "5-> Change Date of sale\n";
			*dpur = "6-> Change Purchase price\n";
			*dsal = "7-> Change Selling price\n";
			*brr = "Brand: ";
			*mdll = "Model: ";
			*yearr = "Year: ";
			*ddtd = "Date of purchase dd.mm.yy: ";
			*ddsd = "Date of sale dd.mm.yy: ";
			*purpr = "Purchase price BYN: ";
			*slprs = "Selling price BYN: ";
			break;
			
	case 2:
		*sel = "�������� �������: ";
		*ch = "��������: 1->������ �������   2->������ ����  0->�����\n";
		*exec = "���������: ";
		*cser = "1-> �������� �������\n";
		*cnm = "2-> �������� ���\n";
		*cpt = "3-> �������� ��������\n";
		*cadr = "4-> �������� ������\n";
		*ser = "�������: ";
		*nm = "���: ";
		*pt = "��������: ";
		*adr = "������: ";
		*cto = " �������� �� -> ";
		*inf = "������ ���� ��������!\n";
		*vin = "������� VIN ����: ";
		*cbr = "1-> �������� �����\n";
		*cmd = "2-> �������� ������\n";
		*cye = "3-> �������� ��� �������\n";
		*cpur = "4-> �������� ���� �������\n";
			*csal = "5-> �������� ���� �������\n";
			*dpur = "6-> �������� ���� �������\n";
			*dsal = "7-> �������� ���� �������\n";
			*brr = "�����: ";
			*mdll = "������: ";
			*yearr = "��� �������: ";
			*ddtd = "���� ������� ��.��.��: ";
			*ddsd = "���� ������� ��.��.��: ";
			*purpr = "���� ������� � BYN: ";
			*slprs = "���� ������� � BYN: ";
			break;
	default:
		break;
	}
}

Patron Patron::ChangeInfo(deque<Patron>* patrons, int *numberer, int language) // ��������� ���������� � �������
{
	string sel, chd, exec, cser, cnm, cpt, cadr, ser, nm, pt, adr, cto, inf, vin, cbr, cmd, cye, cpur, csal, dpur, dsal, brr,mdll,yearr,ddtd,
		ddsd,purpr,slprs;
	lang(language, &sel, &chd, &exec, &cser, &cnm, &cpt, &cadr, &ser, &nm, &pt, &adr, &cto, &inf, &vin, &cbr, &cmd, &cye, &cpur, &csal, &dpur, 
		&dsal, &brr, &mdll, &yearr, &ddtd,    // ��������� ����� ����������
		&ddsd, &purpr, &slprs); // ����� ������� ��������� �����
	Patron p;
	int VIN = 0, ch = 0;
	if ((*patrons).size() > 1) // �������� ����� �� ������������
	{
		do
		{
			cout << sel; cin >> *numberer;
		}
		while ((*numberer) < 1 || (*numberer) >(*patrons).size());
		p = (*patrons)[(*numberer) - 1]; 
	}
	else p = (*patrons)[0];
	int Number = 0;
	do {
		system("CLS");
		cout << p;
		cout << chd;
		int change = 0, i = 0;
		do
		{
			cout << exec; cin >> Number;
		} while (Number < 0 || Number > 2);
		switch (Number)
		{
		case 1: // ��������� ���������� � �������
			system("CLS");
			cout << p;
			cout << cser;
			cout << cnm;
			cout << cpt;
			cout << cadr;
			do
			{
				cout << exec;
				cin >> change;
			} while (change < 1 || change > 4);
			if (change == 1) { cout << ser << p.SerName << cto; cin >> p.SerName; } // ��������� �������
			if (change == 2) { cout << nm << p.Name << cto; cin >> p.Name; } // ���. �����
			if (change == 3) { cout << pt << p.Patronymic << cto; cin >> p.Patronymic; } // ���.��������
			if (change == 4) { cout << adr << p.Adress << cto; cin >> p.Adress; } // ���. �������
			system("CLS");
			cout << inf;
			cout << p;
			system("pause");
			system("CLS");
			break;
		case 2: // ��������� ���������� �� ���������� ������
			system("CLS");
			cout << p;
			i = 0;
			if (p.NumberOfCars > 1) // ���� ����������� ���������, �� ������� ����
			{
				cout << vin; cin >> VIN;
				while (VIN != p.cars[i].VIN) // ����� ���� �� VIN
				{
					i++;
				}
			}
			cout << cbr; // ����� ������ ����
			cout << cmd;
			cout << cye;
			cout << cpur;
			cout << csal;
			cout << dpur;
			cout << dsal;
			do
			{
				cout << exec;
				cin >> ch;
			} while (ch < 1 || ch > 7);
			if (ch == 1) { cout << brr << p.cars[i].Brand << cto; cin >> p.cars[i].Brand; }  // ��������� �����
			if (ch == 2) { cout << mdll << p.cars[i].Model << cto; cin >> p.cars[i].Model; } // ��������� ������
			if (ch == 3) { cout << yearr << p.cars[i].Year << cto; cin >> p.cars[i].Year; } // ��������� ���� �������
			if (ch == 4) {
				cout << ddtd << p.cars[i].Dayget << "." << p.cars[i].Monthget << "." << p.cars[i].YearOfPurchase // ��������� ���� ������� �����������
					<< cto; cin >> p.cars[i].Dayget >> p.cars[i].Monthget >> p.cars[i].YearOfPurchase;
			}
			if (ch == 5) {
				cout << ddsd << p.cars[i].BuyDay << "." << p.cars[i].BuyMonth << "." << p.cars[i].BuyYear // ��������� ���� ������� �����������
					<< cto; cin >> p.cars[i].BuyDay >> p.cars[i].BuyMonth >> p.cars[i].BuyYear;
			}
			if (ch == 6) { cout << purpr << p.cars[i].firstPrice << cto; cin >> p.cars[i].firstPrice; } // ��������� ���� � ����������
			if (ch == 7) { cout << slprs << p.cars[i].ruble << cto; cin >> p.cars[i].ruble; } // ��������� ���� ������� ����
			system("CLS");
			cout << inf; // ����� ��������������� ����������
			cout << p;
			system("pause");
			system("CLS");
			break;
		default:
			break;
		}
	} while (Number != 0);
	system("CLS");
	return p;
}

deque <Patron> Patron::SearchBy(int operation, deque<Patron> patrons, int language) // ����� ������ ����
{
	deque<Patron> p;
	switch (operation)
	{
	case 1:
		p = SearchByClient(&patrons, language); break; // ����� ������� ������ �� ��
	case 2:  
		p = SearchByBrand(&patrons, language); break; // ����� ������� ������ �� ����� ����
	case 3:
		p = SearchByYear(&patrons, language); break; // ����� ������� ������ �� ���� �������
	case 0: break;
	default:
		break;
	}
	return p;
}

void Patron::CancelLastActionSold(int operation, int index, int delnumb) // ������ ���������� ��������(����������, �������� ����-�������)
{
	if (operation == 1) // ���� ��������� �������� - ���������� �������-����
	{
		deque <Patron> patrons;
		FileManager<Patron> f("SoldCars.txt");
		f.read(&patrons); // ������ �������� �� �����
		FileManager<AutoInStock> r("Basket.txt");
		deque <AutoInStock> cars;
		r.read(&cars); // ������ ���� � ������� �� �������

		deque <AutoInStock> carsa;
		FileManager<AutoInStock> k("AutoInStock.txt");
		k.read(&carsa); // ������ ���� � �������
		for (int i = 0; i < patrons[patrons.size() - 1].NumberOfCars; i++)
		{
			carsa.push_back(cars[cars.size() - 1]); // ������ ���� � ������� �� �������
			cars.pop_back(); // �������� ���� � ������� �� �������
		}
		r.writeDeque(cars); // ������ ���������������� ������ ���� � ������� � �������
		k.writeDeque(carsa); // ������ ������ ���� � ������� � ����
		patrons.pop_back(); // �������� ������� - ���� 
		f.writeDeque(patrons); // ������ �������� - ���� � ����
	}
	else if (operation == 2) // ���� ��������� �������� - �������� ������� - ����
	{
		deque <Patron> patrons;
		FileManager<Patron> f("SoldCars.txt");
		f.read(&patrons); // ������ �������� - ���� �� �����

		deque <Patron> patronsdel;
		FileManager<Patron> W("BasketSoldCars.txt");
		W.read(&patronsdel); // ������ ���������� ������� - ���� �� �������
		auto iter = patrons.begin() + delnumb; // ������������� ��������� �� ������������������ �������
		patrons.insert(iter, patronsdel[patronsdel.size() - 1]); // ������� ������� � ������ 
		patronsdel.pop_back(); // �������� ������� �� �������
		W.writeDeque(patronsdel); // ������ � ���� ��������
		f.writeDeque(patrons);  // ������ � ���� ��������
	}
}