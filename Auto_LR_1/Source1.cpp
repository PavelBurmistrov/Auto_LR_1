#include "AutoInStock.h"

int AutoinStockMenu(int operation, int *indexofremovecar, int language) // ���� ������� ���� � ������� (Auto in stock)
{
	AutoInStock autom;
	int NumberOfAddedCar = 0;
		switch (operation)
		{
		case 1: // ���������� ����������� � ������ "���� � �������"
		{
		    NumberOfAddedCar = autom.NumberOfAddedCars(language);
			deque <AutoInStock> cars(NumberOfAddedCar);
			autom.add_car_to_AutoInStock(NumberOfAddedCar, cars, language);
		}
		break;
		case 2: // �������� ���������� �� ������ "���� � �������"
		{
			system("CLS");
			autom.DeleteCar(&(*indexofremovecar), language);
		}
		break;
		case 3: // ��������� ������ "���� � �������", ������� � �����
			autom.GetInfoFromFile(language);
			break;
		case 0: break;
		default:
			break;
		}
		return NumberOfAddedCar;
}