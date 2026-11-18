#include "render/trace.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

// The camera's ray: origin (0, 0, -1), direction (0, 0, 1). The sphere is red, with radius 5.

TEST_CASE("Trace gives the sphere's colour when the ray hits it", "[trace]")
{
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));

    Colour colour = trace(ray, sphere);

    REQUIRE(colour.r() == Catch::Approx(1));
    REQUIRE(colour.g() == Catch::Approx(0));
    REQUIRE(colour.b() == Catch::Approx(0));
}

TEST_CASE("Trace gives black when the ray misses the sphere", "[trace]")
{
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(6, 0, 9), 5, Colour(1, 0, 0));

    Colour colour = trace(ray, sphere);

    REQUIRE(colour.r() == Catch::Approx(0));
    REQUIRE(colour.g() == Catch::Approx(0));
    REQUIRE(colour.b() == Catch::Approx(0));
}
