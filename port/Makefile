#CC = g++
CC = em++
CFLAGS=-w -Wall -O3 -sFULL_ES2 -lSDL2 -lSDL2_image -lSDL2_mixer --use-port=sdl2 --use-port=sdl2_image --use-preload-plugins --use-port=sdl2_mixer --preload-file data/animations --preload-file data/images --preload-file data/maps --preload-file data/sounds --preload-file data/models -I/home/will/repos/gl4es/include --profiling
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
TARGET := glfighters.html

.PHONY: fmt clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) /home/will/repos/gl4es/lib/libGL.a -o $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

fmt:
	find . -regex '.*\.\(cpp\|h\)' -exec clang-format -style="{ColumnLimit: 0}" -i {} \;

clean:
	rm -f $(OBJS) $(TARGET)
