#include "Image.hpp"
#include "../utilities/RGBColor.hpp"
#include "../world/ViewPlane.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <algorithm> 

Image::Image(int hres, int vres): hres(hres), vres(vres) {
    colors = new RGBColor*[vres];
    for (int i = 0; i < vres; i++) {
        colors[i] = new RGBColor[hres];
        for (int j = 0; j < hres; j++) {
            colors[i][j] = RGBColor(0, 0, 0);
        }
    }
}

Image::Image(const ViewPlane &vp): hres(vp.hres), vres(vp.vres) {
    colors = new RGBColor*[vres];
    for (int i = 0; i < vres; i++) {
        colors[i] = new RGBColor[hres];
        for (int j = 0; j < hres; j++) {
            colors[i][j] = RGBColor(0, 0, 0);
        }
    }
}

Image::~Image() {
    for (int i = 0; i < vres; i++) {
        delete[] colors[i];
    }
    delete[] colors;
}

void Image::set_pixel(int x, int y, const RGBColor& color) {
    if (x >= 0 && x < hres && y >= 0 && y < vres) {
        colors[y][x] = color;
    }
}

void Image::write_png(std::string path) const {
    unsigned char* data = new unsigned char[hres * vres * 3]; 
    
    int index = 0;
    for (int y = 0; y < vres; y++) {
        for (int x = 0; x < hres; x++) {
            data[index++] = static_cast<unsigned char>(std::max(0.0f, std::min(1.0f, colors[y][x].r)) * 255.0f);
            data[index++] = static_cast<unsigned char>(std::max(0.0f, std::min(1.0f, colors[y][x].g)) * 255.0f);
            data[index++] = static_cast<unsigned char>(std::max(0.0f, std::min(1.0f, colors[y][x].b)) * 255.0f);
        }
    }
    
    stbi_write_png(path.c_str(), hres, vres, 3, data, hres * 3);
    delete[] data;
}