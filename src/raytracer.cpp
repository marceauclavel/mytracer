#include <fstream>
#include <iostream>
#include <cmath>

#include "header.h"

bool init(Scene* scene, Camera* camera, char* ifn) {

	std::ifstream file(ifn);
	if (!file) return false;
	file >> scene->nMaterials >> scene->nSpheres >> scene->nLights;
	file >> camera->pos >> camera->dir >> camera->xOpening >> camera->yOpening >> camera->xRes >> camera->yRes >> camera->depth;

	camera->nPixels = camera->xRes * camera->yRes;

	//memory allocation
	scene->materials = new Material[scene->nMaterials];
	scene->spheres = new Sphere[scene->nSpheres];
	scene->lights = new Light[scene->nLights];
	camera->screen = new Pixel[camera->nPixels];

	//filling scene data
	for (int i = 0; i < scene->nMaterials; i++){
		file >> scene->materials[i];
		//std::cout << scene->materials[i].col << std::endl;
	}
	for (int i = 0; i < scene->nSpheres; i++){
		file >> scene->spheres[i];
	}
	for (int i = 0; i < scene->nLights; i++){
		file >> scene->lights[i];
	}

	//linking spheres to materials
	for (int i = 0; i < scene->nSpheres; i++){
		scene->spheres[i].mat = scene->materials[scene->spheres[i].matNb];
	}

	return true;
}

void intersect(Ray ray, Scene* scene, Intersection* intersection){
	int closestSphereIndex = -1;
	float dmin = std::numeric_limits<double>::infinity();
	for (int i = 0; i < scene->nSpheres; ++i){
		float d = scene->spheres[i].intersects(ray);
		if (d > 0){
			if (d < dmin){
				dmin = d;
				closestSphereIndex = i;
			}
		}
	}
	if (closestSphereIndex == -1) {
		intersection->d = -1;
	} else {
		intersection->d = dmin;
		intersection->sph = &scene->spheres[closestSphereIndex];
		intersection->mat = &intersection->sph->mat;
		Vector n = intersection->sph->pos - (dmin * ray.dir) + ray.pos;
		n.normalize();
		intersection->n = n;
		intersection->iray = &ray;
		intersection->pos = intersection->sph->pos + intersection->sph->r * n;
	}
}

float computeLightExposure(Scene* scene, Intersection* intersection) {
	Light light = scene->lights[0];
	Vector lightDir = intersection->pos - light.pos;
	lightDir.normalize();
	//std::cout << intersection->n.norm() << std::endl;
	float lightFacingRatio = std::max(0.0f, -1 * (intersection->n).dot(lightDir));
	return lightFacingRatio;
}

float computePreExpSpec(Scene* scene, Intersection* intersection) {
	Light light = scene->lights[0];
	Vector lightDir = intersection->pos - light.pos;
	lightDir.normalize();
	Vector n = intersection->n;
	Vector perfRefl = lightDir + 2 * n.dot(lightDir) * n;
	perfRefl.normalize();
	//std::cout << intersection->iray->dir.norm() << perfRefl.norm() << std::endl;
	//std::cout << std::max(0.f, intersection->iray->dir.dot(perfRefl)) << std::endl;
	return std::max(0.0f, intersection->iray->dir.dot(perfRefl));
}

bool trace(Scene* scene, Camera* camera) {
	//Phong model constants
	float ka(.1), kd(.7), ks(0.2);
	Color white(255);
	camera->setupScreen();
	Pixel* currentPixel;
	Intersection intersection;
	Color ambient, diffuse, specular, finalCol;
	float lightExposure, shininess, preExpSpec;
	for (unsigned int p = 0; p < camera->nPixels; ++p){
		currentPixel = &camera->screen[p];
		intersect(currentPixel->pray, scene, &intersection);
		if (intersection.d  == -1 ) {
			finalCol = white;
		} else {
			ambient = intersection.mat->ambient;
			diffuse = intersection.mat->diffuse;
			specular = intersection.mat->specular;
			shininess = intersection.mat->shininess;

			lightExposure = computeLightExposure(scene, &intersection);
			preExpSpec = computePreExpSpec(scene, &intersection);

			ambient = ka * ambient;
			std::cout << diffuse << std::endl;
			std::cout << lightExposure << std::endl;
			diffuse = 2 * lightExposure * diffuse;
			specular = ks * pow(preExpSpec, shininess) * specular;
			//specular = ks * preExpSpec * specular;
			//finalCol = ambient + diffuse;
			//finalCol = finalCol + specular;
			//currentPixel->col = diffuse;
			finalCol = diffuse;
		}
		currentPixel->col = finalCol;
	}
	return true;
}

bool print(Camera* camera, char* ofn) {
	std::ofstream ofs(ofn, std::ios::out | std::ios::binary);
	ofs << "P6\n" << camera->xRes << " " << camera->yRes << "\n255\n";
	for (unsigned i = 0; i < camera->nPixels; ++i) {
		ofs << (unsigned char)(std::min(255.f, (float)camera->screen[i].col.r )) <<
		(unsigned char)(std::min(255.f, (float)camera->screen[i].col.g )) <<
		(unsigned char)(std::min(255.f, (float)camera->screen[i].col.b ));
	}
	ofs.close();
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
	if (init(&scene, &camera, argv[1])) {
		std::cout << "initialization successfull !" << std::endl;
	}
	//compute the image
	if (trace(&scene, &camera)) {
		std::cout << "tracing successfull !" << std::endl;
	}
	//print the image
	if (print(&camera, argv[2])) {
		std::cout << "printing successfull !" << std::endl;
	}
	return -1;
}

