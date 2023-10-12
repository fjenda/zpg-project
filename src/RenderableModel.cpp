#include "../Include/RenderableModel.h"

#include "../Models/Models.h"

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
    this->shader->setViewMatrix();
    this->shader->setProjectionMatrix();
	this->model->bindVertexArray();
	
	glDrawElements(GL_TRIANGLES, this->model->getIndexCount(), GL_UNSIGNED_INT, 0);
}

void RenderableModel::tick() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    transformations->tick(deltaTime);
}

void RenderableModel::infoLog() {
	fprintf(stdout, "\n[INFO] RenderableModel info:\n");
	this->model->infoLog();
	this->shader->infoLog();
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