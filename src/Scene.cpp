#include <utility>

#include "../Include/Scene.h"
#include "../Include/CallbackController.h"
#include "imgui/imgui.h"

Scene::Scene(int id) {
    this->id = id;
    this->shader = ShaderBuilder().build();
    this->camera = new Camera(this->shader);
    this->shader->setCamera(this->camera);
    CallbackController::setCamera(this->camera);

    this->camera->notify();
    fprintf(stdout, "[DEBUG] Scene #%d created\n", id);
}

Scene::~Scene() {
	for (auto model : models) {
		delete model;
	}
	fprintf(stdout, "[DEBUG] Scene #%d & models destroyed\n", id);
}

void Scene::render(GLFWwindow* window) {
    this->camera->move(glfwGetKey(window, GLFW_KEY_W),
                       glfwGetKey(window, GLFW_KEY_S),
                       glfwGetKey(window, GLFW_KEY_A),
                       glfwGetKey(window, GLFW_KEY_D));


	for (auto model : models) {
		model->render();
	}
}

void Scene::addModel(RenderableModel* model) {
    if (!lights.empty())
        model->setShaderLight(lights);
	models.push_back(model);

    // Model info
//	fprintf(stdout, "[DEBUG] Added model to scene #%d\n", id);
//	model->infoLog();
}

std::vector<RenderableModel*> Scene::getModels() {
	return models;
}

void Scene::setLights(const std::vector<Light *> l) {
    this->lights = l;
    this->shader->setLights(l);
}

void Scene::enableDebugInterface() {
    ImGui::Begin("Debug interface");

    this->camera->enableDebugInterface();


    ImGui::BeginChildFrame(ImGui::GetID("Models"), ImVec2(300, 300));
    ImGui::Text("Models - %zu", models.size());
    int i = 1;
    for (auto model : models) {
        model->enableDebugInterface(i);
        i++;
    }

    ImGui::EndChild();

    ImGui::End();
}