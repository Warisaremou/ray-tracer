#pragma once

#include "material/material.h"

// One colour everywhere, whatever the light or the angle.
class FlatShader : public Material
{
  private:
    Colour _colour;

  public:
    explicit FlatShader(const Colour& colour);

    Colour shade(const Vector& normal, const Vector& toLight) const override;
};
