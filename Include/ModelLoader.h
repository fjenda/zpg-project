/**
 * @file ModelLoader.h
 *
 * @brief  ModelLoader class
 *
 * @details This class is used to load models from files.
 *          It uses Assimp library to load models.
 *
 * @author Jan Fojtik
 *
 * @year 2023
 **/
#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <string>
#include "RenderableModel.h"


class ModelLoader {

public:
    static std::shared_ptr<Model> loadModel(const std::string& file);
};


#endif //MODELLOADER_H
