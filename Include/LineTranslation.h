//
// Created by Honza Fojtík on 29.11.2023.
//

#ifndef ZPGPROJECT_LINETRANSLATION_H
#define ZPGPROJECT_LINETRANSLATION_H

#include "Transformation.h"

class LineTranslation : public Transformation {
private:
    std::vector<glm::vec3> startPoints;
    std::vector<glm::vec3> endPoints;
    float t = 0.5f;
    float delta = 0.01f;
    float index = 0;
    float speed;
public:
    LineTranslation(glm::vec3 start, glm::vec3 end, float speed);
    LineTranslation(std::vector<glm::vec3> startPoints, std::vector<glm::vec3> endPoints, float speed);
    glm::mat4 getMatrix() override;
};

#endif //ZPGPROJECT_LINETRANSLATION_H
