//
// Created by Honza Fojtík on 10.10.2023.
//

#include "../Include/CallbackController.h"
#include "../Include/Application.h"


Camera* CallbackController::camera = nullptr;
CallbackController* CallbackController::controller = nullptr;

CallbackController::CallbackController(GLFWwindow* window) {
    this->window = window;
    controller = this;
}

void CallbackController::setCamera(Camera* c) {
    instance().camera = c;
    instance().attach(instance().camera);
    instance().notify();
}

CallbackController& CallbackController::instance() {
    return *controller;
}

void CallbackController::initialization() {
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowFocusCallback(window, windowFocusCallback);
    glfwSetWindowIconifyCallback(window, windowIconifyCallback);
    glfwSetWindowSizeCallback(window, windowSizeCallback);
    glfwSetCursorPosCallback(window, cursorCallback);
    glfwSetMouseButtonCallback(window, buttonCallback);
    glfwSetScrollCallback(window, scrollCallback);
}

void CallbackController::cursorCallback(GLFWwindow* window, double x, double y) {
    if (!Application::get().isLockedCursor()) return;

    Application::get().getCurrentScene()->getCamera()->mouseAction(x, y);

    //fprintf(stdout, "[CALLBACK] cursorCallback [%f %f]\n", x, y);
}

void CallbackController::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    if (!Application::get().isLockedCursor()) return;
    Application::get().getCurrentScene()->getCamera()->scrollAction(yoffset);
    //fprintf(stdout, "[CALLBACK] scrollCallback [%f %f]\n", xoffset, yoffset);
}

void CallbackController::buttonCallback(GLFWwindow* window, int button, int action, int mode) {
    //if (action == GLFW_PRESS) fprintf(stdout, "[CALLBACK] buttonCallback [%d,%d,%d]\n", button, action, mode);
}

void CallbackController::errorCallback(int error, const char* description) { fputs(description, stderr); }

void CallbackController::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

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
                Application::get().getCurrentScene()->getCamera()->notify();
                return;
            }
        }
    }

    if ((key == GLFW_KEY_LEFT_CONTROL) && action == GLFW_PRESS) {
        Application::get().setLockedCursor(!Application::get().isLockedCursor());
        glfwSetInputMode(window, GLFW_CURSOR, Application::get().isLockedCursor() ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
        Application::get().getCurrentScene()->getCamera()->setFirstMouse(true);
    }

    //fprintf(stdout, "[CALLBACK] keyCallback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void CallbackController::windowSizeCallback(GLFWwindow* window, int width, int height) {
    Application::get().setWidth(width);
    Application::get().setHeight(height);

    float ratio = (float) width / (float) height;
    Application::get().setRatio(ratio);

    glViewport(0, 0, Application::get().getWidth(), Application::get().getHeight());
    Application::get().getCurrentScene()->getCamera()->notify();


    //fprintf(stdout, "[CALLBACK] window_sizeCallback [%d,%d] \n", width, height);
}

void CallbackController::windowIconifyCallback(GLFWwindow* window, int iconified) {
    //fprintf(stdout, "[CALLBACK] window_iconifyCallback \n");
}

void CallbackController::windowFocusCallback(GLFWwindow* window, int focused) {
    //fprintf(stdout, "[CALLBACK] window_focusCallback \n");
}
