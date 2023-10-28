#include "../Include/ModelLoader.h"

std::shared_ptr<Model> ModelLoader::loadModel(const std::string &file) {
    Assimp::Importer importer;

    fprintf(stdout, "[DEBUG] Loading file %s\n", file.c_str());

    std::string filePath = "../Models/obj/" + file;
    const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate |
                                                                    aiProcess_GenNormals |
                                                                    aiProcess_JoinIdenticalVertices);


    if (!scene) {
        fprintf(stderr, "ERROR: reading mesh %s\n", file.c_str());
        throw std::invalid_argument("[ERROR] Reading mesh");
    }

    fprintf(stdout, "[DEBUG] Finished loading file %s\n", file.c_str());

    std::vector<float> points;
    std::vector<int> indices;

    //get points from file.obj
    for (uint32_t j = 0; j < scene->mNumMeshes; j++) {
        for (uint32_t i = 0; i < scene->mMeshes[j]->mNumVertices; i++) {
            points.push_back(scene->mMeshes[j]->mVertices[i].x);
            points.push_back(scene->mMeshes[j]->mVertices[i].y);
            points.push_back(scene->mMeshes[j]->mVertices[i].z);
            points.push_back(scene->mMeshes[j]->mNormals[i].x);
            points.push_back(scene->mMeshes[j]->mNormals[i].y);
            points.push_back(scene->mMeshes[j]->mNormals[i].z);
        }

        for (uint32_t i = 0; i < scene->mMeshes[j]->mNumFaces; i++) {
            indices.push_back(scene->mMeshes[j]->mFaces[i].mIndices[2]);
            indices.push_back(scene->mMeshes[j]->mFaces[i].mIndices[1]);
            indices.push_back(scene->mMeshes[j]->mFaces[i].mIndices[0]);
        }
    }

    return std::make_shared<Model>(points, indices);
}