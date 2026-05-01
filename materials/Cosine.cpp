#include "Cosine.hpp"
#include "../utilities/RGBColor.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/Ray.hpp"
#include <algorithm> // for std::max

Cosine::Cosine(): color(RGBColor(0.0f, 0.0f, 0.0f)) {}

Cosine::Cosine(float c): color(RGBColor(c, c, c)) {}

Cosine::Cosine(float r, float g, float b): color(RGBColor(r, g, b)) {}

Cosine::Cosine(const RGBColor &c): color(c) {}

// Copy constuctor and assignment operator.
Cosine::Cosine(const Cosine &other)
{
    color = other.color;
}

Cosine &Cosine::operator=(const Cosine &other)
{
    if (this == &other)
    {
        return *this;
    }
    color = other.color;
    return *this;
}

// lambertian reflection
RGBColor Cosine::shade(const ShadeInfo &sinfo) const {
    Vector3D view_dir = -sinfo.ray.d;
    view_dir.normalize();
    
    float cos_angle = sinfo.normal * view_dir;
    float intensity = std::max(0.0f, cos_angle);
    
    return color * intensity;
}