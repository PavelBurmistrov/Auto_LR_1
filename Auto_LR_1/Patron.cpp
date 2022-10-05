#include "Patron.h"
#include "InputException.h"
#include "AutoInStock.h"
#include "FileManager.h"

ifstream& operator >> (ifstream& in, Patron &patrons) // Запись клиента в файл
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

ofstream& operator << (ofstream &out, const Patron &patrons) // Чтение клиента из файла
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

ostream& operator << (ostream &out, const Patron &patrons) // Вывод клиента на экран
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

ostream& operator >= (ostream &out, const Patron &patrons) // Вывод проданных автомобилей на экран
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

ostream& operator -= (ostream &out, const Patron &patrons) // Вывод клиентов на экран
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

void Patron::InputClient(Patron *p, int language)  // Ввод данных клиента
{
	string sec = "Patron's second name: ";
	string nm = "Patron's name: ";
	string pt = "Patron's patronymic: ";
	string adr = "Patron's adress: ";
	string num = "Number of patron's cars: ";
	if (language == 2)
	{
		sec = "Фамилия клиента: ";
		nm = "Имя клиента: ";
		pt = "Отчество клиента: ";
		adr = "Адрес: ";
		num = "Количество автомобилей: ";
	} 
	cout << sec; cin >> (*p).SerName; // Ввод ФИО клиента
	cout << nm; cin >> (*p).Name;
	cout << pt; cin >> (*p).Patronymic;
	cout << adr; cin >> (*p).Adress; // Ввод адреса клиента
	cout << num; cin >> (*p).NumberOfCars;
	(*p).Metod((*p).NumberOfCars); // Выделение памяти под массив автомобилей клиента
	if ((*p).SerName[0] >= 'a' && (*p).SerName[0] <= 'z' || (*p).SerName[0] >= 'а' && (*p).SerName[0] <= 'я'
		|| (*p).Name[0] >= 'a' && (*p).Name[0] <= 'z' || (*p).Name[0] >= 'а' && (*p).Name[0] <= 'я'
		|| (*p).Patronymic[0] >= 'a' && (*p).Patronymic[0] <= 'z' || (*p).Patronymic[0] >= 'а' && (*p).Patronymic[0] <= 'я')
		throw InputException("Lowercase letter"); // Если ФИО введены с строчной буквы, заменить на заглавную, бросив исключение
}

void Patron::InputDate(Patron *p, int kol)
{
	cin >> (*p).cars[kol].Dayget >> (*p).cars[kol].Monthget >> (*p).cars[kol].YearOfPurchase;
	if (!(*p).cars[kol].YearOfPurchase || !(*p).cars[kol].Dayget || !(*p).cars[kol].Monthget)
		throw InputException("Сharacters entered incorrectly!"); // Бросить исключение, если дата введена некорректно
	if ((*p).cars[kol].YearOfPurchase < (*p).cars[kol].BuyYear ||
		((*p).cars[kol].YearOfPurchase == (*p).cars[kol].BuyYear && (*p).cars[kol].Monthget < (*p).cars[kol].BuyMonth) ||
		((*p).cars[kol].YearOfPurchase == (*p).cars[kol].BuyYear && (*p).cars[kol].Monthget == (*p).cars[kol].BuyMonth && (*p).cars[kol].Dayget < (*p).cars[kol].BuyDay))
		throw InputException("Date of sale before date of purchase!"); // Бросить исключение, если дата продажи раньше даты покупки автомобиля
}

