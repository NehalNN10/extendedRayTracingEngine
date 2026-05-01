#include "BBox.hpp"
#include "Ray.hpp" // for hit function
#include "Constants.hpp"
#include "../geometry/Geometry.hpp"

// constructor
BBox::BBox(const Point3D& min, const Point3D& max) : pmin(min), pmax(max) {}

std::string BBox::to_string() const {
    return "BBox(" + pmin.to_string() + ", " + pmax.to_string() + ")";
}

// ray-AABB intersection
bool BBox::hit(const Ray &ray, float &t_enter, float &t_exit) const {
    
    // temp float var
    float swap;
    
    // x plane intersection
    float tx_min = (pmin.x - ray.o.x) / ray.d.x;
    float tx_max = (pmax.x - ray.o.x) / ray.d.x;
    if (tx_min > tx_max)
    {
        swap = tx_min;
        tx_min = tx_max;
        tx_max = swap;
    }

    // y plane intersection
    float ty_min = (pmin.y - ray.o.y) / ray.d.y;
    float ty_max = (pmax.y - ray.o.y) / ray.d.y;
    if (ty_min > ty_max)
    {
        swap = ty_min;
        ty_min = ty_max;
        ty_max = swap;
    }

    // If the ray misses the box in the XY projection, it misses completely
    if ((tx_min > ty_max) || (ty_min > tx_max)) return false;

    // Find the largest entering t and the smallest exiting t so far
    if (ty_min > tx_min) tx_min = ty_min;
    if (ty_max < tx_max) tx_max = ty_max;

    // Calculate intersections with the Z planes
    float tz_min = (pmin.z - ray.o.z) / ray.d.z;
    float tz_max = (pmax.z - ray.o.z) / ray.d.z;
    if (tz_min > tz_max)
    {
        swap = tz_min;
        tz_min = tz_max;
        tz_max = swap;
    }

    // If the ray misses the box in the XYZ projection, it misses completely
    if ((tx_min > tz_max) || (tz_min > tx_max)) return false;

    // Final largest entering t and smallest exiting t
    if (tz_min > tx_min) tx_min = tz_min;
    if (tz_max < tx_max) tx_max = tz_max;

    t_enter = tx_min;
    t_exit = tx_max;

    // Ensure the hit happens in front of the camera (t > 0)
    return (t_enter < kHugeValue && t_exit > kEpsilon);
}

void BBox::extend(const BBox& b) {
    pmin = min(pmin, b.pmin); 
    pmax = max(pmax, b.pmax);
}

// call on geometry's bbox
void BBox::extend(Geometry* g) {
    extend(g->getBBox());
}

// Checks if a 3D point is inside the box
bool BBox::contains(const Point3D& p) {
    return (p.x >= pmin.x && p.x <= pmax.x &&
            p.y >= pmin.y && p.y <= pmax.y &&
            p.z >= pmin.z && p.z <= pmax.z);
}

bool BBox::overlaps(const BBox& b) {
    return (pmax.x >= b.pmin.x && pmin.x <= b.pmax.x &&
            pmax.y >= b.pmin.y && pmin.y <= b.pmax.y &&
            pmax.z >= b.pmin.z && pmin.z <= b.pmax.z);
}

bool BBox::overlaps(Geometry* g) {
    return overlaps(g->getBBox());
}