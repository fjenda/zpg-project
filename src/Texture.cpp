#include "../Include/Texture.h"

//Include STB
#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb/stb_image.h"

Texture::Texture(bool skybox, const char *path) {
    this->skybox = skybox;

    if (skybox) {
        std::vector<std::string> faces {
            "right.jpg",
            "left.jpg",
            "top.jpg",
            "bottom.jpg",
            "front.jpg",
            "back.jpg",
        };

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

//        stbi_set_flip_vertically_on_load(false);

        for (unsigned int i = 0; i < faces.size(); i++) {
            std::string actualPath = "../Textures/Skybox/" + std::string(path) + faces[i];

            data = stbi_load(actualPath.c_str(), &width, &height, &nrChannels, 0);

            if (data) {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                             0, GL_RGB, width, height,
                             0,
                             GL_RGB,
                             GL_UNSIGNED_BYTE,
                             data
                );
            } else {
                fprintf(stderr, "Failed to load texture: %s\n", actualPath.c_str());
            }
            stbi_image_free(data);
        }
    } else {
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        std::string actualPath = "../Textures/" + std::string(path);

        stbi_set_flip_vertically_on_load(true);
        data = stbi_load(actualPath.c_str(), &width, &height, &nrChannels, 0);

        if (data) {
            GLenum format;
            if (nrChannels == 1) {
                format = GL_RED;
            } else if (nrChannels == 3) {
                format = GL_RGB;
            } else if (nrChannels == 4) {
                format = GL_RGBA;
            }

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            fprintf(stderr, "Failed to load texture: %s\n", path);
        }

        stbi_image_free(data);
    }
}

Texture::~Texture() {
    glDeleteTextures(1, &textureId);
}

void Texture::bind() const {
    if (skybox)
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    else
        glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::unbind() const {
    if (skybox)
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    else
        glBindTexture(GL_TEXTURE_2D, 0);
}