void Patron::add_car_to_SoldCars(int *undo, int language) // Добавление автомобилей в спикок "В наличии" 
{
	Patron p;
	try                     
	{
		InputClient(&p, language); // Вызов функции ввода данных клиента
	}
	catch (InputException &ex)  // Обработка исключения первой буквы Имени, фамилии, Отчества
	{
		cout << ex.what() << endl; // Вывод сообщения об ошибке
		ex.UpperCase(&p); // Вызов метода поднятия буквы в верхний регистр
	}
	for (int kol = 0; kol < p.NumberOfCars; kol++) // Добавление автомобилей клиента
	{

		deque <AutoInStock> carsa;
		FileManager<AutoInStock> f("AutoInStock.txt");
		f.read(&carsa); // Чтение из файла автомобилей в наличии
		int numb = 0;
		if (carsa.empty()) // Если список авто в наличии пуст, вывести сообщение об этом
		{
			if (language == 2) cout << "Список пуст :(\n"; else
			cout << "list is empty :(\n";
			system("pause");
			return;
		}
		system("CLS");
		cout -= p; // Вывод введенных данных клиента
		for (auto iter = carsa.begin(); iter != carsa.end(); iter++)
			cout < *iter; // Вывод списка авто в ниличии
		if (language == 2) cout << "Введите VIN авто: "; else
		cout << "Enter car VIN: "; cin >> numb; // Ввод VIN автомобиля
		int i = 0;
		while (numb != carsa[i].VIN) // Поиск автомобиля в списке по VIN
		{
			i++;
		}
		(*undo) = i; // Запоминаем номер автомобиля в списке 
		{
			p.cars[kol].BuyDay = carsa[i].Dayget; // Перемещение автомобиля в наличии в проданные авто
			p.cars[kol].BuyMonth = carsa[i].Monthget; // Инициализация даты покупки автосалоном
			p.cars[kol].BuyYear = carsa[i].YearOfPurchase; // Инициализация даты покупки автосалоном
			p.cars[kol].Brand = carsa[i].Brand; // Инициализация марки авто
			p.cars[kol].Model = carsa[i].Model; // Инициализация модели авто
			p.cars[kol].Year = carsa[i].Year; // Инициализация года  выпуска
			p.cars[kol].VIN = carsa[i].VIN; // Инициализация VIN
			p.cars[kol].firstPrice = carsa[i].ruble; // Инициализация цены покупки автосалоном
		}
		if (language == 2) cout << "Дата продажи дд.мм.гг: "; else
		cout << "Date of sale dd.mm.yy: ";
		try
		{
			InputDate(&p, kol); // Вводдаты продажи автомобиля
		}
		catch (InputException &ex) // Обработка исключения (если дата продажи раньше даты покупки)
		{
			cout << ex.what() << endl;
			ex.ChangeDate(kol, &p); // Изменение даты 
		}
		catch (...)
		{
			cout << "Some error :(" << endl; // Если возникла непредвиденная ситуация
		}
		FileManager<AutoInStock> W("Basket.txt");
		W.write(carsa[i]); // Запись авто в ниличии в файл-корзину
		auto iter = carsa.begin(); // Инициализация итератора на начало списка авто в наличии
		carsa.erase(iter + i);     // Удаление авто в наличии, которое было продано
		f.writeDeque(carsa); // Запись списка автомобилей в наличии в файл
		if (language == 2) cout << "Стоимость в BYN: "; else 
		cout << "Price in BYN: ";
		cin >> p.cars[kol].ruble; // Ввод стоимости продажи автомобиля
		FileManager<Patron> E("SoldCars.txt");
		deque <Patron> patrons;
		E.read(&patrons); // Чтение из файла клиентов - авто
		if (!patrons.empty()) // Инициализация VIN авто
			p.cars[kol].VIN = patrons[patrons.size() - 1].cars[patrons[patrons.size() - 1].NumberOfCars - 1].VIN += (kol + 1);
		else p.cars[kol].VIN = carsa[carsa.size() - 1].VIN += kol;
	}
	FileManager<Patron> W("SoldCars.txt");
	W.write(p); // Запись клиента-авто в файл
	if (language == 2) cout << "Клиент добавлен! " << endl; else 
	cout << "Client was added!" << endl; // Вывод сообщения успешного добавления клиента-авто
	system("pause");
}

int Patron::DeleteCarSold(int language) // Удаление клиента-автомобиля из списка
{
	FileManager<Patron> f("SoldCars.txt");
	int numberToDelete, i = 1;
	deque <Patron> patrons;
	f.read(&patrons); // Чтение клиентов из файла
	if (patrons.empty()) // Если список пустой вывести сообщение 
	{
		if (language == 2) cout << "Список пуст :(\n"; else
		cout << "List is empty:(" << endl;
		system("pause");
		return 0;
	}
	for (auto itera = patrons.begin(); itera != patrons.end(); itera++)
	{
		cout << "|"<< i << "| ";
		cout << *itera; // Вывод списка клиентов - авто
		i++;
	}
	if (language == 2) cout << "0->Выйти\nНомер удаляемого клиента: "; else
	cout << "0->Exit \nPatron number to delete: ";
	i = 1;
	do
	{
		cin >> numberToDelete; // Ввод номера клиента для удаения
		if (numberToDelete == 0) return 0;
	} while (numberToDelete < 1 || numberToDelete > patrons.size()); // Пока ввод некорректный
	auto iterNumberToDelete = patrons.begin(); // Инициализация итератора список клиентов - авто
	FileManager<Patron> W("BasketSoldCars.txt");
	W.write(patrons[numberToDelete - 1]); // Запись удаленного клиента в файл-корзину
	iterNumberToDelete += (numberToDelete - 1); // Перемещение итератора на удаляемого клиента
	patrons.erase(iterNumberToDelete);  // Удаление выбранного клиента
	system("CLS");

	if (patrons.empty()) // Если список пуст, вывести сообщение об этом
	{ 
		if (language == 2) cout << "Список пуст :(\n"; else
			cout << "List is empty:(" << endl;
		system("pause"); return 0;
	}
	else
		for (auto itera = patrons.begin(); itera != patrons.end(); itera++)
		{
			cout <<"|"<< i << "| ";
			cout << *itera; // Вывод преобразованного списка
			i++;
		}
	system("pause");								
	f.writeDeque(patrons); // Запись клиентов в файл
	return numberToDelete - 1; // Возвращаем индекс удаленного клиента
}

