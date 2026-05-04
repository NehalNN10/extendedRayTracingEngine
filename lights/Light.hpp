#pragma once

/*
This file declares the Light abstract class from which other concrete light classes will inherit.
*/

#include "../utilities/RGBColor.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Vector3D.hpp"

#include <string>

class Light 
{
protected:
  RGBColor color; // color of the light
  float intensity; // radiance scale factor

public:
  // Constructors.
  Light(); 
  Light(const RGBColor& col);
  Light(const RGBColor& col, float intensity_val);

  // Copy constructor and assignment operator.
  Light(const Light &object) = default;
  Light &operator=(const Light &rhs) = default;

  // Destructor.
  virtual ~Light() = default;
  
  // String representation.
  virtual std::string to_string() const = 0;

  // Get/setters 
  RGBColor get_color() const;
  void set_color(const RGBColor& col);
  float get_intensity() const;
  void set_intensity(float intensity_val);

  virtual Vector3D get_direction(const Point3D& point) const = 0; // direction from a point to the light
  virtual double get_distance(const Point3D& point) const = 0; // distance from a point to the light
  virtual double get_attenuation(const Point3D& point) const = 0; // attenuation at a point
};
