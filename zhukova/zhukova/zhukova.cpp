
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <format>
#include "pipe.h"
#include "CS.h"
#include "utils.h"
using namespace std;
using namespace chrono;

//  Фильтры
// Каждый фильтр: "подходит ли этот объект под условие?"

bool CheckPipeByName(const Pipe& pipe, string param)
{
	return pipe.name.find(param) != string::npos;   // название содержит param
}

bool CheckPipeByRepair(const Pipe& pipe, bool param)
{
	return pipe.repair == param;
}

bool CheckCSByName(const CS& cs, string param)
{
	return cs.name.find(param) != string::npos;
}

bool CheckCSByUnused(const CS& cs, double param)
{
	return cs.getUnusedPercent() >= param;   // процент незадействованных цехов не меньше param
}

//  Вспомогательная функция 

// есть ли число x в векторе v
bool contains(const vector<int>& v, int x)
{
	for (int element : v)
	{
		if (element == x)
			return true;
	}
	return false;
}

// 
void addPipe(unordered_map<int, Pipe>& pipes)
{
	Pipe pipe;
	cin >> pipe;
	pipes.emplace(pipe.getId(), pipe);   // кладем трубу в map под ее id
}

void addCS(unordered_map<int, CS>& stations)
{
	CS cs;
	cin >> cs;
	stations.emplace(cs.getId(), cs);
}



void showAll(const unordered_map<int, Pipe>& pipes, const unordered_map<int, CS>& stations)
{
	if (pipes.empty())
		cout << "Трубы не созданы. Их просмотр невозможен." << endl;
	for (const auto& [id, pipe] : pipes)
		cout << pipe << endl;

	if (stations.empty())
		cout << "КС не созданы. Их просмотр невозможен." << endl;
	for (const auto& [id, cs] : stations)
		cout << cs << endl;
}

// вывод труб, id которых лежат в векторе ids
void printPipes(const unordered_map<int, Pipe>& pipes, const vector<int>& ids)
{
	if (ids.empty())
	{
		cout << "Ничего не найдено" << endl;
		return;
	}
	for (int id : ids)
		cout << pipes.at(id) << endl;
}

// вывод КС, id которых лежат в векторе ids
void printStations(const unordered_map<int, CS>& stations, const vector<int>& ids)
{
	if (ids.empty())
	{
		cout << "Ничего не найдено" << endl;
		return;
	}
	for (int id : ids)
		cout << stations.at(id) << endl;
}


void editPipe(Pipe& pipe, bool repair)
{
	pipe.repair = repair;
}


void chooseEditPipe(Pipe& pipe)
{
	cout << "Режим редактирования трубы" << endl;
	cout << "Убрать из ремонта - 0" << endl;
	cout << "Отправить в ремонт - 1" << endl;

	cout << "Сделайте выбор: ";
	int vibor = GetCorrectNumber(0, 1);

	editPipe(pipe, vibor == 1);
	cout << pipe;
}


