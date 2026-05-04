---
layout: default
title: "Our Custom C++ Raytracer"
---

# CS 440 Project 2: Extended Ray Tracing Engine 

**Team Members:** Nehal Naeem Haji, Raahim Hashmi, Hania Kashif

---

## Scene Overview
[Write a short description of your scene containing 1 million primitives here. Explain how you came up with the idea, what 3D assets you used, and what techniques you used to build it.]

### High-Quality Render
<!-- ![High Quality Render](images/high_quality_render.png) -->
*Resolution: 1920x1080*

### Low-Quality Render
<!-- ![Low Quality Render](images/low_quality_render.png) -->
*Resolution: 480x360*

---

## Implementation Features
Here are the features implemented in our ray tracing engine:
* **Homework 5 Base:** Spheres, Planes, Triangles, Basic Cosine Shading.
* **Acceleration:** Bounding Volume Hierarchy (BVH) for optimized spatial partitioning.
* **Materials (BRDFs):** Diffuse, Glossy, and Specular materials.
* **Lighting:** Point lights and Directional lights.
* **Tracers:** Basic ray casting and secondary Shadow rays.
* **Sampling:** Jittered sampling for anti-aliasing.

---

## Acceleration Analysis
We implemented a Bounding Volume Hierarchy (BVH) to speed up rendering. Below is the performance comparison for our 1-million primitive scene.

| Metric | Without BVH (Brute Force) | With BVH |
| :--- | :--- | :--- |
| **Render Time** | [e.g., 45 minutes] | [e.g., 1.5 minutes] |

<!-- ![BVH Render](images/bvh_comparison.png) -->

---

## Build Details
The following `World::build` functions generate the images seen on this page:
* `buildFinalScene()` - Generates the High-Quality and Low-Quality showcase renders.
* `buildBVHTest()` - Generates the Acceleration comparison image.

---

## Team Contributions
* **Nehal Naeem Haji:** Implemented the BVH Acceleration structure and the Basic/Shadow Tracers.
* **Raahim Hashmi:** Implemented the BRDFs and Material hierarchy.
* **Hania Kashif:** Implemented the Light hierarchy and Anti-aliasing Samplers. Designed the final scene.

---

## References
* [Link to 3D models used, e.g., Sketchfab]
* [Link to any tutorials or papers referenced]