#pragma once

#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "math/vector.h"
#include "render/image.h"

class Camera
{
  private:
    Vector _eye;
    Vector _screenCentre;
    double _screenWidth;

  public:
    Camera(const Vector& eye, const Vector& screenCentre, double screenWidth);

    Ray rayThroughCentre() const;

    Ray rayThroughPixel(unsigned int x, unsigned int y, unsigned int imageWidth,
                        unsigned int imageHeight) const;

    Image render(const Sphere& sphere, unsigned int imageWidth, unsigned int imageHeight) const;
};
