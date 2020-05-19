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
	}
	for (int i = 0; i < scene->nSpheres; i++){
		file >> scene->spheres[i];
	}
	for (int i = 0; i < scene->nLights; i++){
		file >> scene->lights[i];
	}

	//linking spheres to materials
	for (int i = 0; i < scene->nSpheres; i++){
		scene->spheres[i].mat = scene->materials[0];
	}

	return true;
}

void intersect(Ray ray, Scene* scene, Intersection* intersection){
	Material background;
	//Sphere* closestSphere = nullptr;
	//float d = std::numeric_limits<double>::infinity();
	float ns = 0;
	for (int i = 0; i < scene->nSpheres; ++i){
		float hit = scene->spheres[i].intersects(ray);
		if (hit > 0){
			ns += 1;
		}
	}
	if (ns > 0) {
		intersection->mat = &scene->spheres[0].mat;
	} else {
		intersection->mat = &background;
	}
}

bool trace(Scene* scene, Camera* camera) {
	camera->setupScreen();
	Pixel* currentPixel;
	Intersection intersection;
	for (unsigned int p = 0; p < camera->nPixels; ++p){
		currentPixel = &camera->screen[p];
		//std::cout << currentPixel->pray.dir << std::endl;
		intersect(currentPixel->pray, scene, &intersection);
		currentPixel->col = intersection.mat->col;
	}
	return true;
}

bool print(Camera* camera, char* ofn) {
	std::ofstream ofs(ofn, std::ios::out | std::ios::binary);
	ofs << "P6\n" << camera->xRes << " " << camera->yRes << "\n255\n";
	for (unsigned i = 0; i < camera->nPixels; ++i) {
		//if (i%2 == 0) {
		//ofs << (unsigned char)(255) <<
		//(unsigned char)(255) <<
		//(unsigned char)(255);
		//} else {
		ofs << (unsigned char)(std::min(255, camera->screen[i].col.r )) <<
		(unsigned char)(std::min(255, camera->screen[i].col.g )) <<
		(unsigned char)(std::min(255, camera->screen[i].col.b ));
		//}
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

