#include "colour/colour.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Colour gives back its channels", "[colour]")
{
    Colour colour(1, 0.5, 0);

    REQUIRE(colour.r() == Catch::Approx(1));
    REQUIRE(colour.g() == Catch::Approx(0.5));
    REQUIRE(colour.b() == Catch::Approx(0));
}