deque <Patron> Patron:: SearchByClient(deque<Patron> *patrons, int language) // Поиск клиента по Фамилии Имени
{
	Patron p;
	deque <Patron> clients;
	string name = " ", secname = " "; int num = 1;
	if (language == 2)
	{
		cout << "Фамилия: "; cin >> secname;
		cout << "Имя: "; cin >> name;
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
			clients.push_back(*iter); // Добавление искомых клиентов 
			cout << num << " "; // Вывод искомых клиентов
			num++;
			cout << *iter;
		}
	return clients;
}

deque <Patron> Patron::SearchByBrand(deque<Patron> *patrons, int language) // Поиск клиентов по Марке автомобиля
{
	Patron p;
	string Brand = " ";
	deque <Patron> clients; int num = 1;
	if (language == 2) { cout << "Марка: "; cin >> Brand; }
	else {
		cout << "Brand: "; cin >> Brand;
	}
	system("CLS");
	for (auto iter = (*patrons).begin(); iter != (*patrons).end(); iter++)
		for (int i = 0; i < (*iter).NumberOfCars; i++)
			if (Brand == (*iter).cars[i].Brand)
			{
				clients.push_back(*iter); // Добавление искомых клиентов 
				cout << num << " "; // Вывод искомых клиентов
				num++;
				cout << *iter;
			}
	return clients;
}

deque <Patron> Patron::SearchByYear(deque <Patron> *patrons, int language) // Поиск по году выпуска автомобиля
{
	Patron p;
	deque<Patron> clients;
	int Year = 0, num = 1;
	if (language == 2) { cout << "Год выпуска: "; cin >> Year; }
	else
	{
		cout << "Year: "; cin >> Year;
	}
	system("CLS");
	auto iter = (*patrons).begin(); // Инициализация итератора 
	for (auto iter = (*patrons).begin(); iter != (*patrons).end(); iter++)
		for (int i = 0; i < (*iter).NumberOfCars; i++)
			if (Year == (*iter).cars[i].Year)
			{
				clients.push_back(*iter); // Добавление искомых клиентов 
				cout << num << " "; // Вывод искомых клиентов
				num++;
				cout << *iter;
			}
	return clients;
}

void Patron::DisplaySoldCars(int language) // Вывод на экран спика проданных авто
{
	string sold = "SOLD CARS";
	if (language == 2) sold = "Проданные автомобили";
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
	f.close(); // Закрытие файла
	system("pause");
}


void Patron::GetInfoFromFileSold(int language) // Получение информации о клиентах-авто
{
	string lst = "\t\tlist\n";
	string ser = "Search by:    1->Client SN     2->Car Brand    3->Car year    0->Exit to the Menu\n";
	string sr = "Search: ";
	if (language == 2)
	{
		lst = "\t\t\t\tСписок\n";
		ser = "Искать по:    1->Ф.И. Клиента    2->Марка авто    3->Год выпуска    0->Выйти в меню\n";
		sr = "Искать: ";
	}
	deque <Patron> patrons;
	deque <Patron> clients;
	Patron p;
	FileManager<Patron> f("SoldCars.txt");
	f.read(&patrons);
	system("CLS");
	cout << lst;
	auto itera = patrons.begin(); int count = 1;
	while (itera != patrons.end()) // Вывод списка клиентов-авто
	{
		cout << "|"<<count << "| ";
		count++;
		cout << *itera;
		itera++;
	}
	f.close(); // Закрытие файла
	cout << ser; // Выбор сортировки списка авто
	int Number = 0;
	do
	{
		cout << sr; cin >> Number;
	} while (Number < 0 || Number > 3);
	if (Number == 0) return;
	clients = SearchBy(Number, patrons, language); // Вызов функции поиска клиентов
	int numberer = 0;
	p = ChangeInfo(&clients, &numberer, language); // Вызов функции изменения информации от клинтов 
	auto iter = patrons.begin();
	for (iter = patrons.begin(); iter != patrons.end(); iter++) // Поиск по VIN авто 
	{
		if (p.cars[0].VIN == (*iter).cars[0].VIN)
			break;
	}
	(*iter) = p;
	itera = patrons.begin();
	while (itera != patrons.end())
	{
		cout << *itera; // Вывод преобразованного списка
		itera++;
	}
	system("pause");
	f.writeDeque(patrons); // Запись клиентов в файл
}

