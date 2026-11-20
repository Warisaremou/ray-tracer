#pragma once

#include "colour/colour.h"
#include "geometry/ray.h"
#include "material/material.h"
#include "math/vector.h"

#include <catch2/matchers/catch_matchers.hpp>
#include <memory>
#include <string>

// Absolute tolerance of the comparisons below. Without it, Catch::Approx(0) only matches exactly
// 0.0, so a computed zero such as 1e-17 would fail against an expected 0.
inline constexpr double tolerance = 1e-9;

// Catch2 matcher comparing two vectors component by component, with a tolerance.
// Usage: REQUIRE_THAT(actual, ApproxEquals(Vector(1, 2, 3)));
class ApproxEqualsMatcher : public Catch::Matchers::MatcherBase<Vector>
{
  private:
    Vector _expected;

  public:
    explicit ApproxEqualsMatcher(const Vector& expected);

    bool match(const Vector& actual) const override;
    std::string describe() const override;
};

ApproxEqualsMatcher ApproxEquals(const Vector& expected);

// Same for colours, channel by channel.
// Usage: REQUIRE_THAT(actual, ApproxEquals(Colour(1, 0, 0)));
class ColourApproxEqualsMatcher : public Catch::Matchers::MatcherBase<Colour>
{
  private:
    Colour _expected;

  public:
    explicit ColourApproxEqualsMatcher(const Colour& expected);

    bool match(const Colour& actual) const override;
    std::string describe() const override;
};

ColourApproxEqualsMatcher ApproxEquals(const Colour& expected);

// A red Lambert material.
std::shared_ptr<const Material> redMaterial();

// The ray of our camera in the first scene: origin (0, 0, -1), direction (0, 0, 1).
Ray cameraRay();
