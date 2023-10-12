//
// Created by Honza Fojtík on 10.10.2023.
//

#include "../Include/CallbackController.h"

void CallbackController::cursorCallback(GLFWwindow* window, double x, double y) {
    Camera* cam = Application::get().getCurrentScene()->getCamera();

    if (cam->getFirstMouse()) {
        cam->setLastX(x);
        cam->setLastY(y);
        cam->setFirstMouse(false);
    }

    float xoffset = x - cam->getLastX();
    float yoffset = cam->getLastY() - y;
    cam->setLastX(x);
    cam->setLastY(y);

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    cam->setYaw(cam->getYaw() + xoffset);
    cam->setPitch(cam->getPitch() + yoffset);

    if (cam->getPitch() > 89.0f)
        cam->setPitch(89.0f);
    if (cam->getPitch() < -89.0f)
        cam->setPitch(-89.0f);

    glm::vec3 direction;
    direction.x = cos(glm::radians(cam->getYaw())) * cos(glm::radians(cam->getPitch()));
    direction.y = sin(glm::radians(cam->getPitch()));
    direction.z = sin(glm::radians(cam->getYaw())) * cos(glm::radians(cam->getPitch()));
    cam->setCameraFront(glm::normalize(direction));

    //fprintf(stdout, "[CALLBACK] cursorCallback [%f %f]\n", x, y);
}

void CallbackController::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    Camera* cam = Application::get().getCurrentScene()->getCamera();

    cam->setFov(cam->getFov() - yoffset);
    if (cam->getFov() < 10.0f)
        cam->setFov(10.0f);
    if (cam->getFov() > 90.0f)
        cam->setFov(90.0f);

    //fprintf(stdout, "[CALLBACK] scrollCallback [%f %f]\n", xoffset, yoffset);
}

void CallbackController::buttonCallback(GLFWwindow* window, int button, int action, int mode) {
    //if (action == GLFW_PRESS) fprintf(stdout, "[CALLBACK] buttonCallback [%d,%d,%d]\n", button, action, mode);
}

void CallbackController::errorCallback(int error, const char* description) { fputs(description, stderr); }

void CallbackController::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // ending application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    // changing scenes
    if ((key >= 49 && key <= 57) && action == GLFW_PRESS) {
        int id = key - 48;

        //if scene with this id exists
        for (auto scene : Application::get().getScenes()) {
            if (scene->getId() == id && Application::get().getCurrentScene() != scene) {
                Application::get().setCurrentScene(scene);
                fprintf(stdout, "[DEBUG] Switched to scene %d\n", id);
                Application::get().getCurrentScene()->getCamera()->setFirstMouse(true);
                return;
            }
        }
    }

    // moving the camera
    if ((key == GLFW_KEY_W || key == GLFW_KEY_S ||
         key == GLFW_KEY_A || key == GLFW_KEY_D) &&
        (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        float cameraSpeed = 15.f * Application::get().getDeltaTime();
        Camera *cam = Application::get().getCurrentScene()->getCamera();

        if (key == GLFW_KEY_W) {
            cam->moveForward(cameraSpeed);
        }
        if (key == GLFW_KEY_S) {
            cam->moveBackward(cameraSpeed);
        }
        if (key == GLFW_KEY_A) {
            cam->moveLeft(cameraSpeed);
        }
        if (key == GLFW_KEY_D) {
            cam->moveRight(cameraSpeed);
        }
    }

    //fprintf(stdout, "[CALLBACK] keyCallback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void CallbackController::windowSizeCallback(GLFWwindow* window, int width, int height) {
    Application::get().setWidth(width);
    Application::get().setHeight(height);
    glViewport(0, 0, Application::get().getWidth(), Application::get().getHeight());

    //fprintf(stdout, "[CALLBACK] window_sizeCallback [%d,%d] \n", width, height);
}

void CallbackController::windowIconifyCallback(GLFWwindow* window, int iconified) {
    //fprintf(stdout, "[CALLBACK] window_iconifyCallback \n");
}

void CallbackController::windowFocusCallback(GLFWwindow* window, int focused) {
    //fprintf(stdout, "[CALLBACK] window_focusCallback \n");
}
