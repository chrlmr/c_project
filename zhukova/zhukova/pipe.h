#pragma once

#include <iostream>
#include <string>


class Pipe
{
private:
	std::string name;
	int length;
	int diameter;
	bool repair;

public:

	/*Pipe(const std::string& name, int length, int diameter, bool repair)
	{
		this->name = name;
		this-> length = length;
		this->diameter = diameter;
		this->repair = repair;
	}
	void setName(std::string value);

	std::string getName();
	{
		return name;
	}

	void setLength(int value);

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

	void setRepair(bool value);


	bool getRepair()
	{
		return repair;
	}*/

	friend std::ostream& operator << (std::ostream& out,const Pipe& pipe);

	friend std::istream& operator >> (std::istream& in, Pipe& pipe);

};