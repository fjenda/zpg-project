//
// Created by Honza Fojtík on 05.10.2023.
//

#include "Rotation.h"

Rotation::Rotation(float angle, glm::vec3 axis) : angle(angle), axis(axis) {}

glm::mat4 Rotation::getMatrix() {
    return glm::rotate(glm::mat4(1.f), glm::radians(angle), axis);
}

void Rotation::tick(float deltaTime) {
    if (speed == 0.f) return;

    angle += deltaTime * speed;
}
