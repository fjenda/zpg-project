/**
 * @file Translation.h
 *
 * @brief Translation class
 *
 * @details Translation class for transformation
 *          It is used for translating objects
 *          It is derived from Transformation class
 *
 * @author Jan Fojtik
 *
 * @year 2023
 **/

#ifndef ZPGPROJECT_TRANSLATION_H
#define ZPGPROJECT_TRANSLATION_H


#include "Transformation.h"

class Translation : public Transformation {
private:
    glm::vec3 translation = glm::vec3(0.f);

public:
    explicit Translation(glm::vec3 translation);
    explicit Translation(bool stationary, glm::vec3 translation);
    glm::mat4 getMatrix() override;
};


#endif //ZPGPROJECT_TRANSLATION_H
