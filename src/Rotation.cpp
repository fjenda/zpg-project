//
// Created by Honza Fojtík on 05.10.2023.
//

#include <GLFW/glfw3.h>
#include "../Include/Rotation.h"

glm::mat4 Rotation::getMatrix() {
    //return glm::rotate(glm::mat4(1.f), glm::radians(angle), axis);
    glm::mat4 trans = glm::mat4(1.0f);
    if (stationary) {
        trans = glm::rotate(glm::mat4(1.0f), glm::radians(speed), axis);
    } else {
        trans = glm::rotate(trans, glm::radians((float) glfwGetTime() * speed), glm::normalize(axis));
    }
    trans = glm::translate(trans, position);

    return trans;
}
