/**
 * @file SolarSystemScene.h
 *
 * @brief SolarSystemScene class
 *
 * @author Jan Fojtik
 *
 * @year 2023
 **/

#ifndef ZPGPROJECT_SOLARSYSTEMSCENE_H
#define ZPGPROJECT_SOLARSYSTEMSCENE_H

#include "../Include/Scene.h"

class SolarSystemScene : public Scene {
public:
    explicit SolarSystemScene(int id);
    ~SolarSystemScene();

private:
    std::vector<Shader*> shaders;
    std::vector<Light*> lights;
    std::vector<Material*> materials;
    std::vector<Transformation*> transformations;
};


#endif //ZPGPROJECT_SOLARSYSTEMSCENE_H
