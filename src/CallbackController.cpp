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
    instance().notify(VIEW_UPDATE);
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
//   if (action == GLFW_PRESS) fprintf(stdout, "[CALLBACK] buttonCallback [%d,%d,%d]\n", button, action, mode);

    if ((button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT || button == GLFW_KEY_B) && action == GLFW_PRESS) {
        GLbyte color[4];
        GLfloat depth;
        GLuint index = 0;

        double x, y;
//        glfwGetCursorPos(window, &x, &y);

        x = Application::get().getWidth() / 2;
        y = Application::get().getHeight() / 2;

//        y = viewPort[3] - y;
        glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &color);
        glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
        glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

        printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n",
               (int) x, (int) y, color[0], color[1], color[2], color[3], depth, index);

        glm::vec3 screenPos = glm::vec3(x, y, depth);
        glm::mat4 view = camera->getCamera();
        glm::mat4 projection = camera->getPerspective();
        glm::vec4 viewPort = Application::get().getViewport();

        // screen position into object position
        glm::vec3 pos = glm::unProject(screenPos, view, projection, viewPort);

        printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);
        instance().data[0] = pos.x;
        instance().data[1] = pos.y;
        instance().data[2] = pos.z;
        instance().data[3] = index;

        if (button == GLFW_MOUSE_BUTTON_RIGHT)
            instance().notify(CLICK_RIGHT);
        else if (button == GLFW_MOUSE_BUTTON_LEFT)
            instance().notify(CLICK_LEFT);
        else if (button == GLFW_KEY_B)
            instance().notify(ADD_POINT);
    }
}

void CallbackController::errorCallback(int error, const char* description) { fputs(description, stderr); }

void CallbackController::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

    // ending application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    // adding bezier control point
    if (key == GLFW_KEY_B && action == GLFW_PRESS)
        buttonCallback(window, GLFW_KEY_B, GLFW_PRESS, 0);

    // changing scenes
    if ((key >= 49 && key <= 57) && action == GLFW_PRESS) {
        int id = key - 48;

        //if scene with this id exists
        for (auto scene : Application::get().getScenes()) {
            if (scene->getId() == id && Application::get().getCurrentScene() != scene) {

                // detach current scene
                instance().detach(Application::get().getCurrentScene());

                Application::get().setCurrentScene(scene);

                // attach new scene
                instance().attach(Application::get().getCurrentScene());

                fprintf(stdout, "[DEBUG] Switched to scene %d\n", id);
                Application::get().getCurrentScene()->getCamera()->setFirstMouse(true);
                Application::get().getCurrentScene()->getCamera()->notify(VIEW_UPDATE);
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
    Application::get().getCurrentScene()->getCamera()->notify(WINDOW_SIZE_CHANGE);

    //fprintf(stdout, "[CALLBACK] window_sizeCallback [%d,%d] \n", width, height);
}

void CallbackController::windowIconifyCallback(GLFWwindow* window, int iconified) {
    //fprintf(stdout, "[CALLBACK] window_iconifyCallback \n");
}

void CallbackController::windowFocusCallback(GLFWwindow* window, int focused) {
    //fprintf(stdout, "[CALLBACK] window_focusCallback \n");
}

const double* CallbackController::getLastData() {
    return data;
}
