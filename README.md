# GLFighters-SDL

Port of GLFighters to SDL

## Dependencies

## Linux

For building on Linux, you will need:
* GCC C++ compiler
* [SDL2](https://www.libsdl.org/) and [SDL_Mixer](https://github.com/libsdl-org/SDL_mixer)
* OpenGL

On Fedora, you can install these with:
```
dnf install gcc-c++ SDL2-devel SDL2_mixer-devel mesa-libGL-devel
```

## WASM

To build for WebAssembly (WASM), you need emscripten.

Follow the instructions at [emscripten.org](https://emscripten.org/docs/getting_started/downloads.html) to install `emmake` and `em++`.

## Building and running

Build both Linux and WASM using `make` from the root of the repository:
```
make
```

To run the Linux binary:
```
$(cd ./port; ./glfighters)
```

To run in a browser:
```
make server
```
Then use a browser to open the link printed to the console
