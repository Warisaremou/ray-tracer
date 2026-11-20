#include "sphere.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <optional>
#include <utility>

Sphere::Sphere(const Vector& centre, double radius, std::shared_ptr<const Material> material)
    : _centre(centre), _radius(radius), _material(std::move(material))
{
    if (radius <= 0.0)
    {
        throw std::domain_error("A sphere needs a positive radius");
    }
    if (_material == nullptr)
    {
        throw std::invalid_argument("A sphere needs a material");
    }
}

namespace
{
std::optional<double> closestAhead(double t1, double t2)
{
    if (t1 > 0.0 && t2 > 0.0)
        return std::min(t1, t2);
    if (t1 > 0.0)
        return t1;
    if (t2 > 0.0)
        return t2;
    return std::nullopt;
}
}

std::optional<Hit> Sphere::hit(const Ray& ray) const
{
    Vector O = ray.origin();
    Vector D = ray.direction();
    Vector C = _centre;

    Vector L = O - C;

    double a = D.dot(D);
    double b = 2.0 * D.dot(L);
    double c = L.dot(L) - _radius * _radius;

    double discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0)
    {
        return std::nullopt;
    }

    double root = std::sqrt(discriminant);
    double t1 = (-b - root) / (2.0 * a);
    double t2 = (-b + root) / (2.0 * a);

    std::optional<double> t = closestAhead(t1, t2);
    if (false == t.has_value())
    {
        return std::nullopt;
    }

    Vector point = ray.at(t.value());
    Vector normal = (point - _centre).normalised();
    return Hit{t.value(), point, normal, _material};
}
