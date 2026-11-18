#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>
#include <stdexcept>

TEST_CASE("Sphere gives back its colour", "[sphere]")
{
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));

    REQUIRE_THAT(sphere.colour(), ApproxEquals(Colour(1, 0, 0)));
}

// The camera's ray (see cameraRay()) and a sphere of radius 5.
// a = D·D = 1, and b = 2 D·L = -20 for every centre ahead of the camera.

TEST_CASE("Sphere with centre (0, 0, 9) is hit by the camera's ray", "[sphere]")
{
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));
    Ray ray = cameraRay();

    // L = (0, 0, -10), c = 100 - 25 = 75, discriminant = 400 - 300 = 100
    REQUIRE(sphere.isHitBy(ray));
}

TEST_CASE("Sphere with centre (3, 0, 9) is hit by the camera's ray", "[sphere]")
{
    Sphere sphere(Vector(3, 0, 9), 5, Colour(1, 0, 0));
    Ray ray = cameraRay();

    // L = (-3, 0, -10), c = 109 - 25 = 84, discriminant = 400 - 336 = 64
    REQUIRE(sphere.isHitBy(ray));
}

TEST_CASE("Sphere with centre (6, 0, 9) is missed by the camera's ray", "[sphere]")
{
    Sphere sphere(Vector(6, 0, 9), 5, Colour(1, 0, 0));
    Ray ray = cameraRay();

    // L = (-6, 0, -10), c = 136 - 25 = 111, discriminant = 400 - 444 = -44
    REQUIRE_FALSE(sphere.isHitBy(ray));
}

TEST_CASE("Sphere with centre (0, 0, -11) behind the camera is missed by its ray", "[sphere]")
{
    Sphere sphere(Vector(0, 0, -11), 5, Colour(1, 0, 0));
    Ray ray = cameraRay();

    // L = (0, 0, 10), b = 20, c = 100 - 25 = 75, discriminant = 400 - 300 = 100
    // t = (-20 - 10) / 2 = -15 or (-20 + 10) / 2 = -5: both behind the origin
    REQUIRE_FALSE(sphere.isHitBy(ray));
}

TEST_CASE("Sphere is hit by a ray starting inside it", "[sphere]")
{
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));
    Ray ray(Vector(0, 0, 9), Vector(0, 0, 1));

    // L = (0, 0, 0), b = 0, c = -25, discriminant = 100
    // t = (0 - 10) / 2 = -5 or (0 + 10) / 2 = 5: one behind, one ahead
    REQUIRE(sphere.isHitBy(ray));
}

TEST_CASE("Sphere is missed by a ray leaving from its surface", "[sphere]")
{
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));
    Ray ray(Vector(0, 0, 4), Vector(0, 0, -1));

    // L = (0, 0, -5), b = 10, c = 25 - 25 = 0, discriminant = 100
    // t = (-10 - 10) / 2 = -10 or (-10 + 10) / 2 = 0: none is greater than 0
    REQUIRE_FALSE(sphere.isHitBy(ray));
}

TEST_CASE("Sphere refuses a negative radius", "[sphere]")
{
    REQUIRE_THROWS_AS(Sphere(Vector(0, 0, 9), -5, Colour(1, 0, 0)), std::domain_error);
}

TEST_CASE("Sphere refuses a zero radius", "[sphere]")
{
    REQUIRE_THROWS_AS(Sphere(Vector(0, 0, 9), 0, Colour(1, 0, 0)), std::domain_error);
}
