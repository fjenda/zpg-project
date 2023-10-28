/**
 * @file ForestScene.h
 *
 * @brief ForestScene class
 *
 * @author Jan Fojtik
 *
 * @year 2023
 **/

#ifndef ZPGPROJECT_FORESTSCENE_H
#define ZPGPROJECT_FORESTSCENE_H


#include "../Include/Scene.h"

class ForestScene : public Scene {
public:
    explicit ForestScene(int id);
    ~ForestScene();

private:
    std::vector<std::shared_ptr<Model>> sh_models;
    std::vector<std::shared_ptr<Shader>> sh_shaders;
    std::vector<Model*> models;
    std::vector<Light*> lights;
    std::vector<Material*> materials;
    std::vector<Transformation*> transformations;
};


#endif //ZPGPROJECT_FORESTSCENE_H
