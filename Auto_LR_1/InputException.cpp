#include "InputException.h"
void InputException::ChangeDate(int carnumber, Patron *p) // ��������� ������� ��������� ����
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

void InputException::UpperCase(Patron *p) // ��������� ��� � ��������� �����
{
	if ((*p).SerName[0] >= 'a' && (*p).SerName[0] <= 'z' || (*p).SerName[0] >= '�' && (*p).SerName[0] <= '�')
		(*p).SerName[0] -= 32;
	if ((*p).Name[0] >= 'a' && (*p).Name[0] <= 'z' || (*p).Name[0] >= '�' && (*p).Name[0] <= '�')
		(*p).Name[0] -= 32;
	if ((*p).Patronymic[0] >= 'a' && (*p).Patronymic[0] <= 'z' || (*p).Patronymic[0] >= '�' && (*p).Patronymic[0] <= '�')
		(*p).Patronymic[0] -= 32;
}
