#include "light/light.h"

Light::Light(const Vector& position, const Colour& colour) : _position(position), _colour(colour) {}

Vector Light::position() const { return _position; }

Colour Light::colour() const { return _colour; }
