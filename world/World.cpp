#include "World.hpp"
#include "../geometry/Geometry.hpp"
#include "../cameras/Camera.hpp"
#include "../samplers/Sampler.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Constants.hpp"

// no need to initialize ViewPlane, base constructor is already called
World::World() : bg_color(black), camera_ptr(nullptr), sampler_ptr(nullptr) {}

World::~World() {
    for (Geometry* geom : geometry) {
        delete geom;
    }
    geometry.clear();
    delete camera_ptr;
    delete sampler_ptr;
}

void World::add_geometry(Geometry *geom_ptr) {
    geometry.push_back(geom_ptr);
}

void World::set_camera(Camera *c_ptr) {
    camera_ptr = c_ptr;
}

ShadeInfo World::hit_objects(const Ray &ray) {
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