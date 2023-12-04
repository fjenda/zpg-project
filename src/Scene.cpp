#include <utility>

#include "../Include/Scene.h"
#include "../Include/CallbackController.h"
#include "imgui/imgui.h"
#include "../Include/Colors.h"
#include "../Include/Application.h"

Scene::Scene(int id) {
    this->id = id;
    this->shader = ShaderBuilder().build();
    this->camera = new Camera(this->shader);
    this->shader->setCamera(this->camera);
    CallbackController::setCamera(this->camera);

    this->model = ModelLoader::loadModel("tree.obj");

    this->camera->notify(VIEW_UPDATE);
    fprintf(stdout, "[DEBUG] Scene #%d created\n", id);
}

Scene::~Scene() {
	for (auto model : models) {
		delete model;
	}

    delete this->camera;

    delete this->skybox;

	fprintf(stdout, "[DEBUG] Scene #%d & models destroyed\n", id);
}

void Scene::render(GLFWwindow* window) {
    this->camera->move(glfwGetKey(window, GLFW_KEY_W),
                       glfwGetKey(window, GLFW_KEY_S),
                       glfwGetKey(window, GLFW_KEY_A),
                       glfwGetKey(window, GLFW_KEY_D));

    if (this->skybox != nullptr) {
        glStencilFunc(GL_ALWAYS, 0, 0xFF);

        glDepthFunc(GL_LEQUAL);
        this->skybox->render();
        glDepthFunc(GL_LESS);
    }

    int i = 1;
	for (auto model : models) {
        glStencilFunc(GL_ALWAYS, i, 0xFF);
        model->render();
        i++;
	}
}

void Scene::addModel(RenderableModel* model) {

    if (!lights.empty())
        model->setShaderLight(lights);

	models.push_back(model);

    // Model info
//	fprintf(stdout, "[DEBUG] Added model to scene #%d\n", id);
//	model->infoLog();
}

std::vector<RenderableModel*> Scene::getModels() {
	return models;
}

void Scene::setLights(const std::vector<Light *> l) {
    this->lights = l;
    this->shader->setLights(l);
}

void Scene::setSkybox(RenderableModel* skybox) {
    this->skybox = skybox;
}

void Scene::setCallbackController(CallbackController* callbackController) {
    this->callbackController = callbackController;
}

void Scene::update(Event event) {
    if (!Application::get().isLockedCursor())
        return;

    if (event == CLICK_LEFT) {
        // get click data
        auto data = this->callbackController->getLastData();

        // get index
        int index = data[3];

        // delete on index
        if (this->canDelete(index))
            return;

    } else if (event == CLICK_RIGHT) {
        // get click data
        auto data = this->callbackController->getLastData();

        // get click position
        double x = data[0];
        double y = data[1];
        double z = data[2];

        // transformations
        auto composite = new Composite();
        auto scale = new Scale(glm::vec3((0.5 + (rand() % 1000) / 1000.0)));
        auto rotation = new Rotation(glm::vec3(0.f, 1.f, 0.f), (rand() % 360));
        auto translation = new Translation(glm::vec3(x, y, z));
        composite->addChild(translation);
        composite->addChild(rotation);
        composite->addChild(scale);

        // add model
        addModel(RenderableModelBuilder()
            .setModel(this->model)
            ->setShader(ShaderBuilder()
                .setCamera(this->camera)
                ->setVertexShader("textured_vs.vert")
                ->setFragmentShader("multilight_textured_fs.frag")
            ->build())
            ->setMaterial(new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 32.f, WHITE))
            ->setTransformation(composite)
            ->setTexture(new Texture("tree.png"))
            ->setRemovable(true)
        ->build());

        this->camera->notify(VIEW_UPDATE);
    } else if (event == ADD_POINT) {
        fprintf(stdout, "[DEBUG] Adding bezier point\n");
        // adding a new bezier control point to the vector
        auto data = this->callbackController->getLastData();

        // get click position
        double x = data[0];
        double y = data[1];
        double z = data[2];

        this->bezierPointsVec.push_back(glm::vec3(x, y, z));

        // if we have 4 points we can create a bezier curve
        if (this->bezierPointsVec.size() == 4) {
            fprintf(stdout, "[DEBUG] Creating bezier curve\n");
            // create mat4 from vector
            glm::mat4 bezierCurve = glm::mat4x3(
                glm::vec3(this->bezierPointsVec[0]),
                glm::vec3(this->bezierPointsVec[1]),
                glm::vec3(this->bezierPointsVec[2]),
                glm::vec3(this->bezierPointsVec[3])
            );

            // add it to the vector
            this->bezierPoints.push_back(bezierCurve);

            // clear the vector but keep the last point
            this->bezierPointsVec.erase(this->bezierPointsVec.begin(), this->bezierPointsVec.begin() + 3);

            // get model from the scene by id
            auto model = this->models[this->models.size() - 1];
            model->setTransformation(new BezierTranslation(this->bezierPoints, 1.f));
        }
    }
}

bool Scene::canDelete(int i) {
    i = i - 1;

    if (i < 0) return false;

    if (i >= models.size()) return false;

    // if model is removable
    if (!models[i]->isRemovable()) return false;

    models.erase(models.begin() + i);
    return true;
}

void Scene::enableDebugInterface() {
    ImGui::Begin("Debug interface");

    this->camera->enableDebugInterface();
    ImGui::Separator();

    auto lightsT = "Lights - " + std::to_string(lights.size());
    if (ImGui::TreeNode(lightsT.c_str())) {
        ImGui::Indent(5.f);

        int i = 1;
        for (auto light : lights) {
            light->enableDebugInterface(i);
            i++;
        }
        ImGui::TreePop();
    }
    ImGui::Separator();

    auto modelsT = "Entities - " + std::to_string(models.size());
    if (ImGui::TreeNode(modelsT.c_str())) {
        int i = 1;
        for (auto model : models) {
            model->enableDebugInterface(i);
            i++;
        }
        ImGui::TreePop();
    }

    ImGui::End();
}