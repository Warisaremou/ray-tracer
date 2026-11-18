#include "geometry/ray.h"
#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>
#include <stdexcept>

TEST_CASE("Ray gives back its origin and direction", "[ray]")
{
    Ray ray(Vector(1, 2, 3), Vector(3, 4, 0));

    REQUIRE_THAT(ray.origin(), ApproxEquals(Vector(1, 2, 3)));
    REQUIRE_THAT(ray.direction(), ApproxEquals(Vector(3, 4, 0)));
}

TEST_CASE("Ray refuses a zero direction", "[ray]")
{
    REQUIRE_THROWS_AS(Ray(Vector(1, 2, 3), Vector(0, 0, 0)), std::domain_error);
}
