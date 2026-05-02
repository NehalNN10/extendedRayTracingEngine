#include "BVHNode.hpp"
#include <algorithm> // For std::sort
#include <cstdlib>   // For rand()

// for sorting objects by bounding box
bool compare_x(Geometry* a, Geometry* b) {
    return a->getBBox().pmin.x < b->getBBox().pmin.x;
}

bool compare_y(Geometry* a, Geometry* b) {
    return a->getBBox().pmin.y < b->getBBox().pmin.y;
}

bool compare_z(Geometry* a, Geometry* b) {
    return a->getBBox().pmin.z < b->getBBox().pmin.z;
}

BVHNode::~BVHNode() {}

BBox BVHNode::getBBox() const {
    return box;
}

std::string BVHNode::to_string() const {
    return "BVHNode";
}

BVHNode::BVHNode(std::vector<Geometry*>& objects, size_t start, size_t end) {
    // random axis for sorting
    // x = 0, y = 1, z = 2
    int axis = rand() % 3;

    size_t object_span = end - start;

    // recursive splitting
    // base cases: 1 or 2 objects
    if (object_span == 1) {
        left = right = objects[start];
    } 
    else if (object_span == 2) {
        // Manually check if they are in the right order based on the axis
        bool is_sorted = false;
        if (axis == 0) {
            is_sorted = compare_x(objects[start], objects[start + 1]);
        } else if (axis == 1) {
            is_sorted = compare_y(objects[start], objects[start + 1]);
        } else {
            is_sorted = compare_z(objects[start], objects[start + 1]);
        }

        // Assign left and right based on the check above
        if (is_sorted) {
            left = objects[start];
            right = objects[start + 1];
        } else {
            left = objects[start + 1];
            right = objects[start];
        }
    } 
    else {
        // Recursive Step: We have more than 2 objects.
        // Sort the objects using the correct helper function
        if (axis == 0) {
            std::sort(objects.begin() + start, objects.begin() + end, compare_x);
        } else if (axis == 1) {
            std::sort(objects.begin() + start, objects.begin() + end, compare_y);
        } else {
            std::sort(objects.begin() + start, objects.begin() + end, compare_z);
        }
        
        // Find the middle and split!
        size_t mid = start + object_span / 2;
        left = new BVHNode(objects, start, mid);
        right = new BVHNode(objects, mid, end);
    }

    // Combine the bounding boxes of the left and right children
    box = left->getBBox();
    box.extend(right->getBBox()); 
}

bool BVHNode::hit(const Ray& ray, float& t, ShadeInfo& sinfo) const {
    float t_enter, t_exit;
    
    // 1. Did the ray even hit this giant bounding box?
    if (!box.hit(ray, t_enter, t_exit)) {
        return false; // Missed completely! Skip everything inside.
    }

    // 2. It hit the box! Now check the left and right children.
    float t_left, t_right;
    ShadeInfo sinfo_left = sinfo;   
    ShadeInfo sinfo_right = sinfo;  

    bool hit_left = left->hit(ray, t_left, sinfo_left);
    bool hit_right = right->hit(ray, t_right, sinfo_right);

    // 3. Find out which hit was closer to the camera
    if (hit_left && hit_right) {
        if (t_left < t_right) {
            t = t_left;
            sinfo = sinfo_left;
        } else {
            t = t_right;
            sinfo = sinfo_right;
        }
        return true;
    } else if (hit_left) {
        t = t_left;
        sinfo = sinfo_left;
        return true;
    } else if (hit_right) {
        t = t_right;
        sinfo = sinfo_right;
        return true;
    }

    return false; // Hit the bounding box, but missed the actual geometry inside
}