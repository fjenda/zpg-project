#include "../Include/RenderableModel.h"

#include "../Models/Models.h"
#include "imgui/imgui.h"

RenderableModel::~RenderableModel() {
	delete model;
	delete shader;
	//delete transformation;
}

RenderableModel::RenderableModel(Model* model, Shader* shader, Transformation* transformation) {
	this->model = model;
	this->shader = shader;
	this->transformations = transformation;
}

void RenderableModel::render() {
	// model matrix
	glm::mat4 modelMatrix = transformations->getMatrix();

	// render
	this->shader->use();
	this->shader->setModelMatrix(modelMatrix);
    this->shader->setUniformLights();
    this->shader->setUniformCamera();

    if (firstInit) {
        this->shader->setViewMatrix();
        this->shader->setProjectionMatrix();
        firstInit = false;
    }

	this->model->bindVertexArray();
	
	glDrawElements(GL_TRIANGLES, this->model->getIndexCount(), GL_UNSIGNED_INT, 0);
}

void RenderableModel::tick() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    transformations->tick(deltaTime);
}

void RenderableModel::setShaderLight(std::vector<Light *> l) {
    this->shader->setLights(l);
}

void RenderableModel::infoLog() {
	fprintf(stdout, "\n[INFO] RenderableModel info:\n");
	this->model->infoLog();
	this->shader->infoLog();
}

void RenderableModel::enableDebugInterface(int id) {
    ImGui::BeginChild("RenderableModel");
    ImGui::Text("RenderableModel #%d", id);
    ImGui::Indent();
    ImGui::Text("Model:");
    ImGui::Unindent();

    ImGui::EndChildFrame();
}

RenderableModelBuilder::RenderableModelBuilder(ModelKind kind) {
	switch (kind) {
		case ModelKind::PLAIN: model = new Model(plain); break;
		case ModelKind::SQUARE: model = new Model(square); break;
		case ModelKind::SPHERE: model = new Model(sphere); break;
		case ModelKind::TRIANGLE: model = new Model(triangle_rgb); break;
		case ModelKind::PYRAMID: model = new Model(pyramid); break;
		case ModelKind::SUZI: model = new Model(suziFlat); break;
		case ModelKind::SUZI_SMOOTH: model = new Model(suziSmooth); break;
        case ModelKind::TREE: model = new Model(tree); break;
        case ModelKind::BUSHES: model = new Model(bushes); break;
        case ModelKind::GIFT: model = new Model(gift); break;
	}
}

RenderableModelBuilder::RenderableModelBuilder(std::vector<float> points) {
	this->model = new Model(std::move(points));
}

RenderableModelBuilder::RenderableModelBuilder(std::vector<float> points, std::vector<int> indices) {
	this->model = new Model(std::move(points), std::move(indices));
}

RenderableModelBuilder* RenderableModelBuilder::setShader(Shader* shader) {
	this->shader = shader;
	return this;
}

RenderableModelBuilder* RenderableModelBuilder::setTransformation(Transformation* transformation) {
	this->transformation = transformation;
	return this;
}

RenderableModel* RenderableModelBuilder::build() {
	if (this->shader == nullptr) {
		throw std::runtime_error("[ERROR] Shader is null");
	}

	return new RenderableModel(model, shader, transformation);
}