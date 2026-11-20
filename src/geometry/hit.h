#pragma once

#include "material/material.h"
#include "math/vector.h"

#include <memory>

struct Hit
{
    double t;
    Vector point;
    Vector normal;
    std::shared_ptr<const Material> material;
};
