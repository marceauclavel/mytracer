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
	./raytracer.exe test/input1.txt test/output1.ppm

verify: raytracer.exe
	./raytracer.exe test/input1.txt test/output1.ppm
	diff test/output1.ppm test/output1-REF.ppm
	./raytracer.exe test/input2.txt test/output2.ppm
	diff test/output2.ppm test/output2-REF.ppm
	./raytracer.exe test/input3.txt test/output3.ppm
	diff test/output3.ppm test/output3-REF.ppm
	./raytracer.exe test/input4.txt test/output4.ppm
	diff test/output4.ppm test/output4-REF.ppm

testseveral: raytracer.exe
	./raytracer.exe test/input1.txt test/output1.ppm
	./raytracer.exe test/input2.txt test/output2.ppm
	./raytracer.exe test/input3.txt test/output3.ppm

#debug: broken.exe
#	gdb broken.exe test/input.txt test/output.ppm

clean:
	rm *.o *.exe
