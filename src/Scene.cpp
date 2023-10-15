#include "../Include/Scene.h"
#include "../Include/CallbackController.h"

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
        model->tick();
		model->render();
	}
}

void Scene::addModel(RenderableModel* model) {
	models.push_back(model);

	fprintf(stdout, "[DEBUG] Added model to scene #%d\n", id);
	model->infoLog();
}

std::vector<RenderableModel*> Scene::getModels() {
	return models;
}