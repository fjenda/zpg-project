//
// Created by Honza Fojtík on 05.10.2023.
//

#include "../Include/Composite.h"

Composite::~Composite() {
    for (auto child : children) {
        delete child;
    }
}

glm::mat4 Composite::getMatrix() {
    glm::mat4 matrix = glm::mat4(1.0f);
    for (auto child : children) {
        matrix *= child->getMatrix();
    }
    return matrix;
}

void Composite::addChild(Transformation *child) {
    children.push_back(child);
}

void Composite::removeChild(Transformation *child) {
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}