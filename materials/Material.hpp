#pragma once

/**
   This file declares the Material class which is an abstract class for concrete
   materials to inherit from.

   Courtesy Kevin Suffern.
*/

#include "../utilities/RGBColor.hpp"

class ShadeInfo;
class Vector3D;

class Material {
public:
  // Constructors.
  Material() = default; // does nothing.

  // Copy constuctor and assignment operator.
  Material(const Material &other) = default;
  Material &operator=(const Material &other) = default;

  // Desctructor.
  virtual ~Material() = default;

  // BRDF evaluation used by tracers for direct lighting.
  virtual RGBColor f(const ShadeInfo &sinfo, const Vector3D &wo, const Vector3D &wi) const = 0;
  virtual RGBColor rho(const ShadeInfo &sinfo, const Vector3D &wo) const = 0;

  // specular component for recursion
  virtual bool is_specular() const { return false; }
  virtual RGBColor sample_specular(const ShadeInfo &sinfo, const Vector3D &wo, Vector3D &wi) const {
    return RGBColor(0.0f);
  }
};
