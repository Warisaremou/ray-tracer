#include "vector.h"

#include <cmath>
#include <stdexcept>

Vector::Vector(double x, double y, double z) : _x(x), _y(y), _z(z) {}

double Vector::x() const { return _x; }
double Vector::y() const { return _y; }
double Vector::z() const { return _z; }

Vector Vector::operator+(const Vector& other) const
{
    return Vector(_x + other._x, _y + other._y, _z + other._z);
}

Vector Vector::operator-(const Vector& other) const
{
    return Vector(_x - other._x, _y - other._y, _z - other._z);
}

double Vector::length() const { return std::sqrt(dot(*this)); }

Vector Vector::normalised() const
{
    double len = length();
    if (len == 0.0)
    {
        throw std::domain_error("Cannot normalise a zero-length vector");
    }
    return Vector(_x / len, _y / len, _z / len);
}

double Vector::dot(const Vector& other) const
{
    return _x * other._x + _y * other._y + _z * other._z;
}

Vector operator*(double t, const Vector& v) { return Vector(t * v.x(), t * v.y(), t * v.z()); }
