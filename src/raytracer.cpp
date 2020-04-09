#include <iostream>

#include "src/structs/Camera.h"
#include "src/structs/Color.h"
#include "src/structs/Intersection.h"
#include "src/structs/Light.h"
#include "src/structs/Material.h"
#include "src/structs/Pixel.h"
#include "src/structs/Point.h"
#include "src/structs/Ray.h"
#include "src/structs/Scene.h"
#include "src/structs/Sphere.h"
#include "src/structs/Vector.h"

bool init(scene, camera, const char* ifn){
	//scene variables
	int nMaterials, nSpheres, nLights;
	//camera variables
	Point pos;
	Vector dir;
	int xOpening, yOpening, xRes, yRes;
	int nPixels;

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

