#include "geometry/plane.h"

#include <utility>

Plane::Plane(const Vector& point, const Vector& normal, std::shared_ptr<const Material> material)
    : _point(point), _normal(normal.normalised()), _material(std::move(material))
{
}

std::optional<Hit> Plane::hit(const Ray& ray) const
{
    double alongNormal = _normal.dot(ray.direction());
    if (alongNormal == 0.0)
    {
        return std::nullopt;
    }

    double t = _normal.dot(_point - ray.origin()) / alongNormal;
    if (t <= 0.0)
    {
        return std::nullopt;
    }

    return Hit{t, ray.at(t), _normal, _material};
}
