#include "RGBColor.hpp"
#include <cmath>
#include <string>

// Added the missing default constructor
RGBColor::RGBColor() : r(0.0f), g(0.0f), b(0.0f) {}

RGBColor::RGBColor(float c): r(c), g(c), b(c) {}

RGBColor::RGBColor(float _r, float _g, float _b): r(_r), g(_g), b(_b) {}

std::string RGBColor::to_string() const {
    return "RGBColor(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ")"; 
}

// Operations.

RGBColor RGBColor::operator+(const RGBColor &c) const
{
    return RGBColor(r + c.r, g + c.g, b + c.b);
}

RGBColor& RGBColor::operator+=(const RGBColor &c)
{
    r += c.r;
    g += c.g;
    b += c.b;
    return *this; // *this returns the object itself
}

RGBColor RGBColor::operator*(const float a) const
{
    return RGBColor(r * a, g * a, b * a);
}

RGBColor& RGBColor::operator*=(const float a)
{
    r *= a;
    g *= a;
    b *= a;
    return *this;
}

RGBColor RGBColor::operator/(const float a) const
{
    return RGBColor(r / a, g / a, b / a);
}

RGBColor& RGBColor::operator/=(const float a)
{
    r /= a;
    g /= a;
    b /= a;
    return *this;
}

RGBColor RGBColor::operator*(const RGBColor &c) const
{
    return RGBColor(r * c.r, g * c.g, b * c.b);
}

bool RGBColor::operator==(const RGBColor &c) const
{
    return (r == c.r) && (g == c.g) && (b == c.b);
}

RGBColor RGBColor::powc(float p) const
{
    return RGBColor(std::pow(r, p), std::pow(g, p), std::pow(b, p));
}

float RGBColor::average() const
{
    return (r + g + b) / 3.0;
}

RGBColor operator*(const float a, const RGBColor &c)
{
    return RGBColor(c.r * a, c.g * a, c.b * a);
}