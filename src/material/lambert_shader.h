#pragma once

#include "material/material.h"

class LambertShader : public Material
{
  private:
    Colour _colour;

  public:
    explicit LambertShader(const Colour& colour);

    Colour shade(const Vector& normal, const Vector& toLight) const override;
};