void editCS(CS& cs)
{
	cout << "Режим редактирования КС" << endl;
	cout << "Запустить цех - 1" << endl;
	cout << "Остановить цех - 2" << endl;

	cout << "Сделайте выбор: ";
	int vibor = GetCorrectNumber(1, 2);

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

// спрашивает id трубы и редактирует ее
void editPipeById(unordered_map<int, Pipe>& pipes)
{
	cout << "Введите id трубы: ";
	int id = GetCorrectNumber(0, 100000);

	if (pipes.count(id) == 0)
		cout << "Трубы с таким id нет" << endl;
	else
		chooseEditPipe(pipes.at(id));
}

// спрашивает id КС и редактирует ее
void editCSById(unordered_map<int, CS>& stations)
{
	cout << "Введите id КС: ";
	int id = GetCorrectNumber(0, 100000);

	if (stations.count(id) == 0)
		cout << "КС с таким id нет" << endl;
	else
		editCS(stations.at(id));
}



void deletePipe(unordered_map<int, Pipe>& pipes)
{
	cout << "Введите id трубы: ";
	int id = GetCorrectNumber(0, 100000);

	if (pipes.count(id) == 0)
		cout << "Трубы с таким id нет" << endl;
	else
	{
		pipes.erase(id);
		cout << "Труба удалена" << endl;
	}
}

void deleteCS(unordered_map<int, CS>& stations)
{
	cout << "Введите id КС: ";
	int id = GetCorrectNumber(0, 100000);

	if (stations.count(id) == 0)
		cout << "КС с таким id нет" << endl;
	else
	{
		stations.erase(id);
		cout << "КС удалена" << endl;
	}
}


// Поиск возвращает вектор id найденных объектов 

vector<int> searchPipes(const unordered_map<int, Pipe>& pipes)
{
	cout << "Поиск труб: 1 - по названию, 2 - по признаку \"в ремонте\": ";
	int vibor = GetCorrectNumber(1, 2);

	if (vibor == 1)
	{
		string name;
		cout << "Введите название (или его часть): ";
		INPUT_LINE(cin, name);
		return FindByFilter(pipes, CheckPipeByName, name);
	}

	cout << "Труба в ремонте? (1 - да, 0 - нет): ";
	bool repair = GetCorrectNumber(0, 1);
	return FindByFilter(pipes, CheckPipeByRepair, repair);
}

vector<int> searchCS(const unordered_map<int, CS>& stations)
{
	cout << "Поиск КС: 1 - по названию, 2 - по проценту незадействованных цехов: ";
	int vibor = GetCorrectNumber(1, 2);

	if (vibor == 1)
	{
		string name;
		cout << "Введите название (или его часть): ";
		INPUT_LINE(cin, name);
		return FindByFilter(stations, CheckCSByName, name);
	}

	cout << "Введите минимальный процент незадействованных цехов (0-100): ";
	double percent = GetCorrectNumber(0.0, 100.0);
	return FindByFilter(stations, CheckCSByUnused, percent);
}

// Пакетное редактирование труб

void batchEditPipes(unordered_map<int, Pipe>& pipes)
{
	//  ищем подмножество и показываем его
	vector<int> found = searchPipes(pipes);
	printPipes(pipes, found);
	if (found.empty())
		return;

	// выбираем, с какими трубами работать со всеми найденными или по id
	vector<int> chosen = found;

	cout << "1 - выбрать все найденные, 2 - выбрать по id: ";
	int vibor = GetCorrectNumber(1, 2);

	if (vibor == 2)
	{
		chosen.clear();

		cout << "Сколько труб выбрать: ";
		unsigned int count = GetCorrectNumber<uint64_t>(1, found.size());

		while (chosen.size() < count)
		{
			cout << "Введите id трубы из найденных: ";
			int id = GetCorrectNumber(0, 100000);

			if (!contains(found, id))
				cout << "Этого id нет среди найденных" << endl;
			else if (contains(chosen, id))
				cout << "Этот id уже выбран" << endl;
			else
				chosen.push_back(id);
		}
	}

	//  выбираем действие и применяем ко всем выбранным
	cout << "1 - убрать из ремонта, 2 - отправить в ремонт, 3 - удалить: ";
	int action = GetCorrectNumber(1, 3);

	for (int id : chosen)
	{
		if (action == 3)
			pipes.erase(id);
		else
			editPipe(pipes.at(id), action == 2);
	}
	cout << "Обработано труб: " << chosen.size() << endl;
}



void saveFile(const unordered_map<int, Pipe>& pipes, const unordered_map<int, CS>& stations)
{
	string name;
	cout << "Введите имя файла с расширением: ";
	INPUT_LINE(cin, name);
	ofstream file(name);

	if (!file.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
		return;
	}

	// сначала количество труб, потом сами трубы
	file << pipes.size() << endl;
	for (const auto& [id, pipe] : pipes)
		file << pipe;

	// потом количество КС и сами КС
	file << stations.size() << endl;
	for (const auto& [id, cs] : stations)
		file << cs;

	cout << "Данные сохранены" << endl;
}

void zagruzitFile(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& stations)
{
	string name;
	cout << "Введите имя файла с расширением: ";
	INPUT_LINE(cin, name);
	ifstream file(name);

	if (!file.is_open())
	{
		cout << "Ошибка чтения данных" << endl;
		return;
	}


	pipes.clear();
	stations.clear();

	int count;
	file >> count;
	while (count--)
	{
		Pipe pipe;
		file >> pipe;
		pipes.emplace(pipe.getId(), pipe);
	}

	file >> count;
	while (count--)
	{
		CS cs;
		file >> cs;
		stations.emplace(cs.getId(), cs);
	}

	cout << "Данные загружены" << endl;
}


void printMenu()
{
	cout << "1. Добавить трубу" << endl;
	cout << "2. Добавить КС" << endl;
	cout << "3. Просмотр всех объектов" << endl;
	cout << "4. Редактировать трубу" << endl;
	cout << "5. Редактировать КС" << endl;
	cout << "6. Сохранить" << endl;
	cout << "7. Загрузить" << endl;
	cout << "8. Удалить трубу" << endl;
	cout << "9. Удалить КС" << endl;
	cout << "10. Поиск труб" << endl;
	cout << "11. Поиск КС" << endl;
	cout << "12. Пакетное редактирование труб" << endl;
	cout << "0. Выход" << endl;
	cout << "Сделайте выбор: ";
}

int main()
{
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// логирование
	redirect_output_wrapper cerr_out(cerr);
	string time = std::format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("logs/log_" + time + ".txt");
	if (logfile)
		cerr_out.redirect(logfile);

	unordered_map<int, Pipe> pipes;
	unordered_map<int, CS> stations;

	while (true)
	{
		printMenu();

		switch (GetCorrectNumber(0, 12))
		{
		case 1:
			addPipe(pipes);
			break;
		case 2:
			addCS(stations);
			break;
		case 3:
			showAll(pipes, stations);
			break;
		case 4:
			editPipeById(pipes);
			break;
		case 5:
			editCSById(stations);
			break;
		case 6:
			saveFile(pipes, stations);
			break;
		case 7:
			zagruzitFile(pipes, stations);
			break;
		case 8:
			deletePipe(pipes);
			break;
		case 9:
			deleteCS(stations);
			break;
		case 10:
			printPipes(pipes, searchPipes(pipes));
			break;
		case 11:
			printStations(stations, searchCS(stations));
			break;
		case 12:
			batchEditPipes(pipes);
			break;
		case 0:
			return 0;
		}
	}

	return 0;
}