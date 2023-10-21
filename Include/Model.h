/**
 * @file Model.h
 *
 * @brief Model class
 *
 * @details Definition of Model class
 *          Model class is used for storing vertices and indices of model
 *          and for binding them to OpenGL
 *
 * @author Jan Fojtik
 *
 * @year 2023
 **/

#ifndef MODEL_H
#define MODEL_H

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

#include <vector>
#include <numeric>

class Model {

private:
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	size_t vertexCount;
	size_t indexCount;

public:
	Model(std::vector<float> points, std::vector<int> indices);
	Model(std::vector<float> points);
	~Model();

	void bindVertexArray();
	
	size_t getVertexCount();
	size_t getIndexCount();

	void infoLog();
};

#endif