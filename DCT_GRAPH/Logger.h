#pragma once

#include <vector>
#include <iostream>

template<class T>
class Logger
{
public:
	static void log_vector(std::vector<T> &vec);
};

template<class T>
inline void Logger<T>::log_vector(std::vector<T>& vec)
{
	for (T& i : vec)
	{
		std::cout << i << " ";
	}
	std::cout << "\n";
}