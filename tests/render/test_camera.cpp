#include "render/camera.h"
#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Camera looking along z gives a ray along z", "[camera]")
{
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0));

    Ray ray = camera.rayThroughCentre();

    REQUIRE_THAT(ray.origin(), ApproxEquals(Vector(0, 0, -1)));
    REQUIRE_THAT(ray.direction(), ApproxEquals(Vector(0, 0, 1)));
}

TEST_CASE("Camera with an offset screen centre gives a ray towards it", "[camera]")
{
    Camera camera(Vector(1, 2, -1), Vector(4, 6, -1));

    Ray ray = camera.rayThroughCentre();

    REQUIRE_THAT(ray.origin(), ApproxEquals(Vector(1, 2, -1)));
    REQUIRE_THAT(ray.direction(), ApproxEquals(Vector(3, 4, 0)));
}
