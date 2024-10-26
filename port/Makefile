CC = g++
CFLAGS=-w -lSDL2

.PHONY: fmt

all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))

%.out: %.cpp Makefile
	$(CC) $(CFLAGS) $< -o $@ -lm

fmt:
	find . -regex '.*\.\(cpp\|h\)' -exec clang-format -i {} \;

clean:
	rm *.out
