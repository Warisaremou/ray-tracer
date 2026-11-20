#include "render/image.h"

Image::Image(unsigned int width, unsigned int height)
    : _width(width), _height(height), _pixels(width * height, Colour(0, 0, 0))
{
}

unsigned int Image::width() const { return _width; }

unsigned int Image::height() const { return _height; }

void Image::setPixel(unsigned int column, unsigned int row, Colour colour)
{
    _pixels[index(column, row)] = colour;
}

Colour Image::pixel(unsigned int column, unsigned int row) const { return _pixels[index(column, row)]; }

int Image::index(int column, int row) const {
    return row * _width + column;
}