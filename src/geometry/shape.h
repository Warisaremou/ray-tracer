#pragma once

#include "geometry/hit.h"
#include "geometry/ray.h"

#include <optional>

class Shape
{
  public:
    virtual ~Shape() = default;

    virtual std::optional<Hit> hit(const Ray& ray) const = 0;
};
