/**
 * @file Texture.h
 *
 * @brief Texture class
 *
 * @details Texture class for loading and using textures
 *
 * @author Jan Fojtik
 *
 * @year 2023
 **/

#ifndef ZPGPROJECT_TEXTURE_H
#define ZPGPROJECT_TEXTURE_H

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

#include <cstdio>
#include <string>
#include <map>

class Texture {
private:
    inline static std::map<std::string, GLuint> textures;

    unsigned int textureId;
//    int width;
//    int height;
//    int nrChannels;
//    unsigned char *data;

    bool skybox = false;

public:
    Texture(const char *path);
    Texture(const char *path, std::vector<std::string> faces);
    ~Texture();

    void bind() const;
    void unbind() const;

    bool checkIfLoaded(const char *path);

//    int getWidth() const { return width; };
//    int getHeight() const { return height; };
//    int getNrChannels() const { return nrChannels; };
//    unsigned char *getData();
    bool isSkybox() const { return skybox; };
};

#endif //ZPGPROJECT_TEXTURE_H
