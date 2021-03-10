
#include "stdafx.h"
#include "Vecteur2.h"
#include <math.h> // importation de cos et sin


sf::Vector2f v2::Rotation(sf::Vector2f v, float angle)
{
	float n = v2::Abs(v);
	double c = cos(angle * v2::PI / 180.0f);
	double s = sin(angle * v2::PI / 180.0f);

	v.x = v.x*c - v.y*s;
	v.y = v.x*s + v.y*c;

	//std::cout << std::sqrt(v.x*v.x+v.y*v.y) << std::endl;
	v = n * v2::Normalize(v);
	return v;
}

float v2::Abs(sf::Vector2f v)
{
	return std::sqrt(v.x*v.x + v.y*v.y);
}

sf::Vector2f v2::Normalize(sf::Vector2f v)
{
	float len(v2::Abs(v));
	v.x /= len;
	v.y /= len;

	return v;
}


float v2::Det(const sf::Vector2f& a, const sf::Vector2f& b)
{
	float d = a.x*b.y - b.x * a.y;

	return d;
}

float v2::Dot(const sf::Vector2f& a, const sf::Vector2f& b)
{
	float d = a.x*b.x + b.y * a.y;

	return d;
}

float v2::IntersectionSegment(sf::Vector2f A, sf::Vector2f B, sf::Vector2f I, sf::Vector2f P)
{
	sf::Vector2f D = B - A;
	sf::Vector2f E = P - I;

	float denom = v2::Det(D, E);
	if (denom == 0)
		return -2;   // erreur, cas limite

	float t = (v2::Det(E, A) - v2::Det(E, I)) / denom;
	if ( t < 0 || t >= 1)
		return -1;

	float u = (v2::Det(D, A) - v2::Det(D,I)) / denom;
	if ( u < 0 || u >= 1)
		return -1;

	return t;
}

sf::Vector2f v2::Horto(sf::Vector2f v)
{
	return sf::Vector2f(-v.y, v.x);
}


std::ostream& operator<<(std::ostream& os, const sf::Vector2f& v)
{
	os << v.x << " " << v.y << std::endl;
	return os;
}


/*
Vec2::Vec2(): _x(0.0), _y(0.0) {}

Vec2::Vec2(double x, double y):  _x(x), _y(y) {}

Vec2::~Vec2() {}

double const Vec2::Abs()
{
	double n = x()*x() + y()*y();
	return std::sqrt(n);
}

Vec2 Vec2::Normalize()
{
	double len(Abs());
	_x /= len;
	_y /= len;

	return *this;
}

Vec2 const Vec2::Ortho() 
{
	Vec2 o(-y(), x());
	return o;
}


Vec2 const Vec2::Rotation(float angle)
{
	double c = cos(angle * v2::PI / 180.0);
	double s = sin(angle * v2::PI / 180.0);

	double x(_x*c - _y*s);
	double y(_x*s + _y*c);

	_x = x;
	_y = y;

	return *this;
}

void Vec2::operator+=(const Vec2& a)
{
	_x += a.x();
	_y += a.y();
}

double Vec2::AngleBetween(Vec2 from, Vec2 to)
{
	double det = Det(from, to);
	double dot = Dot(from, to);
	Vec2 a = from - to;

	double angle = atan2(a.x(), a.y());
	return angle;
}

Vec2 operator+(const Vec2& a, const Vec2& b)
{
	Vec2 c(a.x() + b.x(), a.y() + b.y());

	return c;
}

Vec2 operator-(const Vec2& a, const Vec2& b)
{
	Vec2 c(a.x() - b.x(), a.y() - b.y());

	return c;
}

Vec2 operator*(const Vec2& a, const double s)
{
	Vec2 c(s*a.x(), s*a.y());

	return c;
}

Vec2 operator*(const double s, const Vec2& a)
{
	Vec2 c(s*a.x(), s*a.y());

	return c;
}

ostream& operator<<(ostream& os, const Vec2& v)
{
	os << "(" << v.x() << "," << v.y() << ')';
	return os;
}

bool operator==(const Vec2& a, const Vec2& b)
{
	if (a.x() == b.x() && a.y() == b.y())
		return true;
	return false;
}

double Det(const Vec2& a, const Vec2& b)
{
	double d = a.x()*b.y() - b.x() * a.y();

	return d;
}

double Dot(const Vec2& a, const Vec2& b)
{
	double d = a.x()*b.x() + b.y() * a.y();

	return d;
}*/