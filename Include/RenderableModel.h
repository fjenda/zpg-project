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
#include "BezierTranslation.h"
#include "LineTranslation.h"
#include "Material.h"
#include "Texture.h"

#include <vector>

class RenderableModel {

private:
	Model* model;
	Shader* shader;
	Transformation* transformations;
    Material* material;
    Texture* texture;
    std::vector<Texture*> textures;

    std::string name;
    bool removable;

    float deltaTime;
    float lastFrame = 0.0f;
    bool firstInit = true;

public:
    RenderableModel(Model* model, Shader* shader, Transformation* transformation, Material* material, std::string name, bool removable);
    RenderableModel(Model* model, Shader* shader, Transformation* transformation, Material* material, Texture* texture, std::string name, bool removable);
    RenderableModel(Model* model, Shader* shader, Transformation* transformation, Material* material, std::vector<Texture*> textures, std::string name, bool removable);

	void render();

    void setShaderLight(std::vector<Light*> l);
    bool isRemovable() { return this->removable; };
    std::string getName() { return this->name; };
    void setTransformation(Transformation* transformation) { this->transformations = transformation; };

	void infoLog();
    void enableDebugInterface(int id);
};

class RenderableModelBuilder {

private:
	Model* model;
	Shader* shader;
	Transformation* transformation;
    Material* material;
    Texture* texture = nullptr;
    std::vector<Texture*> textures;
	std::vector<float> points;
    std::string name = "";
    bool removable = false;
	
public:
    RenderableModelBuilder() = default;

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
    RenderableModelBuilder* setTexture(std::shared_ptr<Texture> texture);

    RenderableModelBuilder* setModel(Model* model);
    RenderableModelBuilder* setShader(Shader* shader);
	RenderableModelBuilder* setTransformation(Transformation * transformation);
    RenderableModelBuilder* setMaterial(Material* material);
    RenderableModelBuilder* setTexture(Texture* texture);
    RenderableModelBuilder* setTextures(std::vector<Texture*> textures);
    RenderableModelBuilder* setName(std::string name);
    RenderableModelBuilder* setRemovable(bool removable);

	RenderableModel* build();	
};
	
#endif