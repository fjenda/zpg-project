#include "Scene.h"

Scene::Scene(int id) {
    this->id = id;
    this->camera = new Camera(ShaderBuilder().build());
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