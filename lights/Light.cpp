#include "Light.hpp"
#include "../utilities/RGBColor.hpp"

Light::Light() : color(RGBColor(0.0f, 0.0f, 0.0f)), intensity(1.0f) {}

Light::Light(const RGBColor& col) : color(col), intensity(1.0f) {}

Light::Light(const RGBColor& col, float intensity_val) : color(col), intensity(intensity_val) {}

RGBColor Light::get_color() const
{
    return color;
}

void Light::set_color(const RGBColor& col) 
{
    color = col;
}

float Light::get_intensity() const
{
    return intensity;
}

void Light::set_intensity(float intensity_val)
{
    intensity = intensity_val;
}