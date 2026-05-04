#include "../world/World.hpp"
#include "../cameras/Perspective.hpp"
#include "../geometry/Plane.hpp"
#include "../materials/Matte.hpp" 
#include "../materials/Reflective.hpp" 
#include "../materials/Phong.hpp" 
#include "../samplers/Jittered.hpp" 
#include "../tracers/Shadow.hpp"
#include "../lights/PointLight.hpp"
#include "../acceleration/bvh.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/PLYReader.hpp"
#include <iostream>
#include <cstdlib>

void World::build(void) {
    // 1. FULL HD WIDESCREEN & ASPECT RATIO FIX
    vplane.set_hres(1920);
    vplane.set_vres(1080);
    
    // Stretch the physical ViewPlane boundaries to match 16:9
    vplane.top_left = Point3D(-480, 270, 0); 
    vplane.bottom_right = Point3D(480, -270, 0);
    bg_color = RGBColor(0.1, 0.1, 0.15);

    // 2. CAMERA SETUP (No view distance, just move Z backward to zoom out!)
    Perspective* cam = new Perspective(Point3D(0, 400, 2200));
    set_camera(cam);
    
    // 3. ANTI-ALIASING SAMPLER 
    // Passes the camera, the viewplane, and 16 samples for buttery smooth edges
    sampler_ptr = new Jittered(camera_ptr, &vplane, 16); 
    
    tracer_ptr = new Shadow(this); 

    // 4. LIGHTING
    PointLight* key_light = new PointLight(Point3D(800, 1000, 800), white, 1.0, 0.0, 0.0);
    add_light(key_light);
    PointLight* fill_light = new PointLight(Point3D(-800, 500, 500), RGBColor(0.4), 1.0, 0.0, 0.0);
    add_light(fill_light);

    // 5. MATERIAL LIBRARY 
    Reflective* mat_bronze = new Reflective(0.25f, 0.50f, 0.50f, 50.0f, 0.40f, RGBColor(0.8, 0.6, 0.2));
    Reflective* mat_silver = new Reflective(0.25f, 0.50f, 0.60f, 60.0f, 0.50f, RGBColor(0.8, 0.8, 0.8));
    
    Matte* mat_blue = new Matte();
    mat_blue->set_cd(RGBColor(0.2, 0.4, 0.8));
    
    // Using the 5-parameter Phong constructor for Red Plastic
    Phong* mat_red = new Phong(0.25f, 0.60f, 0.50f, 32.0f, RGBColor(0.8, 0.1, 0.1));

    Material* material_library[4] = {mat_bronze, mat_silver, mat_blue, mat_red};

    // 6. THE GRID
    std::cout << "Loading 64 models. This will take a moment...\n";
    for (int x = 0; x < 8; x++) {
        for (int z = 0; z < 8; z++) {
            float x_pos = -700.0f + (x * 200.0f);
            float z_pos = -500.0f + (z * 200.0f);
            
            // Randomly select one of the 4 materials
            int random_index = rand() % 4;
            Material* chosen_mat = material_library[random_index];

            PLYReader::load_ply("models/bunny.ply", this, chosen_mat, 800.0f, Vector3D(x_pos, -150, z_pos));
        }
    }

    // 7. FLOOR PLANE
    Plane* floor = new Plane(Point3D(0, -150, 0), Vector3D(0, 1, 0));
    Matte* floor_mat = new Matte();
    floor_mat->set_cd(RGBColor(0.8, 0.8, 0.8));
    floor->set_material(floor_mat);
    add_geometry(floor);

    // 8. BVH
    std::cout << "Building BVH for massive scene...\n";
    bvh_ptr = new BVHNode(geometry, 0, geometry.size());
    use_acceleration = true; 
}