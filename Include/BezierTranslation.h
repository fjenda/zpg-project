//
// Created by Honza Fojtík on 17.11.2023.
//

#ifndef ZPGPROJECT_BEZIERTRANSLATION_H
#define ZPGPROJECT_BEZIERTRANSLATION_H

#include "Transformation.h"

class BezierTranslation : public Transformation {
private:
    glm::mat4 A;
    glm::mat4 B;
    float t = 0.5f;
    float delta = 0.01f;
    float speed;

public:
    BezierTranslation(glm::mat4 B, float speed);
    glm::mat4 getMatrix() override;


};


#endif //ZPGPROJECT_BEZIERTRANSLATION_H
