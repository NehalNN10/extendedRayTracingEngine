#include "Plane.hpp"
#include "Geometry.hpp"
#include "../utilities/BBox.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Constants.hpp"
#include <string>
#include <cmath>

Plane::Plane(): a(Point3D(0, 0, 0)), n(Vector3D(0, 1, 0)) {}

Plane::Plane(const Point3D &pt, const Vector3D &normal): a(pt), n(normal) {
    n.normalize();
}

// initialize base class
Plane::Plane(const Plane &object) : Geometry(object), a(object.a), n(object.n) {}

Plane& Plane::operator=(const Plane &rhs) {
    if (this == &rhs) {
        return *this;
    }
    // copy base class
    Geometry::operator=(rhs);
    a = rhs.a;
    n = rhs.n;
    return *this;
}

std::string Plane::to_string() const {
    return "Plane(point: " + a.to_string() + ", normal: " + n.to_string() + ")";
}

// it's a plane, so we get this infinitely huge bounding box
BBox Plane::getBBox() const {
    return BBox(Point3D(-kHugeValue, -kHugeValue, -kHugeValue), 
                Point3D(kHugeValue, kHugeValue, kHugeValue));
}

// ray-plane intersection
bool Plane::hit(const Ray &ray, float &t, ShadeInfo &s) const {
    // denominator calculation (D.N)
    float denominator = ray.d * n; 
    
    // if denominator is very small, ray misses plane
    if (std::abs(denominator) < kEpsilon) {
        return false;
    }
    
    // calculate distance t
    Vector3D temp = a - ray.o; // numerator
    float hit_t = (temp * n) / denominator;
    
    // if t is infront of camera (i.e. positive and greater than small constant) then there is intersection
    // using small constant works better for some reason
    if (hit_t > kEpsilon) {
        t = hit_t;
        s.t = t;
        s.hit_point = ray.o + ray.d * t;
        s.normal = n; // normal of hitpoint is the same as normal of plane
        s.material_ptr = material_ptr;
        return true;
    }
    
    return false;
}