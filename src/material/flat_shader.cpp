#include "material/flat_shader.h"

FlatShader::FlatShader(const Colour& colour) : _colour(colour) {}

Colour FlatShader::shade(const Vector&, const Vector&) const { return _colour; }
