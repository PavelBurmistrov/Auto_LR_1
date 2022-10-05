#include "Patron.h"

void SoldCarsMenuSold(int operation, int *undo, int *delnumb, int language) // Меню раздела Авто в наличии (Auto in stock)
{
	Patron p;
	switch (operation)
	{
	case 1: p.add_car_to_SoldCars(&(*undo), language);	break; // Добавление автомобилей в список "Авто в наличии"

	case 4: p.DisplaySoldCars(language);	break;

	case 2: // Удаление автомобиля из списка "Клиент-авто"
		system("CLS");
		(*delnumb) = p.DeleteCarSold(language);
		break;

	case 3: // Полчуение списка "Клиента-авто", чтением с файла
		system("CLS");
		p.GetInfoFromFileSold(language);
		break;

	case 0: break;

	default: break;
	}
}