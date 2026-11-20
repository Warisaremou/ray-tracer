#pragma once

#include "render/image.h"

#include <string>

class ImageSaver
{
  public:
    virtual ~ImageSaver() = default;

    virtual void save(Image& image, const std::string& path) = 0;
};
