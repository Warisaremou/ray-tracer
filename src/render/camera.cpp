#include "camera.h"

#include "render/trace.h"

Camera::Camera(const Vector& eye, const Vector& screenCentre, double screenWidth)
    : _eye(eye), _screenCentre(screenCentre), _screenWidth(screenWidth)
{
}

Ray Camera::rayThroughCentre() const { return Ray(_eye, _screenCentre - _eye); }

Ray Camera::rayThroughPixel(unsigned int column, unsigned int row, unsigned int imageWidth,
                            unsigned int imageHeight) const
{
    double screenHeight = _screenWidth * imageHeight / imageWidth;

    double offsetX = ((column + 0.5) / imageWidth - 0.5) * _screenWidth;
    double offsetY = (0.5 - (row + 0.5) / imageHeight) * screenHeight;

    Vector pixelCentre = _screenCentre + Vector(offsetX, offsetY, 0);
    return Ray(_eye, pixelCentre - _eye);
}

Image Camera::render(const Scene& scene, unsigned int imageWidth, unsigned int imageHeight) const
{
    Image image(imageWidth, imageHeight);

    for (unsigned int row = 0; row < imageHeight; row++)
    {
        for (unsigned int column = 0; column < imageWidth; column++)
        {
            Ray ray = rayThroughPixel(column, row, imageWidth, imageHeight);
            image.setPixel(column, row, trace(ray, scene));
        }
    }

    return image;
}
