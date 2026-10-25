#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define INPUT_LINE(in, str) getline(in>>std::ws, str); \
						std::cerr << str << std::endl

class redirect_output_wrapper
{
	std::ostream& stream;
	std::streambuf* const old_buf;
public:
	redirect_output_wrapper(std::ostream& src)
		:old_buf(src.rdbuf()), stream(src)
	{
	}

	~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
	}
	void redirect(std::ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};



template <typename T>
T GetCorrectNumber(T min, T max)
{
	T x;
	while ((std::cin >> x).fail()	
		|| std::cin.peek() != '\n'	
		|| x < min || x > max)		
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Ошибка. Введите корректное число: ";
	}
	std::cerr << x << std::endl;
	return x;
}


template<typename Obj, typename T>
using Filter = bool(const Obj& obj, T param);


template<typename Obj, typename T>
std::unordered_set<int> FindByFilter(const std::unordered_map<int, Obj>& objects, Filter<Obj, T> f, T param)
{
	std::unordered_set<int> res;
	for (const auto& [id, obj] : objects)
	{
		if (f(obj, param))
			res.insert(id);
	}
	return res;
}