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

class Camera;

class Shader : public Observer {

private:
    Camera* camera;

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 4.f/4.f, 0.1f, 100.0f);
    glm::mat4 viewMatrix = glm::mat4(1.0f);
//	glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);

public:
    Shader();
    explicit Shader(glm::vec3 color);
	~Shader();

	void use() const; 
	//void setModelViewProjectionMatrix(glm::mat4 MVPMatrix);
    void setModelMatrix(glm::mat4 modelMatrix) const;
    void setViewMatrix();
    void setProjectionMatrix();

    void setCamera(Camera* camera);

    void update(Subject* subject) override;

	void infoLog();
};

class ShaderBuilder {
private:
    Camera* camera;
    glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);

public:
    ShaderBuilder();
    explicit ShaderBuilder(glm::vec3 color);

    ShaderBuilder* setColor(glm::vec3 color);
    ShaderBuilder* setCamera(Camera* camera);
    Shader* build();
};

#endif