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

	return true;
}

bool trace(Scene* scene, Camera* camera) {
	float xStep, yStep;
	Vector dir, xDir, yDir;
	Point pos;
	xStep = (2. / camera->xRes) * std::tan(camera->xOpening / 2.);
	yStep = (2. / camera->yRes) * std::tan(camera->yOpening / 2.);
	for ( int i = 0; i < camera->xRes; i++) {
		for ( int j = 0; j < camera->yRes; j++) {
			pos = camera->pos;
			dir = camera->dir;
			xDir = dir.cross(Vector(0, 0, 1));
			yDir = Vector(0, 0, 1);
			dir = dir + ( i * xStep ) * xDir + ( j * yStep ) * yDir;
			dir.normalize();
			camera->screen[i + camera->xRes * j].col.r = i ;
		}
	}
	return true;
}

bool print(Camera* camera, char* ofn) {
	std::ofstream ofs(ofn, std::ios::out | std::ios::binary);
	ofs << "P6\n" << camera->xRes << " " << camera->yRes << "\n255\n";
	for (unsigned i = 0; i < camera->nPixels; ++i) {
		ofs << (unsigned char)(std::min(255, camera->screen[i].col.r )) <<
		(unsigned char)(std::min(255, camera->screen[i].col.g )) <<
		(unsigned char)(std::min(255, camera->screen[i].col.b ));
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

