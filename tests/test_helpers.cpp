#include "test_helpers.h"

#include <catch2/catch_approx.hpp>
#include <sstream>

ApproxEqualsMatcher::ApproxEqualsMatcher(const Vector& expected) : _expected(expected) {}

bool ApproxEqualsMatcher::match(const Vector& actual) const
{
    return actual.x() == Catch::Approx(_expected.x()) &&
           actual.y() == Catch::Approx(_expected.y()) && actual.z() == Catch::Approx(_expected.z());
}

std::string ApproxEqualsMatcher::describe() const
{
    std::ostringstream out;
    out << "is approximately (" << _expected.x() << ", " << _expected.y() << ", " << _expected.z()
        << ")";
    return out.str();
}

ApproxEqualsMatcher ApproxEquals(const Vector& expected) { return ApproxEqualsMatcher(expected); }
