#include "Material.h"
#include "Sphere.h"
#include "Light.h"

struct Scene {
	int nMaterials, nSpheres, nLights;
	Material* materials;
	Sphere* spheres;
	Light* lights;
	Scene(nMaterials, nSpheres, nLights, materials, spheres, lights);
}
