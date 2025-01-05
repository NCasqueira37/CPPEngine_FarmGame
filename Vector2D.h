#pragma once
#include <cmath>

class Vector2D
{

public:
	double x, y;
	Vector2D() :x(0), y(0) {};
	Vector2D(double x, double y) : x(x), y(y) {};

	double getMagnitude();
	Vector2D normalize();

	Vector2D operator+(const Vector2D& other) const;
	Vector2D operator-(const Vector2D& other) const;
	Vector2D operator/(const Vector2D& other) const;
	Vector2D operator*(const Vector2D& other) const;

	Vector2D operator+(const double& amount) const;
	Vector2D operator-(const double& amount) const;
	Vector2D operator*(const double& amount) const;
	Vector2D operator/(const double& amount) const;

	bool operator=(const Vector2D& other) const;
	bool operator!=(const Vector2D& other) const;
};

