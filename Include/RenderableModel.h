/**
 * @file RenderableModel.h
 *
 * @brief Class for renderable models
 *
 * @details This class is used for rendering models. It contains
 *          model, shader and transformation. It also contains
 *          methods for rendering and ticking.
 *
 * @author Jan Fojtik
 *
 * @year 2023
 **/

#ifndef RENDERABLEMODEL_H
#define RENDERABLEMODEL_H

#include "Model.h"
#include "Shader.h"
#include "ModelKind.h"
#include "Transformation.h"
#include "Composite.h"
#include "Rotation.h"
#include "Scale.h"
#include "Translation.h"
#include "Material.h"

#include <vector>

class RenderableModel {

private:
	Model* model;
	Shader* shader;
	Transformation* transformations;
    Material* material;

    float deltaTime;
    float lastFrame = 0.0f;
    bool firstInit = true;

public:
    RenderableModel(Model* model, Shader* shader, Transformation* transformation, Material* material);

	void render();

    void setShaderLight(std::vector<Light*> l);

	void infoLog();
    void enableDebugInterface(int id);
};

class RenderableModelBuilder {

private:
	Model* model;
	Shader* shader;
	Transformation* transformation;
    Material* material;
	std::vector<float> points;
	
public:
    RenderableModelBuilder() = default;

    //loading through file
    explicit RenderableModelBuilder(const std::string& pFile);

    //loading through kind
	explicit RenderableModelBuilder(ModelKind kind);

    //loading through points (VBO + simulated EBO)
	explicit RenderableModelBuilder(std::vector<float> points);

    //loading through points and indices (VBO + EBO)
	RenderableModelBuilder(std::vector<float> points, std::vector<int> indices);

    RenderableModelBuilder* setModel(std::shared_ptr<Model> model);
    RenderableModelBuilder* setShader(std::shared_ptr<Shader> shader);
    RenderableModelBuilder* setTransformation(std::shared_ptr<Transformation> transformation);
    RenderableModelBuilder* setMaterial(std::shared_ptr<Material> material);

    RenderableModelBuilder* setModel(Model* model);
    RenderableModelBuilder* setShader(Shader* shader);
	RenderableModelBuilder* setTransformation(Transformation * transformation);
    RenderableModelBuilder* setMaterial(Material* material);
	RenderableModel* build();	
};
	
#endif