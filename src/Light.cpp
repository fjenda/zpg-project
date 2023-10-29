//
// Created by Honza Fojtík on 16.10.2023.
//

#include "../Include/Light.h"

Light::Light(glm::vec3 position, float intensity, glm::vec3 color) :
    position(position), color(color), intensity(intensity) { }

Light::Light(glm::vec3 position, float intensity, glm::vec3 color, float lightRadius) :
    position(position), color(color), intensity(intensity), lightRadius(lightRadius) { }

void Light::enableDebugInterface() {
    if (ImGui::TreeNode("Light")) {
        ImGui::TreePop();

        if (ImGui::DragFloat3("Position", glm::value_ptr(this->position), 0.1f))
            notify();

        if (ImGui::ColorEdit3("Color", glm::value_ptr(this->color)))
            notify();

        if (ImGui::DragFloat("Intensity", &this->intensity, 0.01f, 0.0f, 1.0f))
            notify();

        if (ImGui::DragFloat("Light radius", &this->lightRadius, 0.5f, 0.0f, 100.0f)) {
            notify();
        }
    }
}