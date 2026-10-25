#pragma once

#include <iostream>
#include <fstream>
#include <string>


class Pipe
{
private:
	static int MaxID;

	int id;
	std::string name;
	int length;
	int diameter;
	bool repair;

public:
	Pipe();

	int getId() const;

	void edit();
	void editRepair(bool value);
	static void ResetMaxID();

	friend std::ostream& operator << (std::ostream& out, const Pipe& pipe);
	friend std::istream& operator >> (std::istream& in, Pipe& pipe);

	friend std::ofstream& operator << (std::ofstream& out, const Pipe& pipe);
	friend std::ifstream& operator >> (std::ifstream& in, Pipe& pipe);

	friend bool CheckPipeByName(const Pipe& pipe, std::string param);
	friend bool CheckPipeByRepair(const Pipe& pipe, bool param);
};