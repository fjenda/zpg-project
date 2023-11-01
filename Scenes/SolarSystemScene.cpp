//
// Created by Honza Fojtík on 26.10.2023.
//

#include "SolarSystemScene.h"
#include "../Include/Colors.h"

SolarSystemScene::SolarSystemScene(int id) : Scene(id) {
    // Shaders
    auto phongShader = std::shared_ptr<Shader>(ShaderBuilder()
        .setVertexShader("vertexShader_light.vert")
        ->setFragmentShader("phong_fs.frag")
        ->setCamera(getCamera())
    ->build());
    this->shaders.push_back(phongShader);

    // Materials
    auto sunMaterial = new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 32.f, YELLOW);
    this->materials.push_back(sunMaterial);

    auto greyMaterial = new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 32.f, GREY);
    this->materials.push_back(greyMaterial);

    auto orangeMaterial = new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 32.f, ORANGE);
    this->materials.push_back(orangeMaterial);

    auto blueMaterial = new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 32.f, BLUE);
    this->materials.push_back(blueMaterial);

    // Lights
    auto lights = std::vector<Light*>();
    lights.push_back(new Light(glm::vec3(0.f, 10.f, 0.f), WHITE));
    setLights(lights);
    this->lights = lights;

    // Sun
    auto sun = new Composite();
    auto sun_rot = new Composite();

    sun_rot->addChild(new Rotation(false, glm::vec3(0.f, 1.f, 0.f), 50.f, glm::vec3(0.f, 0.f, 0.f)));

    sun->addChild(sun_rot);
    sun->addChild(new Scale(glm::vec3(2.f)));

    this->transformations.push_back(sun);

    addModel(RenderableModelBuilder(ModelKind::SPHERE)
        .setShader(phongShader)
        ->setMaterial(sunMaterial)
        ->setTransformation(sun)
    ->build());

    // Mercury
    auto mercury = new Composite();
    mercury->addChild(sun_rot);
    mercury->addChild(new Translation(glm::vec3(5.f, 0.f, 0.f)));
    mercury->addChild(new Rotation(false, glm::vec3(0.f, 1.f, 0.f), 30.f, glm::vec3(0.f, 0.f, 0.f)));
    mercury->addChild(new Scale(glm::vec3(0.5f)));
    this->transformations.push_back(mercury);

    addModel(RenderableModelBuilder(ModelKind::SPHERE)
        .setShader(phongShader)
        ->setMaterial(greyMaterial)
        ->setTransformation(mercury)
    ->build());

    // Venus
    auto venus = new Composite();
    venus->addChild(new Rotation(false, glm::vec3(0.f, 1.f, 0.f), -20.f, glm::vec3(0.f, 0.f, 0.f)));
    venus->addChild(new Translation(glm::vec3(10.f, 0.f, 0.f)));
    venus->addChild(new Rotation(false, glm::vec3(0.f, 1.f, 0.f), 50.f, glm::vec3(0.f, 0.f, 0.f)));
    this->transformations.push_back(venus);

    addModel(RenderableModelBuilder(ModelKind::SPHERE)
        .setShader(phongShader)
        ->setMaterial(orangeMaterial)
        ->setTransformation(venus)
    ->build());

    // Earth
    auto earth = new Composite();
    auto earth_rot = new Composite();

    earth_rot->addChild(new Rotation(false, glm::vec3(0.f, 1.f, 0.f), 50.f, glm::vec3(0.f, 0.f, 0.f)));

    earth->addChild(new Rotation(false, glm::vec3(0.f, 1.f, 0.f), 35.f, glm::vec3(0.f, 0.f, 0.f)));
    earth->addChild(new Translation(glm::vec3(15.f, 0.f, 0.f)));
    earth->addChild(earth_rot);
    this->transformations.push_back(earth_rot);
    this->transformations.push_back(earth);

    addModel(RenderableModelBuilder(ModelKind::SPHERE)
        .setShader(phongShader)
        ->setMaterial(blueMaterial)
        ->setTransformation(earth)
    ->build());

    // Moon
    auto moon = new Composite();

    moon->addChild(earth);
    moon->addChild(new Translation(glm::vec3(2.f, 0.f, 0.f)));
    moon->addChild(new Scale(glm::vec3(0.5f)));
    this->transformations.push_back(moon);

    addModel(RenderableModelBuilder(ModelKind::SPHERE)
        .setShader(phongShader)
        ->setMaterial(greyMaterial)
        ->setTransformation(moon)
    ->build());

    // Mars
    auto mars = new Composite();
    auto mars_rot = new Composite();

    mars_rot->addChild(new Rotation(false, glm::vec3(0.f, 1.f, 0.f), 50.f, glm::vec3(0.f, 0.f, 0.f)));

    mars->addChild(new Rotation(false, glm::vec3(0.f, 1.f, 0.f), 50.f, glm::vec3(0.f, 0.f, 0.f)));
    mars->addChild(new Translation(glm::vec3(20.f, 0.f, 0.f)));
    mars->addChild(mars_rot);
    mars->addChild(new Scale(glm::vec3(0.8f)));
    this->transformations.push_back(mars_rot);
    this->transformations.push_back(mars);

    addModel(RenderableModelBuilder(ModelKind::SPHERE)
        .setShader(phongShader)
        ->setMaterial(orangeMaterial)
        ->setTransformation(mars)
    ->build());

    // Mars moon 1
    auto mars_moon1 = new Composite();

//    mars_moon1->addChild(new Rotation(false, glm::vec3(0.f, 1.f, 0.f), 50.f, glm::vec3(0.f, 0.f, 0.f)));
//    mars_moon1->addChild(new Translation(glm::vec3(20.f, 0.f, 0.f)));
//    mars_moon1->addChild(mars_rot);
    mars_moon1->addChild(mars);
    mars_moon1->addChild(new Scale(glm::vec3(1.2f)));
    mars_moon1->addChild(new Translation(glm::vec3(2.f, 0.f, 0.f)));
    mars_moon1->addChild(new Scale(glm::vec3(0.5f)));
    this->transformations.push_back(mars_moon1);

    addModel(RenderableModelBuilder(ModelKind::SPHERE)
        .setShader(phongShader)
        ->setMaterial(greyMaterial)
        ->setTransformation(mars_moon1)
    ->build());

    // Mars moon 2
    auto mars_moon2 = new Composite();

//    mars_moon2->addChild(new Rotation(false, glm::vec3(0.f, 1.f, 0.f), 50.f, glm::vec3(0.f, 0.f, 0.f)));
//    mars_moon2->addChild(new Translation(glm::vec3(20.f, 0.f, 0.f)));
//    mars_moon2->addChild(mars_rot);
    mars_moon2->addChild(mars);
    mars_moon2->addChild(new Scale(glm::vec3(1.2f)));
    mars_moon2->addChild(new Translation(glm::vec3(-2.f, 0.f, 0.f)));
    mars_moon2->addChild(new Scale(glm::vec3(0.5f)));
    this->transformations.push_back(mars_moon2);

    addModel(RenderableModelBuilder(ModelKind::SPHERE)
        .setShader(phongShader)
        ->setMaterial(greyMaterial)
        ->setTransformation(mars_moon2)
    ->build());
}

SolarSystemScene::~SolarSystemScene() {
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