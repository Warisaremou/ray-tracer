#pragma once

#include "colour/colour.h"
#include "math/vector.h"

class Material
{
  public:
    virtual ~Material() = default;

    // normal and toLight must be unit vectors: shade does not normalise them.
    virtual Colour shade(const Vector& normal, const Vector& toLight) const = 0;
};
