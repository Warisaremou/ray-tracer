#include "geometry/plane.h"
#include "geometry/sphere.h"
#include "material/lambert_shader.h"
#include "scene/scene.h"
#include "test_helpers.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <memory>

namespace
{
std::shared_ptr<const Material> blueMaterial()
{
    return std::make_shared<LambertShader>(Colour(0, 0, 1));
}

// With the sun along the normal the dot product is 1, so shading gives the material's whole colour.
Colour colourOf(const Hit& hit) { return hit.material->shade(hit.normal, hit.normal); }
} // namespace

// The camera's ray (see cameraRay()) hits a red sphere with centre (0, 0, 9) and radius 5 at t = 5.

TEST_CASE("Scene gives back its direction to the sun", "[scene]")
{
    Scene scene(Vector(0, 0, -1));

    REQUIRE_THAT(scene.toLight(), ApproxEquals(Vector(0, 0, -1)));
}

TEST_CASE("Scene gives the hit of a nearer shape added after a farther one", "[scene]")
{
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, redMaterial()));
    scene.add(std::make_unique<Plane>(Vector(0, 0, 2), Vector(0, 0, -1), blueMaterial()));

    // The plane is at z = 2, 3 in front of the origin (0, 0, -1): t = 3, before the sphere's 5.
    std::optional<Hit> hit = scene.nearestHit(cameraRay());

    REQUIRE(hit.has_value());
    REQUIRE(hit->t == Catch::Approx(3).margin(tolerance));
    REQUIRE_THAT(colourOf(hit.value()), ApproxEquals(Colour(0, 0, 1)));
}

TEST_CASE("Scene gives the hit of the nearest shape when it was added first", "[scene]")
{
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, redMaterial()));
    scene.add(std::make_unique<Plane>(Vector(0, 0, 20), Vector(0, 0, -1), blueMaterial()));

    // The plane is at z = 20: t = 21, after the sphere's 5.
    std::optional<Hit> hit = scene.nearestHit(cameraRay());

    REQUIRE(hit.has_value());
    REQUIRE(hit->t == Catch::Approx(5).margin(tolerance));
    REQUIRE_THAT(colourOf(hit.value()), ApproxEquals(Colour(1, 0, 0)));
}

TEST_CASE("Scene gives nothing when the ray hits no shape", "[scene]")
{
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(Vector(6, 0, 9), 5, redMaterial()));

    REQUIRE_FALSE(scene.nearestHit(cameraRay()).has_value());
}
