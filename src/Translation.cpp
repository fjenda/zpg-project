//
// Created by Honza Fojtík on 05.10.2023.
//

#include "../Include/Translation.h"

Translation::Translation(glm::vec3 translation) : translation(translation) {}

glm::mat4 Translation::getMatrix() {
    return glm::translate(glm::mat4(1.0f), this->translation);
}

void Translation::tick(float deltaTime) {
    // TODO: implement
}