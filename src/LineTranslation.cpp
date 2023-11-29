//
// Created by Honza Fojtík on 29.11.2023.
//

#include "../Include/LineTranslation.h"

LineTranslation::LineTranslation(glm::vec3 start, glm::vec3 end, float speed) {
    this->startPoints.push_back(start);
    this->endPoints.push_back(end);
    this->speed = speed;
}

glm::mat4 LineTranslation::getMatrix() {
    if (startPoints.size() == 1 && endPoints.size() == 1) {
        if (t >= 1.0f || t <= 0.0f)
            delta *= -1;
        t += delta * speed;

        glm::vec3 start = startPoints[0];
        glm::vec3 end = endPoints[0];
        glm::vec3 moveDirection = end - start;
        glm::mat4 mod{1.0f};
        mod = glm::translate(mod, start + moveDirection * t);
        return mod;
    } else {
        if (t >= 1.0f || t <= 0.0f) {
            index++;
            delta *= -1;
        }
        t += delta * speed;

        glm::vec3 start = startPoints.at(index);
        glm::vec3 end = endPoints.at(index);
        glm::vec3 moveDirection = end - start;
        glm::mat4 mod{1.0f};
        mod = glm::translate(mod, start + moveDirection * t);
        return mod;

    }

}