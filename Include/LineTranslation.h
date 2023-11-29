//
// Created by Honza Fojtík on 29.11.2023.
//

#ifndef ZPGPROJECT_LINETRANSLATION_H
#define ZPGPROJECT_LINETRANSLATION_H

#include "Transformation.h"

class LineTranslation : public Transformation {
private:
    glm::vec3 start;
    glm::vec3 end;
    float t = 0.5f;
    float delta = 0.01f;
    float speed;
public:
    LineTranslation(glm::vec3 start, glm::vec3 end, float speed);
    glm::mat4 getMatrix() override;
};

#endif //ZPGPROJECT_LINETRANSLATION_H
