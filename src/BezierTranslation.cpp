//
// Created by Honza Fojtík on 17.11.2023.
//

#include <utility>

#include "../Include/BezierTranslation.h"

BezierTranslation::BezierTranslation(glm::mat4 B, float speed) {
    this->A = glm::mat4(
        glm::vec4(-1.0, 3.0, -3.0, 1.0),
        glm::vec4(3.0, -6.0, 3.0, 0),
        glm::vec4(-3.0, 3.0, 0, 0),
        glm::vec4(1, 0, 0, 0));

    this->B = B;
    this->speed = speed;
}

BezierTranslation::BezierTranslation(std::vector<glm::mat4> points, float speed) {
    this->A = glm::mat4(
        glm::vec4(-1.0, 3.0, -3.0, 1.0),
        glm::vec4(3.0, -6.0, 3.0, 0),
        glm::vec4(-3.0, 3.0, 0, 0),
        glm::vec4(1, 0, 0, 0));

    this->points = std::move(points);
    this->increasing = true;
    this->speed = speed;
}

glm::mat4 BezierTranslation::getMatrix() {
    if (B != glm::mat4(0.0f)) {
        if (t >= 1.0f || t <= 0.0f)
            delta *= -1;
        t += delta * speed;

        glm::vec4 moveDirection{1.0f, 1.0f, 1.0f, 0.0f};
        glm::mat4 mod{1.0f};
        glm::vec4 p = glm::vec4(pow(t, 3), pow(t, 2), t, 1.0f);
        // p * A -> bázové polynomy
        moveDirection = moveDirection * (p * A * glm::transpose(B));
        mod = glm::translate(mod, glm::vec3(moveDirection));
        return mod;
    } else {
        if (t >= 1.0f || t <= 0.0f) {
            index += increasing ? 1 : -1;

            if (index > points.size() - 1 || index < 0) {
                increasing = !increasing;
                delta *= -1;
                index += increasing ? 1 : -1;
            }
            t = increasing ? 0.0f : 1.0f;
        }
        t += delta * speed;

        // get current segment
        glm::mat4 B = points[index];
        glm::vec4 moveDirection{1.0f, 1.0f, 1.0f, 0.0f};
        glm::mat4 mod{1.0f};
        glm::vec4 p = glm::vec4(pow(t, 3), pow(t, 2), t, 1.0f);
        // p * A -> bázové polynomy
        moveDirection = moveDirection * (p * A * glm::transpose(B));
        mod = glm::translate(mod, glm::vec3(moveDirection));
        return mod;
    }
}