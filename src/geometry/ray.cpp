#include "geometry/ray.h"

#include <stdexcept>

Ray::Ray(const Vector& origin, const Vector& direction) : _origin(origin), _direction(direction)
{
    if (direction.dot(direction) == 0.0)
    {
        throw std::domain_error("A ray needs a non-zero direction");
    }
}

Vector Ray::origin() const { return _origin; }

Vector Ray::direction() const { return _direction; }

Vector Ray::at(double t) const { return _origin + t * _direction; }
