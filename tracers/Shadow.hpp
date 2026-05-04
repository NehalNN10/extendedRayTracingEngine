#pragma once

#include "Tracer.hpp"

class Shadow : public Tracer {
public:
    Shadow(World* w_ptr) : Tracer(w_ptr) {}
    virtual ~Shadow() = default;

    virtual RGBColor trace_ray(const Ray& ray, int depth = 0) const override;
};
