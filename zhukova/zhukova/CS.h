#pragma once

#include <iostream>
#include <fstream>
#include <string>


class CS
{
private:
	static int MaxID;

	int id;
	std::string name;
	int countWorkshops;
	int workingWorkshops;
	int classStation;

public:
	CS();

	int getId() const;

	double getUnusedPercent() const;

	friend std::ostream& operator << (std::ostream& out, const CS& cs);
	friend std::istream& operator >> (std::istream& in, CS& cs);

	friend std::ofstream& operator << (std::ofstream& out, const CS& cs);
	friend std::ifstream& operator >> (std::ifstream& in, CS& cs);


	friend bool CheckCSByName(const CS& cs, std::string param);
	friend void editCS(CS& cs);
};