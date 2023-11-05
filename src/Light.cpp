//
// Created by Honza Fojtík on 16.10.2023.
//

#include "../Include/Light.h"

Light::Light(glm::vec3 position, glm::vec3 color) : position(position), color(color) { }

Light::Light(glm::vec3 position, glm::vec3 color, float intensity) :
    position(position), color(color), intensity(intensity) { }

void Light::enableDebugInterface(int id) {
    auto label = std::string("Light - ") + std::to_string(id);
    if (ImGui::TreeNode(label.c_str())) {
        if (ImGui::DragFloat3("Position", glm::value_ptr(this->position), 0.1f))
            notify(LIGHT_UPDATE);

        if (this->type != 0) {
            if (ImGui::DragFloat3("Direction", glm::value_ptr(this->direction), 1.f, -1.f, 1.f))
                notify(LIGHT_UPDATE);
        }

        if (this->type == 2) {
            if (ImGui::DragFloat("Inner cutoff", &this->innerCutoff, 1.f, 0.f, 180.f))
                notify(LIGHT_UPDATE);

            if (ImGui::DragFloat("Outer cutoff", &this->outerCutoff, 1.f, 0.f, 180.f))
                notify(LIGHT_UPDATE);
        }

        if (ImGui::ColorEdit3("Color", glm::value_ptr(this->color)))
            notify(LIGHT_UPDATE);

        if (ImGui::DragFloat("Intensity", &this->intensity, 0.01f, 0.0f, 1.0f))
            notify(LIGHT_UPDATE);

        ImGui::TreePop();
    }
}

PointLight::PointLight(glm::vec3 position, glm::vec3 color) : Light(position, color) {
    this->type = 0;
}

DirLight::DirLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction) : Light(position, color) {
    this->type = 1;
    this->direction = direction;
}

SpotLight::SpotLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction, float innerCutoff, float outerCutoff) : Light(position, color) {
    this->type = 2;
    this->innerCutoff = innerCutoff;
    this->outerCutoff = outerCutoff;
    this->direction = direction;
}

SpotLight::SpotLight(Camera* cam, glm::vec3 position, glm::vec3 color, glm::vec3 direction, float innerCutoff, float outerCutoff) : Light(position, color) {
    this->type = 2;
    this->innerCutoff = innerCutoff;
    this->outerCutoff = outerCutoff;
    this->direction = direction;
    this->flashlight = flashlight;

    this->camera = cam;
    cam->attach(this);
}