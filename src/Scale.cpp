//
// Created by Honza Fojtík on 05.10.2023.
//

#include "../Include/Scale.h"

Scale::Scale(glm::vec3 scale) : scale(scale) {}

glm::mat4 Scale::getMatrix() {
    return glm::scale(glm::mat4(1.0f), this->scale);
}