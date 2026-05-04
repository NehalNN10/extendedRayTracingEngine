#pragma once

#include "Tracer.hpp"

class Basic : public Tracer {
public:
    Basic(World* w_ptr) : Tracer(w_ptr) {}
    virtual ~Basic() = default;

    virtual RGBColor trace_ray(const Ray& ray, int depth = 0) const override;
};