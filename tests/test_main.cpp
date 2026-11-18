#include "test_helpers.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Sanity check", "[smoke]") { REQUIRE(1 + 1 == 2); }

TEST_CASE("Floating point equality", "[smoke]")
{
    float a = 0.1f + 0.2f;
    REQUIRE(a == Catch::Approx(0.3f).epsilon(1e-5));
}

// The comparison helpers treat a tiny error as zero, so a computed 0 can match an expected 0.

TEST_CASE("ApproxEquals accepts a tiny error around zero for vectors", "[helpers]")
{
    REQUIRE_THAT(Vector(1e-12, -1e-12, 0), ApproxEquals(Vector(0, 0, 0)));
}

TEST_CASE("ApproxEquals accepts a tiny error around zero for colours", "[helpers]")
{
    REQUIRE_THAT(Colour(1e-12, 0, 1e-12), ApproxEquals(Colour(0, 0, 0)));
}

TEST_CASE("ApproxEquals still rejects a clear difference from zero", "[helpers]")
{
    REQUIRE_THAT(Vector(1e-6, 0, 0), !ApproxEquals(Vector(0, 0, 0)));
}
