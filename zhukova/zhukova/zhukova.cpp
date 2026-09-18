
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct Pipe
{
	string name;
	int length;
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

int proverkaVvoda()
{
	int number;
	cin >> number;

	while (cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(100, '\n');

		cout << "Ошибка. Введите целое число: ";
		cin >> number;
	}
	return number;
}

void newPipe(Pipe& pipe)
{
	cout << "Введите название трубы : ";
	cin >> pipe.name;

	cout << "Введите длину трубы(км): ";
	pipe.length = proverkaVvoda();
	while (pipe.length <= 0)
	{
		cout << "Ошибка. Введите положительное число: ";
		pipe.length = proverkaVvoda();
	}

	cout << "Введите диаметр трубы(мм): ";
	pipe.diameter = proverkaVvoda();
	while (pipe.diameter <= 0)
	{
		cout << "Ошибка. Введите положительное число";
		pipe.diameter = proverkaVvoda();
	}
	cout << "Труба в ремонте? (1 - да, 0 - нет): ";
	int remont = proverkaVvoda();
	while (remont < 0 || remont > 1)
	{
		cout << "Ошибка. Введите 1 или 0: ";
		remont = proverkaVvoda();
	}
	pipe.repair = remont;

}

void newCS(CS&cs)
{
	cout << "Введите название КС: ";
	cin >> cs.name;

	cout << "Введите количество цехов: ";
	cs.countWorkshops = proverkaVvoda();
	while (cs.countWorkshops <= 0)
	{
		cout << "Ошибка. Количество должно быть больше 0: ";
		cs.countWorkshops = proverkaVvoda();
	}

	cout << "Введите количество цехов в работе: ";
	cs.workingWorkshops = proverkaVvoda();
	while (cs.workingWorkshops < 0 || cs.workingWorkshops > cs.countWorkshops)
	{
		cout << "Ошибка. Количество работающих цехов может быть от 0 до " << cs.countWorkshops << ": ";
		cs.workingWorkshops = proverkaVvoda();
	}
	cout << "Введите класс станции (1 - маленькая, 2 - средняя, 3 - крупная): ";
	cs.classStation = proverkaVvoda();
	while (cs.classStation < 1 || cs.classStation >3)
	{
		cout << "Ошибка. Введите число от 1 до 3: ";
		cs.classStation = proverkaVvoda();
	}


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
	vibor = proverkaVvoda();
	while (vibor < 1 || vibor >2)
	{
		cout << "Ошибка. Введите 1 или 2: ";
		vibor = proverkaVvoda();
	}

	if (vibor == 1)
	{
		if (pipe.repair == false)
		{
			pipe.repair = true;
			cout << "Труба теперь в ремонте" << endl;
		}
		else
		{
			cout << "Труба уже в ремонте" << endl;
		}
		
	}
	if (vibor == 2)
	{
		if (pipe.repair == true)
		{
			pipe.repair = false;
			cout << "Труба больше не в ремонте" << endl;
		}
		else
		{
			cout << "Труба уже не в ремонте" << endl;
		}
		
	}
}

void editCS(CS& cs)
{
	cout << "Режим редактирования КС" << endl;
	cout << "Запустить цех - 1" << endl;
	cout << "Остановить цех - 2" << endl;
	int vibor;
	cout << "Сделайте выбор :" << endl;
	vibor = proverkaVvoda();
	while (vibor <1 || vibor >2)
	{
		cout << "Ошибка. Введите 1 или 2: ";
		vibor = proverkaVvoda();
	}

	if (vibor == 1)
	{
		if (cs.workingWorkshops != cs.countWorkshops)
		{
			++cs.workingWorkshops;
			cout << "Цех запущен" << endl;
		}
		else
		{
			cout << "Все цеха уже запущены" << endl;
		}
	}
	if (vibor == 2)
	{
		if (cs.workingWorkshops > 0)
		{
			--cs.workingWorkshops;
			cout << "Цех остановлен" << endl;
		}
		else
		{
			cout << "Невозможно остановить цех, т.к. нет запущенных цехов" << endl;
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

		cout << "Данные сохранены" << endl;
	}
	else
	{
		cout << "Ошибка записи в файл" << endl;
	}
	

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
		vibor = proverkaVvoda();

		while (vibor < 0 || vibor >7)
		{
			cout << "Ошибка. Введите число из меню: ";
			vibor = proverkaVvoda();
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