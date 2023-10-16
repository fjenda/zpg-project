//
// Created by Honza Fojtík on 16.10.2023.
//

#ifndef ZPGPROJECT_LIGHT_H
#define ZPGPROJECT_LIGHT_H

#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "imgui/imgui.h"

class Light {
private:
    glm::vec3 position;
    glm::vec3 color;

public:
    Light(glm::vec3 position, glm::vec3 color);
    glm::vec3 getPosition() const { return this->position; }
    glm::vec3 getColor() const { return this->color; }

    void enableDebugInterface();
};

#endif //ZPGPROJECT_LIGHT_H
