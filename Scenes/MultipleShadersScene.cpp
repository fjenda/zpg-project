//
// Created by Honza Fojtík on 05.12.2023.
//

#include "MultipleShadersScene.h"

MultipleShadersScene::MultipleShadersScene(int id) : Scene(id) {
    std::vector<Light*> sceneLights;
    sceneLights.push_back(new Light(glm::vec3(0.f), glm::vec3(1.f)));
    setLights(sceneLights);

    auto basicMaterial = new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 32.f, glm::vec3(0.385, 0.647, 0.812));

    addModel(RenderableModelBuilder(ModelKind::SUZI_SMOOTH)
    .setShader(ShaderBuilder()
        .setCamera(getCamera())
        ->setVertexShader("vertexShader_light.vert")
        ->setFragmentShader("constant_fs.frag")
        ->build())
    ->setTransformation(new Translation(glm::vec3(3.f, 0.f, 0.f)))
    ->setMaterial(basicMaterial)
    ->build());

    addModel(RenderableModelBuilder(ModelKind::SUZI)
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
        ->setFragmentShader("lambert_fs.frag")
        ->build())
    ->setTransformation(new Translation(glm::vec3(0.f, -3.f, 0.f)))
    ->setMaterial(basicMaterial)
    ->build());

    addModel(RenderableModelBuilder(ModelKind::SPHERE)
    .setShader(ShaderBuilder()
        .setCamera(getCamera())
        ->setVertexShader("vertexShader_light.vert")
        ->setFragmentShader("blinn_fs.frag")
        ->build())
    ->setTransformation(new Translation(glm::vec3(0.f, 3.f, 0.f)))
    ->setMaterial(basicMaterial)
    ->build());
}