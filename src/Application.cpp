#include "../Include/Application.h"

Application::~Application() {
    for (auto scene : this->scenes) {
        delete scene;
    }

    fprintf(stdout, "[DEBUG] Application destroyed\n");
}

void Application::initialization(int w, int h)
{     
	this->width = w;
	this->height = h;
    this->window = new Window(w, h);
    this->callbackController = new CallbackController(this->window->getWindow());
    this->callbackController->initialization();

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    //set callbacks
//    setCallbacks();

    //hide the cursor
    glfwSetInputMode(this->window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //init scenes
    this->currentScene = new Scene(1);
    this->scenes.push_back(this->currentScene);
}

void Application::run()
{
    //enable depth buffer
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(this->window->getWindow())) {
        // calculate delta time of current frame
        float currentFrame = glfwGetTime();
        this->deltaTime = currentFrame - this->lastFrame;
        this->lastFrame = currentFrame;

        // update other events like input handling
        glfwPollEvents();

        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        this->currentScene->render(this->window->getWindow());

        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(this->window->getWindow());
    }

    glfwDestroyWindow(this->window->getWindow());
    glfwTerminate();
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

//void Application::setCallbacks() {
//    // Sets the key callback
//    glfwSetErrorCallback(CallbackController::errorCallback);
//    glfwSetKeyCallback(this->window->getWindow(), CallbackController::keyCallback);
//    glfwSetCursorPosCallback(this->window->getWindow(), CallbackController::cursorCallback);
//    glfwSetMouseButtonCallback(this->window->getWindow(), CallbackController::buttonCallback);
//    glfwSetWindowFocusCallback(this->window->getWindow(), CallbackController::windowFocusCallback);
//    glfwSetWindowIconifyCallback(this->window->getWindow(), CallbackController::windowIconifyCallback);
//    glfwSetWindowSizeCallback(this->window->getWindow(), CallbackController::windowSizeCallback);
//    glfwSetScrollCallback(this->window->getWindow(), CallbackController::scrollCallback);
//}