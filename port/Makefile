CC = g++
CFLAGS=-w -Wall -lSDL2 -lGL

.PHONY: fmt

all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))

%.out: %.cpp Makefile
	$(CC) $(CFLAGS) $< -o $@ -lm

fmt:
	find . -regex '.*\.\(cpp\|h\)' -exec clang-format -i {} \;

clean:
	rm *.out
