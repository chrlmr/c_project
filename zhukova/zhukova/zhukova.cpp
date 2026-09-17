
#include <iostream>
#include <string>
#include <fstream>
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

 void newPipe(Pipe&pipe)
{
	cout << "Введите название трубы : ";
	cin >> pipe.name;
	cout << "Введите длину трубы(км): ";
	cin >> pipe.length;
	while (!proverkaVvoda() || pipe.diameter <= 0)
	{
		cout << "Ошибка. Введите положительное число: ";
		cin >> pipe.length;
	}
	cout << "Введите диаметр трубы(мм): ";
	cin >> pipe.diameter;
	cout << "Труба в ремонте? (1 - да, 0 - нет): ";
	cin >> pipe.repair;

}

void newCS(CS&cs)
{
	cout << "Введите название КС: ";
	cin >> cs.name;
	cout << "Введите количество цехов: ";
	cin >> cs.countWorkshops;
	cout << "Введите количество цехов в работе: ";
	cin >> cs.workingWorkshops;
	cout << "Введите класс станции (1 - маленькая, 2 - средняя, 3 - крупная): ";
	cin >> cs.classStation;

}

void printPipe(const Pipe& pipe)
{
	cout << "Название трубы: " << pipe.name << endl;
	cout << "Длина трубы: " << pipe.length << endl;
	cout << "Диаметр трубы: " << pipe.diameter << endl;
	cout << "Труба в ремонте?: " << (pipe.repair? "Да":"Нет") << endl;
}

void printCS(const CS& cs)
{
	cout << "Название КС: " << cs.name << endl;
	cout << "Количество цехов: " << cs.countWorkshops << endl;
	cout << "Количество цехов в работе: " << cs.workingWorkshops << endl;
	cout << "Класс станции: " << cs.classStation << endl;
}

void editPipe(Pipe& pipe)
{
	cout << "Режим редактирования трубы" << endl;
	cout << "Отправить в ремонт - 1" << endl;
	cout << "Убрать из ремонта - 2" << endl;
	int vibor;
	cout << "Сделайте выбор: ";
	cin >> vibor;

	if (vibor == 1)
	{
		pipe.repair = true;
		cout << "Труба теперь в ремонте";
	}
	else if (vibor == 2)
	{
		pipe.repair = false;
		cout << "Труба больше не в ремонте";
	}
}

void editCS(CS& cs)
{
	cout << "Режим редактирования КС" << endl;
	cout << "Запустить цех - 1" << endl;
	cout << "Остановить цех - 2" << endl;
	int vibor;
	cout << "Сделайте выбор";
	cin >> vibor;

	if (vibor == 1)
	{
		if (cs.workingWorkshops != cs.countWorkshops)
		{
			++cs.workingWorkshops;
			cout << "Цех запущен";
		}
		else
		{
			cout << "Все цеха уже запущены";
		}
	}
	else if (vibor == 2)
	{
		if (cs.workingWorkshops > 0)
		{
			--cs.workingWorkshops;
			cout << "Цех остановлен";
		}
		else
		{
			cout << "Нет запущенных цехов";
		}
	}
}

void saveFile(const Pipe& pipe, const CS& cs)
{
	ofstream fout("file.txt");

	if (fout)
	{
		fout << pipe.name << endl;
		fout << pipe.length << endl;
		fout << pipe.diameter << endl;
		fout << pipe.repair << endl;

		fout << cs.name << endl;
		fout << cs.countWorkshops << endl;
		fout << cs.workingWorkshops << endl;
		fout << cs.classStation << endl;
	}
	else
	{
		cout << "Ошибка записи в файл" << endl;
	}
	fout.close();
	

}

void zagruzitFile(Pipe& pipe, CS& cs)
{
	ifstream fin("file.txt");

	if (fin)
	{
		fin >> pipe.name;
		fin >> pipe.length;
		fin >> pipe.diameter;
		fin >> pipe.repair;

		fin >> cs.name;
		fin >> cs.countWorkshops;
		fin >> cs.workingWorkshops;
		fin >> cs.classStation;

		cout << "Данные загружены" << endl;
	}
	else
	{
		cout << "Ошибка загрузки данных из файла";
	}
	fin.close();
}

bool proverkaVvoda()
{
	if (cin.fail)
	{
		cin.clear();
		cin.ignore(100, '\n');

		return false;
	}
	return true;
}


int main()
{
	setlocale(LC_ALL, "RU");

	Pipe pipe;
	CS cs;

	while (true)
	{
		cout << "1. Добавить трубу" << endl;
		cout << "2. Добавить КС" << endl;
		cout << "3. Просмотр всех объектов" << endl;
		cout << "4. Редактировать трубу" << endl;
		cout << "5. Редактировать КС" << endl;
		cout << "6. Сохранить" << endl;
		cout << "7. Загрузить" << endl;
		cout << "0. Выход" << endl;

		int vibor;
		cout << "Сделайте выбор: ";
		cin >> vibor;

		while (cin.fail())
		{
			cout << "Ошибка. Введите число из меню: ";
			cin.clear();
			cin.ignore(100, '\n');
			cin >> vibor;
		}


		switch (vibor)
		{
		case 1:
			newPipe(pipe);
			break;
		case 2:
			newCS(cs);
			break;
		case 3:
			if (pipe.name.empty())
			{
				cout << "Труба не создана. Ее просмотр невозможен." << endl;
			}
			else
			{
				printPipe(pipe);
			}
			if (cs.name.empty())
			{
				cout << "КС не создана. Ее просмотр невозможен." << endl;
			}
			else
			{
				printCS(cs);
			}
			break;
		case 4:
			if (pipe.name.empty())
			{
				cout << "Труба не создана. Редактирование невозможно." << endl;
			}
			else
			{
				editPipe(pipe);
			}
			break;
		case 5:
			if (cs.name.empty())
			{
				cout << "КС не создана. Редактирование невозможно." << endl;
			}
			else
			{
				editCS(cs);
			}
			break;
		case 6:
			if (pipe.name.empty() || cs.name.empty())
			{
				cout << "Не все данные заполнены. Сохранение невозможно" << endl;
			}
			else
			{
				saveFile(pipe, cs);
				cout << "Данные сохранены" << endl;
			}
			break;
		case 7:
			zagruzitFile(pipe, cs);
			break;
		case 0:
			return 0;
		default:
			cout << "Ошибка. Введите число из меню" << endl;
		}





	}


	
	return 0;
}