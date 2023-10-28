//
// Created by Honza Fojtík on 23.10.2023.
//

#include "ForestScene.h"
#include "../Include/Colors.h"
#include <random>

float getRandom(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);

    return dis(gen);
}

ForestScene::ForestScene(int id) : Scene(id) {

    auto phongShader = std::make_shared<Shader*>(ShaderBuilder()
        .setVertexShader("vertexShader_light.vert")
        ->setFragmentShader("phong_fs.frag")
        ->setCamera(getCamera())
        ->build());

    auto basicMaterial = new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 32.f, GREEN);
    this->materials.push_back(basicMaterial);

    auto lights = std::vector<Light*>();
    lights.push_back(new Light(glm::vec3(0.f, 10.f, 0.f), 1, glm::vec3(1.f)));
    setLights(lights);
    this->lights = lights;

    for (int i = 0; i < 200; i++) {
        auto composite = new Composite();
        auto scale = new Scale(glm::vec3(getRandom(0.5, 2.0)));
        auto rotation = new Rotation(glm::vec3(0.f, 1.f, 0.f), getRandom(0.f, 360.f));
        auto translation = new Translation(glm::vec3(getRandom(-5., 5.) * 7.0f, -1.f, getRandom(-5., 5.) * 7.f));
        composite->addChild(translation);
        composite->addChild(rotation);
        composite->addChild(scale);
        this->transformations.push_back(composite);

        ModelKind modelKind = ModelKind::TREE;
        if (i % 3 == 0)
            modelKind = ModelKind::BUSHES;
        else
            modelKind = ModelKind::TREE;

        addModel(RenderableModelBuilder(modelKind)
            .setShader(phongShader)
            ->setMaterial(basicMaterial)
            ->setTransformation(composite)
        ->build());
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
}