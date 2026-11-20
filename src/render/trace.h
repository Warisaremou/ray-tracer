#pragma once

#include "colour/colour.h"
#include "geometry/ray.h"
#include "scene/scene.h"

// The colour the ray sees: the scene's nearest hit shaded with the scene's sun, or black if the
// ray hits nothing.
Colour trace(const Ray& ray, const Scene& scene);
