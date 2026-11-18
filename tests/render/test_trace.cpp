#include "render/trace.h"
#include "test_helpers.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

// The camera's ray (see cameraRay()) and a red sphere of radius 5.

TEST_CASE("Trace gives the sphere's colour when the ray hits it", "[trace]")
{
    Ray ray = cameraRay();
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));

    Colour colour = trace(ray, sphere);

    REQUIRE_THAT(colour, ApproxEquals(Colour(1, 0, 0)));
}

TEST_CASE("Trace gives black when the ray misses the sphere", "[trace]")
{
    Ray ray = cameraRay();
    Sphere sphere(Vector(6, 0, 9), 5, Colour(1, 0, 0));

    Colour colour = trace(ray, sphere);

    REQUIRE_THAT(colour, ApproxEquals(Colour(0, 0, 0)));
}
