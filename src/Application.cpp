#include "../Include/Application.h"

Application::~Application() {
    for (auto scene : this->scenes) {
        delete scene;
    }

    fprintf(stdout, "[DEBUG] Application destroyed\n");
}

void Application::initialization(int width, int height)
{     
	this->width = width;
	this->height = height;
    
//    glfwSetErrorCallback([](int error, const char* description) -> void { Application::get().error_callback(error, description); });

    if (!glfwInit())
        exit(EXIT_FAILURE);

    //inicialization of correct version of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
       
    
    this->window = glfwCreateWindow(800, 800, "ZPG", NULL, NULL);
    if (!this->window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }  
    
    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    // get version info
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);
    
    glfwGetFramebufferSize(this->window, &this->width, &this->height);

    //set the viewport
    glViewport(0, 0, this->width, this->height);

    //set key callbacks
    setCallbacks();

    //enable depth buffer
	glEnable(GL_DEPTH_TEST);

    //hide the cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //init scene
    this->currentScene = new Scene(1);

    //init scenes
    this->scenes.push_back(this->currentScene);
}

void Application::run()
{
    while (!glfwWindowShouldClose(this->window)) {
        // calculate delta time of current frame
        float currentFrame = glfwGetTime();
        this->deltaTime = currentFrame - this->lastFrame;
        this->lastFrame = currentFrame;

        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        this->currentScene->render();

        // update other events like input handling
        glfwPollEvents();
        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(this->window);
    }

    glfwDestroyWindow(this->window);
    glfwTerminate();
    //exit(EXIT_SUCCESS);
}

Application& Application::get() {
    static Application app;
    return app;
}

void Application::createScene() {
    if (this->scenes.size() == 9) {
        throw std::runtime_error("Maximum number of scenes reached");
    }

    this->scenes.push_back(new Scene(this->scenes.size() + 1));
}

Scene* Application::getSceneById(int id) {
    for (auto scene : this->scenes) {
        if (scene->getId() == id) {
            return scene;
        }
    }

    throw std::runtime_error("Scene with id " + std::to_string(id) + " not found");
}

void Application::setCallbacks() {
    // Sets the key callback
    glfwSetErrorCallback(CallbackController::errorCallback);
    glfwSetKeyCallback(this->window, CallbackController::keyCallback);
    glfwSetCursorPosCallback(this->window, CallbackController::cursorCallback);
    glfwSetMouseButtonCallback(this->window, CallbackController::buttonCallback);
    glfwSetWindowFocusCallback(this->window, CallbackController::windowFocusCallback);
    glfwSetWindowIconifyCallback(this->window, CallbackController::windowIconifyCallback);
    glfwSetWindowSizeCallback(this->window, CallbackController::windowSizeCallback);
    glfwSetScrollCallback(this->window, CallbackController::scrollCallback);
}