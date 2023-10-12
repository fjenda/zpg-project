//
// Created by Honza Fojtík on 05.10.2023.
//

#ifndef ZPGPROJECT_TRANSLATION_H
#define ZPGPROJECT_TRANSLATION_H


#include "Transformation.h"

class Translation : public Transformation {
private:
    glm::vec3 translation = glm::vec3(0.f);

public:
    explicit Translation(glm::vec3 translation);
    glm::mat4 getMatrix() override;
    void tick(float deltaTime) override;
};


#endif //ZPGPROJECT_TRANSLATION_H
