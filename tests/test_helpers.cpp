#include "test_helpers.h"

#include "material/lambert_shader.h"

#include <catch2/catch_approx.hpp>
#include <sstream>

ApproxEqualsMatcher::ApproxEqualsMatcher(const Vector& expected) : _expected(expected) {}

bool ApproxEqualsMatcher::match(const Vector& actual) const
{
    return actual.x() == Catch::Approx(_expected.x()).margin(tolerance) &&
           actual.y() == Catch::Approx(_expected.y()).margin(tolerance) &&
           actual.z() == Catch::Approx(_expected.z()).margin(tolerance);
}

std::string ApproxEqualsMatcher::describe() const
{
    std::ostringstream out;
    out << "is approximately (" << _expected.x() << ", " << _expected.y() << ", " << _expected.z()
        << ")";
    return out.str();
}

ApproxEqualsMatcher ApproxEquals(const Vector& expected) { return ApproxEqualsMatcher(expected); }

ColourApproxEqualsMatcher::ColourApproxEqualsMatcher(const Colour& expected) : _expected(expected)
{
}

bool ColourApproxEqualsMatcher::match(const Colour& actual) const
{
    return actual.r() == Catch::Approx(_expected.r()).margin(tolerance) &&
           actual.g() == Catch::Approx(_expected.g()).margin(tolerance) &&
           actual.b() == Catch::Approx(_expected.b()).margin(tolerance);
}

std::string ColourApproxEqualsMatcher::describe() const
{
    std::ostringstream out;
    out << "is approximately colour (" << _expected.r() << ", " << _expected.g() << ", "
        << _expected.b() << ")";
    return out.str();
}

ColourApproxEqualsMatcher ApproxEquals(const Colour& expected)
{
    return ColourApproxEqualsMatcher(expected);
}

Ray cameraRay() { return Ray(Vector(0, 0, -1), Vector(0, 0, 1)); }

std::shared_ptr<const Material> redMaterial()
{
    return std::make_shared<LambertShader>(Colour(1, 0, 0));
}
