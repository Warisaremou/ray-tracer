#pragma once

#include "geometry/ray.h"
#include "math/vector.h"

class Camera
{
  private:
    Vector _eye;
    Vector _screenCentre;

  public:
    Camera(const Vector& eye, const Vector& screenCentre);

    Ray rayThroughCentre() const;
};
