#include "Material.h"

Material::Material() {
	ambient = Color(0, 0, 0);
	diffuse = Color(0, 0, 0);
	specular = Color(0, 0, 0);
	shininess = 0;
}

Material::Material(Color nambient, Color ndiffuse, Color nspecular, float nshininess) {
	ambient = nambient;
	diffuse = ndiffuse;
	specular = nspecular;
	shininess = nshininess;
}
