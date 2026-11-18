#pragma once

#include "math/vector.h"

#include <catch2/matchers/catch_matchers.hpp>
#include <string>

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
