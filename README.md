# CS 440 Project 2: Extended Ray Tracing Engine

**Team Members:** Nehal Naeem Haji, Raahim Hashmi, Hania Kashif

🌐 **[View our Live Project Showcase & Renders!](https://nehalnn10.github.io/extendedRayTracingEngine/)**

---

## Project Overview
This repository contains our custom-built C++ Ray Tracing Engine. We extended our base engine to support complex materials, advanced lighting, shadow casting, anti-aliasing, and spatial partitioning.

Our final showcase scene, **"Neon Chess,"** renders over 2.2 million primitives by utilizing a Bounding Volume Hierarchy (BVH) to cut trace times down from an estimated 48+ hours to just a few minutes.

Please visit our **[Project Website](https://nehalnn10.github.io/extendedRayTracingEngine/)** to view our high-resolution renders, performance analysis, and detailed feature breakdowns.

---

## How to Build and Run
This project is built using a standard C++ Makefile. To compile and run the engine from your terminal:

1.  **Compile the code:**
    ```bash
    make
    ```
2.  **Run the executable:**
    ```bash
    ./raytracer
    ```
    *(Note: The exact name of the executable may vary depending on your Makefile output).*

### Changing the Active Scene
The scenes are generated via the `World::build()` function. To change which scene renders, ensure the desired build file is included in your compilation sequence.
*   `buildBunny.cpp` - Generates the 32-piece "Neon Chess" showcase.
*   `buildBVHTest.cpp` - Generates the Acceleration comparison scene.

---

## Testing the Acceleration Structure (BVH)
As per the project requirements, the Bounding Volume Hierarchy (BVH) can be toggled on or off.

To render using Brute Force (without acceleration), open `buildBunny.cpp` and modify the flag at the very bottom of the `World::build(void)` function:
```cpp
// Set to true to use BVH, false to use Brute Force
use_acceleration = false;