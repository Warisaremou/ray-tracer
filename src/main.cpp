#include "colour/colour.h"
#include "geometry/sphere.h"
#include "io/png_saver.h"
#include "math/vector.h"
#include "render/camera.h"

#include <iostream>
#include <string>

int main()
{
    const unsigned int imageWidth = 512;
    const unsigned int imageHeight = 512;
    const std::string outputPath = "output.png";

    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2.0);
    Sphere sphere(Vector(0, 0, 9), 3.0, Colour(1.0, 0.0, 1.0));

    Image image = camera.render(sphere, imageWidth, imageHeight);

    PngSaver saver;
    saver.save(image, outputPath);

    std::cout << "Saved " << outputPath << "\n";
    return 0;
}
