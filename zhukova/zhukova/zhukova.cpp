
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <format>
#include <unordered_set>
#include "pipe.h"
#include "CS.h"
#include "utils.h"
using namespace std;
using namespace chrono;



bool CheckPipeByName(const Pipe& pipe, string param)
{
	return pipe.name.find(param) != string::npos; 
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
	return cs.getUnusedPercent() >= param;   
}


 
void addPipe(unordered_map<int, Pipe>& pipes)
{
	Pipe pipe;
	cin >> pipe;
	pipes.emplace(pipe.getId(), pipe);   
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


void printPipes(const unordered_map<int, Pipe>& pipes, const unordered_set<int>& ids)
{
	if (ids.empty())
	{
		cout << "Ничего не найдено" << endl;
		return;
	}
	for (int id : ids)
		cout << pipes.at(id) << endl;
}


void printStations(const unordered_map<int, CS>& stations, const unordered_set<int>& ids)
{
	if (ids.empty())
	{
		cout << "Ничего не найдено" << endl;
		return;
	}
	for (int id : ids)
		cout << stations.at(id) << endl;
}


void editPipeById(unordered_map<int, Pipe>& pipes)
{
	cout << "Введите id трубы: ";
	int id = GetCorrectNumber(0, 100000);

	if (pipes.contains(id) == 0)
		cout << "Трубы с таким id нет" << endl;
	else
	{
		pipes[id].edit();
		cout << pipes[id];
	}
}

void editCSById(unordered_map<int, CS>& stations)
{
	cout << "Введите id КС: ";
	int id = GetCorrectNumber(0, 100000);

	if (stations.contains(id) == 0)
		cout << "КС с таким id нет" << endl;
	else
	{
		stations[id].edit();
		cout << stations[id];
	}
}



void deletePipe(unordered_map<int, Pipe>& pipes)
{
	cout << "Введите id трубы: ";
	int id = GetCorrectNumber(0, 100000);

	if (pipes.contains(id) == 0)
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

	if (stations.contains(id) == 0)
		cout << "КС с таким id нет" << endl;
	else
	{
		stations.erase(id);
		cout << "КС удалена" << endl;
	}
}



unordered_set<int> searchPipes(const unordered_map<int, Pipe>& pipes)
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

unordered_set<int> searchCS(const unordered_map<int, CS>& stations)
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


unordered_set<int> chooseByIds(const unordered_set<int>& found)
{
	unordered_set<int> chosen;

	while (true)
	{
		cout << "Введите id трубы из найденных (0 - закончить): ";
		int id = GetCorrectNumber(0, 100000);

		if (id == 0)
			break;

		if (!found.contains(id))
			cout << "Этого id нет среди найденных" << endl;
		else if (chosen.contains(id))
			cout << "Этот id уже выбран" << endl;
		else
			chosen.insert(id);
	}
	return chosen;
}



void batchEditPipes(unordered_map<int, Pipe>& pipes)
{
	unordered_set<int> found = searchPipes(pipes);
	printPipes(pipes, found);
	if (found.empty())
		return;

	cout << "1 - выбрать все найденные, 2 - выбрать по id: ";
	int vibor = GetCorrectNumber(1, 2);

	unordered_set<int> chosen = found;

	if (vibor == 2)
		chosen = chooseByIds(found);

	if (chosen.empty())
	{
		cout << "Ничего не выбрано" << endl;
		return;
	}
	
	cout << "1 - убрать из ремонта, 2 - отправить в ремонт, 3 - удалить: ";
	int deistvie = GetCorrectNumber(1, 3);

	for (int id : chosen)
	{
		if (deistvie == 3)
			pipes.erase(id);
		else
			pipes[id].editRepair(deistvie == 2);
	}
	cout << "Обработано труб: " << chosen.size() << endl;
}



void saveFile(const unordered_map<int, Pipe>& pipes, const unordered_map<int, CS>& stations)
{
	string name;
	cout << "Введите имя файлa: ";
	INPUT_LINE(cin, name);
	ofstream file(name);

	if (!file.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
		return;
	}

	file << pipes.size() << endl;
	for (const auto& [id, pipe] : pipes)
		file << pipe;

	file << stations.size() << endl;
	for (const auto& [id, cs] : stations)
		file << cs;

	cout << "Данные сохранены" << endl;
}

void zagruzitFile(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& stations)
{
	string name;
	cout << "Введите имя файла: ";
	INPUT_LINE(cin, name);
	ifstream file(name);

	if (!file.is_open())
	{
		cout << "Ошибка чтения данных" << endl;
		return;
	}


	pipes.clear();
	stations.clear();
	Pipe::ResetMaxID();
	CS::ResetMaxID();

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