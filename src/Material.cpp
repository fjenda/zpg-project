//
// Created by Honza Fojtík on 25.10.2023.
//

#include "../Include/Material.h"

Material::Material() {
    this->r_ambient = glm::vec3(0.1f);
    this->r_diffuse = glm::vec3(1.f);
    this->r_specular = glm::vec3(1.f);
}

Material::Material(glm::vec3 r_ambient, glm::vec3 r_diffuse, glm::vec3 r_specular, float shininess) {
    this->r_ambient = r_ambient;
    this->r_diffuse = r_diffuse;
    this->r_specular = r_specular;
    this->shininess = shininess;
}