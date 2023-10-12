//
// Created by Honza Fojtík on 12.10.2023.
//

#ifndef ZPGPROJECT_WINDOW_H
#define ZPGPROJECT_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>

class Window {
private:
    GLFWwindow* window;
    int width;
    int height;

public:
    Window(int w, int h);
    ~Window();

    GLFWwindow* getWindow() const { return this->window; }
    void getVersionInfo();
};


#endif //ZPGPROJECT_WINDOW_H
