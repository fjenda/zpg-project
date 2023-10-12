#include "Shader.h"
#include "../../Camera/Camera.h"

Shader::~Shader() {
	glDeleteProgram(shaderProgram);
}

Shader::Shader() : Shader(glm::vec3(0.0f, 0.0f, 0.0f)) {}

Shader::Shader(glm::vec3 color) {
    std::string fragment_shader_str;
    std::string vertex_shader_str;

    // Fragment shader loading
    // check if color isnt 0, 0, 0 -> color with normals
    if (color != glm::vec3(0.0f)) {
        fragment_shader_str =
            "#version 330\n"
            "out vec4 frag_colour;"
            "in vec3 vn_out;"
            "void main () {"
            "     frag_colour = vec4 (" + std::to_string(color.x) + ", " + std::to_string(color.y) + ", " + std::to_string(color.z) + ", 1.0);"
            "}";
    }
    else {
        std::ifstream fragmentShaderFile("fragmentShader.frag");
        std::string fragmentShaderLine;

        while (std::getline(fragmentShaderFile, fragmentShaderLine)) {
            fragment_shader_str += fragmentShaderLine + "\n";
        }
        fragmentShaderFile.close();
    }
    const char* fragment_shader = fragment_shader_str.c_str();

    // Vertex shader loading
    std::ifstream vertexShaderFile("vertexShader.vert");
    std::string vertexShaderLine;

    while (std::getline(vertexShaderFile, vertexShaderLine)) {
        vertex_shader_str += vertexShaderLine + "\n";
    }
    vertexShaderFile.close();
    const char* vertex_shader = vertex_shader_str.c_str();


    // Create and compile vertex shader
    this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(this->vertexShader, 1, &vertex_shader, NULL);
    glCompileShader(this->vertexShader);

    // Create and compile fragment shader
    this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(this->fragmentShader, 1, &fragment_shader, NULL);
    glCompileShader(this->fragmentShader);

    // Link the vertex and fragment shader into a shader program
    this->shaderProgram = glCreateProgram();
    glAttachShader(this->shaderProgram, this->fragmentShader);
    glAttachShader(this->shaderProgram, this->vertexShader);
    glLinkProgram(this->shaderProgram);

    GLint status;
    glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(this->shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(this->shaderProgram, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }

    // Delete the fragment and vertex shaders once linked
    glDeleteShader(this->fragmentShader);
    glDeleteShader(this->vertexShader);
}

void Shader::use() const {
	glUseProgram(this->shaderProgram);
}

void Shader::setModelMatrix(glm::mat4 modelMatrix) const {
    GLuint matrixID = glGetUniformLocation(this->shaderProgram, "model");

    if (matrixID == -1) {
        fprintf(stderr, "[ERROR] Shader::setModelMatrix: matrixID not found\n");
        return;
    }

    glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void Shader::setViewMatrix() {
    glm::mat4 viewMatrix = camera->getCamera();
    GLuint matrixID = glGetUniformLocation(this->shaderProgram, "view");

    if (matrixID == -1) {
        fprintf(stderr, "[ERROR] Shader::setViewMatrix: matrixID not found\n");
        return;
    }

    glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}

void Shader::setProjectionMatrix() const {
    glm::mat4 projectionMatrix = camera->getPerspective();
    GLuint matrixID = glGetUniformLocation(this->shaderProgram, "projection");

    if (matrixID == -1) {
        fprintf(stderr, "[ERROR] Shader::setProjectionMatrix: matrixID not found\n");
        return;
    }

    glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

void Shader::setCamera(Camera *camera) {
    this->camera = camera;
}

void Shader::update(Subject *subject) {
    if (subject == this->camera) {
        this->setViewMatrix();
    }
}

void Shader::infoLog() {
	fprintf(stdout, "Shader:\n");
	fprintf(stdout, "   Vertex shader: %d\n", this->vertexShader);
	fprintf(stdout, "   Fragment shader: %d\n", this->fragmentShader);
	fprintf(stdout, "   Shader program: %d\n", this->shaderProgram);
}

ShaderBuilder::ShaderBuilder() : ShaderBuilder(glm::vec3(0.0f, 0.0f, 0.0f)) {}

ShaderBuilder::ShaderBuilder(glm::vec3 color) {
    this->color = color;
}

ShaderBuilder* ShaderBuilder::setColor(glm::vec3 color) {
    this->color = color;
    return this;
}

ShaderBuilder* ShaderBuilder::setCamera(Camera* camera) {
    this->camera = camera;
    return this;
}

Shader* ShaderBuilder::build() {
//    if (this->camera == nullptr) {
//        fprintf(stderr, "[ERROR] ShaderBuilder::build: camera is null\n");
//        return nullptr;
//    }

    Shader* s = new Shader(this->color);
    s->setCamera(this->camera);
    return s;
}