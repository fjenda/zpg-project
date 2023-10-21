/**
 * @file Scale.h
 *
 * @brief Scale transformation
 *
 * @details Scale transformation
 *          It is used for scaling objects
 *          It is derived from Transformation class
 *
 * @author Jan Fojtik
 *
 * @year 2023
 **/

#ifndef ZPGPROJECT_SCALE_H
#define ZPGPROJECT_SCALE_H


#include "Transformation.h"

class Scale : public Transformation {
private:
    glm::vec3 scale = glm::vec3(1.0f);

public:
    explicit Scale(glm::vec3 scale);
    glm::mat4 getMatrix() override;
    void tick(float deltaTime) override;
};


#endif //ZPGPROJECT_SCALE_H
