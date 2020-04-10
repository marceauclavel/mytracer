#include <fstream>
#include <iostream>

#include "structs/Camera.h"
#include "structs/Color.h"
#include "structs/Intersection.h"
#include "structs/Light.h"
#include "structs/Material.h"
#include "structs/Pixel.h"
#include "structs/Point.h"
#include "structs/Ray.h"
#include "structs/Scene.h"
#include "structs/Sphere.h"
#include "structs/Vector.h"

bool init(Scene scene, Camera camera, char* ifn){
	//declaring variables
	int nMaterials, nSpheres, nLights, nPixels, xOpening, yOpening, xRes, yRes, depth;
	Point pos;
	Vector dir;

	std::ifstream file(ifn);
	if (!file) return false;
	file >> nMaterials >> nSpheres >> nLights;
	file >> pos >> dir >> xOpening >> yOpening >> xRes >> yRes >> depth;

	std::cout << nMaterials << nSpheres << nLights << std::endl;
	std::cout << pos.x << dir.y << xOpening << yOpening << std::endl;

	nPixels = xRes * yRes;

	//memory allocation
	Material* materials = new Material[nMaterials];
	Sphere* spheres = new Sphere[nSpheres];
	Light* lights = new Light[nLights];
	Pixel* screen = new Pixel[nPixels];

	// filling scene data
	for (int i = 0; i < nMaterials; i++){
		file >> materials[i];
	}
	for (int i = 0; i < nSpheres; i++){
		file >> spheres[i];
	}
	for (int i = 0; i < nLights; i++){
		file >> lights[i];
	}

	scene = Scene(nMaterials, nSpheres, nLights, materials, spheres, lights);
	camera = Camera(pos, dir, xOpening, yOpening, xRes, yRes, depth, nPixels, screen);

	return true;
}

int main(int argc, char** argv) {
	if (argc < 3) {
		std::cerr << "[inut file] [output file]" << std::endl;
		return -1;
	}
	//initialising scene and camera
	Scene scene;
	Camera camera;
	if (init(scene, camera, argv[1])) {
		std::cout << "initialization successfull !" << std::endl;
		return -1;
	}
}

