//
// Created by Honza Fojtík on 29.11.2023.
//

#include "../Include/LineTranslation.h"

LineTranslation::LineTranslation(glm::vec3 start, glm::vec3 end, float speed) {
    this->start = start;
    this->end = end;
    this->speed = speed;
}

glm::mat4 LineTranslation::getMatrix() {
    if (t >= 1.0f || t <= 0.0f)
        delta *= -1;
    t += delta * speed;

    glm::vec3 moveDirection = end - start;
    glm::mat4 mod{1.0f};
    mod = glm::translate(mod, start + moveDirection * t);
    return mod;
}