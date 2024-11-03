#CC = g++
CC = em++
CFLAGS=-w -Wall -lSDL2 -lSDL2_image -lSDL2_mixer -lGL -lGLU --use-port=sdl2 --use-port=sdl2_image --use-port=sdl2_mixer -sLEGACY_GL_EMULATION --preload-file data
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
TARGET := glfighters.html

.PHONY: fmt clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

fmt:
	find . -regex '.*\.\(cpp\|h\)' -exec clang-format -style="{ColumnLimit: 0}" -i {} \;

clean:
	rm -f $(OBJS) $(TARGET)
