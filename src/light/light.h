#pragma once

#include "colour/colour.h"
#include "math/vector.h"

// A point light: it shines from one position, in one colour.
class Light
{
  private:
    Vector _position;
    Colour _colour;

  public:
    Light(const Vector& position, const Colour& colour);

    Vector position() const;
    Colour colour() const;
};
