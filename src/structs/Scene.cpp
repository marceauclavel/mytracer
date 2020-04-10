#include "Scene.h"
#include <ostream>

Scene::Scene() {
	nMaterials = 0;
	nSpheres = 0;
	nLights = 0;
	materials = nullptr;
	spheres = nullptr;
	lights = nullptr;
}

Scene::Scene(int nMaterials, int nSpheres, int nLights, Material* materials, Sphere* spheres, Light* lights){
	nMaterials = nMaterials;
	nSpheres = nSpheres;
	nLights = nLights;
	materials = materials;
	spheres = spheres;
	lights = lights;
}

