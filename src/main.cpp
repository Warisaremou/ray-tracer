#include "colour/colour.h"
#include "geometry/sphere.h"
#include "io/png_saver.h"
#include "material/lambert_shader.h"
#include "math/vector.h"
#include "render/camera.h"

#include <iostream>
#include <memory>
#include <string>

int main()
{
    const unsigned int imageWidth = 512;
    const unsigned int imageHeight = 512;
    const std::string outputPath = "image.png";

    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2.0);
    Sphere sphere(Vector(0, 0, 9), 3.0, std::make_shared<LambertShader>(Colour(0.0, 0.0, 0.5)));
    // The sun shines from above, from the left and from behind the camera.
    Vector toLight = Vector(-1, 1, -1).normalised();

    Image image = camera.render(sphere, toLight, imageWidth, imageHeight);

    PngSaver saver;
    saver.save(image, outputPath);

    std::cout << "Saved " << outputPath << "\n";
    return 0;
}
