#include "../world/World.hpp"

#include "../acceleration/bvh.hpp"
#include "../cameras/Perspective.hpp"
#include "../geometry/Plane.hpp"
#include "../lights/SpotLight.hpp"
#include "../materials/Matte.hpp"
#include "../materials/Phong.hpp"
#include "../materials/Reflective.hpp"
#include "../samplers/Simple.hpp"
#include "../samplers/Jittered.hpp"
#include "../tracers/Shadow.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/PLYReader.hpp"

void World::build(void) {
    vplane.set_hres(1920);
    vplane.set_vres(1080);
    vplane.top_left = Point3D(-520, 300, 0);
    vplane.bottom_right = Point3D(520, -260, 0);

    bg_color = RGBColor(0.04, 0.05, 0.07);

    set_camera(new Perspective(Point3D(0, 520, 2500)));
    sampler_ptr = new Jittered(camera_ptr, &vplane, 1);
    tracer_ptr = new Shadow(this);

    auto* table_material = new Matte();
    table_material->set_cd(RGBColor(0.35, 0.25, 0.14));

    auto* dragon_material = new Reflective(0.25f, 0.75f, 0.5f, 32.0f, 0.5f, RGBColor(0.16, 0.60, 0.22));
    auto* teapot_material = new Phong(0.20f, 0.60f, 0.35f, 40.0f, RGBColor(0.80, 0.48, 0.18));
    auto* bunny_material = new Matte(RGBColor(0.88, 0.86, 0.82));

    PLYReader::load_ply("models/umbrella_table.ply", this, table_material, 420.0f, Vector3D(0, -210, 0));
    PLYReader::load_ply("models/dragon_vrip.ply", this, dragon_material, 62.0f, Vector3D(-320, -122, -20));
    PLYReader::load_ply("models/utah_teapot.ply", this, teapot_material, 72.0f, Vector3D(320, -118, -10));
    PLYReader::load_ply("models/bunny.ply", this, bunny_material, 58.0f, Vector3D(0, -132, -150));

    auto* overhead_spot = new SpotLight(
        Point3D(0, 1450, 0),
        white,
        1.0,
        0.0,
        0.0,
        Vector3D(0, -1, 0),
        72.0,
        3.0);
    overhead_spot->set_intensity(5.0f);
    add_light(overhead_spot);

    auto* floor = new Plane(Point3D(0, -360, 0), Vector3D(0, 1, 0));
    auto* floor_material = new Matte();
    floor_material->set_cd(RGBColor(0.12, 0.12, 0.14));
    floor->set_material(floor_material);
    add_geometry(floor);

    ambient_color = RGBColor(0.22, 0.22, 0.24);
    ambient_intensity = 0.18f;
    max_depth = 3;

    bvh_ptr = new BVHNode(geometry, 0, geometry.size());
    use_acceleration = true;
}