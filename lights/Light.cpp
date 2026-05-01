#include "Light.hpp"
#include "../utilities/RGBColor.hpp"

Light::Light() : color(RGBColor(0.0f, 0.0f, 0.0f)) {}

Light::Light(const RGBColor& col) : color(col) {}

RGBColor Light::get_color() const
{
    return color;
}

void Light::set_color(const RGBColor& col) 
{
    color = col;
}