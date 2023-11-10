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
#include "../Models/skybox.h"
#include <random>

float getRandom(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);

    return dis(gen);
}

ForestScene::ForestScene(int id) : Scene(id) {

    // Shaders
//    auto phongShader = std::shared_ptr<Shader>(ShaderBuilder()
//        .setVertexShader("vertexShader_light.vert")
//        ->setFragmentShader("phong_fs.frag")
//        ->setCamera(getCamera())
//    ->build());
//
//    auto lambertShader = std::shared_ptr<Shader>(ShaderBuilder()
//        .setVertexShader("vertexShader_light.vert")
//        ->setFragmentShader("lambert_fs.frag")
//        ->setCamera(getCamera())
//    ->build());
//
//    auto constantShader = std::shared_ptr<Shader>(ShaderBuilder()
//        .setVertexShader("vertexShader_light.vert")
//        ->setFragmentShader("constant_fs.frag")
//        ->setCamera(getCamera())
//    ->build());
//
    auto skyboxShader = std::shared_ptr<Shader>(ShaderBuilder()
        .setVertexShader("skybox_vs.vert")
        ->setFragmentShader("skybox_fs.frag")
        ->setCamera(getCamera())
        ->build());

//    this->sh_shaders.push_back(phongShader);
//    this->sh_shaders.push_back(lambertShader);
//    this->sh_shaders.push_back(constantShader);
    this->sh_shaders.push_back(skyboxShader);

    auto multiLightShader = std::shared_ptr<Shader>(ShaderBuilder()
        .setVertexShader("vertexShader_light.vert")
        ->setFragmentShader("multilight_fs.frag")
        ->setCamera(getCamera())
    ->build());

    this->sh_shaders.push_back(multiLightShader);

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
//    lights.push_back(new DirLight(glm::vec3(0.f, 10.f, 0.f), WHITE, glm::vec3(0.f, -1.f, 0.f)));
    lights.push_back(new SpotLight(getCamera(), glm::vec3(0.f, 10.f, 0.f), glm::vec3(1.f), glm::vec3(0.f, 0.f, -1.f), 12.5f, 17.5f));
    setLights(lights);
    this->lights = lights;

    // Models
    this->sh_models.push_back(ModelLoader::loadModel("tree.obj"));
    this->sh_models.push_back(ModelLoader::loadModel("suzi_hq.obj"));
    this->sh_models.push_back(ModelLoader::loadModel("rat.obj"));
    this->models.push_back(new Model(ArrayConverter::convert(tree, sizeof(tree)), 3, 3, 0));
    this->models.push_back(new Model(ArrayConverter::convert(bushes, sizeof(bushes)), 3, 3, 0));
    this->models.push_back(new Model(ArrayConverter::convert(gift, sizeof(gift)), 3, 3, 0));
    this->models.push_back(new Model(ArrayConverter::convert(sphere, sizeof(sphere)), 3, 3, 0));

    // Skybox
    auto skybox = RenderableModelBuilder()
        .setModel(new Model(skycube, 3, 0, 0))
        ->setShader(skyboxShader)
        ->setMaterial(new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 32.f, WHITE))
        ->setTexture(new Texture("NightSkybox/", {"right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg"}))
        ->setTransformation(new Translation(glm::vec3(0.f, 0.f, 0.f)))
        ->build();

    setSkybox(skybox);

    for (int i = 0; i < 300; i++) {
        auto composite = new Composite();
        auto scale = new Scale(glm::vec3(getRandom(0.5, 2.0)));
        auto rotation = new Rotation(glm::vec3(0.f, 1.f, 0.f), getRandom(0.f, 360.f));
        auto translation = new Translation(glm::vec3(getRandom(-10., 10.) * 7.0f, 0.f, getRandom(-10., 5.) * 10.f));
        composite->addChild(translation);
        composite->addChild(rotation);
        composite->addChild(scale);
        this->transformations.push_back(composite);

//        if (i % 3 == 0) { // Bushes
//            addModel(RenderableModelBuilder()
//                .setModel(models[1])
//                ->setShader(phongShader.get())
//                ->setMaterial(greenMaterial)
//                ->setTransformation(composite)
//            ->build());
//        } else if (i % 10 == 0) { // Gift
//            addModel(RenderableModelBuilder()
//                .setModel(models[2])
//                ->setShader(phongShader.get())
//                ->setMaterial(redMaterial)
//                ->setTransformation(composite)
//            ->build());
//        } else if (i % 7 == 0) { // Suzi HQ
//            auto position = new Translation(glm::vec3(getRandom(-10., 10.) * 7.0f, 2.f, getRandom(-10., 5.) * 10.f));
//
//            auto composite2 = new Composite();
//            composite2->addChild(position);
//            composite2->addChild(rotation);
//            composite2->addChild(scale);
//            addModel(RenderableModelBuilder()
//                .setModel(sh_models[1])
//                ->setShader(lambertShader.get())
//                ->setMaterial(blueMaterial)
//                ->setTransformation(composite2)
//            ->build());
//        } else if (i % 4 == 0) { // Sphere
//            addModel(RenderableModelBuilder()
//                .setModel(models[3])
//                ->setShader(constantShader.get())
//                ->setMaterial(yellowMaterial)
//                ->setTransformation(composite)
//            ->build());
//        } else { // Tree
//            addModel(RenderableModelBuilder()
//                .setModel(models[0])
//                ->setShader(phongShader.get())
//                ->setMaterial(greenMaterial)
//                ->setTransformation(composite)
//            ->build());
//        }

        addModel(RenderableModelBuilder()
            .setModel(models[0])
            ->setShader(multiLightShader)
            ->setMaterial(greenMaterial)
            ->setTransformation(composite)
        ->build());
    }

    addModel(RenderableModelBuilder(ModelKind::PLAIN_TEXTURED)
        .setShader(ShaderBuilder()
                .setVertexShader("textured_vs.vert")
                ->setFragmentShader("multilight_textured_fs.frag")
                ->setCamera(getCamera())
            ->build())
        ->setMaterial(basicMaterial)
        ->setTransformation(new Translation(glm::vec3(0.0f, -1.f, 0.0f)))
        ->setTexture(new Texture("grass.png"))
        ->setTransformation(new Scale(glm::vec3(100.f)))
    ->build());

    auto ratComp = new Composite();
    ratComp->addChild(new Translation(glm::vec3(getRandom(-10., 10.), 0.f, getRandom(-10., 10.))));
    ratComp->addChild(new Scale(glm::vec3(5.f)));

    addModel(RenderableModelBuilder()
        .setModel(sh_models[2])
        ->setShader(ShaderBuilder()
            .setVertexShader("textured_vs.vert")
            ->setFragmentShader("multilight_textured_fs.frag")
            ->setCamera(getCamera())
            ->build())
        ->setTransformation(ratComp)
        ->setMaterial(basicMaterial)
        ->setTexture(new Texture("rat_diff.jpg"))
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