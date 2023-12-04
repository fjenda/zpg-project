//
// Created by Honza Fojtík on 29.11.2023.
//

#ifndef ZPGPROJECT_LINETRANSLATION_H
#define ZPGPROJECT_LINETRANSLATION_H

#include "Transformation.h"

class LineTranslation : public Transformation {
private:
    glm::vec3 start = glm::vec3(0);
    glm::vec3 end = glm::vec3(0);
    std::vector<glm::vec3> points;
    float t = 0.5f;
    float delta = 0.01f;
    int index = 0;
    bool increasing = false;
    float speed;
public:
    LineTranslation(glm::vec3 start, glm::vec3 end, float speed);
    LineTranslation(std::vector<glm::vec3> points, float speed);
    glm::mat4 getMatrix() override;
};

#endif //ZPGPROJECT_LINETRANSLATION_H
