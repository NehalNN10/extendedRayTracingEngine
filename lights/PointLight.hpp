#pragma once

#include "Light.hpp"
#include "../utilities/Point3D.hpp"
#include <string>

class PointLight : public Light
{
    protected:
        Point3D position; // position of the light
        
        double constant;
        double linear;
        double quadratic;

    public:
        PointLight();
        PointLight(const Point3D& pos, const RGBColor& col, double att_const, double lin, double quad);

        // Copy constructor and assignment operator.
        PointLight(const PointLight &object) = default;
        PointLight &operator=(const PointLight &rhs) = default;

        // Destructor.
        ~PointLight() = default;

        std::string to_string() const override;

        Point3D get_position() const;
        void set_position(const Point3D& pos);

        double get_constant() const;
        void set_constant(double c);

        double get_linear() const;
        void set_linear(double l);

        double get_quadratic() const;
        void set_quadratic(double q);

        Vector3D get_direction(const Point3D& point) const override;
        double get_distance(const Point3D& point) const override;

        virtual double get_attenuation(const Point3D& point) const;
};