CC = g++
OBJ = raytracer.o Camera.o Scene.o Vector.o
CFLAGS = -c -Wall

all: raytracer.exe

.secondary:

raytracer.o: src/raytracer.cpp
	$(CC) $(CFLAGS) $< -o $@

%.o: src/structs/%.cpp
	$(CC) $(CFLAGS) $< -o $@

raytracer.exe: $(OBJ)
	$(CC) $(OBJ) -o $@

test: raytracer.exe
	./raytracer.exe test/input.txt test/output.txt

clean:
	rm *.o *.exe
