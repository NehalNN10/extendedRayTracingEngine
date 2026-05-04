#include "World.hpp"
#include "../geometry/Geometry.hpp"
#include "../cameras/Camera.hpp"
#include "../samplers/Sampler.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Constants.hpp"
#include "../lights/Light.hpp"
#include "../tracers/Tracer.hpp"
#include "../acceleration/bvh.hpp"

// no need to initialize ViewPlane, base constructor is already called
World::World() : max_depth(5), bg_color(black), camera_ptr(nullptr), sampler_ptr(nullptr), tracer_ptr(nullptr), bvh_ptr(nullptr), use_acceleration(false) {}

World::World(ViewPlane vp, int md, RGBColor bg, Camera *c_ptr, Sampler *s_ptr, Tracer* t_ptr, Geometry* bvh, bool accel) : vplane(vp), max_depth(md), bg_color(bg), camera_ptr(c_ptr), sampler_ptr(s_ptr), tracer_ptr(t_ptr), bvh_ptr(bvh), use_acceleration(accel) {}

World::~World() {
    for (Geometry* geom : geometry) {
        delete geom;
    }
    geometry.clear();
    delete camera_ptr;
    delete sampler_ptr;
    delete tracer_ptr;
    delete bvh_ptr;
    for (Light* light : lights) {
        delete light;
    }
    lights.clear();
}

void World::add_light(Light *light_ptr) {
    lights.push_back(light_ptr);
}

void World::add_geometry(Geometry *geom_ptr) {
    geometry.push_back(geom_ptr);
}

void World::set_camera(Camera *c_ptr) {
    camera_ptr = c_ptr;
}

ShadeInfo World::hit_objects(const Ray &ray) const 
{
    
    float weight = ray.w;
    if (use_acceleration && bvh_ptr) // we can just build the BVH in build() and assume it exists here
    {
        ShadeInfo bvh_hit_info(*this);
        bool hit = bvh_ptr->hit(ray, bvh_hit_info.t, bvh_hit_info);
        return bvh_hit_info;
    }
    ShadeInfo sr(*this);
    float t; // distance to first intersection
    float tmin = kHugeValue; // track closest hit
    bool hit_anything = false;

    for (Geometry* geom : geometry) {
        ShadeInfo temp_sr(*this); // check specific object

        // replace tmin if object is closer
        if (geom->hit(ray, t, temp_sr) && t < tmin) {
            hit_anything = true;
            tmin = t;
            sr = temp_sr;
            sr.hit = true;
            sr.t = tmin;
        }
    }

    if (hit_anything) {
        sr.ray = ray;
    }

    return sr;
}

// World::build() implemented in build files