/**
 * @file Application.h
 *
 * @brief Class for application
 *
 * @author Jan Fojtik
 *
 * @year 2023
 **/

#ifndef APPLICATION_H
#define APPLICATION_H

#include "Scene.h"
#include "ModelLoader.h"
#include "CallbackController.h"
#include "Window.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

class Application {

private:
	Application() = default;

    Window* window;
	//GLFWwindow* window;
	Scene* currentScene;
    std::vector<Scene*> scenes;
    CallbackController* callbackController;

	int width;
	int height;
    float ratio;

    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    bool lockedCursor = true;

public:
	static Application& get();
	~Application();

	void initialization(int w, int h);
	void run();

    void createScene();
	Scene* getCurrentScene() { return this->currentScene; }
    Scene* getSceneById(int id);
    std::vector<Scene*> getScenes() { return this->scenes; }
    void setCurrentScene(Scene* scene) { this->currentScene = scene; }
    void addScene(Scene* scene);

    glm::vec4 getViewport() { return glm::vec4(0, 0, this->width, this->height); }
    int getWidth() { return this->width; }
    int getHeight() { return this->height; }
    float getRatio() { return this->ratio; }
    void setWidth(int width) { this->width = width; }
    void setHeight(int height) { this->height = height; }
    void setRatio(float ratio) { this->ratio = ratio; }

    void enableDebugInterface();


    float getDeltaTime() { return this->deltaTime; }

    void setLockedCursor(bool locked) { this->lockedCursor = locked; }
    bool isLockedCursor() { return this->lockedCursor; }

//    void setCallbacks();
};

#endif