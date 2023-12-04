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
//    this->lights.push_back(new DirLight(glm::vec3(0.f, 0.f, 0.f), WHITE, glm::vec3(0.f, -1.f, 0.f)));
    this->lights.push_back(new SpotLight(getCamera(), glm::vec3(0.f, 10.f, 0.f), glm::vec3(1.f), glm::vec3(0.f, 0.f, -1.f), 12.5f, 17.5f));
    this->lights.push_back(new PointLight(glm::vec3(10.f, 5.f, 0.f), WHITE));

    setLights(this->lights);

    // Models
    this->sh_models.push_back(ModelLoader::loadModel("rat.obj"));
    this->sh_models.push_back(ModelLoader::loadModel("building.obj"));
    this->sh_models.push_back(ModelLoader::loadModel("zombie.obj"));
    this->sh_models.push_back(ModelLoader::loadModel("plane.obj"));
    this->sh_models.push_back(ModelLoader::loadModel("fish.obj"));
    this->sh_models.push_back(ModelLoader::loadModel("cat.obj"));
    this->sh_models.push_back(ModelLoader::loadModel("ferrari.obj"));
    this->sh_models.push_back(ModelLoader::loadModel("tree.obj"));
    this->sh_models.push_back(ModelLoader::loadModel("terrain.obj"));
    this->sh_models.push_back(ModelLoader::loadModel("circle_wall.obj"));

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

    for (int i = 0; i < 100; i++) {
        if (i % 3 == 0) { // Bushes
            auto composite = new Composite();
            auto translation = new Translation(glm::vec3(getRandom(-10., 10.) * 7.0f, 0.f, getRandom(-10., 5.) * 10.f));
            auto rotation = new Rotation(glm::vec3(0.f, 1.f, 0.f), getRandom(0.f, 360.f));
            auto scale = new Scale(glm::vec3(getRandom(1., 2.5)));
            composite->addChild(translation);
            composite->addChild(rotation);
            composite->addChild(scale);
            this->transformations.push_back(composite);

            addModel(RenderableModelBuilder()
                .setModel(models[1])
                ->setShader(multilightShader.get())
                ->setMaterial(greenMaterial)
                ->setTransformation(composite)
                ->setRemovable(true)
            ->build());
        } else { // Tree
            auto composite = new Composite();
            auto translation = new Translation(glm::vec3(getRandom(5., 10.) * 7.0f, 0.f, getRandom(-10., 5.) * 10.f));
            auto rotation = new Rotation(glm::vec3(0.f, 1.f, 0.f), getRandom(0.f, 360.f));
            auto scale = new Scale(glm::vec3(getRandom(0.5, 1.)));
            composite->addChild(translation);
            composite->addChild(rotation);
            composite->addChild(scale);
            this->transformations.push_back(composite);

            addModel(RenderableModelBuilder()
                .setModel(sh_models[7])
                ->setShader(multilightTexturedShader.get())
                ->setMaterial(greenMaterial)
                ->setTexture(new Texture("tree.png"))
                ->setTransformation(composite)
                ->setRemovable(true)
            ->build());
        }
    }

    // Floor
    addModel(RenderableModelBuilder()
        .setModel(sh_models[8])
        ->setShader(multilightTexturedShader.get())
        ->setMaterial(basicMaterial)
        ->setTransformation(new Translation(glm::vec3(0.0f, -1.f, 0.0f)))
        ->setTexture(new Texture("grass.png"))
        ->setTransformation(new Scale(glm::vec3(0.7f)))
    ->build());

    auto ratComp = new Composite();
    ratComp->addChild(new Translation(glm::vec3(9.f, 0.f, 10.f)));
    ratComp->addChild(new Scale(glm::vec3(1.f)));

    // Rat
    addModel(RenderableModelBuilder()
        .setModel(sh_models[0])
        ->setShader(multilightTexturedShader.get())
        ->setTransformation(ratComp)
        ->setMaterial(basicMaterial)
        ->setTexture(new Texture("rat_diff.jpg"))
        ->setRemovable(true)
    ->build());

    // Building
    auto buildComp = new Composite();
    buildComp->addChild(new Translation(glm::vec3(10.f, 0.f, 0.f)));
    buildComp->addChild(new Scale(glm::vec3(0.5f)));
    addModel(RenderableModelBuilder()
        .setModel(sh_models[1])
        ->setShader(multilightTexturedShader.get())
        ->setMaterial(basicMaterial)
        ->setTransformation(buildComp)
        ->setTexture(new Texture("building.png"))
    ->build());

    // Zombie
    auto zombieComp = new Composite();
    zombieComp->addChild(new Translation(glm::vec3(8.f, 0.f, 10.f)));
    zombieComp->addChild(new Scale(glm::vec3(0.5f)));
    addModel(RenderableModelBuilder()
        .setModel(sh_models[2])
        ->setShader(ShaderBuilder()
            .setVertexShader("textured_vs.vert")
            ->setFragmentShader("multilight_textured_fs.frag")
            ->setCamera(getCamera())
        ->build())
        ->setMaterial(basicMaterial)
        ->setTransformation(zombieComp)
        ->setTexture(new Texture("zombie.png"))
        ->setRemovable(true)
    ->build());

    // Cat
    auto catComp = new Composite();
    catComp->addChild(new Translation(glm::vec3(10.f, 0.f, 10.f)));
    catComp->addChild(new Scale(glm::vec3(0.05f)));
    addModel(RenderableModelBuilder()
        .setModel(sh_models[5])
        ->setShader(multilightTexturedShader.get())
        ->setMaterial(basicMaterial)
        ->setTransformation(catComp)
        ->setTexture(new Texture("cat.jpg"))
        ->setRemovable(true)
    ->build());

    // Car
    auto carComp = new Composite();
    carComp->addChild(new Translation(glm::vec3(9.f, 0.f, 10.f)));
