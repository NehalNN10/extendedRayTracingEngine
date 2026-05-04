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
This project is built using a standard C++ Makefile (on Windows). To compile and run the engine from your terminal, switch to the project directory and execute the following commands:

1.  **Compile the code:**
    ```bash
    mingw32-make
    ```
2.  **Run the executable:**
    ```bash
    mingw32-make run
    ```

Note that if you want to build and run a specific scene, add ```BUILD=build/<build_file>.cpp``` to the make and run command. For example:
```bash
mingw32-make BUILD=build/buildBunny.cpp
```
and 
```bash
mingw32-make run BUILD=build/buildBunny.cpp
```

If you are on a different platform or using a different build system, you would need to run a compile command that includes all the necessary source files and run the resulting executable. For example:
```bash
g++ -g raytracer.cpp world/*.cpp utilities/*.cpp geometry/*.cpp acceleration/*.cpp lights/*.cpp tracers/*.cpp cameras/*.cpp image/*.cpp samplers/*.cpp materials/BRDF/*.cpp materials/*.cpp build/testbench.cpp -o raytracer.exe
```

### Changing the Active Scene
The scenes are generated via the `World::build()` function. To change which scene renders, ensure the desired build file is included in your compilation sequence.
*   `buildBunny.cpp` - Generates the 32-piece "Neon Chess" showcase.
*   `testbench.cpp` - Used for testing individual features and materials during development (contains flags at the top to toggle features on/off).

---

## Testing the Acceleration Structure (BVH)
As per the project requirements, the Bounding Volume Hierarchy (BVH) can be toggled on or off.

To render using Brute Force (without acceleration), open `buildBunny.cpp` and modify the flag at the very bottom of the `World::build(void)` function:
```cpp
// Set to true to use BVH, false to use Brute Force
use_acceleration = false;