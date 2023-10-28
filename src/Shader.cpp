#include "../Include/Shader.h"
#include "../Include/Camera.h"

Shader::~Shader() {
    GLint* result = nullptr;
    glGetProgramiv(this->shaderProgram, GL_DELETE_STATUS, result);

    if (result == nullptr) {
        glDeleteProgram(this->shaderProgram);
    }
}

Shader::Shader() : Shader("vertexShader.vert", "fragmentShader.frag") {}

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath) {
//    this->lights.push_back(new Light(glm::vec3(0.0f, 0.0f, 0.0f), 1, glm::vec3(0.4f)));
    this->vertexShaderPath = vertexShaderPath;
    this->fragmentShaderPath = fragmentShaderPath;

    std::string fragment_shader_str;
    std::string vertex_shader_str;
    std::ifstream vertexShaderFile("../Shaders/" + vertexShaderPath);
    std::ifstream fragmentShaderFile("../Shaders/" + fragmentShaderPath);

    // Fragment shader loading
    std::string fragmentShaderLine;

    while (std::getline(fragmentShaderFile, fragmentShaderLine)) {
        fragment_shader_str += fragmentShaderLine + "\n";
    }
    fragmentShaderFile.close();
    const char* fragment_shader = fragment_shader_str.c_str();

    // Vertex shader loading
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
    setUniformVariable("model", modelMatrix);
}

void Shader::setViewMatrix() {
    setUniformVariable("view", viewMatrix);
}

void Shader::setProjectionMatrix() {
    setUniformVariable("projection", projectionMatrix);
}

void Shader::setUniformLights() const {
    if (this->vertexShaderPath == "vertexShader.vert" ||
        this->fragmentShaderPath == "fragmentShader.frag" ||
        this->fragmentShaderPath == "constant_fs.frag") {
        return;
    }

    // TODO: multiple lights
    setUniformVariable("lightPos", lights[0]->getPosition());
    setUniformVariable("lightColor", lights[0]->getColor());
}

void Shader::setUniformCamera() const {
    if (this->vertexShaderPath == "vertexShader.vert" ||
        this->fragmentShaderPath == "fragmentShader.frag" ||
        this->fragmentShaderPath == "constant_fs.frag" ||
        this->fragmentShaderPath == "lambert_fs.frag") {
        return;
    }

    setUniformVariable("cameraPosition", camera->getPosition());
}

void Shader::setUniformMaterial(Material *material) const {
    if (this->fragmentShaderPath == "fragmentShader.frag")
        return;

    setUniformVariable("objectColor", material->getColor());

    if (this->fragmentShaderPath == "constant_fs.frag")
        return;

    setUniformVariable("r_ambient", material->getAmbient());
    setUniformVariable("r_diffuse", material->getDiffuse());

    if (this->fragmentShaderPath == "lambert_fs.frag")
        return;

    setUniformVariable("r_specular", material->getSpecular());
    setUniformVariable("shininess", material->getShininess());
}

void Shader::setUniformVariable(const std::string &uniformName, const std::variant<float, glm::vec3, glm::vec4, glm::mat3, glm::mat4> &value) const {
    GLuint uniformID = glGetUniformLocation(this->shaderProgram, uniformName.c_str());

    if (uniformID == -1u) {
        fprintf(stderr, "[ERROR] Shader::setUniformVariable: %s not found \n", uniformName.c_str());
        return;
    }

    // what type of uniform is it?
    if (std::holds_alternative<float>(value)) {
        glProgramUniform1f(this->shaderProgram, uniformID, std::get<float>(value));
    } else if (std::holds_alternative<glm::vec3>(value)) {
        glProgramUniform3fv(this->shaderProgram, uniformID, 1, glm::value_ptr(std::get<glm::vec3>(value)));
    } else if (std::holds_alternative<glm::vec4>(value)) {
        glProgramUniform4fv(this->shaderProgram, uniformID, 1, glm::value_ptr(std::get<glm::vec4>(value)));
    } else if (std::holds_alternative<glm::mat3>(value)) {
        glProgramUniformMatrix3fv(this->shaderProgram, uniformID, 1, GL_FALSE, glm::value_ptr(std::get<glm::mat3>(value)));
    } else if (std::holds_alternative<glm::mat4>(value)) {
        glProgramUniformMatrix4fv(this->shaderProgram, uniformID, 1, GL_FALSE, glm::value_ptr(std::get<glm::mat4>(value)));
    } else {
        fprintf(stderr, "[ERROR] Shader::setUniformVariable: unknown type \n");
    }
}

void Shader::setLights(std::vector<Light *> l) {
    this->lights = l;
}

void Shader::updateViewMatrix() {
    this->viewMatrix = camera->getCamera();
    this->setViewMatrix();
}

void Shader::updateProjectionMatrix() {
    this->projectionMatrix = camera->getPerspective();
    this->setProjectionMatrix();
}

void Shader::setCamera(Camera *camera) {
    this->camera = camera;
}

void Shader::update(Subject *subject) {
    if (subject == this->camera) {
        this->updateViewMatrix();
        this->updateProjectionMatrix();
    }
}

void Shader::infoLog() {
	fprintf(stdout, "Shader:\n");
	fprintf(stdout, "   Vertex shader: %d\n", this->vertexShader);
	fprintf(stdout, "   Fragment shader: %d\n", this->fragmentShader);
	fprintf(stdout, "   Shader program: %d\n", this->shaderProgram);
}

ShaderBuilder* ShaderBuilder::setVertexShader(std::string vertexShaderPath) {
    this->vertexShaderPath = vertexShaderPath;
    return this;
}

ShaderBuilder* ShaderBuilder::setFragmentShader(std::string fragmentShaderPath) {
    this->fragmentShaderPath = fragmentShaderPath;
    return this;
}

ShaderBuilder* ShaderBuilder::setCamera(Camera* camera) {
    this->camera = camera;
    return this;
}

Shader* ShaderBuilder::build() {
    auto s = new Shader(this->vertexShaderPath, this->fragmentShaderPath);

    if (this->camera != nullptr) {
        s->setCamera(this->camera);
        this->camera->attach(s);
    }
    return s;
}