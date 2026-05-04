#include "../world/World.hpp"
#include "../cameras/Perspective.hpp"
#include "../geometry/Plane.hpp"
#include "../geometry/Triangle.hpp"
#include "../materials/Matte.hpp" 
#include "../materials/Reflective.hpp" 
#include "../materials/Phong.hpp"   
#include "../samplers/Simple.hpp"   
#include "../tracers/Shadow.hpp"
#include "../lights/PointLight.hpp"
#include "../acceleration/bvh.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/PLYReader.hpp"
#include <iostream>
#include <cstdlib>

void World::build(void) {
    // 1. FULL HD RESOLUTION & ASPECT RATIO
    vplane.set_hres(1920);
    vplane.set_vres(1080);
    
    // Stretch the ViewPlane boundaries to match a 16:9 aspect ratio using your new setter
    vplane.set_bounds(Point3D(-480, 270, 0), Point3D(480, -270, 0));
    bg_color = RGBColor(0.05, 0.05, 0.05); 

    // 2. 45-DEGREE CAMERA ANGLE
    // X=0, Y=1200, Z=1200 looking through Z=0 gives a perfect 45-degree downward angle.
    set_camera(new Perspective(Point3D(0, 1200, 1200)));
    sampler_ptr = new Simple(camera_ptr, &vplane); // NO ANTI-ALIASING for fast renders
    tracer_ptr = new Shadow(this); 

    // 3. LIGHTING
    PointLight* key_light = new PointLight(Point3D(800, 1500, 800), white, 1.0, 0.0, 0.0);
    add_light(key_light);
    PointLight* fill_light = new PointLight(Point3D(-800, 800, 500), RGBColor(0.5), 1.0, 0.0, 0.0);
    add_light(fill_light);

    // 4. MATERIAL LIBRARY (Now with 6 BRDF Types)
    Reflective* mat_bronze = new Reflective(0.25f, 0.50f, 0.50f, 50.0f, 0.40f, RGBColor(0.8, 0.6, 0.2));
    Reflective* mat_silver = new Reflective(0.25f, 0.50f, 0.60f, 60.0f, 0.50f, RGBColor(0.8, 0.8, 0.8));
    
    Matte* mat_blue = new Matte(); 
    mat_blue->set_cd(RGBColor(0.2, 0.4, 0.8));
    Matte* mat_yellow = new Matte(); 
    mat_yellow->set_cd(RGBColor(0.8, 0.8, 0.2)); // Added Yellow Clay
    
    Phong* mat_red = new Phong(0.25f, 0.60f, 0.50f, 32.0f, RGBColor(0.8, 0.1, 0.1));
    Phong* mat_green = new Phong(0.25f, 0.60f, 0.50f, 32.0f, RGBColor(0.1, 0.8, 0.2)); // Added Green Plastic
    
    // Expand the array to hold 6 materials
    Material* bunny_mats[6] = {mat_bronze, mat_silver, mat_blue, mat_yellow, mat_red, mat_green};

    // Chessboard Materials
    Matte* tile_light = new Matte(); tile_light->set_cd(RGBColor(0.9, 0.9, 0.9));
    Matte* tile_dark = new Matte();  tile_dark->set_cd(RGBColor(0.2, 0.2, 0.2));

    // 5. BUILD CHESSBOARD & BUNNIES
    std::cout << "Loading 64 models and building chessboard...\n";
    
    float tile_size = 200.0f;
    float start_x = -800.0f;
    
    // SHIFTED CLOSER TO CAMERA! (Was -1000)
    float start_z = -200.0f; 

    for (int x = 0; x < 8; x++) {
        for (int z = 0; z < 8; z++) {
            
            float x0 = start_x + (x * tile_size);
            float x1 = x0 + tile_size;
            float z0 = start_z + (z * tile_size);
            float z1 = z0 + tile_size;
            float y = -150.0f; 
            
            Material* tile_mat = ((x + z) % 2 == 0) ? tile_light : tile_dark;
            
            Point3D p0(x0, y, z0);
            Point3D p1(x1, y, z0);
            Point3D p2(x1, y, z1);
            Point3D p3(x0, y, z1);
            
            Triangle* t1 = new Triangle(p0, p1, p2);
            t1->set_material(tile_mat);
            add_geometry(t1);
            
            Triangle* t2 = new Triangle(p0, p2, p3);
            t2->set_material(tile_mat);
            add_geometry(t2);

            float bx = x0 + (tile_size / 2.0f);
            float bz = z0 + (tile_size / 2.0f);
            
            // INCREASED RANDOMIZER TO 6
            int rand_idx = rand() % 6; 
            PLYReader::load_ply("models/bunny.ply", this, bunny_mats[rand_idx], 800.0f, Vector3D(bx, y, bz));
        }
    }

    // 6. INFINITE BACKGROUND PLANE (To cover the void beyond the chessboard)
    Plane* floor = new Plane(Point3D(0, -151, 0), Vector3D(0, 1, 0)); // Placed 1 unit below the chessboard!
    Matte* floor_mat = new Matte();
    floor_mat->set_cd(RGBColor(0.1, 0.1, 0.1));
    floor->set_material(floor_mat);
    add_geometry(floor);

    // 7. BVH
    std::cout << "Building BVH for massive scene...\n";
    bvh_ptr = new BVHNode(geometry, 0, geometry.size());
    use_acceleration = true; 
}