#include "../world/World.hpp"
#include "../cameras/Perspective.hpp"
#include "../geometry/Sphere.hpp"
#include "../materials/Matte.hpp" // Using your partner's new Matte material
#include "../samplers/Simple.hpp"
#include "../tracers/Basic.hpp"
#include "../lights/PointLight.hpp"
#include "../acceleration/bvh.hpp"
#include "../utilities/Constants.hpp"
#include <cstdlib>

void World::build(void) {
    // 1. Viewplane & Background
    vplane.set_hres(400);
    vplane.set_vres(400);
    bg_color = RGBColor(0.1, 0.1, 0.1); // Dark gray background

    // 2. Camera, Sampler, and Tracer
    set_camera(new Perspective(Point3D(0, 0, 500)));
    sampler_ptr = new Simple(camera_ptr, &vplane);
    tracer_ptr = new Basic(this); // Use Basic tracer for pure geometry speed testing

    // 3. Add a Light
    PointLight* light = new PointLight(Point3D(0, 500, 500), white, 1.0, 0.0, 0.0);
    add_light(light);

    // 4. Generate 1,000,000 Spheres (100 x 100 x 100 grid)
    Matte* matte_mat = new Matte();
    matte_mat->set_cd(RGBColor(0.2, 0.5, 0.8)); // Blue-ish

    int gridSize = 100;
    float spacing = 3.0f;
    float offset = (gridSize * spacing) / 2.0f;

    for (int x = 0; x < gridSize; x++) {
        for (int y = 0; y < gridSize; y++) {
            for (int z = 0; z < gridSize; z++) {
                Point3D center(
                    (x * spacing) - offset, 
                    (y * spacing) - offset, 
                    (z * spacing) - offset
                );
                Sphere* s = new Sphere(center, 1.0f);
                s->set_material(matte_mat);
                add_geometry(s);
            }
        }
    }

    // 5. Build the BVH Tree and Toggle it!
    bvh_ptr = new BVHNode(geometry, 0, geometry.size());
    
    // CHANGE THIS TO TRUE/FALSE TO TEST SPEED
    use_acceleration = true; 
}