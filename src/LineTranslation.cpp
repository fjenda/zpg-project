//
// Created by Honza Fojtík on 29.11.2023.
//

#include "../Include/LineTranslation.h"

LineTranslation::LineTranslation(glm::vec3 start, glm::vec3 end, float speed) {
    this->start = start;
    this->end = end;
    this->speed = speed;
}

LineTranslation::LineTranslation(std::vector<glm::vec3> points, float speed) {
    this->points = points;
    this->increasing = true;
    this->speed = speed;
}

glm::mat4 LineTranslation::getMatrix() {
    if (start != glm::vec3(0) && end != glm::vec3(0)) {
        if (t >= 1.0f || t <= 0.0f)
            delta *= -1;
        t += delta * speed;

        glm::vec3 moveDirection = end - start;
        glm::mat4 mod{1.0f};
        mod = glm::translate(mod, start + moveDirection * t);
        return mod;
    } else {
        if (t >= 1.0f || t <= 0.0f) {
            index += increasing ? 1 : -1;
            t = 0.0f;

            if (index == points.size() - 1 || index == 0)
                increasing = !increasing;
        }
        t += delta * speed;

        // get current segment
        glm::vec3 start = points[index];
        glm::vec3 end;

        if (increasing)
            end = points[index + 1];
        else
            end = points[index - 1];
        glm::vec3 moveDirection = end - start;
        glm::mat4 mod{1.0f};
        mod = glm::translate(mod, start + moveDirection * t);
        return mod;
    }

}