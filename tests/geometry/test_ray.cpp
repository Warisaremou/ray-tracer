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

TEST_CASE("Ray gives the point at distance t along it", "[ray]")
{
    Ray ray(Vector(1, 2, 3), Vector(0, 2, 1));

    REQUIRE_THAT(ray.at(0), ApproxEquals(Vector(1, 2, 3)));
    REQUIRE_THAT(ray.at(2), ApproxEquals(Vector(1, 6, 5)));
    REQUIRE_THAT(ray.at(-1), ApproxEquals(Vector(1, 0, 2)));
}
