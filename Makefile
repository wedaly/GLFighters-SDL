.PHONY: linux wasm server clean

WASMOBJDIR := wasmobjs
WASMVARS := CXXFLAGS="-sUSE_SDL=2 -sUSE_SDL_MIXER=2 -I../vendor/gl4es-v1.1.6/include" \
	OBJDIR=$(WASMOBJDIR) \
	LDLIBS="../vendor/gl4es-v1.1.6/lib/libGL.a" \
	LDFLAGS="--use-port=sdl2 --use-port=sdl2_mixer -sFULL_ES2 --preload-file=./data --shell-file ../site/emscripten-shell.html" \
	BIN="../site/glfighters.html"

all: linux wasm

linux:
	$(MAKE) -C port

wasm:
	emmake $(MAKE) -C port $(WASMVARS)

server: wasm
	emrun ./site/

clean:
	$(MAKE) -C port clean; \
	emmake $(MAKE) -C port clean $(WASMVARS); \
	rm -rf ./site/glfighters.{data,js,wasm}
