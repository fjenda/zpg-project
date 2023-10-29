// Jan Fojtík
// FOJ0127

//Include the standard C++ headers
#include <stdlib.h>
#include <stdio.h>

// Include chrono for time measurement
#include <chrono>

#include "Include/Application.h"
#include "Include/Colors.h"
#include "Scenes/BallScene.h"
#include "Scenes/ForestScene.h"
#include "Scenes/SolarSystemScene.h"

int main(void)
{
	// get start time
	auto start = std::chrono::high_resolution_clock::now();

    Application& app = Application::get();
    app.initialization(1280, 720);

    // Scene 1 automatically created
    app.addScene(new BallScene(2));  // Scene 2 - Ball scene
    app.createScene();  // Scene 3 - Phong shader scene
    app.createScene();  // Scene 4 - Multiple shaders scene
    app.addScene(new ForestScene(5)); // Scene 5 - Forest scene
    app.addScene(new SolarSystemScene(6)); // Scene 6 - Solar system scene
    // Scene # = press number to switch to desired scene

    auto floorTransform = new Composite();
    floorTransform->addChild(new Translation(glm::vec3(0.f, -1.f, 1.f)));
    floorTransform->addChild(new Scale(glm::vec3(3.f, 3.f, 3.f)));

    auto sc1Transform = new Composite();
//    sc1Transform->addChild(new Rotation(glm::vec3(0.f, 0.f, 1.f), 180.f));
    sc1Transform->addChild(new Scale(glm::vec3(0.8f)));
    sc1Transform->addChild(new Translation(glm::vec3(5.f, 5.0f, 0.f)));
    sc1Transform->addChild(new Rotation(false, glm::vec3(0.f, 1.f, 0.f), 100.f, glm::vec3(0.f, 0.f, 0.f)));

    auto sc1Transform2 = new Composite();
    sc1Transform2->addChild(new Rotation(glm::vec3(0.f, 0.f, 1.f), 180.f));
    sc1Transform2->addChild(new Scale(glm::vec3(1.8f)));
    sc1Transform2->addChild(new Translation(glm::vec3(1.f, -0.5f, 0.f)));
    sc1Transform2->addChild(sc1Transform);

    auto centerTransform = new Composite();
    centerTransform->addChild(new Translation(glm::vec3(0.f, 0.f, 0.f)));

    // Material
    auto blueMaterial = new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 32.f, glm::vec3(0.385, 0.647, 0.812));

    // Light
    auto sc1_lights = std::vector<Light*>();
    sc1_lights.push_back(new Light(glm::vec3(0.f, 10.f, 0.f), 1, glm::vec3(1.f)));
    app.getSceneById(1)->setLights(sc1_lights);

    // Scene 1
    auto objsLoaded = std::vector<std::shared_ptr<Model>>();
    objsLoaded.push_back(ModelLoader::loadModel("m4.obj"));
    objsLoaded.push_back(ModelLoader::loadModel("backpack.obj"));

    app.getSceneById(1)->addModel(RenderableModelBuilder(ModelKind::PLAIN)
        .setShader(ShaderBuilder()
            .setVertexShader("vertexShader_light.vert")
            ->setFragmentShader("phong_fs.frag")
            ->setCamera(app.getSceneById(1)->getCamera())
            ->build())
        ->setTransformation(floorTransform)
        ->setMaterial(blueMaterial)
        ->build());

    app.getSceneById(1)->addModel(RenderableModelBuilder()
        .setModel(objsLoaded[0])
        ->setShader(ShaderBuilder()
            .setVertexShader("textured_vs.vert")
            ->setFragmentShader("phong_textured_fs.frag")
            ->setCamera(app.getSceneById(1)->getCamera())
            ->build())
        ->setTransformation(sc1Transform)
        ->setMaterial(blueMaterial)
        ->setTexture(new Texture("m4_diff.png"))
        ->build());

    app.getSceneById(1)->addModel(RenderableModelBuilder()
        .setModel(objsLoaded[1])
        ->setShader(ShaderBuilder()
            .setVertexShader("textured_vs.vert")
            ->setFragmentShader("phong_textured_fs.frag")
            ->setCamera(app.getSceneById(1)->getCamera())
            ->build())
        ->setTransformation(new Translation(glm::vec3(0.f, 5.f, 0.f)))
        ->setMaterial(blueMaterial)
        ->setTexture(new Texture("backpack_diff.jpg"))
        ->build());

    // Scene 3

    // Material
    auto material = new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 1.f, glm::vec3(0.385, 0.647, 0.812));

    // Lights
    auto backLight = std::vector<Light*>();
    backLight.push_back(new Light(glm::vec3(0.f, 0.f, -3.f), 1, glm::vec3(1.f)));
    app.getSceneById(3)->setLights(backLight);

    // Objects
    app.getSceneById(3)->addModel(RenderableModelBuilder(ModelKind::SPHERE)
        .setShader(ShaderBuilder()
            .setCamera(app.getSceneById(3)->getCamera())
            ->setVertexShader("vertexShader_light.vert")
            ->setFragmentShader("phong_fs.frag")
            ->build())
        ->setTransformation(new Translation(glm::vec3(0.f, 0.f, 0.f)))
        ->setMaterial(material)
        ->build());

    // Scene 4

    // Lights
    auto centerLight = std::vector<Light*>();
    centerLight.push_back(new Light(glm::vec3(0.f, 0.f, 0.f), 1, glm::vec3(1.f)));
    app.getSceneById(4)->setLights(centerLight);

    // Objects
    app.getSceneById(4)->addModel(RenderableModelBuilder(ModelKind::SUZI)
        .setShader(ShaderBuilder()
            .setCamera(app.getSceneById(4)->getCamera())
            ->setVertexShader("vertexShader_light.vert")
            ->setFragmentShader("constant_fs.frag")
            ->build())
        ->setTransformation(new Translation(glm::vec3(-3.f, 0.f, 0.f)))
        ->setMaterial(material)
        ->build());

    app.getSceneById(4)->addModel(RenderableModelBuilder(ModelKind::SPHERE)
        .setShader(ShaderBuilder()
            .setCamera(app.getSceneById(4)->getCamera())
            ->setVertexShader("vertexShader_light.vert")
            ->setFragmentShader("lambert_fs.frag")
            ->build())
        ->setTransformation(new Translation(glm::vec3(3.f, 0.f, 0.f)))
        ->setMaterial(material)
        ->build());

    app.getSceneById(4)->addModel(RenderableModelBuilder(ModelKind::SPHERE)
        .setShader(ShaderBuilder()
            .setCamera(app.getSceneById(4)->getCamera())
            ->setVertexShader("vertexShader_light.vert")
            ->setFragmentShader("phong_fs.frag")
            ->build())
        ->setTransformation(new Translation(glm::vec3(0.f, 3.f, 0.f)))
        ->setMaterial(material)
        ->build());

    app.getSceneById(4)->addModel(RenderableModelBuilder(ModelKind::SPHERE)
        .setShader(ShaderBuilder()
            .setCamera(app.getSceneById(4)->getCamera())
            ->setVertexShader("vertexShader_light.vert")
            ->setFragmentShader("blinn_fs.frag")
            ->build())
        ->setTransformation(new Translation(glm::vec3(0.f, -3.f, 0.f)))
        ->setMaterial(material)
        ->build());

    app.run();

    // get end time
	auto finish = std::chrono::high_resolution_clock::now();

	fprintf(stdout, "[DEBUG] Application stats\n");
	fprintf(stdout, "   Time elapsed: %f seconds\n", std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / 1000000000.0);

	return 0;
}