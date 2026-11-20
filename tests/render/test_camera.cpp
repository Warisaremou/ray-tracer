#include "geometry/sphere.h"
#include "render/camera.h"
#include "scene/scene.h"
#include "test_helpers.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <stdexcept>

TEST_CASE("Camera looking along z gives a ray along z", "[camera]")
{
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);

    Ray ray = camera.rayThroughCentre();

    REQUIRE_THAT(ray.origin(), ApproxEquals(Vector(0, 0, -1)));
    REQUIRE_THAT(ray.direction(), ApproxEquals(Vector(0, 0, 1)));
}

TEST_CASE("Camera with an offset screen centre gives a ray towards it", "[camera]")
{
    Camera camera(Vector(1, 2, -1), Vector(4, 6, -1), 5);

    Ray ray = camera.rayThroughCentre();

    REQUIRE_THAT(ray.origin(), ApproxEquals(Vector(1, 2, -1)));
    REQUIRE_THAT(ray.direction(), ApproxEquals(Vector(3, 4, 0)));
}

TEST_CASE("Camera with its eye on the screen centre has no ray to give", "[camera]")
{
    Camera camera(Vector(1, 2, 3), Vector(1, 2, 3), 5);

    REQUIRE_THROWS_AS(camera.rayThroughCentre(), std::domain_error);
}

// Screen is 5 wide, image is 5 columns by 3 rows, so each pixel is 1 by 1 and the screen is 3 high.
// The eye is 1 in front of the screen centre, so every direction has z = 1.
TEST_CASE("Camera gives the ray through the centre pixel", "[camera]")
{
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);

    Ray ray = camera.rayThroughPixel(2, 1, 5, 3);

    REQUIRE_THAT(ray.origin(), ApproxEquals(Vector(0, 0, -1)));
    REQUIRE_THAT(ray.direction(), ApproxEquals(Vector(0, 0, 1)));
}

TEST_CASE("Camera gives the ray through the top right pixel", "[camera]")
{
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);

    Ray ray = camera.rayThroughPixel(4, 0, 5, 3);

    REQUIRE_THAT(ray.origin(), ApproxEquals(Vector(0, 0, -1)));
    REQUIRE_THAT(ray.direction(), ApproxEquals(Vector(2, 1, 1)));
}

TEST_CASE("Camera gives the ray through the bottom left pixel", "[camera]")
{
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);

    Ray ray = camera.rayThroughPixel(0, 2, 5, 3);

    REQUIRE_THAT(ray.origin(), ApproxEquals(Vector(0, 0, -1)));
    REQUIRE_THAT(ray.direction(), ApproxEquals(Vector(-2, -1, 1)));
}

// Screen is 2 wide, image is 512 by 256, so the screen is 1 high and each pixel is 1/256 by 1/256.
TEST_CASE("Camera scales the pixel size to the screen and the image size", "[camera]")
{
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2);

    Ray topLeft = camera.rayThroughPixel(0, 0, 512, 256);
    Ray justPastCentre = camera.rayThroughPixel(256, 128, 512, 256);

    REQUIRE_THAT(topLeft.direction(), ApproxEquals(Vector(-511.0 / 512, 255.0 / 512, 1)));
    REQUIRE_THAT(justPastCentre.direction(), ApproxEquals(Vector(1.0 / 512, -1.0 / 512, 1)));
}

// 3 by 3 image on a 2 wide screen: the centre pixel looks straight at the sphere,
// the top-left pixel looks towards (-2/3, 2/3, 1), which passes far from a sphere of radius 1 at z
// = 9.
TEST_CASE("Camera renders the pixels that hit the sphere and leaves the others black", "[camera]")
{
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2);
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 1, redMaterial()));

    Image image = camera.render(scene, 3, 3);

    REQUIRE(image.width() == 3);
    REQUIRE(image.height() == 3);
    REQUIRE(image.pixel(1, 1).r() == Catch::Approx(1));
    REQUIRE(image.pixel(0, 0).r() == Catch::Approx(0));
}
