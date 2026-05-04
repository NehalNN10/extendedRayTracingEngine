#pragma once

#include "PointLight.hpp"
#include "../utilities/Vector3D.hpp"
#include <string>

class SpotLight : public PointLight
{
    protected:
        Vector3D direction_axis; // direction_axis of the spotlight
        double cutoff_angle; // cutoff angle in degrees
        double exponent; // exponent for spotlight intensity falloff

    public:
        SpotLight();
        SpotLight(const Point3D& pos, const RGBColor& col, double att_const, double lin, double quad, const Vector3D& dir, double cutoff, double exp);

        SpotLight(const SpotLight &object) = default;
        SpotLight &operator=(const SpotLight &rhs) = default;

        ~SpotLight() = default;

        std::string to_string() const override;

        Vector3D get_direction_axis() const;
        void set_direction_axis(const Vector3D& dir);

        double get_cutoff_angle() const;
        void set_cutoff_angle(double cutoff);

        double get_exponent() const;
        void set_exponent(double exp);

        double get_attenuation(const Point3D& point) const override;
};