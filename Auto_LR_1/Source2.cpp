#include "Patron.h"

void SoldCarsMenuSold(int operation, int *undo, int *delnumb, int language) // ���� ������� ���� � ������� (Auto in stock)
{
	Patron p;
	switch (operation)
	{
	case 1: p.add_car_to_SoldCars(&(*undo), language);	break; // ���������� ����������� � ������ "���� � �������"

	case 4: p.DisplaySoldCars(language);	break;

	case 2: // �������� ���������� �� ������ "������-����"
		system("CLS");
		(*delnumb) = p.DeleteCarSold(language);
		break;

	case 3: // ��������� ������ "�������-����", ������� � �����
		system("CLS");
		p.GetInfoFromFileSold(language);
		break;

	case 0: break;

	default: break;
	}
}