void lang(int language, string *sel, string *ch, string *exec, string *cser, string *cnm, string *cpt, string *cadr, string *ser, string *nm,
	string *pt, string *adr, string *cto, string *inf, string *vin, string *cbr, string *cmd, string *cye, string *cpur, string *csal, string
 *dpur, string *dsal, string *brr, string *yearr, string *mdll, string *ddtd, string *ddsd, string *purpr, string *slprs) // Установка языка
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
		*sel = "Выберите клиента: ";
		*ch = "Изменить: 1->Данные Клиента   2->Данные авто  0->Выйти\n";
		*exec = "Выполнить: ";
		*cser = "1-> Изменить Фамилию\n";
		*cnm = "2-> Изменить Имя\n";
		*cpt = "3-> Изменить Отчество\n";
		*cadr = "4-> Изменить Адресс\n";
		*ser = "Фамилия: ";
		*nm = "Имя: ";
		*pt = "Отчество: ";
		*adr = "Адресс: ";
		*cto = " Изменить на -> ";
		*inf = "Данные были изменены!\n";
		*vin = "Введите VIN авто: ";
		*cbr = "1-> Изменить Марку\n";
		*cmd = "2-> Изменить Модель\n";
		*cye = "3-> Изменить Год выпуска\n";
		*cpur = "4-> Изменить Дату покупки\n";
			*csal = "5-> Изменить Дату продажи\n";
			*dpur = "6-> Изменить Цену покупки\n";
			*dsal = "7-> Изменить Цену продажи\n";
			*brr = "Марка: ";
			*mdll = "Модель: ";
			*yearr = "Год выпуска: ";
			*ddtd = "Дата покупки дд.мм.гг: ";
			*ddsd = "Дата продажи дд.мм.гг: ";
			*purpr = "Цена покупки в BYN: ";
			*slprs = "Цена продажи в BYN: ";
			break;
	default:
		break;
	}
}

