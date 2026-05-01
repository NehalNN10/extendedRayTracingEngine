#include "Triangle.hpp"
#include "Geometry.hpp"
#include "../utilities/BBox.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"
#include <string>
#include <algorithm> // for min and max

Triangle::Triangle() : v0(Point3D(0.0, 0.0, 0.0)), v1(Point3D(0.0, 0.0, 0.0)), v2(Point3D(0.0, 0.0, 0.0)) {}

Triangle::Triangle(const Point3D &a, const Point3D &b, const Point3D &c) : v0(a), v1(b), v2(c) {}

Triangle::Triangle(const Triangle &object) : Geometry(object), v0(object.v0), v1(object.v1), v2(object.v2) {}

Triangle& Triangle::operator=(const Triangle &rhs) {
    if (this == &rhs) {
        return *this;
    }
    Geometry::operator=(rhs);
    v0 = rhs.v0;
    v1 = rhs.v1;
    v2 = rhs.v2;
    return *this;
}

std::string Triangle::to_string() const {
    return "Triangle(" + v0.to_string() + ", " + v1.to_string() + ", " + v2.to_string() + ")";
}

BBox Triangle::getBBox() const {
    // min and max corners
    Point3D pmin = min(v0, min(v1, v2));
    Point3D pmax = max(v0, max(v1, v2));
    
    // add small padding JIC the triangle lies flat on one axis
    return BBox(Point3D(pmin.x - kEpsilon, pmin.y - kEpsilon, pmin.z - kEpsilon),
                Point3D(pmax.x + kEpsilon, pmax.y + kEpsilon, pmax.z + kEpsilon));
}

bool Triangle::hit(const Ray &ray, float &t, ShadeInfo &s) const {
    // find normal of triangle's plane by calculating normal to 2 edges
    Vector3D e1 = v1 - v0;
    Vector3D e2 = v2 - v0;
    Vector3D normal = e1 ^ e2; 
    normal.normalize();

    // now we perform ray-plane intersection (copied a lot from Plane.cpp)
    float denominator = ray.d * normal;

    if (std::abs(denominator) < kEpsilon) {
        return false;
    }

    Vector3D temp = v0 - ray.o;
    float hit_t = (temp * normal) / denominator;

    if (hit_t <= kEpsilon) {
        return false;
    }

    Point3D p = ray.o + ray.d * hit_t;

    // We check each edge. If the cross product points in the opposite direction of the normal,
    // the point is outside the triangle.
    
    // Test Edge 0 (v0 to v1)
    Vector3D edge0 = v1 - v0;
    Vector3D vp0 = p - v0;
    if (normal * (edge0 ^ vp0) < 0.0) {
        return false;
    }

    // Test Edge 1 (v1 to v2)
    Vector3D edge1 = v2 - v1;
    Vector3D vp1 = p - v1;
    if (normal * (edge1 ^ vp1) < 0.0) {
        return false;
    }

    // Test Edge 2 (v2 to v0)
    Vector3D edge2 = v0 - v2;
    Vector3D vp2 = p - v2;
    if (normal * (edge2 ^ vp2) < 0.0) {
        return false;
    }

    // point is inside triangle
    t = hit_t;
    s.t = t;
    s.hit_point = p;
    s.normal = normal;
    s.material_ptr = material_ptr;
    return true;
}