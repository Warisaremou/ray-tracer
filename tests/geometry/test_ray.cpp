#include "geometry/ray.h"
#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Ray gives back its origin and direction", "[ray]")
{
    Ray ray(Vector(1, 2, 3), Vector(3, 4, 0));

    REQUIRE_THAT(ray.origin(), ApproxEquals(Vector(1, 2, 3)));
    REQUIRE_THAT(ray.direction(), ApproxEquals(Vector(3, 4, 0)));
}
