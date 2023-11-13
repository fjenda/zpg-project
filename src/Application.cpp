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

    //init scenes
    this->currentScene = new Scene(1);
    this->currentScene->setCallbackController(this->callbackController);
    this->callbackController->attach(this->currentScene);
    this->scenes.push_back(this->currentScene);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(this->window->getWindow(), true);
    ImGui_ImplOpenGL3_Init();
}

void Application::run()
{
    // enable stencil buffer
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    // enable depth buffer
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(this->window->getWindow())) {
        // calculate delta time of current frame
        float currentFrame = glfwGetTime();
        this->deltaTime = currentFrame - this->lastFrame;
        this->lastFrame = currentFrame;

        // update other events like input handling
        glfwPollEvents();

        // clear color, depth and stencil buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // loop of imgui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        this->enableDebugInterface();

        this->currentScene->render(this->window->getWindow());

        // get mouse position
        double x, y;
//        glfwGetCursorPos(this->window->getWindow(), &x, &y);

        // imgui getter for width and height
        ImGui::GetIO().DisplaySize = ImVec2(this->width, this->height);
        x = this->width / 2;
        y = this->height / 2;

        GLuint index;
//        double new_y = this->height - y;
        glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

        ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);
        ImGui::SetWindowPos(ImVec2(x, y));
        ImGui::Text("Index - %d", index);
        ImGui::Text("[%fl, %fl]", x, y);
        ImGui::End();

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

    auto scene = new Scene(this->scenes.size() + 1);
    scene->setCallbackController(this->callbackController);
    this->scenes.push_back(scene);
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

    scene->setCallbackController(this->callbackController);
    this->scenes.push_back(scene);
}

void Application::enableDebugInterface() {
    this->currentScene->enableDebugInterface();
}