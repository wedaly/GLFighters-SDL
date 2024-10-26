all: glfighters

glfighters:
	$(MAKE) -C port
	cp port/main.out glfighters
