#include "InputException.h"
void InputException::ChangeDate(int carnumber, Patron *p) // Обработка неверно введенной даты
{
	int operation = 0;
	cout << "Change please: 1-> Day of purchase  or  2-> Day of sale   3->Continue\n";
	cin >> operation;
	if (operation == 1)
	{
		cout << "Date of purchase dd.mm.yy: ";
		cin >> (*p).cars[carnumber].BuyDay >> (*p).cars[carnumber].BuyMonth >> (*p).cars[carnumber].BuyYear;
	}
	else if (operation == 2)
	{
		cout << "Date of sale dd.mm.yy: ";
		cin >> (*p).cars[carnumber].Dayget >> (*p).cars[carnumber].Monthget >> (*p).cars[carnumber].YearOfPurchase;
	}
}

void InputException::UpperCase(Patron *p) // Обработка ФИО с маленькой буквы
{
	if ((*p).SerName[0] >= 'a' && (*p).SerName[0] <= 'z' || (*p).SerName[0] >= 'а' && (*p).SerName[0] <= 'я')
		(*p).SerName[0] -= 32;
	if ((*p).Name[0] >= 'a' && (*p).Name[0] <= 'z' || (*p).Name[0] >= 'а' && (*p).Name[0] <= 'я')
		(*p).Name[0] -= 32;
	if ((*p).Patronymic[0] >= 'a' && (*p).Patronymic[0] <= 'z' || (*p).Patronymic[0] >= 'а' && (*p).Patronymic[0] <= 'я')
		(*p).Patronymic[0] -= 32;
}
