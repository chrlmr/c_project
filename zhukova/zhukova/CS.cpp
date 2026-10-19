#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "CS.h"
#include "utils.h"

int CS::MaxID = 0;

CS::CS()
{
	id = MaxID++;
	name = "";
	countWorkshops = 0;
	workingWorkshops = 0;
	classStation = 1;
}

int CS::getId() const
{
	return id;
}

double CS::getUnusedPercent() const
{
	return (countWorkshops - workingWorkshops) * 100.0 / countWorkshops;
}

std::ostream& operator << (std::ostream& out, const CS& cs)
{
	out << "Id КС: " << cs.id << '\n';
	out << "Название КС: " << cs.name << '\n';
	out << "Количество цехов: " << cs.countWorkshops << '\n';
	out << "Количество цехов в работе: " << cs.workingWorkshops << '\n';
	out << "Процент незадействованных цехов: " << cs.getUnusedPercent() << '\n';
	out << "Класс станции: " << cs.classStation << '\n';
	return out;
}

std::istream& operator >> (std::istream& in, CS& cs)
{
	std::cout << "Введите название КС: ";
	INPUT_LINE(in, cs.name);

	std::cout << "Введите количество цехов: ";
	cs.countWorkshops = GetCorrectNumber(1, 1000);

	std::cout << "Введите количество цехов в работе: ";
	cs.workingWorkshops = GetCorrectNumber(0, cs.countWorkshops);

	std::cout << "Введите класс станции (1 - маленькая, 2 - средняя, 3 - крупная): ";
	cs.classStation = GetCorrectNumber(1, 3);

	return in;
}

std::ofstream& operator << (std::ofstream& out, const CS& cs)
{
	out << cs.id << std::endl;
	out << cs.name << std::endl;
	out << cs.countWorkshops << std::endl;
	out << cs.workingWorkshops << std::endl;
	out << cs.classStation << std::endl;
	return out;
}

std::ifstream& operator >> (std::ifstream& in, CS& cs)
{
	in >> cs.id;
	std::getline(in >> std::ws, cs.name);
	in >> cs.countWorkshops;
	in >> cs.workingWorkshops;
	in >> cs.classStation;
	CS::MaxID = std::max(CS::MaxID, cs.id + 1);
	return in;
}