//
// Created by Honza Fojtík on 10.10.2023.
//

#ifndef ZPGPROJECT_CALLBACKCONTROLLER_H
#define ZPGPROJECT_CALLBACKCONTROLLER_H

#include "Application.h"
#include "Camera.h"

class CallbackController : public Subject {
private:
    static CallbackController& instance();
    static Camera* camera;
public:
    static void errorCallback(int error, const char* description);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void windowFocusCallback(GLFWwindow* window, int focused);
    static void windowIconifyCallback(GLFWwindow* window, int iconified);
    static void windowSizeCallback(GLFWwindow* window, int width, int height);
    static void cursorCallback(GLFWwindow* window, double x, double y);
    static void buttonCallback(GLFWwindow* window, int button, int action, int mode);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    static void setCamera(Camera* c);
};


#endif //ZPGPROJECT_CALLBACKCONTROLLER_H
