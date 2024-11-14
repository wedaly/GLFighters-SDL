# GLFighters-SDL

GLFighters was originally written by David Rosen for Classic Mac OS. This repo contains a port of the game to SDL, which can be built for both Linux and WebAssembly.

You can play it online at [https://devnonsense.com/GLFighters-SDL/](https://devnonsense.com/GLFighters-SDL/). The site is built from this repository.

## Dependencies

### Linux

For building on Linux, you will need:
* GCC C++ compiler
* [SDL2](https://www.libsdl.org/) and [SDL_Mixer](https://github.com/libsdl-org/SDL_mixer)
* OpenGL

On Fedora, you can install these with:
```
dnf install gcc-c++ SDL2-devel SDL2_mixer-devel mesa-libGL-devel
```

### WASM

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

## Changes from the original

There are a few changes from the original game to make it more accessible to modern gamers.
* The default map, player skins, and starting position are chosen so they stand out
  against the background and are easier to see.
* The default weapon for player 1 is the lightsaber, because the animation/sounds are awesome
  and because it shows that GLFighters has multiple types of weapons.
* There is help text printed showing the most important keys (movement, attack, and toggling the AI)
  so casual players can get started.
* The ability to save and open map files is not yet implemented.

The original used the numpad for player 2 controls and map editor commands, but none of my keyboards
have a numpad, so I haven't tested that these work correctly.

## Contributing

Pull requests are welcome for bugfixes and porting to other platforms.

Changes to the game itself will NOT be accepted, to preserve the character of the original game.
Of course, you're welcome to make any changes you want on a fork.
