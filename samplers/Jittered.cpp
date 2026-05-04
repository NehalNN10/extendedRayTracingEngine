#include "Jittered.hpp"
#include "Sampler.hpp"
#include "../cameras/Camera.hpp"
#include "../world/ViewPlane.hpp"
#include "../utilities/Ray.hpp"

Jittered::Jittered(Camera *c_ptr, ViewPlane *v_ptr, int n) : Sampler(c_ptr, v_ptr), n(n) 
{
    pixel_size_x = (viewplane_ptr->bottom_right.x - viewplane_ptr->top_left.x) / viewplane_ptr->hres;
    pixel_size_y = (viewplane_ptr->top_left.y - viewplane_ptr->bottom_right.y) / viewplane_ptr->vres;
    sub_pixel_size_x = pixel_size_x / n;
    sub_pixel_size_y = pixel_size_y / n;
}

Jittered::Jittered(const Jittered &camera)
{
    camera_ptr = camera.camera_ptr;
    viewplane_ptr = camera.viewplane_ptr;
    pixel_size_x = camera.pixel_size_x;
    pixel_size_y = camera.pixel_size_y;
    n = camera.n;
    sub_pixel_size_x = camera.sub_pixel_size_x;
    sub_pixel_size_y = camera.sub_pixel_size_y;
}

Jittered& Jittered::operator=(const Jittered &other)
{
    if (this == &other)
    {
        return *this;
    }
    camera_ptr = other.camera_ptr;
    viewplane_ptr = other.viewplane_ptr;
    pixel_size_x = other.pixel_size_x;
    pixel_size_y = other.pixel_size_y;
    n = other.n;
    sub_pixel_size_x = other.sub_pixel_size_x;
    sub_pixel_size_y = other.sub_pixel_size_y;
    return *this;
}

std::vector<Ray> Jittered::get_rays(int px, int py) const 
{
    std::vector<Ray> rays;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            float pixel_offset_x = sub_pixel_size_x * (i + static_cast<float>(rand()) / RAND_MAX);
            float pixel_offset_y = sub_pixel_size_y * (j + static_cast<float>(rand()) / RAND_MAX);
            Point3D pt;
            pt.x = viewplane_ptr->top_left.x + pixel_size_x * px + pixel_offset_x;
            pt.y = viewplane_ptr->top_left.y - pixel_size_y * py - pixel_offset_y;
            pt.z = viewplane_ptr->top_left.z;
            Point3D origin = camera_ptr->get_origin(pt);
            Vector3D dir = camera_ptr->get_direction(pt);
            Ray ray(origin, dir);
            ray.w = 1.0f / (n * n); // weight of each ray is 1/n^2
            rays.push_back(ray);
        }
    }

    return rays;
}