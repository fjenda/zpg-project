#include "../Include/Model.h"

Model::~Model() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

Model::Model(std::vector<float> points, std::vector<int> indices) {
    this->vertexCount = points.size() / 6;
    this->indexCount = indices.size();

    //Vertex Array Object (VAO)
    glGenVertexArrays(1, &this->VAO); //generate the VAO
    glBindVertexArray(this->VAO); //bind the VAO

    //vertex buffer object (VBO)
    glGenBuffers(1, &this->VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); //enable vertex attributes
    glEnableVertexAttribArray(1); //enable normal attributes
    glEnableVertexAttribArray(2); //enable texture attributes

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (sizeof(float) * 8), NULL);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (sizeof(float) * 8), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (sizeof(float) * 8), (void*)(6 * sizeof(float)));

    glGenBuffers(1, &this->EBO); // generate the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);
}

Model::Model(std::vector<float> points) {
	this->vertexCount = points.size() / 6;

    std::vector<int> indices(this->vertexCount);
    std::iota(std::begin(indices), std::end(indices), 0);
    this->indexCount = indices.size();

    //Vertex Array Object (VAO)
    glGenVertexArrays(1, &this->VAO); //generate the VAO
    glBindVertexArray(this->VAO); //bind the VAO

    //vertex buffer object (VBO)
    glGenBuffers(1, &this->VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); //enable vertex attributes
    glEnableVertexAttribArray(1); //enable vertex attributes

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (sizeof(float) * 6), NULL);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (sizeof(float) * 6), (void*)(3 * sizeof(float)));

    glGenBuffers(1, &this->EBO); // generate the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);
}

Model::Model(std::vector<float> points, std::vector<int> indices, int pointSize, int normalSize, int textureSize) {
    this->vertexCount = points.size() / (pointSize + normalSize + textureSize);
    this->indexCount = indices.size();

    //Vertex Array Object (VAO)
    glGenVertexArrays(1, &this->VAO); //generate the VAO
    glBindVertexArray(this->VAO); //bind the VAO

    //vertex buffer object (VBO)
    glGenBuffers(1, &this->VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); //enable vertex attributes
    glVertexAttribPointer(0, pointSize, GL_FLOAT, GL_FALSE, (sizeof(float) * (pointSize + normalSize + textureSize)), NULL);

    if (normalSize > 0) {
        glEnableVertexAttribArray(1); //enable normal attributes
        glVertexAttribPointer(1, normalSize, GL_FLOAT, GL_FALSE, (sizeof(float) * (pointSize + normalSize + textureSize)), (void*)(pointSize * sizeof(float)));
    }

    if (textureSize > 0) {
        glEnableVertexAttribArray(2); //enable texture attributes
        glVertexAttribPointer(2, textureSize, GL_FLOAT, GL_FALSE, (sizeof(float) * (pointSize + normalSize + textureSize)), (void*)((pointSize + normalSize) * sizeof(float)));
    }

    glGenBuffers(1, &this->EBO); // generate the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);
}

Model::Model(std::vector<float> points, int pointSize, int normalSize, int textureSize) {
    this->vertexCount = points.size() / (pointSize + normalSize + textureSize);

    std::vector<int> indices(this->vertexCount);
    std::iota(std::begin(indices), std::end(indices), 0);
    this->indexCount = indices.size();

    //Vertex Array Object (VAO)
    glGenVertexArrays(1, &this->VAO); //generate the VAO
    glBindVertexArray(this->VAO); //bind the VAO

    //vertex buffer object (VBO)
    glGenBuffers(1, &this->VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); //enable vertex attributes
    glVertexAttribPointer(0, pointSize, GL_FLOAT, GL_FALSE, (sizeof(float) * (pointSize + normalSize + textureSize)), NULL);

    if (normalSize > 0) {
        glEnableVertexAttribArray(1); //enable normal attributes
        glVertexAttribPointer(1, normalSize, GL_FLOAT, GL_FALSE, (sizeof(float) * (pointSize + normalSize + textureSize)), (void*)(pointSize * sizeof(float)));
    }

    if (textureSize > 0) {
        glEnableVertexAttribArray(2); //enable texture attributes
        glVertexAttribPointer(2, textureSize, GL_FLOAT, GL_FALSE, (sizeof(float) * (pointSize + normalSize + textureSize)), (void*)((pointSize + normalSize) * sizeof(float)));
    }

    glGenBuffers(1, &this->EBO); // generate the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);
}

void Model::bindVertexArray() {
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
}

size_t Model::getVertexCount() {
	// TODO: Implement
    return this->vertexCount;
}

size_t Model::getIndexCount() {
    // TODO: Implement
    return this->indexCount;
}

void Model::infoLog() {
	fprintf(stdout, "Model:\n");
	fprintf(stdout, "   VAO: %d\n", this->VAO);
	fprintf(stdout, "   VBO: %d\n", this->VBO);
	fprintf(stdout, "   EBO: %d\n", this->EBO);
	fprintf(stdout, "   vertexCount: %d\n", (int)this->vertexCount);
	fprintf(stdout, "   indexCount: %d\n", (int)this->indexCount);
	fprintf(stdout, "   triangleCount: %d\n", (int)this->indexCount / 3);
}