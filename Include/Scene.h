#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "RenderableModel.h"
#include "Camera.h"

class Scene {
	
private:
    int id;
	std::vector<RenderableModel*> models;

    Camera* camera;
    Shader* shader;
public:
	Scene(int id);
	~Scene();

	void render(GLFWwindow* window);
	void addModel(RenderableModel* model);
    void addModel(const std::string& pFile);

    int getId() { return this->id; }

    Camera* getCamera() { return this->camera; }

	std::vector<RenderableModel*> getModels();
};

#endif