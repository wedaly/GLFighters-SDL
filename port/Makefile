CXX ?= g++
CXXFLAGS ?= -ansi -pedantic -Wall -Wextra -std=c++20
LDFLAGS ?=
LDLIBS ?= -lSDL2 -lSDL2_mixer -lGL
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
BIN ?= glfighters

.PHONY: fmt clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(BIN)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

fmt:
	find . -regex '.*\.\(cpp\|h\)' -exec clang-format -style="{ColumnLimit: 0}" -i {} \;

clean:
	rm -f $(OBJS) $(BIN)
