#pragma once

#include "geometry/hit.h"
#include "geometry/ray.h"
#include "geometry/shape.h"
#include "material/material.h"
#include "math/vector.h"

#include <memory>
#include <optional>

class Sphere : public Shape
{
  private:
    Vector _centre;
    double _radius;
    std::shared_ptr<const Material> _material;

  public:
    Sphere(const Vector& centre, double radius, std::shared_ptr<const Material> material);

    std::optional<Hit> hit(const Ray& ray) const override;
};
