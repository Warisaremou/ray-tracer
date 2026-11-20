#include "material/lambert_shader.h"

#include <algorithm>

LambertShader::LambertShader(const Colour& colour) : _colour(colour) {}

Colour LambertShader::shade(const Vector& normal, const Vector& toLight) const
{
    double brightness = std::max(0.0, normal.dot(toLight));
    return brightness * _colour;
}
