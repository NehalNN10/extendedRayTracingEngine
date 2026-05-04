#include "Simple.hpp"
#include "Sampler.hpp"
#include "../cameras/Camera.hpp"
#include "../world/ViewPlane.hpp"
#include "../utilities/Ray.hpp"

Simple::Simple(Camera *c_ptr, ViewPlane *v_ptr) : Sampler(c_ptr, v_ptr) 
{
    float width = viewplane_ptr->bottom_right.x - viewplane_ptr->top_left.x;
    float height = viewplane_ptr->top_left.y - viewplane_ptr->bottom_right.y;
    pixel_size_x = width / viewplane_ptr->hres;
    pixel_size_y = height / viewplane_ptr->vres;
}

Simple::Simple(const Simple &camera)
{
    camera_ptr = camera.camera_ptr;
    viewplane_ptr = camera.viewplane_ptr;
    pixel_size_x = camera.pixel_size_x;
    pixel_size_y = camera.pixel_size_y;
}

Simple& Simple::operator=(const Simple &other)
{
    if (this == &other)
    {
        return *this;
    }
    camera_ptr = other.camera_ptr;
    viewplane_ptr = other.viewplane_ptr;
    pixel_size_x = other.pixel_size_x;
    pixel_size_y = other.pixel_size_y;
    return *this;
}

std::vector<Ray> Simple::get_rays(int px, int py) const {
    std::vector<Ray> rays;

    Point3D pt;
    // use 0.5f for center of pixel
    pt.x = viewplane_ptr->top_left.x + pixel_size_x * (px + 0.5f);
    pt.y = viewplane_ptr->top_left.y - pixel_size_y * (py + 0.5f); 
    pt.z = viewplane_ptr->top_left.z;

    Point3D origin = camera_ptr->get_origin(pt);
    Vector3D dir = camera_ptr->get_direction(pt);
    Ray ray(origin, dir);

    rays.push_back(ray);
    return rays;
}