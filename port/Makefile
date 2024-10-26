CC = g++
CFLAGS=-w -Wall -lSDL2 -lGL
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
TARGET := glfighters

.PHONY: fmt clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

fmt:
	find . -regex '.*\.\(cpp\|h\)' -exec clang-format -i {} \;

clean:
	rm -f $(OBJS) $(TARGET)
