#pragma once

#include <sstream>

inline std::string to_string_with_precision(const float a_value, const int n = 2)
{
	std::ostringstream out;
	out.precision(n);
	out << std::fixed << a_value;
	return out.str();
}

inline float clamp(float x, float min_v, float max_v)
{
	return std::min(max_v, std::max(min_v, x));
}
