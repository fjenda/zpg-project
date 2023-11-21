/**
 * @file Light.h
 *
 * @brief Class for light source
 *
 * @details This class is used for light source. It contains position, color and intensity of the light.
 *
 * @author Jan Fojtik
 *
 * @year 2023
 **/

#ifndef ZPGPROJECT_LIGHT_H
#define ZPGPROJECT_LIGHT_H

#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "imgui/imgui.h"
#include "Subject.h"
#include "Camera.h"

#include <string>

class Light : public Subject {
protected:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 color;

    float intensity = 1.f;

    // attenuation
    float constant = 1.0f;
    float linear = 0.007f;
    float quadratic = 0.0002f;

    // for spot-light
    float innerCutoff = 0.f;
    float outerCutoff = 0.f;
    bool flashlight = false;


    int type = 0; // 0 - point, 1 - directional, 2 - spot

public:
    Light(glm::vec3 position, glm::vec3 color);
    Light(glm::vec3 position, glm::vec3 color, float intensity);

    glm::vec3 getPosition() const { return this->position; }
    glm::vec3 getColor() const { return this->color; }
    float getIntensity() const { return this->intensity; }
    float getAttenuationConst() const { return this->constant; }
    float getAttenuationLinear() const { return this->linear; }
    float getAttenuationQuadratic() const { return this->quadratic; }
    int getType() const { return this->type; }
    glm::vec3 getDirection() const { return this->direction; }

    // spot-light
    float getInnerCutoff() const { return this->innerCutoff; }
    float getOuterCutoff() const { return this->outerCutoff; }
    bool isFlashlight() const { return this->flashlight; }

    void setPosition(glm::vec3 pos) {
        this->position = pos;
        notify(VIEW_UPDATE);
    }

    void setColor(glm::vec3 col) {
        this->color = col;
        notify(VIEW_UPDATE);
    }

    void setDirection(glm::vec3 dir) {
        this->direction = dir;
        notify(VIEW_UPDATE);
    }

    void setIntensity(float inten) {
        this->intensity = inten;
        notify(VIEW_UPDATE);
    }

    void enableDebugInterface(int id);
};

class PointLight : public Light {
public:
    PointLight(glm::vec3 position, glm::vec3 color);
};

class DirLight : public Light {
public:
    DirLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction);
};

class SpotLight : public Light, public Observer {
private:
    Camera* camera;
public:
    SpotLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction, float innerCutoff, float outerCutoff);
    SpotLight(Camera* cam, glm::vec3 position, glm::vec3 color, glm::vec3 direction, float innerCUtoff, float outerCutoff);

    void update(Event event) override {
        if (event == VIEW_UPDATE) {
            this->position = this->camera->getPosition();
            this->direction = this->camera->getDirection();
        }
    }
};

#endif //ZPGPROJECT_LIGHT_H
