#pragma once

#include "Material.h"
#include "Sphere.h"
#include "Light.h"

struct Scene {
	int nMaterials, nSpheres, nLights;
	Material* materials;
	Sphere* spheres;
	Light* lights;
	Scene();
	Scene(int nMaterials, int nSpheres, int nLights, Material* materials, Sphere* spheres, Light* lights);
};
