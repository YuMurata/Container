#pragma once

template<typename T>
struct Coordinate
{
	T x;
	T y;

	Coordinate(){}
	Coordinate(const T &x, const T &y)
		:x(x), y(y) {}
};

using ICoord = Coordinate<int>;
using FCoord = Coordinate<float>;
using DCoord = Coordinate<double>;

template<typename T>
double Distance(const Coordinate<T> &p1, const Coordinate<T> &p2)
{
	auto sq = [](const T &x)
	{
		return x*x;
	};

	auto x = sq(p1.x - p2.x);
	auto y = sq(p1.y - p2.y);

	auto ret = sqrt(x + y);
	return ret;
}