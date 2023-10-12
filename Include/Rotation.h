//
// Created by Honza Fojtík on 05.10.2023.
//

#ifndef ZPGPROJECT_ROTATION_H
#define ZPGPROJECT_ROTATION_H


#include "Transformation.h"

class Rotation : public Transformation {
private:
    float angle;
    glm::vec3 axis = glm::vec3(0.f);
    float speed = 0.f;

public:
    explicit Rotation(float angle) : Rotation(angle, glm::vec3(1.f, 1.f, 1.f)) {};
    Rotation(float angle, glm::vec3 axis);
    Rotation(float angle, glm::vec3 axis, float speed) : angle(angle), axis(axis), speed(speed) {};
    glm::mat4 getMatrix() override;
    void tick(float deltaTime) override;
};


#endif //ZPGPROJECT_ROTATION_H
