#pragma once

#include "geometry/ray.h"
#include "scene/scene.h"
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

    Ray rayThroughPixel(unsigned int column, unsigned int row, unsigned int imageWidth,
                        unsigned int imageHeight) const;

    Image render(const Scene& scene, unsigned int imageWidth, unsigned int imageHeight) const;
};
