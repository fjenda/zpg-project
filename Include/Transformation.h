/**
 * @file Transformation.h
 *
 * @brief Transformation class
 *
 * @details Defines Transformation class
 *          Transformation class is abstract class for all transformations
 *          It contains virtual methods for getting transformation matrix and for ticking
 *
 * @author Jan Fojtik
 *
 * @year 2023
 **/

#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

//Include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <vector>

class Transformation {
public:
    virtual glm::mat4 getMatrix() = 0;
};

#endif // !TRANSFORMATION_H
