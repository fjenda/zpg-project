#ifndef APPLICATION_H
#define APPLICATION_H

#include "../Scene/Scene.h"
#include "../ModelLoader/ModelLoader.h"
#include "../CallbackController/CallbackController.h"

class Application {

private:
	Application() = default;

	GLFWwindow* window;
	Scene* currentScene;
    std::vector<Scene*> scenes;

	int width;
	int height;
    float lastFrame = 0;
    float deltaTime = 0;

public:
	static Application& get();
	~Application();

	void initialization(int width, int height);
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

    void setCallbacks();
};

#endif