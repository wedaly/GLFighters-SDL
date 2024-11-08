CC = g++
CFLAGS=-w -Wall
LDFLAGS=
LDLIBS=-lSDL2 -lSDL2_mixer -lGL
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
TARGET := glfighters

.PHONY: fmt clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

fmt:
	find . -regex '.*\.\(cpp\|h\)' -exec clang-format -style="{ColumnLimit: 0}" -i {} \;

clean:
	rm -f $(OBJS) $(TARGET)
