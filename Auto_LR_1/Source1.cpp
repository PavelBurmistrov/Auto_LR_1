#include "AutoInStock.h"

int AutoinStockMenu(int operation, int *indexofremovecar, int language) // Меню раздела Авто в наличии (Auto in stock)
{
	AutoInStock autom;
	int NumberOfAddedCar = 0;
		switch (operation)
		{
		case 1: // Добавление автомобилей в список "Авто в наличии"
		{
		    NumberOfAddedCar = autom.NumberOfAddedCars(language);
			deque <AutoInStock> cars(NumberOfAddedCar);
			autom.add_car_to_AutoInStock(NumberOfAddedCar, cars, language);
		}
		break;
		case 2: // Удаление автомобиля из списка "Авто в наличии"
		{
			system("CLS");
			autom.DeleteCar(&(*indexofremovecar), language);
		}
		break;
		case 3: // Полчуение списка "Авто в наличии", чтением с файла
			autom.GetInfoFromFile(language);
			break;
		case 0: break;
		default:
			break;
		}
		return NumberOfAddedCar;
}