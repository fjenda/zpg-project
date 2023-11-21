//
// Created by Honza Fojtík on 12.10.2023.
//

#include "../Include/Window.h"

Window::Window(int w, int h) {
    this->width = w;
    this->height = h;

    if (!glfwInit())
        exit(EXIT_FAILURE);

    //inicialization of correct version of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_FALSE);

    this->window = glfwCreateWindow(w, h, "ZPG", NULL, NULL);
    if (!this->window) {
        glfwTerminate();
        fprintf(stderr, "[ERROR] Could not open window with GLFW3\n");
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1);

    getVersionInfo();

    //set the viewport
//    glfwGetFramebufferSize(this->window, &this->width, &this->height);
    glViewport(0, 0, this->width, this->height);

    //hide the cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Window::~Window() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

void Window::getVersionInfo() {
    // get version info
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}