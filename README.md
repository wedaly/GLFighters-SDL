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

## Linux

Build with make:
```
cd ./port
make
```

Then run it:
```
./port/glfighters
```

## WASM

Compile using emscripten:
```
cd ./port

CXXFLAGS="-I./wasm/gl4es-v1.1.6/include" \
LDLIBS="./wasm/gl4es-v1.1.6/lib/libGL.a" \
LDFLAGS="--use-port=sdl2 --use-port=sdl2_mixer -sFULL_ES2 --preload-file=./data --shell-file ./wasm/emscripten-shell.html" \
BIN=glfighters.html \
emmake make
```

To run it, first start a webserver:
```
python -m http.server
```

Then load this page in a browser: [http://localhost:8000/glfighters.html](http://localhost:8000/glfighters.html)
