CC = g++
OBJ = raytracer.o
HEADER = src/header.h
CFLAGS = -c -Wall

all: raytracer.exe

raytracer.exe: $(OBJ)
	$(CC) $(OBJ) -o $@

raytracer.o: src/raytracer.cpp $(HEADER)
	$(CC) $(CFLAGS) $< -o $@
