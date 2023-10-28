//
// Created by Honza Fojtík on 10.10.2023.
//

#include "../Include/Camera.h"
#include "../Include/Shader.h"
#include "../Include/Application.h"

Camera::Camera() : Camera(nullptr) {}

Camera::Camera(Shader* s) {
    this->shader = s;
    attach(this->shader);

    this->position = glm::vec3(0.f, 0.f, 0.f);
//    this->target = glm::vec3(0.f, 0.f, 0.f);
    this->cameraUp = glm::vec3(0.f, 1.f, 0.f);
    this->cameraFront = glm::vec3(0.f, 0.f, -1.f);

    this->lastX = Application::get().getWidth() / 2.f;
    this->lastY = Application::get().getHeight() / 2.f;

    notify();
}

Camera::~Camera() {
    detach(this->shader);
    delete shader;
}

void Camera::setShader(Shader* s) {
    this->shader = s;
}

void Camera::update(Subject* subject) {
    // TOOD
}

glm::mat4 Camera::getCamera() {
    return glm::lookAt(this->position, this->position + this->cameraFront, this->cameraUp);
}

glm::mat4 Camera::getPerspective() {
    return glm::perspective(glm::radians(this->fov), (float)Application::get().getRatio(), 0.1f, 100.f);
}

void Camera::moveForward(float speed) {
    this->position += this->cameraFront * speed;
//    this->position.y = 0.f;
    notify();
}

void Camera::moveBackward(float speed) {
    this->position -= this->cameraFront * speed;
//    this->position.y = 0.f;
    notify();
}

void Camera::moveLeft(float speed) {
    this->position -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
//    this->position.y = 0.f;
    notify();
}

void Camera::moveRight(float speed) {
    this->position += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
//    this->position.y = 0.f;
    notify();
}

void Camera::move(bool forward, bool backward, bool left, bool right) {
    float speed = 10.f * Application::get().getDeltaTime();
    if (forward)
        moveForward(speed);
    if (backward)
        moveBackward(speed);
    if (left)
        moveLeft(speed);
    if (right)
        moveRight(speed);
}

void Camera::scrollAction(float yoffset) {
    this->fov -= yoffset;

    if (this->fov < 10.f)
        this->fov = 10.f;
    if (this->fov > 90.f)
        this->fov = 90.f;

    notify();
}

void Camera::mouseAction(float x, float y) {

    if (firstMouse) {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    float xoffset = x - lastX;
    float yoffset = lastY - y;
    lastX = x;
    lastY = y;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    if (yaw > 360.f)
        yaw -= 360.f;
    if (yaw < -360.f)
        yaw += 360.f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->cameraFront = glm::normalize(direction);

    // keep camera on the ground
//    this->position.y = 0.f;

    notify();
}

void Camera::enableDebugInterface() {
    // Camera frame
    ImGui::BeginChildFrame(ImGui::GetID("Camera"), ImVec2(300, 120));
    ImGui::Text("Camera");
    ImGui::DragFloat3("Position", glm::value_ptr(this->position), -1.f, 1.f);
    ImGui::SliderFloat("Yaw", &this->yaw, -180.f, 180.f);
    ImGui::SliderFloat("Pitch", &this->pitch, -180.f, 180.f);
    ImGui::SliderFloat("Fov", &this->fov, 10.f, 90.f);
    ImGui::EndChildFrame();

    // notify after changing
    notify();
}