#include "../Include/RenderableModel.h"
#include "../Models/Models.h"
#include "../Include/ArrayConverter.h"
#include "imgui/imgui.h"
#include "../Include/Application.h"

RenderableModel::RenderableModel(Model* model, Shader* shader, Transformation* transformation, Material* material) {
    this->model = model;
    this->shader = shader;
    this->transformations = transformation;
    this->material = material;
    this->texture = nullptr;
}

RenderableModel::RenderableModel(Model* model, Shader* shader, Transformation* transformation, Material* material, Texture* texture) {
	this->model = model;
	this->shader = shader;
	this->transformations = transformation;
    this->material = material;
    this->texture = texture;
}

RenderableModel::RenderableModel(Model* model, Shader* shader, Transformation* transformation, Material* material, std::vector<Texture*> textures) {
    this->model = model;
    this->shader = shader;
    this->transformations = transformation;
    this->material = material;
    this->textures = textures;
    this->texture = nullptr;
}

void RenderableModel::render() {
	// model matrix
	glm::mat4 modelMatrix = transformations->getMatrix();

	// render
	this->shader->use();
	this->shader->setModelMatrix(modelMatrix);
    this->shader->setUniformLights();
    this->shader->setUniformCamera();
    this->shader->setUniformMaterial(this->material);

    if (firstInit) {
        this->shader->setViewMatrix();
        this->shader->setProjectionMatrix();
        firstInit = false;
    }

    if (this->texture != nullptr) {
        this->texture->bind();
        this->shader->setTexture(this->texture->getTextureId(), 0);
    }

	this->model->bindVertexArray();
	
	glDrawElements(GL_TRIANGLES, this->model->getIndexCount(), GL_UNSIGNED_INT, 0);
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
    auto text = std::string("RenderableModel - ") + std::to_string(id);
    if (ImGui::TreeNode(text.c_str())) {
        ImGui::TreePop();
    }
}

RenderableModelBuilder::RenderableModelBuilder(ModelKind kind) {
	switch (kind) {
        case ModelKind::PLAIN: model = new Model(ArrayConverter::convert(plain, sizeof(plain)), 3, 3, 0); break;
		case ModelKind::SQUARE: model = new Model(square, 3, 3, 0); break;
        case ModelKind::SPHERE: model = new Model(ArrayConverter::convert(sphere, sizeof(sphere)), 3, 3, 0); break;
		case ModelKind::TRIANGLE: model = new Model(triangle_rgb, 3, 3, 0); break;
		case ModelKind::PYRAMID: model = new Model(pyramid, 3, 3, 0); break;
        case ModelKind::SUZI: model = new Model(ArrayConverter::convert(suziFlat, sizeof(suziFlat)), 3, 3, 0); break;
        case ModelKind::SUZI_SMOOTH: model = new Model(ArrayConverter::convert(suziSmooth, sizeof(suziSmooth)), 3, 3, 0); break;
        case ModelKind::TREE: model = new Model(ArrayConverter::convert(tree, sizeof(tree)), 3, 3, 0); break;
        case ModelKind::BUSHES: model = new Model(ArrayConverter::convert(bushes, sizeof(bushes)), 3, 3, 0); break;
        case ModelKind::GIFT: model = new Model(ArrayConverter::convert(gift, sizeof(gift)), 3, 3, 0); break;
        case ModelKind::PLAIN_TEXTURED: model = new Model(ArrayConverter::convert(plain_textured, sizeof(plain_textured)), 3, 3, 2); break;
	}
}

RenderableModelBuilder::RenderableModelBuilder(std::vector<float> points) {
	this->model = new Model(std::move(points));
}

RenderableModelBuilder::RenderableModelBuilder(std::vector<float> points, std::vector<int> indices) {
	this->model = new Model(std::move(points), std::move(indices));
}

RenderableModelBuilder* RenderableModelBuilder::setShader(std::shared_ptr<Shader> shader) {
    this->shader = shader.get();
    return this;
}

RenderableModelBuilder* RenderableModelBuilder::setTransformation(std::shared_ptr<Transformation> transformation) {
    this->transformation = transformation.get();
    return this;
}

RenderableModelBuilder* RenderableModelBuilder::setMaterial(std::shared_ptr<Material> material) {
    this->material = material.get();
    return this;
}

RenderableModelBuilder* RenderableModelBuilder::setModel(std::shared_ptr<Model> model) {
    this->model = model.get();
    return this;
}

RenderableModelBuilder* RenderableModelBuilder::setTexture(std::shared_ptr<Texture> texture) {
    this->texture = texture.get();
    return this;
}

RenderableModelBuilder *RenderableModelBuilder::setModel(Model *model) {
    this->model = model;
    return this;
}

RenderableModelBuilder* RenderableModelBuilder::setShader(Shader* shader) {
	this->shader = shader;
	return this;
}

RenderableModelBuilder* RenderableModelBuilder::setTransformation(Transformation* transformation) {
	this->transformation = transformation;
	return this;
}

RenderableModelBuilder* RenderableModelBuilder::setMaterial(Material *material) {
    this->material = material;
    return this;
}

RenderableModelBuilder* RenderableModelBuilder::setTexture(Texture *texture) {
    this->texture = texture;
    return this;
}

RenderableModel* RenderableModelBuilder::build() {
	if (this->shader == nullptr) {
		throw std::runtime_error("[ERROR] Shader is null");
	}

    if (this->texture == nullptr) {
        return new RenderableModel(model, shader, transformation, material);
    } else if (this->textures.empty()) {
        return new RenderableModel(model, shader, transformation, material, texture);
    }
	return new RenderableModel(model, shader, transformation, material, textures);
}