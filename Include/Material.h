/**
 * @file Material.h
 *
 * @brief Class for material
 *
 * @details This class is used for material. It contains ambient, diffuse, specular and shininess of the material.
 *
 * @author Jan Fojtik
 *
 * @year 2023
 **/

#ifndef ZPGPROJECT_MATERIAL_H
#define ZPGPROJECT_MATERIAL_H


#include <glm/vec3.hpp>

class Material {
private:
    glm::vec3 r_ambient;
    glm::vec3 r_diffuse;
    glm::vec3 r_specular;
    float shininess = 32.f;

public:
    Material();
    Material(glm::vec3 r_ambient, glm::vec3 r_diffuse, glm::vec3 r_specular, float shininess);
    glm::vec3 getAmbient() const { return this->r_ambient; }
    glm::vec3 getDiffuse() const { return this->r_diffuse; }
    glm::vec3 getSpecular() const { return this->r_specular; }
    float getShininess() const { return this->shininess; }

//    void enableDebugInterface();
};


#endif //ZPGPROJECT_MATERIAL_H
