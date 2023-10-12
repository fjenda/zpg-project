//
// Created by Honza Fojtík on 02.10.2023.
//

#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <string>
#include "RenderableModel.h"


class ModelLoader {

public:
    static RenderableModelBuilder loadModel(const std::string& file);
};


#endif //MODELLOADER_H
