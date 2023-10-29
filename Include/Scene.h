/**
 * @file Scene.h
 *
 * @brief Scene class
 *
 * @details Scene class is used to store all models and lights in the scene.
 *          It also contains camera and shader used for rendering.
 *          Scene class is also responsible for rendering all models in the scene.
 *
 * @author Jan Fojtik
 *
 * @year 2023
 **/

#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "RenderableModel.h"
#include "Camera.h"

class Scene {
	
private:
    int id;
	std::vector<RenderableModel*> models;
    std::vector<Light*> lights;

    Camera* camera;
    Shader* shader;
    RenderableModel* skybox = nullptr;

public:
	Scene(int id);
	~Scene();

	void render(GLFWwindow* window);
	void addModel(RenderableModel* model);
    void addModel(const std::string& pFile);

    void setLights(const std::vector<Light*> l);
    void setSkybox(RenderableModel* skybox);

    int getId() { return this->id; }

    Camera* getCamera() { return this->camera; }

	std::vector<RenderableModel*> getModels();

    void enableDebugInterface();
};

#endif