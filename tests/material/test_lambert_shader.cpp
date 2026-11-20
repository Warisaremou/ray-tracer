#include "material/lambert_shader.h"
#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>

// The surface normal is (0, 0, 1). toLight is a unit vector.

TEST_CASE("Lambert shader gives the full colour when the sun is straight above", "[material]")
{
    LambertShader shader(Colour(1, 0.5, 0.2));

    // The dot product is 1.
    REQUIRE_THAT(shader.shade(Vector(0, 0, 1), Vector(0, 0, 1)), ApproxEquals(Colour(1, 0.5, 0.2)));
}

TEST_CASE("Lambert shader darkens the colour by the dot product for an angled sun", "[material]")
{
    LambertShader shader(Colour(1, 0.5, 0));

    // The dot product of (0, 0, 1) and (0.6, 0, 0.8) is 0.8.
    REQUIRE_THAT(shader.shade(Vector(0, 0, 1), Vector(0.6, 0, 0.8)), ApproxEquals(Colour(0.8, 0.4, 0)));
}

TEST_CASE("Lambert shader gives black when the sun is behind the surface", "[material]")
{
    LambertShader shader(Colour(1, 0.5, 0.2));

    // The dot product is -1, which is clamped to 0.
    REQUIRE_THAT(shader.shade(Vector(0, 0, 1), Vector(0, 0, -1)), ApproxEquals(Colour(0, 0, 0)));
}

TEST_CASE("Lambert shader gives black when the sun is level with the surface", "[material]")
{
    LambertShader shader(Colour(1, 0.5, 0.2));

    // The dot product of (0, 0, 1) and (1, 0, 0) is 0.
    REQUIRE_THAT(shader.shade(Vector(0, 0, 1), Vector(1, 0, 0)), ApproxEquals(Colour(0, 0, 0)));
}
