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

class Texture {
private:
    unsigned int textureId;
    int width;
    int height;
    int nrChannels;
    unsigned char *data;

public:
    Texture(const char *path);
    ~Texture();

    void bind() const;
    void unbind() const;

    int getWidth() const { return width; };
    int getHeight() const { return height; };
    int getNrChannels() const { return nrChannels; };
    unsigned char *getData();
};

#endif //ZPGPROJECT_TEXTURE_H
