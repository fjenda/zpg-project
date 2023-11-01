#include "../Include/Shader.h"
#include "../Include/Camera.h"

Shader::~Shader() {
    glDeleteProgram(this->shaderProgram);
}

Shader::Shader() : Shader("vertexShader.vert", "fragmentShader.frag") {}

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath) {
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

void Shader::unuse() const {
    glUseProgram(0);
}

void Shader::setModelMatrix(glm::mat4 modelMatrix) const {
    if (this->fragmentShaderPath == "skybox_fs.frag")
        return;

    setUniformVariable("model", modelMatrix);
}

void Shader::setViewMatrix() {
    if (this->fragmentShaderPath == "skybox_fs.frag") {
        this->viewMatrix = glm::mat4(glm::mat3(camera->getCamera()));
        setUniformVariable("view", viewMatrix);
    } else {
        setUniformVariable("view", viewMatrix);
    }
}

void Shader::setProjectionMatrix() {
    setUniformVariable("projection", projectionMatrix);
}

void Shader::setUniformLights() const {
    if (lights.empty())
        return;

    if (this->fragmentShaderPath == "fragmentShader.frag" ||
        this->fragmentShaderPath == "constant_fs.frag" ||
        this->fragmentShaderPath == "skybox_fs.frag") {
        return;
    }

    // TODO: multiple lights
    // Single light
    if (this->fragmentShaderPath != "multilight_fs.frag") {
        if (lights.size() > 1) {
            fprintf(stderr, "[WARNING] More than one light in shader\n");
            return;
        }

        setUniformVariable("lightPos", lights[0]->getPosition());
        setUniformVariable("lightColor", lights[0]->getColor());
        setUniformVariable("lightIntensity", lights[0]->getIntensity());

        // Attenuation
        setUniformVariable("lightConstant", lights[0]->getAttenuationConst());
        setUniformVariable("lightLinear", lights[0]->getAttenuationLinear());
        setUniformVariable("lightQuadratic", lights[0]->getAttenuationQuadratic());

        if (lights[0]->getType() == 1 || lights[0]->getType() == 2) { // Directional light
            setUniformVariable("lightDir", lights[0]->getDirection());
        }

        if (lights[0]->getType() == 2) {
            //TODO
//            setUniformVariable("lightCutoff", lights[0]->getCutoff());
        }
    } else {
        for (size_t i = 0; i < lights.size(); i++) {
            // Lights count
            setUniformVariable("lightCount", (int) lights.size());

            setUniformVariable("lights[" + std::to_string(i) + "].position", lights[i]->getPosition());
            setUniformVariable("lights[" + std::to_string(i) + "].color", lights[i]->getColor());
            setUniformVariable("lights[" + std::to_string(i) + "].intensity", lights[i]->getIntensity());

            // Attenuation
            setUniformVariable("lights[" + std::to_string(i) + "].constant", lights[i]->getAttenuationConst());
            setUniformVariable("lights[" + std::to_string(i) + "].linear", lights[i]->getAttenuationLinear());
            setUniformVariable("lights[" + std::to_string(i) + "].quadratic", lights[i]->getAttenuationQuadratic());

            // Light type
            setUniformVariable("lights[" + std::to_string(i) + "].type", lights[i]->getType());

            if (lights[i]->getType() == 1 || lights[i]->getType() == 2) { // Directional light
                setUniformVariable("lights[" + std::to_string(i) + "].direction", lights[i]->getDirection());
            }

            if (lights[i]->getType() == 2) {
                //TODO
//            setUniformVariable("lightCutoff", lights[0]->getCutoff());
            }
        }
    }
}

void Shader::setUniformCamera() const {
    if (this->fragmentShaderPath == "fragmentShader.frag" ||
        this->fragmentShaderPath == "constant_fs.frag" ||
        this->fragmentShaderPath == "lambert_fs.frag" ||
        this->fragmentShaderPath == "skybox_fs.frag") {
        return;
    }

    setUniformVariable("cameraPosition", camera->getPosition());
}

void Shader::setUniformMaterial(Material *material) const {
    if (this->fragmentShaderPath == "fragmentShader.frag" ||
        this->fragmentShaderPath == "skybox_fs.frag")
        return;

    if (this->fragmentShaderPath != "phong_textured_fs.frag")
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

void Shader::_setUniformVariable(const std::string &uniformName, int value) const {
    glProgramUniform1i(this->shaderProgram, glGetUniformLocation(this->shaderProgram, uniformName.c_str()), value);
}

void Shader::_setUniformVariable(const std::string &uniformName, float value) const {
    glProgramUniform1f(this->shaderProgram, glGetUniformLocation(this->shaderProgram, uniformName.c_str()), value);
}

void Shader::_setUniformVariable(const std::string &uniformName, const glm::vec3 &value) const {
    glProgramUniform3fv(this->shaderProgram, glGetUniformLocation(this->shaderProgram, uniformName.c_str()), 1, glm::value_ptr(value));
}

void Shader::_setUniformVariable(const std::string &uniformName, const glm::vec4 &value) const {
    glProgramUniform4fv(this->shaderProgram, glGetUniformLocation(this->shaderProgram, uniformName.c_str()), 1, glm::value_ptr(value));
}

void Shader::_setUniformVariable(const std::string &uniformName, const glm::mat3 &value) const {
    glProgramUniformMatrix3fv(this->shaderProgram, glGetUniformLocation(this->shaderProgram, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::_setUniformVariable(const std::string &uniformName, const glm::mat4 &value) const {
    glProgramUniformMatrix4fv(this->shaderProgram, glGetUniformLocation(this->shaderProgram, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setLights(std::vector<Light *> l) {
    this->lights = l;
    this->lights[0]->attach(this);
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
    if (dynamic_cast<Camera*>(subject) != nullptr) {
        this->updateViewMatrix();
        this->updateProjectionMatrix();
    } else if (dynamic_cast<Light*>(subject) != nullptr) {
        this->setUniformLights();
        fprintf(stdout, "[DEBUG] Light updated\n");
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