# avbd-demo3d

This is a simple 3D implementation of Augmented Vertex Block Descent (AVBD).

For more details on the technique (including a pre-built web demo) see the project page: https://graphics.cs.utah.edu/research/projects/avbd/

This repository is not intended to be a super optimized implementation, but an easy to understand demonstration of how to implement the technique.

Recent updates highlight the move to 3D:
- Default scene renders a grid of boxes in depth
- Camera can pitch and yaw using R/F and Z/C keys
- Physics and rendering now operate on simple 3D boxes

When launched, the demo loads a small 3D box grid to show the new 3D renderer. Use the controls below to move and rotate the camera around the scene.

## Building

Checkout the code (CMake will fetch SDL2 and ImGui automatically):

```git clone https://github.com/savant117/avbd-demo3d```

Make sure you have cmake and a c++ compiler installed.

To build:

### Native

```
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

To run, launch Release/avbd_demo3d.

### Controls

- **Move Camera:** `W`, `A`, `S`, `D` or hold the middle mouse button
- **Zoom:** `Q`/`E` or mouse wheel
- **Rotate:** `R`/`F` pitch, `Z`/`C` yaw

### Web

Install emscripten: https://emscripten.org/docs/getting_started/downloads.html

Install ninja

On Windows, ninja can be installed with:

```winget install Ninja-build.Ninja```

To build:

```
mkdir build-web
cd build-web
emcmake cmake ..
ninja
```

To run, open avbd_demo3d.html in your browser.
