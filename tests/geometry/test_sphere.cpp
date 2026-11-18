#include "geometry/ray.h"
#include "geometry/sphere.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Sphere stores its centre, radius and colour", "[sphere]")
{
    Sphere sphere(Vector(1, 2, 3), 1.5, Colour(0.25, 0.5, 0.75));

    REQUIRE(sphere.centre().x() == Catch::Approx(1));
    REQUIRE(sphere.centre().y() == Catch::Approx(2));
    REQUIRE(sphere.centre().z() == Catch::Approx(3));
    REQUIRE(sphere.radius() == Catch::Approx(1.5));
    REQUIRE(sphere.colour().r() == Catch::Approx(0.25));
    REQUIRE(sphere.colour().g() == Catch::Approx(0.5));
    REQUIRE(sphere.colour().b() == Catch::Approx(0.75));
}

TEST_CASE("Sphere gives back its colour", "[sphere]")
{
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));

    REQUIRE(sphere.colour().r() == Catch::Approx(1));
    REQUIRE(sphere.colour().g() == Catch::Approx(0));
    REQUIRE(sphere.colour().b() == Catch::Approx(0));
}

// The camera's ray: origin (0, 0, -1), direction (0, 0, 1). The sphere has radius 5.
// a = D·D = 1 and b = 2 D·L = -20 for every centre below.

TEST_CASE("Sphere with centre (0, 0, 9) is hit by the camera's ray", "[sphere]")
{
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));

    // L = (0, 0, -10), c = 100 - 25 = 75, discriminant = 400 - 300 = 100
    REQUIRE(sphere.isHitBy(ray));
}

TEST_CASE("Sphere with centre (3, 0, 9) is hit by the camera's ray", "[sphere]")
{
    Sphere sphere(Vector(3, 0, 9), 5, Colour(1, 0, 0));
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));

    // L = (-3, 0, -10), c = 109 - 25 = 84, discriminant = 400 - 336 = 64
    REQUIRE(sphere.isHitBy(ray));
}

TEST_CASE("Sphere with centre (6, 0, 9) is missed by the camera's ray", "[sphere]")
{
    Sphere sphere(Vector(6, 0, 9), 5, Colour(1, 0, 0));
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));

    // L = (-6, 0, -10), c = 136 - 25 = 111, discriminant = 400 - 444 = -44
    REQUIRE_FALSE(sphere.isHitBy(ray));
}

TEST_CASE("Sphere with centre (0, 0, -11) behind the camera is missed by its ray", "[sphere]")
{
    Sphere sphere(Vector(0, 0, -11), 5, Colour(1, 0, 0));
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));

    // L = (0, 0, 10), b = 20, c = 100 - 25 = 75, discriminant = 400 - 300 = 100
    // t = (-20 - 10) / 2 = -15 or (-20 + 10) / 2 = -5: both behind the origin
    REQUIRE_FALSE(sphere.isHitBy(ray));
}
