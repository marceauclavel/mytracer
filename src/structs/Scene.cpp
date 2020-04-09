#include "Scene.h"
#include <ostream>

bool Scene::init(const char* ifn) {
	nMaterials = 1;
	nSpheres = 1;
	nLights = 1;
	Material* materials = Material[nMaterials];
	Sphere* spheres = Sphere[nSpheres];
	Light* lights = Light[nLights];
	std::cout << "scene initialised with file " << ifn << std::endl;
	return true
}
