#pragma once

#ifndef POINT_H
# define POINT_H
# include <algorithm>
# include <cstdlib>
# include <cmath>

template <typename T>
class Point
{
private:
	T	x;
	T	y;

public:
	Point(const T &x = 0, const T &y = 0);
	~Point() = default;

	const T& getX() const;
	const T& getY() const;

	Point<T>& setX(const T& x);
	Point<T>& setY(const T& y);

	Point<T>& add(const T& x, const T& y);

	bool isXBetween(double x1, double x2) const;

};

template<typename T>
Point<T>::Point(const T& x, const T& y)
{
	this->x = x;
	this->y = y;
}

template<typename T>
inline const T& Point<T>::getX() const
{
	return (this->x);
}

template<typename T>
inline const T& Point<T>::getY() const
{
	return (this->y);
}

template<typename T>
Point<T>& Point<T>::setX(const T& x)
{
	this->x = x;
	return (*this);
}

template<typename T>
Point<T>& Point<T>::setY(const T& y)
{
	this->y = y;
	return (*this);
}

template<typename T>
Point<T>& Point<T>::add(const T& x, const T& y)
{
	this->x += x;
	this->y += y;
	return (*this);
}

template<typename T>
bool Point<T>::isXBetween(double x1, double x2) const
{
	if (x1 > x2)
		std::swap(x1, x2);
	return (this->x >= x1 && this->x <= x2);
}

template<typename T>
double getDist(const Point<T>& p1, const Point<T>& p2)
{
	T dx = std::abs(p1.getX() - p2.getX());
	T dy = std::abs(p1.getY() - p2.getY());

	return (std::sqrt(dx * dx + dy * dy));
}

#endif