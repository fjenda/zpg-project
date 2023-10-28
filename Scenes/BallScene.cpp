//
// Created by Honza Fojtík on 16.10.2023.
//

#include "BallScene.h"
#include "../Include/ModelLoader.h"

BallScene::BallScene(int id) : Scene(id) {
    std::vector<Light*> sceneLights;
    sceneLights.push_back(new Light(glm::vec3(0.f), 1, glm::vec3(1.f)));
    setLights(sceneLights);

    auto basicMaterial = new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 32.f, glm::vec3(0.385, 0.647, 0.812));

    addModel(RenderableModelBuilder(ModelKind::SPHERE)
        .setShader(ShaderBuilder()
            .setCamera(getCamera())
            ->setVertexShader("vertexShader_light.vert")
            ->setFragmentShader("phong_fs.frag")
            ->build())
        ->setTransformation(new Translation(glm::vec3(3.f, 0.f, 0.f)))
        ->setMaterial(basicMaterial)
        ->build());

    addModel(RenderableModelBuilder(ModelKind::SPHERE)
        .setShader(ShaderBuilder()
            .setCamera(getCamera())
            ->setVertexShader("vertexShader_light.vert")
            ->setFragmentShader("phong_fs.frag")
            ->build())
        ->setTransformation(new Translation(glm::vec3(-3.f, 0.f, 0.f)))
        ->setMaterial(basicMaterial)
        ->build());

    addModel(RenderableModelBuilder(ModelKind::SPHERE)
        .setShader(ShaderBuilder()
            .setCamera(getCamera())
            ->setVertexShader("vertexShader_light.vert")
            ->setFragmentShader("phong_fs.frag")
            ->build())
        ->setTransformation(new Translation(glm::vec3(0.f, -3.f, 0.f)))
        ->setMaterial(basicMaterial)
        ->build());

    addModel(RenderableModelBuilder(ModelKind::SPHERE)
        .setShader(ShaderBuilder()
            .setCamera(getCamera())
            ->setVertexShader("vertexShader_light.vert")
            ->setFragmentShader("phong_fs.frag")
            ->build())
        ->setTransformation(new Translation(glm::vec3(0.f, 3.f, 0.f)))
        ->setMaterial(basicMaterial)
        ->build());
}