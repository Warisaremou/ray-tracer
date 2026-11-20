#include "geometry/sphere.h"
#include "material/lambert_shader.h"
#include "render/trace.h"
#include "scene/scene.h"
#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>
#include <memory>

// The camera's ray (see cameraRay()) and a red Lambert sphere of radius 5.

TEST_CASE("Trace gives the full colour when the sun is behind the eye", "[trace]")
{
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, redMaterial()));

    // The normal at the hit is (0, 0, -1), so the dot product with (0, 0, -1) is 1.
    Colour colour = trace(cameraRay(), scene);

    REQUIRE_THAT(colour, ApproxEquals(Colour(1, 0, 0)));
}

TEST_CASE("Trace darkens the colour when the sun is at an angle", "[trace]")
{
    Scene scene(Vector(0.6, 0, -0.8));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, redMaterial()));

    // The dot product of (0, 0, -1) and (0.6, 0, -0.8) is 0.8.
    Colour colour = trace(cameraRay(), scene);

    REQUIRE_THAT(colour, ApproxEquals(Colour(0.8, 0, 0)));
}

TEST_CASE("Trace shades with the normal at the hit point", "[trace]")
{
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(Vector(3, 0, 9), 5, redMaterial()));

    // The normal at the hit (0, 0, 5) is (-0.6, 0, -0.8), so the dot product with (0, 0, -1) is 0.8.
    Colour colour = trace(cameraRay(), scene);

    REQUIRE_THAT(colour, ApproxEquals(Colour(0.8, 0, 0)));
}

TEST_CASE("Trace gives black when the ray misses the sphere", "[trace]")
{
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(Vector(6, 0, 9), 5, redMaterial()));

    Colour colour = trace(cameraRay(), scene);

    REQUIRE_THAT(colour, ApproxEquals(Colour(0, 0, 0)));
}
