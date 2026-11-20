#include "render/trace.h"

#include <optional>

Colour trace(const Ray& ray, const Scene& scene)
{
    std::optional<Hit> hit = scene.nearestHit(ray);
    if (hit.has_value())
    {
        return hit->material->shade(hit->normal, scene.toLight());
    }

    return Colour(0, 0, 0);
}
