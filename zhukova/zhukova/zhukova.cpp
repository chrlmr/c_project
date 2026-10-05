
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Pipe
{
private:
	string name;
	int length;
	int diameter;
	bool repair;

public:
	void setName(string value)
	{
		name = value;
	}

	string getName()
	{
		return name
	}

	void setLength(int value)
	{
		length = value;
	}

	int getLength()
	{
		return length;
	}

	void setDiameter(int value)
	{
		diameter = value;
	}

	int getDiameter()
	{
		return diameter;
	}

	void setRepair(bool value)
	{
		repair = value;
	}

	bool getRepair()
	{
		return repair;
	}

	void printPipe()
	{
		cout << "Название трубы: " << name << endl;
		cout << "Длина трубы: " << length << endl;
		cout << "Диаметр трубы: " << diameter << endl;
		cout << "Труба в ремонте?: " << (repair ? "Да" : "Нет") << endl;
	}



};

class CS
{
private:
	string name;
	int countWorkshops;
	int workingWorkshops;
	int classStation;

public:
	void setName(string value)
	{
		name = value;
	}

	string getName()
	{
		return name
	}

	void setCountWorkshops(int value)
	{
		countWorkshops = value;
	}

	int getCountWorkshops()
	{
		return countWorkshops;
	}

	void setWorkingWorkshops(int value)
	{
		workingWorkshops = value;
	}

	int getWorkingWorkshops()
	{
		return workingWorkshops;
	}

	void setClassStation(int value)
	{
		classStation = value;
	}

	int getClassStation()
	{
		return classStation;
	}

	void printCS()
	{
		cout << "Название КС: " << name << endl;
		cout << "Количество цехов: " << countWorkshops << endl;
		cout << "Количество цехов в работе: " << workingWorkshops << endl;
		cout << "Класс станции: " << classStation << endl;
	}


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
	string name;
	cout << "Введите название трубы : ";
	getline(cin >> ws, name);
	pipe.setName(name);

	cout << "Введите длину трубы(км): ";
	int length = proverkaVvoda();
	while (length <= 0)
	{
		cout << "Ошибка. Введите положительное число: ";
		length = proverkaVvoda();
	}
	pipe.setLength(length);

	cout << "Введите диаметр трубы(мм): ";
	int diameter = proverkaVvoda();
	while (diameter <= 0)
	{
		cout << "Ошибка. Введите положительное число";
		diameter = proverkaVvoda();
	}
	pipe.setDiameter(diameter);

	cout << "Труба в ремонте? (1 - да, 0 - нет): ";
	int remont = proverkaVvoda();
	while (remont < 0 || remont > 1)
	{
		cout << "Ошибка. Введите 1 или 0: ";
		remont = proverkaVvoda();
	}
	pipe.setRepair(remont);

}

void newCS(CS& cs)
{
	string name;
	cout << "Введите название КС: ";
	getline(cin >> ws, name);
	cs.setName(name);

	cout << "Введите количество цехов: ";
	int countWorkshops = proverkaVvoda();
	while (countWorkshops <= 0)
	{
		cout << "Ошибка. Количество должно быть больше 0: ";
		countWorkshops = proverkaVvoda();
	}
	cs.setCountWorkshops(countWorkshops);

	cout << "Введите количество цехов в работе: ";
	int workingWorkshops = proverkaVvoda();
	while (workingWorkshops < 0 || workingWorkshops > countWorkshops)
	{
		cout << "Ошибка. Количество работающих цехов может быть от 0 до " << countWorkshops << ": ";
		workingWorkshops = proverkaVvoda();
	}
	cs.setWorkingWorkshops(workingWorkshops);

	cout << "Введите класс станции (1 - маленькая, 2 - средняя, 3 - крупная): ";
	int classStation = proverkaVvoda();
	while (classStation < 1 || classStation >3)
	{
		cout << "Ошибка. Введите число от 1 до 3: ";
		classStation = proverkaVvoda();
	}
	cs.setClassStation(classStation);


}


void editPipe(Pipe& pipe)
{
	cout << "Режим редактирования трубы" << endl;
	cout << "Убрать из ремонта - 0" << endl;
	cout << "Отправить в ремонт - 1" << endl;

	cout << "Сделайте выбор: ";

	int vibor = proverkaVvoda();

	while (vibor < 0 || vibor > 1)
	{
		cout << "Ошибка. Введите 0 или 1: ";
		vibor = proverkaVvoda();
	}

	pipe.setRepair(vibor == 1);
	cout << "Труба в ремонте: " << (pipe.getRepair() ? "Да" : "Нет") << endl;
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
		if (cs.getWorkingWorkshops() != cs.getCountWorkshops())
		{
			++cs.setWorkingWorkshops();
			cout << "Цех запущен" << endl;
		}
		else
		{
			cout << "Все цеха уже запущены" << endl;
		}
	}
	if (vibor == 2)
	{
		if (cs.getWorkingWorkshops() > 0)
		{
			--cs.setWorkingWorkshops();
			cout << "Цех остановлен" << endl;
		}
		else
		{
			cout << "Невозможно остановить цех, т.к. нет запущенных цехов" << endl;
		}
	}
}

void savePipe(ofstream& file, const Pipe& pipe)
{
	if (pipe.name.empty()) {
		return;
	}

	file << pipe.name << endl;
	file << pipe.length << endl;
	file << pipe.diameter << endl;
	file << pipe.repair << endl;
}

void saveCS(ofstream& file, const CS& cs)
{
	if (cs.name.empty()) {
		return;
	}
	file << cs.name << endl;
	file << cs.countWorkshops << endl;
	file << cs.workingWorkshops << endl;
	file << cs.classStation << endl;
}

void zagruzkaPipe(ifstream& file, Pipe& pipe)
{
	getline(file >> ws, pipe.name);
	file >> pipe.length;
	file >> pipe.diameter;
	file >> pipe.repair;
}

void zagruzkaCS(ifstream& file, CS&cs)
{
	getline(file >> ws, cs.name);
	file >> cs.countWorkshops;
	file >> cs.workingWorkshops;
	file >> cs.classStation;
}


void saveFile(const Pipe& pipe, const CS& cs)
{
	string name;
	cout << "Введите имя файла с расширением: ";
	getline(cin >> ws, name);
	ofstream file(name);

	if (!file.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
		return; 
	}
	
	savePipe(file, pipe);
	saveCS(file, cs);
	cout << "Данные сохранены" << endl;
	

}

void zagruzitFile(Pipe& pipe, CS& cs)
{
	string name;
	cout << "Введите имя файла с расширением: ";
	getline(cin >> ws, name);
	ifstream file(name);

	if (!file.is_open())
	{
		cout << "Ошибка чтения данных" << endl;
	}
	else
	{
		zagruzkaPipe(file, pipe);
		zagruzkaCS(file, cs);
		cout << "Данные загружены" << endl;
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
			saveFile(pipe, cs);
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