CC = g++
OBJ = raytracer.o Camera.o Scene.o Vector.o Color.o Sphere.o Material.o Ray.o
CFLAGS = -c -Wall -Wextra

all: raytracer.exe

.secondary:

raytracer.o: src/raytracer.cpp
	$(CC) $(CFLAGS) $< -o $@

%.o: src/structs/%.cpp
	$(CC) $(CFLAGS) $< -o $@

raytracer.exe: $(OBJ)
	$(CC) $(OBJ) -o $@

broken.exe: $(OBJ)
	$(CC) -g $(OBJ) -o $@

test: raytracer.exe
	./raytracer.exe test/input.txt test/output.ppm

debug: broken.exe
	gdb broken.exe test/input.txt test/output.ppm

clean:
	rm *.o *.exe
