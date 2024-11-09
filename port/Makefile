CXX ?= g++
CXXFLAGS ?= -ansi -pedantic -Wall -Wextra -std=c++20
LDFLAGS ?=
LDLIBS ?= -lSDL2 -lSDL2_mixer -lGL
OBJDIR ?= ./objs
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=$(OBJDIR)/%.o)
BIN ?= glfighters

.PHONY: fmt clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(BIN)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

fmt:
	find . -regex '.*\.\(cpp\|h\)' -exec clang-format -style="{ColumnLimit: 0}" -i {} \;

clean:
	rm -rf $(OBJDIR) $(BIN)
