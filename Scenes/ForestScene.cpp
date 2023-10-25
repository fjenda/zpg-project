//
// Created by Honza Fojtík on 23.10.2023.
//

#include "ForestScene.h"
#include "../Include/Colors.h"
#include <random>

float getRandom() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-5., 5.); // range 1 - 20

    return dis(gen);
}

ForestScene::ForestScene(int id) : Scene(id) {

    auto basicShader = ShaderBuilder()
        .setVertexShader("vertexShader_light.vert")
        ->setFragmentShader("phong_v2.frag")
        ->setCamera(getCamera())
        ->build();

    auto basicMaterial = new Material();

    auto lights = std::vector<Light*>();
    lights.push_back(new Light(glm::vec3(0.f, 10.f, 0.f), 1, glm::vec3(0.4f)));
    setLights(lights);

    for (int i = 0; i < 200; i++) {
        addModel(RenderableModelBuilder(ModelKind::TREE)
            .setShader(basicShader)
            ->setMaterial(basicMaterial)
            ->setTransformation(new Translation(glm::vec3(getRandom() * 7.0f, -2.f, getRandom() * 7.f)))
        ->build());
    }

    addModel(RenderableModelBuilder(ModelKind::PLAIN)
        .setShader(basicShader)
        ->setMaterial(basicMaterial)
        ->setTransformation(new Translation(glm::vec3(0.0f, -1.f, 0.0f)))
    ->build());


}