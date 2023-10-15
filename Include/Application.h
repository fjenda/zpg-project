#ifndef APPLICATION_H
#define APPLICATION_H

#include "Scene.h"
#include "ModelLoader.h"
#include "CallbackController.h"
#include "Window.h"

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
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

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

    int getWidth() { return this->width; }
    int getHeight() { return this->height; }
    void setWidth(int width) { this->width = width; }
    void setHeight(int height) { this->height = height; }

    float getDeltaTime() { return this->deltaTime; }

//    void setCallbacks();
};

#endif