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
#include "Observer.h"

#include <string>

class Light : public Subject {
protected:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 color;

    float intensity = 1.f;

    float constant = 1.0f;
    float linear = 0.007f;
    float quadratic = 0.0002f;

    float cutoff = 0.f; // for spot-light

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
    float getCutoff() const { return this->cutoff; }
    int getType() const { return this->type; }
    glm::vec3 getDirection() const { return this->direction; }

    void enableDebugInterface(int id);
};

class PointLight : public Light{
public:
    PointLight(glm::vec3 position, glm::vec3 color);
};

class DirLight : public Light{
public:
    DirLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction);
};

class SpotLight : public Light{
public:
    SpotLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction, float cutoff);
};

#endif //ZPGPROJECT_LIGHT_H
