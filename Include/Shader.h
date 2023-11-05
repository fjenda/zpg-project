/**
 * @file Shader.h
 *
 * @brief Shader class
 *
 * @details Shader class for loading and using shaders
 *
 * @author Jan Fojtik
 *
 * @year 2023
 **/

#ifndef SHADER_H
#define SHADER_H

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h> 

//Include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <string>
#include <fstream>
#include "Observer.h"
#include "Light.h"
#include "Material.h"

class Camera;

class Shader : public Observer {

private:
    Camera* camera;

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram; // ID of shader program

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 16.f/9.f, 0.1f, 100.0f);
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.f, 0.f, 10.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
    std::vector<Light*> lights;

    std::string vertexShaderPath;
    std::string fragmentShaderPath;

    void _setUniformVariable(const std::string &uniformName, int value) const;
    void _setUniformVariable(const std::string &uniformName, float value) const;
    void _setUniformVariable(const std::string &uniformName, const glm::vec3 &value) const;
    void _setUniformVariable(const std::string &uniformName, const glm::vec4 &value) const;
    void _setUniformVariable(const std::string &uniformName, const glm::mat3 &value) const;
    void _setUniformVariable(const std::string &uniformName, const glm::mat4 &value) const;

public:
    Shader();
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
	~Shader();

	void use() const;
    void unuse() const;

    void setModelMatrix(glm::mat4 modelMatrix) const;
    void setViewMatrix();
    void setProjectionMatrix();
    void setUniformLights() const;
    void setUniformCamera() const;
    void setUniformMaterial(Material* material) const;

    template<typename T>
    void setUniformVariable(const std::string &uniformName, T value) const {
        GLuint uniformID = glGetUniformLocation(this->shaderProgram, uniformName.c_str());

        if (uniformID == -1u) {
            fprintf(stderr, "[ERROR] Shader::setUniformVariable: %s not found \n", uniformName.c_str());
            return;
        }

        _setUniformVariable(uniformName, value);
    }

    void setLights(std::vector<Light*> l);

    void updateViewMatrix();
    void updateProjectionMatrix();

    void setCamera(Camera* camera);

    void update(Subject* subject, Event event) override;

	void infoLog();
};

class ShaderBuilder {
private:
    Camera* camera = nullptr;
    std::string vertexShaderPath = "vertexShader.vert";
    std::string fragmentShaderPath = "fragmentShader.frag";

public:
    ShaderBuilder() = default;

    ShaderBuilder* setVertexShader(std::string vertexShaderPath);
    ShaderBuilder* setFragmentShader(std::string fragmentShaderPath);
    ShaderBuilder* setCamera(Camera* camera);
    Shader* build();
};

#endif