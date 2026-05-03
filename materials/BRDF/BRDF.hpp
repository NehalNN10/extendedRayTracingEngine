#pragma once

#include "../../utilities/RGBColor.hpp"
#include "../../utilities/Vector3D.hpp"
#include "../../utilities/ShadeInfo.hpp"

class BRDF {
public:
    BRDF() = default;
    BRDF(const BRDF& other) = default;
    BRDF& operator=(const BRDF& other) = default;
    virtual ~BRDF() = default;

    virtual RGBColor f(const ShadeInfo& sinfo, const Vector3D& wo, const Vector3D& wi) const = 0;
    virtual RGBColor rho(const ShadeInfo& sinfo, const Vector3D& wo) const = 0;
};