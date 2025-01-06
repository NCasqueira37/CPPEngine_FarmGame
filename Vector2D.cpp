#include "Vector2D.h"

double Vector2D::getMagnitude() {
	return (sqrt(x * x + y * y));
}
Vector2D Vector2D::normalize() {
	double magnitude = getMagnitude();
	return Vector2D(x / magnitude, y / magnitude);
}

Vector2D Vector2D::operator+(const Vector2D& other) const {
	return Vector2D(x + other.x, y + other.y);
}
Vector2D Vector2D::operator-(const Vector2D& other) const {
	return Vector2D(x - other.x, y - other.y);
}
Vector2D Vector2D::operator/(const Vector2D& other) const {
	return Vector2D(x / other.x, y / other.y);
}
Vector2D Vector2D::operator*(const Vector2D& other) const {
	return Vector2D(x * other.x, y * other.y);
}


Vector2D Vector2D::operator+(const double& amount) const {
	return Vector2D(x + amount, y + amount);
}
Vector2D Vector2D::operator-(const double& amount) const {
	return Vector2D(x - amount, y - amount);
}
Vector2D Vector2D::operator*(const double& amount) const {
	return Vector2D(x * amount, y * amount);
}
Vector2D Vector2D::operator/(const double& amount) const {
	return Vector2D(x / amount, y / amount);
}


bool Vector2D::operator=(const Vector2D& other) const {
	return (x == other.x && y == other.y);
}
bool Vector2D::operator!=(const Vector2D& other) const {
	return (x != other.x && y != other.y);
}