#include "light/light.h"
#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Light gives back its position and colour", "[light]")
{
    Light light(Vector(1, 2, 3), Colour(1, 0.5, 0));

    REQUIRE_THAT(light.position(), ApproxEquals(Vector(1, 2, 3)));
    REQUIRE_THAT(light.colour(), ApproxEquals(Colour(1, 0.5, 0)));
}
