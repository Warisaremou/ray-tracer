#include "material/flat_shader.h"
#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Flat shader shades with its colour, whatever the sun", "[material]")
{
    FlatShader shader(Colour(1, 0.5, 0));

    REQUIRE_THAT(shader.shade(Vector(0, 0, 1), Vector(0, 0, -1)), ApproxEquals(Colour(1, 0.5, 0)));
}
