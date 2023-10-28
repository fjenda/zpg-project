//
// Created by Honza Fojtík on 25.10.2023.
//

#include "../Include/Material.h"

Material::Material() : Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), 32.f, glm::vec3(1.f)) {}

Material::Material(glm::vec3 r_ambient, glm::vec3 r_diffuse, glm::vec3 r_specular, float shininess, glm::vec3 color) {
    this->r_ambient = r_ambient;
    this->r_diffuse = r_diffuse;
    this->r_specular = r_specular;
    this->shininess = shininess;
    this->color = color;
}