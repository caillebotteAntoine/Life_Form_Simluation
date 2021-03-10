#pragma once
#include <iostream>  
using namespace std;

#include <cmath> // importation de cos et sin
#include <SFML/Graphics.hpp>

namespace v2
{
	static float PI = 3.14159265f;

	sf::Vector2f Horto(sf::Vector2f);
	sf::Vector2f Rotation(sf::Vector2f v, float angle);
	float Abs(sf::Vector2f v);
	sf::Vector2f Normalize(sf::Vector2f v);


	float Det(const sf::Vector2f& a, const sf::Vector2f& b);
	float Dot(const sf::Vector2f& a, const sf::Vector2f& b);

	float IntersectionSegment(sf::Vector2f A, sf::Vector2f B, sf::Vector2f I, sf::Vector2f P);

}


std::ostream& operator<<(std::ostream&, const sf::Vector2f&);

/*
class Vec2
{
public:
	Vec2();
	Vec2(double x, double y);

	~Vec2();

	const double x() const { return _x; }
	const int xint() const { return int(_x); }
	void px() { _x++; }
	const double y() const { return _y; }
	const int yint() const { return int(_y); }
	void py() { _y++; }

	void operator+=(const Vec2&);

	double const Abs();
	Vec2 Normalize();
	Vec2 const Ortho();
	Vec2 const Rotation(float angle);

	static double AngleBetween(Vec2, Vec2);

	static Vec2 Zero() { return Vec2(0, 0); }
	static Vec2 Up() { return Vec2(0, 1); }
	static Vec2 Down() { return Vec2(0, -1); }
	static Vec2 Left() { return Vec2(-1, 0); }
	static Vec2 Right() { return Vec2(1, 0); }
private :
	double _x;
	double _y;

};

Vec2 operator+(const Vec2&, const Vec2&);
Vec2 operator-(const Vec2&, const Vec2&);
Vec2 operator*(const Vec2&, const double);
Vec2 operator*(const double, const Vec2&);
bool operator==(const Vec2&, const Vec2&);


ostream& operator<<(ostream& os, const Vec2& v);

double Det(const Vec2&, const Vec2&);
double Dot(const Vec2&, const Vec2&);

*/