
#include <iostream>
#include <string>
using namespace std;
struct Pipe
{
	string name;
	double length;
	int diameter;
	bool repair;
};

struct CS
{
	string name;
	int countWorkshops;
	int workingWorkshops;
	int classStation;
};

Pipe newPipe()
{
	Pipe p;
	cout << "Введите название трубы : ";
	cin >> p.name;
	cout << "Введите длину трубы(км): ";
	cin >> p.length;
	cout << "Введите диаметр трубы(мм): ";
	cin >> p.diameter;
	cout << "Труба в ремонте? (1 - да, 0 - нет): ";
	cin >> p.repair;
	
	return p;
}

CS newCS()
{
	CS cs;
	cout << "Введите название КС: ";
	cin >> cs.name;
	cout << "Введите количество цехов: ";
	cin >> cs.countWorkshops;
	cout << "Введите количество цехов в работе: ";
	cin >> cs.workingWorkshops;
	cout << "Введите класс станции (1 - маленькая, 2 - средняя, 3 - крупная): ";
	cin >> cs.classStation;

	return cs;
}

int main()
{
	setlocale(LC_ALL, "RU");
	Pipe pipe = newPipe();
	CS cs = newCS();
	return 0;
}