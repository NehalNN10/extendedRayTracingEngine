#pragma once

#include "PointLight.hpp"
#include "../utilities/Vector3D.hpp"
#include <string>

class SpotLight : public PointLight
{
    protected:
        Vector3D direction; // direction of the spotlight
        double cutoff_angle; // cutoff angle in degrees
        double exponent; // exponent for spotlight intensity falloff

    public:
        SpotLight();
        SpotLight(const Point3D& pos, const RGBColor& col, double att_const, double lin, double quad, const Vector3D& dir, double cutoff, double exp);

        // Copy constructor and assignment operator.
        SpotLight(const SpotLight &object) = default;
        SpotLight &operator=(const SpotLight &rhs) = default;

        // Destructor.
        ~SpotLight() = default;

        std::string to_string() const override;

        Vector3D get_direction() const;
        void set_direction(const Vector3D& dir);

        double get_cutoff_angle() const;
        void set_cutoff_angle(double cutoff);

        double get_exponent() const;
        void set_exponent(double exp);
};