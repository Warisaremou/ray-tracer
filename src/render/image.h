#pragma once

#include "colour/colour.h"

#include <vector>

class Image
{
  private:
    unsigned int _width;
    unsigned int _height;
    std::vector<Colour> _pixels;
    int index(int column, int row) const;

  public:
    Image(unsigned int width, unsigned int height);

    unsigned int width() const;
    unsigned int height() const;

    void setPixel(unsigned int column, unsigned int row, Colour colour);
    Colour pixel(unsigned int column, unsigned int row) const;
};
