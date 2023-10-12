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

#include <vector>

class RenderableModel {

private:
	Model* model;
	Shader* shader;
	Transformation* transformations;

    float deltaTime;
    float lastFrame = 0.0f;

public:
    RenderableModel(Model* model, Shader* shader, Transformation* transformation);
//    explicit RenderableModel(std::vector<float> points);
//    explicit RenderableModel(ModelKind kind);
	~RenderableModel();

	void render();
    void tick();

	void infoLog();
};

class RenderableModelBuilder {

private:
	Model* model;
	Shader* shader;
	Transformation* transformation;
	std::vector<float> points;
	
public:
    //loading through file
    explicit RenderableModelBuilder(const std::string& pFile);

    //loading through kind
	explicit RenderableModelBuilder(ModelKind kind);

    //loading through points (VBO + simulated EBO)
	explicit RenderableModelBuilder(std::vector<float> points);

    //loading through points and indices (VBO + EBO)
	RenderableModelBuilder(std::vector<float> points, std::vector<int> indices);

	RenderableModelBuilder* setShader(Shader * shader);
	RenderableModelBuilder* setTransformation(Transformation * transformation);
	RenderableModel* build();	
};
	
#endif