#pragma once

#include "../geometry/Geometry.hpp"
#include "../utilities/BBox.hpp"
#include <vector>

class BVHNode : public Geometry {
protected:
    Geometry* left;
    Geometry* right;
    BBox box; 

public:
    // take objects and build BVH tree
    BVHNode(std::vector<Geometry*>& objects, size_t start, size_t end);
    
    virtual ~BVHNode();

    // override these functions
    virtual bool hit(const Ray& ray, float& t, ShadeInfo& sinfo) const override;
    virtual BBox getBBox() const override;
    virtual std::string to_string() const override;
};