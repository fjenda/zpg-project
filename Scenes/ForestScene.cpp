//
// Created by Honza Fojtík on 23.10.2023.
//

#include "ForestScene.h"
#include "../Include/Colors.h"
#include "../Models/tree.h"
#include "../Models/bushes.h"
#include "../Models/gift.h"
#include "../Models/sphere.h"
#include "../Include/ModelLoader.h"
#include "../Include/ArrayConverter.h"
#include <random>

float getRandom(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);

    return dis(gen);
}

ForestScene::ForestScene(int id) : Scene(id) {

    // Shaders
    auto phongShader = std::shared_ptr<Shader>(ShaderBuilder()
        .setVertexShader("vertexShader_light.vert")
        ->setFragmentShader("phong_fs.frag")
        ->setCamera(getCamera())
    ->build());

    auto lambertShader = std::shared_ptr<Shader>(ShaderBuilder()
        .setVertexShader("vertexShader_light.vert")
        ->setFragmentShader("lambert_fs.frag")
        ->setCamera(getCamera())
    ->build());

    auto constantShader = std::shared_ptr<Shader>(ShaderBuilder()
        .setVertexShader("vertexShader_light.vert")
        ->setFragmentShader("constant_fs.frag")
        ->setCamera(getCamera())
    ->build());
    this->sh_shaders.push_back(phongShader);
    this->sh_shaders.push_back(lambertShader);
    this->sh_shaders.push_back(constantShader);

    // Materials
    auto basicMaterial = new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 32.f, WHITE);
    auto redMaterial = new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 32.f, RED);
    auto greenMaterial = new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 32.f, GREEN);
    auto blueMaterial = new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 32.f, BLUE);
    auto yellowMaterial = new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 32.f, YELLOW);
    this->materials.push_back(basicMaterial);
    this->materials.push_back(redMaterial);
    this->materials.push_back(greenMaterial);
    this->materials.push_back(blueMaterial);
    this->materials.push_back(yellowMaterial);

    // Lights
    auto lights = std::vector<Light*>();
    lights.push_back(new Light(glm::vec3(0.f, 10.f, 0.f), 1, glm::vec3(1.f)));
    setLights(lights);
    this->lights = lights;

    // Models
    this->sh_models.push_back(ModelLoader::loadModel("tree.obj"));
    this->sh_models.push_back(ModelLoader::loadModel("suzi_hq.obj"));
    this->models.push_back(new Model(ArrayConverter::convert(tree, sizeof(tree))));
    this->models.push_back(new Model(ArrayConverter::convert(bushes, sizeof(bushes))));
    this->models.push_back(new Model(ArrayConverter::convert(gift, sizeof(gift))));
    this->models.push_back(new Model(ArrayConverter::convert(sphere, sizeof(sphere))));

    for (int i = 0; i < 700; i++) {
        auto composite = new Composite();
        auto scale = new Scale(glm::vec3(getRandom(0.5, 2.0)));
        auto rotation = new Rotation(glm::vec3(0.f, 1.f, 0.f), getRandom(0.f, 360.f));
        auto translation = new Translation(glm::vec3(getRandom(-10., 10.) * 7.0f, -1.f, getRandom(-10., 5.) * 10.f));
        composite->addChild(translation);
        composite->addChild(rotation);
        composite->addChild(scale);
        this->transformations.push_back(composite);

        if (i % 3 == 0) { // Bushes
            addModel(RenderableModelBuilder()
                .setModel(models[1])
                ->setShader(phongShader.get())
                ->setMaterial(greenMaterial)
                ->setTransformation(composite)
            ->build());
        } else if (i % 10 == 0) { // Gift
            addModel(RenderableModelBuilder()
                .setModel(models[2])
                ->setShader(phongShader.get())
                ->setMaterial(redMaterial)
                ->setTransformation(composite)
            ->build());
        } else if (i % 7 == 0) { // Suzi HQ
            addModel(RenderableModelBuilder()
                .setModel(sh_models[1])
                ->setShader(lambertShader.get())
                ->setMaterial(blueMaterial)
                ->setTransformation(composite)
            ->build());
        } else if (i % 4 == 0) { // Sphere
            addModel(RenderableModelBuilder()
                .setModel(models[3])
                ->setShader(constantShader.get())
                ->setMaterial(yellowMaterial)
                ->setTransformation(composite)
            ->build());
        } else { // Tree
            addModel(RenderableModelBuilder()
                .setModel(models[0])
                ->setShader(phongShader.get())
                ->setMaterial(greenMaterial)
                ->setTransformation(composite)
            ->build());
        }
    }

    addModel(RenderableModelBuilder(ModelKind::PLAIN)
        .setShader(phongShader)
        ->setMaterial(basicMaterial)
        ->setTransformation(new Translation(glm::vec3(0.0f, -1.f, 0.0f)))
    ->build());
}

ForestScene::~ForestScene() {
    for (auto transformation : this->transformations) {
        delete transformation;
    }
    for (auto material : this->materials) {
        delete material;
    }
    for (auto light : this->lights) {
        delete light;
    }

    for (auto model : this->models) {
        delete model;
    }
}