#pragma once

#include "../utilities/RGBColor.hpp"
#include "../utilities/Ray.hpp"

class World; // forward declaration - avoids circular dependency
// https://stackoverflow.com/questions/4757565/what-are-forward-declarations-in-c

class Tracer {
protected:
    World* world_ptr;

public:
    Tracer(World* w_ptr) : world_ptr(w_ptr) {}
    virtual ~Tracer() = default;

    // trace ray and return color; depth defaults to primary ray
    virtual RGBColor trace_ray(const Ray& ray, int depth = 0) const = 0;
};