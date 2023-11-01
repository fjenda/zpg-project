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

    if (this->skybox != nullptr) {
        glDepthFunc(GL_LEQUAL);
        this->skybox->render();
        glDepthFunc(GL_LESS);
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

void Scene::setSkybox(RenderableModel* skybox) {
    this->skybox = skybox;
}

void Scene::enableDebugInterface() {
    ImGui::Begin("Debug interface");

    this->camera->enableDebugInterface();
    ImGui::Separator();

    auto lightsT = "Lights - " + std::to_string(lights.size());
    if (ImGui::TreeNode(lightsT.c_str())) {
        ImGui::Indent(5.f);

        int i = 1;
        for (auto light : lights) {
            light->enableDebugInterface(i);
            i++;
        }
        ImGui::TreePop();
    }
    ImGui::Separator();

    auto modelsT = "Entities - " + std::to_string(models.size());
    if (ImGui::TreeNode(modelsT.c_str())) {
        int i = 1;
        for (auto model : models) {
            model->enableDebugInterface(i);
            i++;
        }
        ImGui::TreePop();
    }


    ImGui::End();
}