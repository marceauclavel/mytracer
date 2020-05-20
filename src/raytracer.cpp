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
		//std::cout << scene->spheres[i].mat.col << std::endl;
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
		intersection->pos = intersection->sph->pos + intersection->sph->r * n;
	}
}

Color computeShadow(Scene* scene, Intersection* intersection) {
	Light light = scene->lights[0];
	Vector lightDir = intersection->pos - light.pos;
	lightDir.normalize();
	float lightFacingRatio = std::max(0.0f, (intersection->n).dot(lightDir));
	Color shadow(255* lightFacingRatio);
	return shadow;
}

void mix(Color cola, Color colb, float coeff, Color* ncol) {
	ncol->r = coeff * cola.r + (1 - coeff) * (float)colb.r;
	ncol->g = coeff * cola.g + (1 - coeff) * (float)colb.g;
	ncol->b = coeff * cola.b + (1 - coeff) * (float)colb.b;
}

Color sub(Color cola, Color colb) {
	int nr = std::max(0, colb.r - cola.r);
	int ng = std::max(0, colb.r - cola.r);
	int nb = std::max(0, colb.b - cola.b);
	Color col(nr, ng, nb);
	return col;
}

bool trace(Scene* scene, Camera* camera) {
	Color white(255);
	camera->setupScreen();
	Pixel* currentPixel;
	Intersection intersection;
	Color diffuse;
	Color shadow;
	for (unsigned int p = 0; p < camera->nPixels; ++p){
		currentPixel = &camera->screen[p];
		intersect(currentPixel->pray, scene, &intersection);
		if (intersection.d  == -1 ) {
			currentPixel->col = white;
		} else {
			diffuse = intersection.mat->col;
			shadow = computeShadow(scene, &intersection);
			Color finalCol;
			mix(shadow, diffuse, 0, &finalCol);
			currentPixel->col = diffuse;
			//currentPixel->col = shadow;
			//currentPixel->col = diffuse;
			//std::cout << currentPixel->col << std::endl;
		}
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

