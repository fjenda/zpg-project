#include "../Include/Scene.h"
#include "../Include/CallbackController.h"

Scene::Scene(int id) {
    this->id = id;
    Shader* s = ShaderBuilder().build();
    this->camera = new Camera(s);
    s->setCamera(this->camera);
    CallbackController::setCamera(this->camera);
    fprintf(stdout, "[DEBUG] Scene #%d created\n", id);
}

Scene::~Scene() {
	for (auto model : models) {
		delete model;
	}
	fprintf(stdout, "[DEBUG] Scene #%d & models destroyed\n", id);
}

void Scene::render() {
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