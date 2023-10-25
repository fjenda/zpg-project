#include "../Include/Shader.h"
#include "../Include/Camera.h"

Shader::~Shader() {
    GLint* result;
    glGetProgramiv(this->shaderProgram, GL_DELETE_STATUS, result);

    if (result == nullptr) {
        glDeleteProgram(this->shaderProgram);
    }
}

Shader::Shader() : Shader("vertexShader.vert", "fragmentShader.frag", glm::vec3(0.0f, 0.0f, 0.0f)) {}

Shader::Shader(glm::vec3 color) : Shader("vertexShader.vert", "fragmentShader.frag", color) {}

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath, glm::vec3 color) {
//    this->lights.push_back(new Light(glm::vec3(0.0f, 0.0f, 0.0f), 1, glm::vec3(0.4f)));
    this->vertexShaderPath = vertexShaderPath;
    this->fragmentShaderPath = fragmentShaderPath;

    std::string fragment_shader_str;
    std::string vertex_shader_str;
    std::ifstream vertexShaderFile("../Shaders/" + vertexShaderPath);
    std::ifstream fragmentShaderFile("../Shaders/" + fragmentShaderPath);

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
        std::string fragmentShaderLine;

        while (std::getline(fragmentShaderFile, fragmentShaderLine)) {
            fragment_shader_str += fragmentShaderLine + "\n";
        }
        fragmentShaderFile.close();
    }
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
    GLuint matrixID = glGetUniformLocation(this->shaderProgram, "model");

    if (matrixID == -1u) {
        fprintf(stderr, "[ERROR] Shader::setModelMatrix: matrixID not found\n");
        return;
    }

    glProgramUniformMatrix4fv(this->shaderProgram, matrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void Shader::setViewMatrix() {
    GLuint matrixID = glGetUniformLocation(this->shaderProgram, "view");

    if (matrixID == -1u) {
        fprintf(stderr, "[ERROR] Shader::setViewMatrix: matrixID not found\n");
        return;
    }

    glProgramUniformMatrix4fv(this->shaderProgram, matrixID, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}

void Shader::setProjectionMatrix() {
    GLuint matrixID = glGetUniformLocation(this->shaderProgram, "projection");

    if (matrixID == -1u) {
        fprintf(stderr, "[ERROR] Shader::setProjectionMatrix: matrixID not found\n");
        return;
    }

    glProgramUniformMatrix4fv(this->shaderProgram, matrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

void Shader::setUniformLights() const {
    if (this->vertexShaderPath == "vertexShader.vert" ||
        this->fragmentShaderPath == "fragmentShader.frag" ||
        this->fragmentShaderPath == "constant_fs.frag") {
        return;
    }

    GLuint lightPosID = glGetUniformLocation(this->shaderProgram, "lightPos");
    GLuint lightColorID = glGetUniformLocation(this->shaderProgram, "lightColor");

    if (lightPosID == -1u) {
        fprintf(stderr, "[ERROR] Shader::setUniformLights: lightPosID not found \n");
        return;
    }

    if (lightColorID == -1u) {
        fprintf(stderr, "[ERROR] Shader::setUniformLights: lightColorID not found \n");
        return;
    }

    // TODO: multiple lights
    glProgramUniform3fv(this->shaderProgram, lightPosID, 1, glm::value_ptr(lights[0]->getPosition()));
    glProgramUniform3fv(this->shaderProgram, lightColorID, 1, glm::value_ptr(lights[0]->getColor()));
}

void Shader::setUniformCamera() const {
    if (this->vertexShaderPath == "vertexShader.vert" ||
        this->fragmentShaderPath == "fragmentShader.frag" ||
        this->fragmentShaderPath == "constant_fs.frag" ||
        this->fragmentShaderPath == "lambert_fs.frag") {
        return;
    }

    GLuint posID = glGetUniformLocation(this->shaderProgram, "cameraPosition");

    if (posID == -1u) {
        printf("%s \n", this->fragmentShaderPath.c_str());
        fprintf(stderr, "[ERROR] Shader::setUniformCamera: ID not found \n");
        return;
    }

    glProgramUniform3fv(this->shaderProgram, posID, 1, glm::value_ptr(camera->getPosition()));
}

void Shader::setUniformMaterial(Material *material) const {
    if (this->fragmentShaderPath != "phong_v2.frag")
        return;

    GLuint ambientID = glGetUniformLocation(this->shaderProgram, "r_ambient");
    GLuint diffuseID = glGetUniformLocation(this->shaderProgram, "r_diffuse");
    GLuint specularID = glGetUniformLocation(this->shaderProgram, "r_specular");
    GLuint shininessID = glGetUniformLocation(this->shaderProgram, "shininess");

    if (ambientID == -1u) {
        fprintf(stderr, "[ERROR] Shader::setUniformMaterial: ambientID not found \n");
        return;
    }

    if (diffuseID == -1u) {
        fprintf(stderr, "[ERROR] Shader::setUniformMaterial: diffuseID not found \n");
        return;
    }

    if (specularID == -1u) {
        fprintf(stderr, "[ERROR] Shader::setUniformMaterial: specularID not found \n");
        return;
    }

    if (shininessID == -1u) {
        fprintf(stderr, "[ERROR] Shader::setUniformMaterial: shininessID not found \n");
        return;
    }

    glProgramUniform3fv(this->shaderProgram, ambientID, 1, glm::value_ptr(material->getAmbient()));
    glProgramUniform3fv(this->shaderProgram, diffuseID, 1, glm::value_ptr(material->getDiffuse()));
    glProgramUniform3fv(this->shaderProgram, specularID, 1, glm::value_ptr(material->getSpecular()));
    glProgramUniform1f(this->shaderProgram, shininessID, material->getShininess());
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

ShaderBuilder::ShaderBuilder() : ShaderBuilder(glm::vec3(0.0f, 0.0f, 0.0f)) {}

ShaderBuilder::ShaderBuilder(glm::vec3 color) {
    this->color = color;
}

ShaderBuilder* ShaderBuilder::setVertexShader(std::string vertexShaderPath) {
    this->vertexShaderPath = vertexShaderPath;
    return this;
}

ShaderBuilder* ShaderBuilder::setFragmentShader(std::string fragmentShaderPath) {
    this->fragmentShaderPath = fragmentShaderPath;
    return this;
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
    auto s = new Shader(this->vertexShaderPath, this->fragmentShaderPath, this->color);

    if (this->camera != nullptr) {
        s->setCamera(this->camera);
        this->camera->attach(s);
    }
    return s;
}