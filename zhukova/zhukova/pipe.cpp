#include <iostream>
#include <string>
#include "pipe.h"

//void Pipe::setName(std::string value)
//{
//	name = value;
//}
//void Pipe::setLength(int value)
//{
//	length = value;
//}
//
//void Pipe::setDiameter(int value)
//{
//	diameter = value;
//}
//
//void Pipe::setRepair(bool value)
//{
//	repair = value;
//}

std::ostream& operator << (std::ostream& out, const Pipe& pipe)
{
	out << "Название трубы: " << pipe.name << '\n';
	out << "Длина трубы: " << pipe.length << '\n';
	out << "Диаметр трубы: " << pipe.diameter << '\n';
	out << "Труба в ремонте?: " << (pipe.repair ? "Да" : "Нет") << '\n';
	return out;
}

std::istream& operator>>(std::istream& in, Pipe& pipe)
{
	std::cout << "Введите название трубы : ";
	std::getline(in >> std::ws, pipe.name);

	std::cout << "Введите длину трубы(км): ";
	in >> pipe.length;

	std::cout << "Введите диаметр трубы(мм): ";
	in >> pipe.diameter;
	
	std::cout << "Труба в ремонте? (1 - да, 0 - нет): ";
	int remont;
	in >> remont;
	

	return in;

}
