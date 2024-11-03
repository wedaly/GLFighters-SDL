# GLFighters-SDL

Port of GLFighters to SDL

## Dependencies

* C++ compiler. On Fedora, `dnf install gcc-c++`
* [SDL2](https://www.libsdl.org/) and [SDL_Image](https://github.com/libsdl-org/SDL_image). On Fedora, `dnf install SDL2-devel SDL2_image-devel`
* OpenGL. On Fedora, `dnf install mesa-libGL-devel mesa-libGLU-devel`

## Building and running

Build with make:
```
make -C port
./port/glfighters
```

