//
// Created by Honza Fojtík on 17.11.2023.
//

#ifndef ZPGPROJECT_BEZIERTRANSLATION_H
#define ZPGPROJECT_BEZIERTRANSLATION_H

#include "Transformation.h"

class BezierTranslation : public Transformation {
private:
    glm::mat4 A;
    glm::mat4 B = glm::mat4(0.0f);
    std::vector<glm::mat4> points;
    float t = 0.5f;
    float delta = 0.01f;
    int index = 0;
    bool increasing = false;
    float speed;

public:
    BezierTranslation(glm::mat4 B, float speed);
    BezierTranslation(std::vector<glm::mat4> points, float speed);
    glm::mat4 getMatrix() override;
    void setPoints(std::vector<glm::mat4> p) { this->points = p; };
};


#endif //ZPGPROJECT_BEZIERTRANSLATION_H
