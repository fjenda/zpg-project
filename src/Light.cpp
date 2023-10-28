//
// Created by Honza Fojtík on 16.10.2023.
//

#include "../Include/Light.h"

Light::Light(glm::vec3 position, float intensity, glm::vec3 color) {
    this->position = position;
    this->intensity = intensity;
    this->color = color;
}

void Light::enableDebugInterface() {
    // Camera frame
    ImGui::BeginChildFrame(ImGui::GetID("Light"), ImVec2(300, 120));
    ImGui::Text("Light");

    if (ImGui::DragFloat3("Position", glm::value_ptr(this->position), 0.1f))
        notify();

    if (ImGui::ColorPicker3("Color", glm::value_ptr(this->color)))
        notify();

    if (ImGui::DragFloat("Intensity", &this->intensity, 0.1f))
        notify();

    ImGui::EndChildFrame();
}