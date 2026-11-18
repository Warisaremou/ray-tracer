#include "camera.h"

#include "render/trace.h"

Camera::Camera(const Vector& eye, const Vector& screenCentre, double screenWidth)
    : _eye(eye), _screenCentre(screenCentre), _screenWidth(screenWidth)
{
}

Ray Camera::rayThroughCentre() const { return Ray(_eye, _screenCentre - _eye); }

Ray Camera::rayThroughPixel(unsigned int x, unsigned int y, unsigned int imageWidth,
                            unsigned int imageHeight) const
{
    double screenHeight = _screenWidth * imageHeight / imageWidth;

    double offsetX = ((x + 0.5) / imageWidth - 0.5) * _screenWidth;
    double offsetY = (0.5 - (y + 0.5) / imageHeight) * screenHeight;

    Vector pixelCentre = _screenCentre + Vector(offsetX, offsetY, 0);
    return Ray(_eye, pixelCentre - _eye);
}

Image Camera::render(const Sphere& sphere, unsigned int imageWidth, unsigned int imageHeight) const
{
    Image image(imageWidth, imageHeight);

    for (unsigned int y = 0; y < imageHeight; y++)
    {
        for (unsigned int x = 0; x < imageWidth; x++)
        {
            Ray ray = rayThroughPixel(x, y, imageWidth, imageHeight);
            image.setPixel(x, y, trace(ray, sphere));
        }
    }

    return image;
}
