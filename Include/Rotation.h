/**
 * @file Rotation.h
 *
 * @brief Class for rotation transformation
 *
 * @details Class for rotation transformation
 *          It is used for rotating objects
 *          It is derived from Transformation class
 *
 * @author Jan Fojtik
 *
 * @year 2023
 **/

#ifndef ZPGPROJECT_ROTATION_H
#define ZPGPROJECT_ROTATION_H


#include "Transformation.h"

class Rotation : public Transformation {
private:
    bool stationary = true;
    glm::vec3 axis = glm::vec3(0.f);
    float speed = 0.f;
    glm::vec3 position = glm::vec3(0.f);

public:
    Rotation(glm::vec3 axis, float speed) : axis(axis), speed(speed) {};
    Rotation(bool stationary, glm::vec3 axis, float speed, glm::vec3 position) : stationary(stationary), axis(axis), speed(speed), position(position) {};
    glm::mat4 getMatrix() override;
};


#endif //ZPGPROJECT_ROTATION_H
