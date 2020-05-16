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

Scene::Scene(int nnMaterials, int nnSpheres, int nnLights, Material* nmaterials, Sphere* nspheres, Light* nlights){
	nMaterials = nnMaterials;
	nSpheres = nnSpheres;
	nLights = nnLights;
	materials = nmaterials;
	spheres = nspheres;
	lights = nlights;
}

