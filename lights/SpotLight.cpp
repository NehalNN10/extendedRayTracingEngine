#include "SpotLight.hpp"
#include "PointLight.hpp"

#include "../utilities/Point3D.hpp"
#include "../utilities/RGBColor.hpp"
#include <string>
#include <cmath>

SpotLight::SpotLight() : PointLight(), direction(Vector3D(0.0, 0.0, -1.0)), cutoff_angle(30.0), exponent(1.0) {}

SpotLight::SpotLight(const Point3D& pos, const RGBColor& col, double att_const, double lin, double quad, const Vector3D& dir, double cutoff, double exp) : PointLight(pos, col, att_const, lin, quad), direction(dir), cutoff_angle(cutoff), exponent(exp) {}

std::string SpotLight::to_string() const
{
    return "SpotLight(position: " + position.to_string() + ", color: " + color.to_string() + ", constant: " + std::to_string(constant) + ", linear: " + std::to_string(linear) + ", quadratic: " + std::to_string(quadratic) + ", direction: " + direction.to_string() + ", cutoff_angle: " + std::to_string(cutoff_angle) + ", exponent: " + std::to_string(exponent) + ")";
}

Vector3D SpotLight::get_direction() const
{
    return direction;
}

void SpotLight::set_direction(const Vector3D& dir) 
{
    direction = dir;
}

double SpotLight::get_cutoff_angle() const 
{
    return cutoff_angle;
}

void SpotLight::set_cutoff_angle(double cutoff) 
{
    cutoff_angle = cutoff;
}

double SpotLight::get_exponent() const 
{
    return exponent;
}

void SpotLight::set_exponent(double exp) 
{
    exponent = exp;
}
