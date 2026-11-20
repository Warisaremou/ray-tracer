#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "test_helpers.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <optional>
#include <stdexcept>

TEST_CASE("Sphere refuses a missing material", "[sphere]")
{
    REQUIRE_THROWS_AS(Sphere(Vector(0, 0, 9), 5, nullptr), std::invalid_argument);
}

// The camera's ray (see cameraRay()) and a sphere of radius 5.
// a = D·D = 1, and b = 2 D·L = -20 for every centre ahead of the camera.

TEST_CASE("Sphere with centre (0, 0, 9) is hit by the camera's ray", "[sphere]")
{
    Sphere sphere(Vector(0, 0, 9), 5, redMaterial());
    Ray ray = cameraRay();

    // L = (0, 0, -10), c = 100 - 25 = 75, discriminant = 400 - 300 = 100
    REQUIRE(sphere.hit(ray).has_value());
}

TEST_CASE("Sphere with centre (3, 0, 9) is hit by the camera's ray", "[sphere]")
{
    Sphere sphere(Vector(3, 0, 9), 5, redMaterial());
    Ray ray = cameraRay();

    // L = (-3, 0, -10), c = 109 - 25 = 84, discriminant = 400 - 336 = 64
    REQUIRE(sphere.hit(ray).has_value());
}

TEST_CASE("Sphere with centre (6, 0, 9) is missed by the camera's ray", "[sphere]")
{
    Sphere sphere(Vector(6, 0, 9), 5, redMaterial());
    Ray ray = cameraRay();

    // L = (-6, 0, -10), c = 136 - 25 = 111, discriminant = 400 - 444 = -44
    REQUIRE_FALSE(sphere.hit(ray).has_value());
}

TEST_CASE("Sphere with centre (0, 0, -11) behind the camera is missed by its ray", "[sphere]")
{
    Sphere sphere(Vector(0, 0, -11), 5, redMaterial());
    Ray ray = cameraRay();

    // L = (0, 0, 10), b = 20, c = 100 - 25 = 75, discriminant = 400 - 300 = 100
    // t = (-20 - 10) / 2 = -15 or (-20 + 10) / 2 = -5: both behind the origin
    REQUIRE_FALSE(sphere.hit(ray).has_value());
}

TEST_CASE("Sphere is hit by a ray starting inside it", "[sphere]")
{
    Sphere sphere(Vector(0, 0, 9), 5, redMaterial());
    Ray ray(Vector(0, 0, 9), Vector(0, 0, 1));

    // L = (0, 0, 0), b = 0, c = -25, discriminant = 100
    // t = (0 - 10) / 2 = -5 or (0 + 10) / 2 = 5: one behind, one ahead
    REQUIRE(sphere.hit(ray).has_value());
}

TEST_CASE("Sphere is missed by a ray leaving from its surface", "[sphere]")
{
    Sphere sphere(Vector(0, 0, 9), 5, redMaterial());
    Ray ray(Vector(0, 0, 4), Vector(0, 0, -1));

    // L = (0, 0, -5), b = 10, c = 25 - 25 = 0, discriminant = 100
    // t = (-10 - 10) / 2 = -10 or (-10 + 10) / 2 = 0: none is greater than 0
    REQUIRE_FALSE(sphere.hit(ray).has_value());
}

TEST_CASE("Sphere refuses a negative radius", "[sphere]")
{
    REQUIRE_THROWS_AS(Sphere(Vector(0, 0, 9), -5, redMaterial()), std::domain_error);
}

TEST_CASE("Sphere refuses a zero radius", "[sphere]")
{
    REQUIRE_THROWS_AS(Sphere(Vector(0, 0, 9), 0, redMaterial()), std::domain_error);
}

// Hit information. The camera's ray is origin (0, 0, -1), direction (0, 0, 1).

TEST_CASE("Sphere gives the hit point and normal of the closest hit", "[sphere]")
{
    Sphere sphere(Vector(0, 0, 9), 5, redMaterial());

    // L = (0, 0, -10), t = (20 - 10) / 2 = 5 or (20 + 10) / 2 = 15. The closest is 5.
    // The hit point is (0, 0, -1) + 5 (0, 0, 1) = (0, 0, 4), the normal is (0, 0, -5) / 5.
    std::optional<Hit> hit = sphere.hit(cameraRay());

    REQUIRE(hit.has_value());
    REQUIRE(hit->t == Catch::Approx(5).margin(tolerance));
    REQUIRE_THAT(hit->point, ApproxEquals(Vector(0, 0, 4)));
    REQUIRE_THAT(hit->normal, ApproxEquals(Vector(0, 0, -1)));
}

TEST_CASE("Sphere gives a normal that points away from the centre for an off-centre hit",
          "[sphere]")
{
    Sphere sphere(Vector(3, 0, 9), 5, redMaterial());

    // t = (20 - 8) / 2 = 6, so the hit point is (0, 0, 5).
    // The normal is (0 - 3, 0, 5 - 9) / 5 = (-3, 0, -4) / 5.
    std::optional<Hit> hit = sphere.hit(cameraRay());

    REQUIRE(hit.has_value());
    REQUIRE(hit->t == Catch::Approx(6).margin(tolerance));
    REQUIRE_THAT(hit->point, ApproxEquals(Vector(0, 0, 5)));
    REQUIRE_THAT(hit->normal, ApproxEquals(Vector(-0.6, 0, -0.8)));
}

TEST_CASE("Sphere gives the far hit for a ray starting inside it", "[sphere]")
{
    Sphere sphere(Vector(0, 0, 9), 5, redMaterial());
    Ray ray(Vector(0, 0, 9), Vector(0, 0, 1));

    // t = -5 is behind the origin, t = 5 is ahead: the hit point is (0, 0, 14).
    std::optional<Hit> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE(hit->t == Catch::Approx(5).margin(tolerance));
    REQUIRE_THAT(hit->point, ApproxEquals(Vector(0, 0, 14)));
    REQUIRE_THAT(hit->normal, ApproxEquals(Vector(0, 0, 1)));
}

TEST_CASE("Sphere gives the far hit for a ray starting inside it, away from the centre", "[sphere]")
{
    Sphere sphere(Vector(0, 0, 1), 5, redMaterial());

    // The sphere is around the eye. L = (0, 0, -2), a = 1, b = -4, c = 4 - 25 = -21,
    // discriminant = 16 + 84 = 100, so t = (4 - 10) / 2 = -3 (behind) or (4 + 10) / 2 = 7 (ahead).
    // The hit point is (0, 0, -1) + 7 (0, 0, 1) = (0, 0, 6) and the normal is (0, 0, 5) / 5.
    std::optional<Hit> hit = sphere.hit(cameraRay());

    REQUIRE(hit.has_value());
    REQUIRE(hit->t == Catch::Approx(7).margin(tolerance));
    REQUIRE_THAT(hit->point, ApproxEquals(Vector(0, 0, 6)));
    REQUIRE_THAT(hit->normal, ApproxEquals(Vector(0, 0, 1)));
}

TEST_CASE("Sphere gives its own material in the hit information", "[sphere]")
{
    std::shared_ptr<const Material> material = redMaterial();
    Sphere sphere(Vector(0, 0, 9), 5, material);

    std::optional<Hit> hit = sphere.hit(cameraRay());

    REQUIRE(hit.has_value());
    REQUIRE(hit->material == material);
}
