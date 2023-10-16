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
    this->ratio = (float) w / (float) h;
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(this->window->getWindow(), true);
    ImGui_ImplOpenGL3_Init();

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

        // loop of imgui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        this->enableDebugInterface();

        // set background color
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        this->currentScene->render(this->window->getWindow());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(this->window->getWindow());
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

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

void Application::addScene(Scene *scene) {
    for (auto s : this->scenes) {
        if (s->getId() == scene->getId()) {
            throw std::runtime_error("Scene with id " + std::to_string(scene->getId()) + " already exists");
        }
    }
    this->scenes.push_back(scene);
}

void Application::enableDebugInterface() {
    this->currentScene->enableDebugInterface();
}