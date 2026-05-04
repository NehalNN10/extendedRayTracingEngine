#include "SpotLight.hpp"
#include "PointLight.hpp"

#include "../utilities/Constants.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/RGBColor.hpp"
#include <string>
#include <cmath>

SpotLight::SpotLight() : PointLight(), direction_axis(Vector3D(0.0, 0.0, -1.0)), cutoff_angle(30.0), exponent(1.0) {}

SpotLight::SpotLight(const Point3D& pos, const RGBColor& col, double att_const, double lin, double quad, const Vector3D& dir, double cutoff, double exp) : PointLight(pos, col, att_const, lin, quad), direction_axis(dir), cutoff_angle(cutoff), exponent(exp) 
{
    direction_axis.normalize(); 
}

std::string SpotLight::to_string() const
{
    return "SpotLight(position: " + position.to_string() + ", color: " + color.to_string() + ", constant: " + std::to_string(constant) + ", linear: " + std::to_string(linear) + ", quadratic: " + std::to_string(quadratic) + ", direction_axis: " + direction_axis.to_string() + ", cutoff_angle: " + std::to_string(cutoff_angle) + ", exponent: " + std::to_string(exponent) + ")";
}

Vector3D SpotLight::get_direction_axis() const
{
    return direction_axis;
}

void SpotLight::set_direction_axis(const Vector3D& dir) 
{
    direction_axis = dir;
    direction_axis.normalize();
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

double SpotLight::get_attenuation(const Point3D& point) const 
{
    double distance = get_distance(point);
    double distance_attenuation = 1.0 / (constant + linear * distance + quadratic * distance * distance);

    Vector3D light_dir = (point - position);
    light_dir.normalize();

    double dot_product = light_dir * direction_axis;
    double cutoff_radians = cutoff_angle * PI / 180.0;
    double cutoff_cosine = std::cos(cutoff_radians);

    // less here means the angle between the light direction and the spotlight axis is greater than the cutoff angle
    if (dot_product < cutoff_cosine) 
    {
        return 0.0; // outside the spotlight cone
    }

    double spot_effect = std::pow(dot_product, exponent);
    return static_cast<double>(distance_attenuation * spot_effect);
}