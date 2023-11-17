//
// Created by Honza Fojtík on 23.10.2023.
//

#include "ForestScene.h"
#include "../Include/Colors.h"
#include "../Models/tree.h"
#include "../Models/bushes.h"
#include "../Models/gift.h"
#include "../Models/skybox.h"
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
    auto multilightTexturedShader = std::shared_ptr<Shader>(ShaderBuilder()
        .setVertexShader("textured_vs.vert")
        ->setFragmentShader("multilight_textured_fs.frag")
        ->setCamera(getCamera())
    ->build());

    auto multilightShader = std::shared_ptr<Shader>(ShaderBuilder()
        .setVertexShader("vertexShader_light.vert")
        ->setFragmentShader("multilight_fs.frag")
        ->setCamera(getCamera())
    ->build());

    auto skyboxShader = std::shared_ptr<Shader>(ShaderBuilder()
        .setVertexShader("skybox_vs.vert")
        ->setFragmentShader("skybox_fs.frag")
        ->setCamera(getCamera())
        ->build());

    this->sh_shaders.push_back(multilightTexturedShader);
    this->sh_shaders.push_back(multilightShader);
    this->sh_shaders.push_back(skyboxShader);

    // Materials
    auto basicMaterial = new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 32.f, WHITE);
    auto greenMaterial = new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 32.f, LIGHTGREEN);
    this->materials.push_back(basicMaterial);

    // Lights
    auto lights = std::vector<Light*>();
//    lights.push_back(new DirLight(glm::vec3(0.f, 0.f, 0.f), WHITE, glm::vec3(0.f, -1.f, 0.f)));
    lights.push_back(new SpotLight(getCamera(), glm::vec3(0.f, 10.f, 0.f), glm::vec3(1.f), glm::vec3(0.f, 0.f, -1.f), 12.5f, 17.5f));
    setLights(lights);
    this->lights = lights;

    // Models
    this->sh_models.push_back(ModelLoader::loadModel("rat.obj"));
    this->sh_models.push_back(ModelLoader::loadModel("building.obj"));
    this->sh_models.push_back(ModelLoader::loadModel("zombie.obj"));
    this->sh_models.push_back(ModelLoader::loadModel("plane.obj"));
    this->sh_models.push_back(ModelLoader::loadModel("fish.obj"));
    this->sh_models.push_back(ModelLoader::loadModel("cat.obj"));
    this->sh_models.push_back(ModelLoader::loadModel("ferrari.obj"));

    this->models.push_back(new Model(ArrayConverter::convert(tree, sizeof(tree)), 3, 3, 0));
    this->models.push_back(new Model(ArrayConverter::convert(bushes, sizeof(bushes)), 3, 3, 0));
    this->models.push_back(new Model(ArrayConverter::convert(gift, sizeof(gift)), 3, 3, 0));
    this->models.push_back(new Model(skycube, 3, 0, 0));

    // Skybox
    auto skybox = RenderableModelBuilder()
        .setModel(models[3])
        ->setShader(skyboxShader)
        ->setMaterial(new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 32.f, WHITE))
        ->setTexture(new Texture("NightSkybox/", {"right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg"}))
        ->setTransformation(new Translation(glm::vec3(0.f, 0.f, 0.f)))
    ->build();

    setSkybox(skybox);

    for (int i = 0; i < 200; i++) {
        auto composite = new Composite();
        auto scale = new Scale(glm::vec3(getRandom(0.5, 2.0)));
        auto rotation = new Rotation(glm::vec3(0.f, 1.f, 0.f), getRandom(0.f, 360.f));
        auto translation = new Translation(glm::vec3(getRandom(-10., 10.) * 7.0f, 0.f, getRandom(-10., 5.) * 10.f));
        composite->addChild(translation);
        composite->addChild(rotation);
        composite->addChild(scale);
        this->transformations.push_back(composite);

        if (i % 3 == 0) { // Bushes
            addModel(RenderableModelBuilder()
                .setModel(models[1])
                ->setShader(multilightShader.get())
                ->setMaterial(greenMaterial)
                ->setTransformation(composite)
            ->build());
        } else { // Tree
            addModel(RenderableModelBuilder()
                .setModel(models[0])
                ->setShader(multilightShader.get())
                ->setMaterial(greenMaterial)
                ->setTransformation(composite)
            ->build());
        }
    }

    // Floor
    addModel(RenderableModelBuilder()
        .setModel(sh_models[3])
        ->setShader(multilightTexturedShader.get())
        ->setMaterial(basicMaterial)
        ->setTransformation(new Translation(glm::vec3(0.0f, -1.f, 0.0f)))
        ->setTexture(new Texture("grass.png"))
        ->setTransformation(new Scale(glm::vec3(100.f)))
    ->build());

    auto ratComp = new Composite();
    ratComp->addChild(new Translation(glm::vec3(getRandom(-10., 10.), 0.f, getRandom(-10., 10.))));
    ratComp->addChild(new Scale(glm::vec3(5.f)));

    // Rat
    addModel(RenderableModelBuilder()
        .setModel(sh_models[0])
        ->setShader(multilightTexturedShader.get())
        ->setTransformation(new BezierTranslation(glm::mat4x3(
                                                      glm::vec3(-5, 0, 0),
                                                      glm::vec3(-5, 0, 0),
                                                      glm::vec3(5, 0, 0),
                                                      glm::vec3(5, 0, 0)),
                                                  0.5f))
        ->setMaterial(basicMaterial)
        ->setTexture(new Texture("rat_diff.jpg"))
    ->build());

    // Building
    addModel(RenderableModelBuilder()
        .setModel(sh_models[1])
        ->setShader(multilightTexturedShader.get())
        ->setMaterial(basicMaterial)
        ->setTransformation(new Translation(glm::vec3(30.f, 0.f, 30.f)))
        ->setTexture(new Texture("building.png"))
    ->build());

    // Zombie
    addModel(RenderableModelBuilder()
        .setModel(sh_models[2])
        ->setShader(ShaderBuilder()
            .setVertexShader("textured_vs.vert")
            ->setFragmentShader("multilight_textured_fs.frag")
            ->setCamera(getCamera())
        ->build())
        ->setMaterial(basicMaterial)
        ->setTransformation(new Translation(glm::vec3(0.f)))
        ->setTexture(new Texture("zombie.png"))
    ->build());

    // Fish
    auto fishComp = new Composite();
    fishComp->addChild(new Translation(glm::vec3(30.f, 0.f, 18.f)));
    fishComp->addChild(new Rotation(true, glm::vec3(0.f, 1.f, 0.f), 180.f, glm::vec3(0.f)));
    fishComp->addChild(new Scale(glm::vec3(0.05f)));
    addModel(RenderableModelBuilder()
        .setModel(sh_models[5])
        ->setShader(multilightTexturedShader.get())
        ->setMaterial(basicMaterial)
        ->setTransformation(fishComp)
        ->setTexture(new Texture("cat.jpg"))
    ->build());

    // Random
    addModel(RenderableModelBuilder()
        .setModel(sh_models[6])
        ->setShader(multilightShader.get())
        ->setMaterial(basicMaterial)
        ->setTransformation(new Translation(glm::vec3(0.f)))
//        ->setTexture(new Texture("cat.jpg"))
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