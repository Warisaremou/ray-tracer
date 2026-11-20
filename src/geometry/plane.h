#pragma once

#include "geometry/shape.h"
#include "material/material.h"
#include "math/vector.h"

#include <memory>

// An infinite flat surface, through a point and facing along a normal.
class Plane : public Shape
{
  private:
    Vector _point;
    Vector _normal;
    std::shared_ptr<const Material> _material;

  public:
    // The normal does not need to have length 1: the plane keeps it normalised.
    Plane(const Vector& point, const Vector& normal, std::shared_ptr<const Material> material);

    std::optional<Hit> hit(const Ray& ray) const override;
};
