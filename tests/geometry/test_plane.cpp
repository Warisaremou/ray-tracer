#include "geometry/plane.h"
#include "material/lambert_shader.h"
#include "test_helpers.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <optional>

namespace
{
std::shared_ptr<const Material> greenMaterial()
{
    return std::make_shared<LambertShader>(Colour(0, 1, 0));
}
} // namespace

// The client's floor: through the origin, facing up.

TEST_CASE("Plane gives the hit of a ray going down onto the floor", "[plane]")
{
    Plane floor(Vector(0, 0, 0), Vector(0, 1, 0), greenMaterial());
    Ray ray(Vector(0, 8, 0), Vector(3, -4, 0));

    // t = n·(Q - O) / (n·D) = (0, 1, 0)·(0, -8, 0) / (0, 1, 0)·(3, -4, 0) = -8 / -4 = 2
    std::optional<Hit> hit = floor.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE(hit->t == Catch::Approx(2).margin(tolerance));
    REQUIRE_THAT(hit->point, ApproxEquals(Vector(6, 0, 0)));
    REQUIRE_THAT(hit->normal, ApproxEquals(Vector(0, 1, 0)));
    // With the sun along the normal the dot product is 1, so shading gives the whole colour.
    REQUIRE_THAT(hit->material->shade(hit->normal, hit->normal), ApproxEquals(Colour(0, 1, 0)));
}

TEST_CASE("Plane normalises its normal", "[plane]")
{
    Plane line(Vector(8, 0, 0), Vector(3, 4, 0), greenMaterial());
    Ray ray(Vector(-8, 0, 0), Vector(4, 3, 0));

    // The line 3x + 4y = 24. t = (3, 4, 0)·(16, 0, 0) / (3, 4, 0)·(4, 3, 0) = 48 / 24 = 2
    // The point is (-8, 0, 0) + 2 (4, 3, 0) = (0, 6, 0) and the normal is (3, 4, 0) / 5.
    std::optional<Hit> hit = line.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE(hit->t == Catch::Approx(2).margin(tolerance));
    REQUIRE_THAT(hit->point, ApproxEquals(Vector(0, 6, 0)));
    REQUIRE_THAT(hit->normal, ApproxEquals(Vector(0.6, 0.8, 0)));
}

TEST_CASE("Plane is missed by a ray parallel to it", "[plane]")
{
    Plane floor(Vector(0, 0, 0), Vector(0, 1, 0), greenMaterial());
    Ray ray(Vector(0, 8, 0), Vector(5, 0, 0));

    // n·D = 0
    REQUIRE_FALSE(floor.hit(ray).has_value());
}

TEST_CASE("Plane is missed by a ray going away from it", "[plane]")
{
    Plane floor(Vector(0, 0, 0), Vector(0, 1, 0), greenMaterial());
    Ray ray(Vector(0, 8, 0), Vector(3, 4, 0));

    // t = -8 / 4 = -2, so the floor is behind the ray.
    REQUIRE_FALSE(floor.hit(ray).has_value());
}
