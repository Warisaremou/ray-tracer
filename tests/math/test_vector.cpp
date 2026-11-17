#include "math/vector.h"
#include "vector_matchers.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <stdexcept>

// Integer values

TEST_CASE("Vector addition with integers", "[vector]")
{
    Vector a(1, 2, 3);
    Vector b(4, 5, 6);

    Vector result = a + b;

    REQUIRE_THAT(result, ApproxEquals(Vector(5, 7, 9)));
}

TEST_CASE("Vector subtraction with integers", "[vector]")
{
    Vector a(-1, 4, 0);
    Vector b(-5, 2, 1);

    Vector result = a - b;

    REQUIRE_THAT(result, ApproxEquals(Vector(4, 2, -1)));
}

TEST_CASE("Vector scale with integers", "[vector]")
{
    Vector v(3, -4, 0);

    Vector result = 2 * v;

    REQUIRE_THAT(result, ApproxEquals(Vector(6, -8, 0)));
}

TEST_CASE("Vector length with integers", "[vector]")
{
    Vector v(6, -8, 0);

    REQUIRE(v.length() == Catch::Approx(10));
}

TEST_CASE("Vector normalised with integers", "[vector]")
{
    Vector v(3, -4, 0);

    Vector result = v.normalised();

    REQUIRE_THAT(result, ApproxEquals(Vector(0.6, -0.8, 0)));
    REQUIRE(result.length() == Catch::Approx(1));
}

TEST_CASE("Vector dot product with integers", "[vector]")
{
    Vector a(3, 4, 0);
    Vector b(4, 3, 0);

    REQUIRE(a.dot(b) == Catch::Approx(24));
}

// Double values

TEST_CASE("Vector addition with doubles", "[vector]")
{
    Vector a(1.5, 2.25, -3.5);
    Vector b(0.5, -1.25, 4.0);

    Vector result = a + b;

    REQUIRE_THAT(result, ApproxEquals(Vector(2.0, 1.0, 0.5)));
}

TEST_CASE("Vector subtraction with doubles", "[vector]")
{
    Vector a(1.5, -2.25, 0.75);
    Vector b(0.5, 1.25, -0.25);

    Vector result = a - b;

    REQUIRE_THAT(result, ApproxEquals(Vector(1.0, -3.5, 1.0)));
}

TEST_CASE("Vector scale with doubles", "[vector]")
{
    Vector v(1.5, -2.5, 0.25);

    Vector result = 0.5 * v;

    REQUIRE_THAT(result, ApproxEquals(Vector(0.75, -1.25, 0.125)));
}

TEST_CASE("Vector length with doubles", "[vector]")
{
    Vector v(1.5, 2.0, 0.0);

    REQUIRE(v.length() == Catch::Approx(2.5));
}

TEST_CASE("Vector normalised with doubles", "[vector]")
{
    Vector v(1.5, 2.0, 0.0);

    Vector result = v.normalised();

    REQUIRE_THAT(result, ApproxEquals(Vector(0.6, 0.8, 0.0)));
    REQUIRE(result.length() == Catch::Approx(1.0));
}

TEST_CASE("Vector dot product with doubles", "[vector]")
{
    Vector a(1.5, -2.0, 0.5);
    Vector b(2.0, 0.25, 4.0);

    REQUIRE(a.dot(b) == Catch::Approx(4.5));
}

// Edge cases

TEST_CASE("Vector normalised throws on the zero vector", "[vector]")
{
    Vector zero(0, 0, 0);

    REQUIRE_THROWS_AS(zero.normalised(), std::domain_error);
}
