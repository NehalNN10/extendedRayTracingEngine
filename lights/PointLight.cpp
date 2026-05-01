#include "PointLight.hpp"
#include "Light.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/RGBColor.hpp"
#include "../utilities/Vector3D.hpp"
#include <string>
#include <cmath>

PointLight::PointLight() : Light(), position(Point3D(0.0, 0.0, 0.0)), constant(1.0), linear(0.0), quadratic(0.0) {}

PointLight::PointLight(const Point3D& pos, const RGBColor& col, double att_const, double lin, double quad) : Light(col), position(pos), constant(att_const), linear(lin), quadratic(quad) {}

std::string PointLight::to_string() const 
{
    return "PointLight(position: " + position.to_string() + ", color: " + color.to_string() + ", constant: " + std::to_string(constant) + ", linear: " + std::to_string(linear) + ", quadratic: " + std::to_string(quadratic) + ")";
}

Point3D PointLight::get_position() const
{
    return position;
}

void PointLight::set_position(const Point3D& pos) 
{
    position = pos;
}

double PointLight::get_constant() const 
{
    return constant;
}

void PointLight::set_constant(double c) 
{
    constant = c;
}

double PointLight::get_linear() const 
{
    return linear;
}

void PointLight::set_linear(double l) 
{
    linear = l;
}

double PointLight::get_quadratic() const 
{
    return quadratic;
}

void PointLight::set_quadratic(double q) 
{
    quadratic = q;
}

Vector3D PointLight::get_direction(const Point3D& point) const 
{
    Vector3D dir = position - point;
    dir.normalize();
    return dir;
}

double PointLight::get_distance(const Point3D& point) const 
{
    return position.distance(point);
}

double PointLight::get_attenuation(const Point3D& point) const 
{
    double d = get_distance(point);
    return 1.0 / (constant + linear * d + quadratic * d * d);
}