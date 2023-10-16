//
// Created by Honza Fojtík on 16.10.2023.
//

#include "BallScene.h"

BallScene::BallScene(int id) : Scene(id) {
    addModel(RenderableModelBuilder(ModelKind::SPHERE)
        .setShader(ShaderBuilder()
            .setCamera(getCamera())
            ->setColor(NORMALS)
            ->setVertexShader("vertexShader_light.vert")
            ->setFragmentShader("fragmentShader_phong.frag")
            ->build())
        ->setTransformation(new Translation(glm::vec3(3.f, 0.f, 0.f)))
        ->build());

    addModel(RenderableModelBuilder(ModelKind::SPHERE)
        .setShader(ShaderBuilder()
            .setCamera(getCamera())
            ->setColor(NORMALS)
            ->setVertexShader("vertexShader_light.vert")
            ->setFragmentShader("fragmentShader_phong.frag")
            ->build())
        ->setTransformation(new Translation(glm::vec3(-3.f, 0.f, 0.f)))
        ->build());

    addModel(RenderableModelBuilder(ModelKind::SPHERE)
        .setShader(ShaderBuilder()
            .setCamera(getCamera())
            ->setColor(NORMALS)
            ->setVertexShader("vertexShader_light.vert")
            ->setFragmentShader("fragmentShader_phong.frag")
            ->build())
        ->setTransformation(new Translation(glm::vec3(0.f, -3.f, 0.f)))
        ->build());

    addModel(RenderableModelBuilder(ModelKind::SPHERE)
        .setShader(ShaderBuilder()
            .setCamera(getCamera())
            ->setColor(NORMALS)
            ->setVertexShader("vertexShader_light.vert")
            ->setFragmentShader("fragmentShader_phong.frag")
            ->build())
        ->setTransformation(new Translation(glm::vec3(0.f, 3.f, 0.f)))
        ->build());
}