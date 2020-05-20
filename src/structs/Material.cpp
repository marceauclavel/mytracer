#include "Material.h"

Material::Material() {
	ambient = Color(0, 0, 0);
	diffuse = Color(0, 0, 0);
}

Material::Material(Color nambient, Color ndiffuse) {
	ambient = nambient;
	diffuse = ndiffuse;
}
