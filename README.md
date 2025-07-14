# avbd-demo2d

This is a simple 2D implementation of Augmented Vertex Block Decent (AVBD).

For more details on the technique (including a pre-built web demo) see the project page: https://graphics.cs.utah.edu/research/projects/avbd/

This repository is not intended to be a super optimized implementation, but an easy to understand demonstration of how to implement the technique.

## Building

Checkout the code and submodules using:

```git clone --recurse-submodules https://github.com/savant117/avbd-demo2d```

Make sure you have cmake and a c++ compiler installed.

To build:

### Native

```
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

To run, launch Release/avbd_demo2d.

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

To run, open avbd_demo2d.html in your browser.

## Blender Add-on

The `blender_addon` directory now contains a physics plugin for Blender. First
build the Python bindings using CMake:

```bash
mkdir build-bindings
cd build-bindings
cmake ../bindings
cmake --build . --config Release
```

Copy the resulting `avbd` module alongside the add-on and enable it from the
preferences. A new **AVBD** panel will appear in the 3D Viewport to run
simulations directly inside Blender.
