#pragma once

#include "geometry/hit.h"
#include "geometry/ray.h"
#include "geometry/shape.h"
#include "math/vector.h"

#include <memory>
#include <optional>
#include <vector>

class Scene
{
  private:
    Vector _toLight;
    std::vector<std::unique_ptr<Shape>> _shapes;

  public:
    explicit Scene(const Vector& toLight);

    Vector toLight() const;

    void add(std::unique_ptr<Shape> shape);

    // The hit with the smallest t among all the shapes, or nothing if the ray hits none.
    std::optional<Hit> nearestHit(const Ray& ray) const;
};
