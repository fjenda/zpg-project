//
// Created by Honza Fojtík on 05.10.2023.
//

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
