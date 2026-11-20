#include "io/png_saver.h"

#include <algorithm>
#include <cmath>
#include <lodepng.h>
#include <stdexcept>
#include <vector>

namespace
{
// Turns a channel in [0, 1] into a byte in [0, 255]. Values outside the range are clamped.
unsigned char toByte(double channel)
{
    double clamped = std::clamp(channel, 0.0, 1.0);
    return static_cast<unsigned char>(std::lround(clamped * 255));
}
} // namespace

void PngSaver::save(Image& image, const std::string& path)
{
    std::vector<unsigned char> bytes;
    bytes.reserve(image.width() * image.height() * 3);

    for (unsigned int y = 0; y < image.height(); y++)
    {
        for (unsigned int x = 0; x < image.width(); x++)
        {
            Colour pixel = image.pixel(x, y);
            bytes.push_back(toByte(pixel.r()));
            bytes.push_back(toByte(pixel.g()));
            bytes.push_back(toByte(pixel.b()));
        }
    }

    unsigned int error = lodepng::encode(path, bytes, image.width(), image.height(), LCT_RGB);
    if (error != 0)
    {
        throw std::runtime_error(std::string("Could not save PNG: ") + lodepng_error_text(error));
    }
}
