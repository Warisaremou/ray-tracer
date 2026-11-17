#pragma once

#include "math/vector.h"

#include <catch2/catch_approx.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <sstream>
#include <string>

// Catch2 matcher comparing two vectors component by component, with a tolerance.
// Usage: REQUIRE_THAT(actual, ApproxEquals(Vector(1, 2, 3)));
class ApproxEqualsMatcher : public Catch::Matchers::MatcherBase<Vector>
{
  private:
    Vector _expected;

  public:
    explicit ApproxEqualsMatcher(const Vector& expected) : _expected(expected) {}

    bool match(const Vector& actual) const override
    {
        return actual.x() == Catch::Approx(_expected.x()) &&
               actual.y() == Catch::Approx(_expected.y()) &&
               actual.z() == Catch::Approx(_expected.z());
    }

    std::string describe() const override
    {
        std::ostringstream out;
        out << "is approximately (" << _expected.x() << ", " << _expected.y() << ", "
            << _expected.z() << ")";
        return out.str();
    }
};

inline ApproxEqualsMatcher ApproxEquals(const Vector& expected)
{
    return ApproxEqualsMatcher(expected);
}