Patron Patron::ChangeInfo(deque<Patron>* patrons, int *numberer, int language) // Изменение информации о клиенте
{
	string sel, chd, exec, cser, cnm, cpt, cadr, ser, nm, pt, adr, cto, inf, vin, cbr, cmd, cye, cpur, csal, dpur, dsal, brr,mdll,yearr,ddtd,
		ddsd,purpr,slprs;
	lang(language, &sel, &chd, &exec, &cser, &cnm, &cpt, &cadr, &ser, &nm, &pt, &adr, &cto, &inf, &vin, &cbr, &cmd, &cye, &cpur, &csal, &dpur, 
		&dsal, &brr, &mdll, &yearr, &ddtd,    // Установка языка интерфейса
		&ddsd, &purpr, &slprs); // Вызов функции установки языка
	Patron p;
	int VIN = 0, ch = 0;
	if ((*patrons).size() > 1) // Проверка ввода на корректность
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
		case 1: // Изменение информации о клиенте
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
			if (change == 1) { cout << ser << p.SerName << cto; cin >> p.SerName; } // Изменение Фамилии
			if (change == 2) { cout << nm << p.Name << cto; cin >> p.Name; } // Изм. имени
			if (change == 3) { cout << pt << p.Patronymic << cto; cin >> p.Patronymic; } // Изм.Отчества
			if (change == 4) { cout << adr << p.Adress << cto; cin >> p.Adress; } // Изм. Адресса
			system("CLS");
			cout << inf;
			cout << p;
			system("pause");
			system("CLS");
			break;
		case 2: // Изменение информации об автомобиле лиента
			system("CLS");
			cout << p;
			i = 0;
			if (p.NumberOfCars > 1) // Если автомобилей несколько, то выбрать один
			{
				cout << vin; cin >> VIN;
				while (VIN != p.cars[i].VIN) // Поиск авто по VIN
				{
					i++;
				}
			}
			cout << cbr; // Вывод данных авто
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
			if (ch == 1) { cout << brr << p.cars[i].Brand << cto; cin >> p.cars[i].Brand; }  // Изменение марки
			if (ch == 2) { cout << mdll << p.cars[i].Model << cto; cin >> p.cars[i].Model; } // Изменение модели
			if (ch == 3) { cout << yearr << p.cars[i].Year << cto; cin >> p.cars[i].Year; } // Изменение года выпуска
			if (ch == 4) {
				cout << ddtd << p.cars[i].Dayget << "." << p.cars[i].Monthget << "." << p.cars[i].YearOfPurchase // Изменение даты покупки автосалоном
					<< cto; cin >> p.cars[i].Dayget >> p.cars[i].Monthget >> p.cars[i].YearOfPurchase;
			}
			if (ch == 5) {
				cout << ddsd << p.cars[i].BuyDay << "." << p.cars[i].BuyMonth << "." << p.cars[i].BuyYear // Изменение даты продажи автосалоном
					<< cto; cin >> p.cars[i].BuyDay >> p.cars[i].BuyMonth >> p.cars[i].BuyYear;
			}
			if (ch == 6) { cout << purpr << p.cars[i].firstPrice << cto; cin >> p.cars[i].firstPrice; } // Изменение цены в автосалоне
			if (ch == 7) { cout << slprs << p.cars[i].ruble << cto; cin >> p.cars[i].ruble; } // Изменение цены продажи авто
			system("CLS");
			cout << inf; // Вывод преобразованной информации
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

deque <Patron> Patron::SearchBy(int operation, deque<Patron> patrons, int language) // Выбор поиска авто
{
	deque<Patron> p;
	switch (operation)
	{
	case 1:
		p = SearchByClient(&patrons, language); break; // Вызов функции поиска по ФИ
	case 2:  
		p = SearchByBrand(&patrons, language); break; // Вызов функции поиска по Марке авто
	case 3:
		p = SearchByYear(&patrons, language); break; // Вызов функции поиска по Году выпуска
	case 0: break;
	default:
		break;
	}
	return p;
}

void Patron::CancelLastActionSold(int operation, int index, int delnumb) // Отмена последнего действия(добавление, удаление авто-клиента)
{
	if (operation == 1) // Если последнее действие - добавление клиента-авто
	{
		deque <Patron> patrons;
		FileManager<Patron> f("SoldCars.txt");
		f.read(&patrons); // Чтение клиентов из файла
		FileManager<AutoInStock> r("Basket.txt");
		deque <AutoInStock> cars;
		r.read(&cars); // Чтение авто в наличии из корзины

		deque <AutoInStock> carsa;
		FileManager<AutoInStock> k("AutoInStock.txt");
		k.read(&carsa); // Чтение авто в наличии
		for (int i = 0; i < patrons[patrons.size() - 1].NumberOfCars; i++)
		{
			carsa.push_back(cars[cars.size() - 1]); // Взятие авто в наличии из корзины
			cars.pop_back(); // Удаление авто в наличии из корзины
		}
		r.writeDeque(cars); // Запись преобразованного списка авто в наличии в корзину
		k.writeDeque(carsa); // Запись списка авто в наличии в файл
		patrons.pop_back(); // Удаление клиента - авто 
		f.writeDeque(patrons); // Запись клиентов - авто в файл
	}
	else if (operation == 2) // Если последнее дейтсвие - удаление клиента - авто
	{
		deque <Patron> patrons;
		FileManager<Patron> f("SoldCars.txt");
		f.read(&patrons); // Чтение клиентов - авто из файла

		deque <Patron> patronsdel;
		FileManager<Patron> W("BasketSoldCars.txt");
		W.read(&patronsdel); // Чтение удаленного клиента - авто из корзины
		auto iter = patrons.begin() + delnumb; // Инициализация итератора на восстанавливаемого клиента
		patrons.insert(iter, patronsdel[patronsdel.size() - 1]); // Вставка клиента в список 
		patronsdel.pop_back(); // Удаление клиента из корзины
		W.writeDeque(patronsdel); // Запись в файл клиентов
		f.writeDeque(patrons);  // Запись в файл клиентов
	}
}