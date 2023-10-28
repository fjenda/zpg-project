/**
 * @file Composite.h
 *
 * @brief Composite class
 *
 * @details Composite class for transformations
 *
 * @author Jan Fojtik
 *
 * @year 2023
 **/

#ifndef ZPGPROJECT_COMPOSITE_H
#define ZPGPROJECT_COMPOSITE_H

#include "Transformation.h"

class Composite : public Transformation {
private:
    std::vector<Transformation*> children;

public:
    ~Composite();
    glm::mat4 getMatrix() override;
    void addChild(Transformation* child);
    void removeChild(Transformation* child);
};


#endif //ZPGPROJECT_COMPOSITE_H