//    carComp->addChild(new BezierTranslation(glm::mat4x3(
//        glm::vec3(-3, 1, 0),
//        glm::vec3(-3, 4, 0),
//        glm::vec3(3, 4, 0),
//        glm::vec3(3, 1, 0)),
//    2.f));
//    carComp->addChild(new Rotation(false, glm::vec3(1.f, 1.f, 1.f), 360.f, glm::vec3(0.f)));
//    carComp->addChild(new LineTranslation(glm::vec3(0.f, 10.f, 0.f), glm::vec3(0.f, 10.f, 10.f), 1.f));

//    auto linePoints = std::vector<glm::vec3>();
//    linePoints.push_back(glm::vec3(-5.f, 5.f, 0.f));
//    linePoints.push_back(glm::vec3(5.f, 5.f, 0.f));
//    linePoints.push_back(glm::vec3(5.f, 10.f, 0.f));
//    linePoints.push_back(glm::vec3(-5.f, 10.f, 0.f));
//
//    carComp->addChild(new LineTranslation(linePoints, 0.5f));

    auto bezierPoints = std::vector<glm::mat4>();
    bezierPoints.push_back(glm::mat4x3(
        glm::vec3(-5, 20, 0),
        glm::vec3(0, 25, 0),
        glm::vec3(5, 25, 0),
        glm::vec3(10, 20, 0)));

    bezierPoints.push_back(glm::mat4x3(
        glm::vec3(10, 20, 0),
        glm::vec3(5, 15, 0),
        glm::vec3(5, 10, 0),
        glm::vec3(10, 5, 0)));

    bezierPoints.push_back(glm::mat4x3(
        glm::vec3(10, 5, 0),
        glm::vec3(5, 0, 0),
        glm::vec3(0, 0, 0),
        glm::vec3(-5, 5, 0)));

    carComp->addChild(new BezierTranslation(bezierPoints, 0.5f));
    carComp->addChild(new Translation(glm::vec3(0.f, 5.f, 0.f)));
    carComp->addChild(new Scale(glm::vec3(0.5f)));

    addModel(RenderableModelBuilder()
        .setModel(sh_models[6])
        ->setShader(multilightTexturedShader.get())
        ->setMaterial(basicMaterial)
        ->setTransformation(carComp)
        ->setTexture(new Texture("ferrari.png"))
        ->setRemovable(true)
    ->build());

    // Circle wall
    auto wallComp = new Composite();
    wallComp->addChild(new Translation(glm::vec3(10.f, 0.f, 0.f)));
    wallComp->addChild(new Rotation(glm::vec3(0.f, 1.f, 0.f), -15.f));
    addModel(RenderableModelBuilder()
        .setModel(sh_models[9])
        ->setShader(multilightTexturedShader.get())
        ->setMaterial(basicMaterial)
        ->setTransformation(wallComp)
        ->setTexture(new Texture("bake.png"))
    ->build());

    // Model for bezier testing
    addModel(RenderableModelBuilder()
        .setModel(sh_models[4])
        ->setShader(multilightTexturedShader.get())
        ->setMaterial(basicMaterial)
        ->setTransformation(new Translation(glm::vec3(0.f, 2.f, 0.f)))
        ->setTexture(new Texture("fish_texture.png"))
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