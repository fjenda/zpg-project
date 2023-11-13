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
#include "CallbackController.h"

class Scene : public Observer {
	
private:
    int id;
	std::vector<RenderableModel*> models;
    std::vector<Light*> lights;

    Camera* camera;
    Shader* shader;
    RenderableModel* skybox = nullptr;
    CallbackController* callbackController;

public:
	Scene(int id);
	~Scene();

	void render(GLFWwindow* window);
	void addModel(RenderableModel* model);

    void setLights(const std::vector<Light*> l);
    void setSkybox(RenderableModel* skybox);
    void setCallbackController(CallbackController* callbackController);

    bool canDelete(int i);

    void update(Subject* subject, Event event) override;

    int getId() const { return this->id; }

    Camera* getCamera() { return this->camera; }

	std::vector<RenderableModel*> getModels();

    void enableDebugInterface();
};

#endif