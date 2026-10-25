#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "pipe.h"
#include "utils.h"

int Pipe::MaxID = 1;

Pipe::Pipe()
{
	id = MaxID++;
	name = "";
	length = 0;
	diameter = 0;
	repair = false;
}

int Pipe::getId() const
{
	return id;
}

void Pipe::ResetMaxID()
{
	MaxID = 1;
}

void Pipe::editRepair(bool value)
{
	repair = value;
}

void Pipe::edit()
{
	std::cout << "Режим редактирования трубы" << std::endl;
	std::cout << "Убрать из ремонта - 0" << std::endl;
	std::cout << "Отправить в ремонт - 1" << std::endl;

	std::cout << "Сделайте выбор: ";
	int vibor = GetCorrectNumber(0, 1);

	editRepair(vibor == 1);
}




std::ostream& operator << (std::ostream& out, const Pipe& pipe)
{
	out << "Id трубы: " << pipe.id << '\n';
	out << "Название трубы: " << pipe.name << '\n';
	out << "Длина трубы: " << pipe.length << '\n';
	out << "Диаметр трубы: " << pipe.diameter << '\n';
	out << "Труба в ремонте?: " << (pipe.repair ? "Да" : "Нет") << '\n';
	return out;
}

std::istream& operator>>(std::istream& in, Pipe& pipe)
{
	std::cout << "Введите название трубы : ";
	INPUT_LINE(in, pipe.name);

	std::cout << "Введите длину трубы(км): ";
	pipe.length = GetCorrectNumber(1, 100000);

	std::cout << "Введите диаметр трубы(мм): ";
	pipe.diameter = GetCorrectNumber(1, 100000);

	std::cout << "Труба в ремонте? (1 - да, 0 - нет): ";
	pipe.repair = GetCorrectNumber(0, 1);

	return in;
}

std::ofstream& operator << (std::ofstream& out, const Pipe& pipe)
{
	out << pipe.id << std::endl;
	out << pipe.name << std::endl;
	out << pipe.length << std::endl;
	out << pipe.diameter << std::endl;
	out << pipe.repair << std::endl;
	return out;
}

std::ifstream& operator >> (std::ifstream& in, Pipe& pipe)
{
	in >> pipe.id;
	std::getline(in >> std::ws, pipe.name);
	in >> pipe.length;
	in >> pipe.diameter;
	in >> pipe.repair;
	Pipe::MaxID = std::max(Pipe::MaxID, pipe.id + 1);
	return in;
}