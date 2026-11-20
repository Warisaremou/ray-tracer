#include "colour/colour.h"
#include "geometry/plane.h"
#include "geometry/sphere.h"
#include "io/png_saver.h"
#include "material/lambert_shader.h"
#include "math/vector.h"
#include "render/camera.h"
#include "scene/scene.h"

#include <iostream>
#include <memory>
#include <string>

int main()
{
    const unsigned int imageWidth = 512;
    const unsigned int imageHeight = 512;
    const std::string outputPath = "image.png";

    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2.0);
    // The sun shines from above, from the left and from behind the camera.
    Scene scene(Vector(-1, 1, -1).normalised());
    scene.add(std::make_unique<Sphere>(
        Vector(0, 0, 9), 3.0, std::make_shared<LambertShader>(Colour(0.0, 0.0, 0.5))));
    scene.add(std::make_unique<Plane>(
        Vector(0, -5, 0), Vector(0, 1, 0), std::make_shared<LambertShader>(Colour(0.8, 0.8, 0.8))));

    Image image = camera.render(scene, imageWidth, imageHeight);

    PngSaver saver;
    saver.save(image, outputPath);

    std::cout << "Saved " << outputPath << "\n";
    return 0;
}
