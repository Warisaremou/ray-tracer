#include "render/image.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("setPixel sets the pixel at the given column and row, the others stay black", "[image]")
{
    Image image(5, 4);

    image.setPixel(3, 2, Colour(1, 0.5, 0.25));

    for (unsigned int y = 0; y < image.height(); y++)
    {
        for (unsigned int x = 0; x < image.width(); x++)
        {
            Colour pixel = image.pixel(x, y);
            if (x == 3 && y == 2)
            {
                REQUIRE(pixel.r() == Catch::Approx(1));
                REQUIRE(pixel.g() == Catch::Approx(0.5));
                REQUIRE(pixel.b() == Catch::Approx(0.25));
            }
            else
            {
                REQUIRE(pixel.r() == Catch::Approx(0));
                REQUIRE(pixel.g() == Catch::Approx(0));
                REQUIRE(pixel.b() == Catch::Approx(0));
            }
        }
    }
}
