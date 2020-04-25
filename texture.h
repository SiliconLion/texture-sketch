#pragma once

#include <stdlib.h> 
#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Texture {
public: 
    unsigned int texture;

    //takes the path to the source of the texture
    Texture(const char* texSource) {
        int width, height;
        //the number of color channels
        int nrChannels;

        stbi_set_flip_vertically_on_load(true);  
        unsigned char* data = stbi_load(texSource, &width, &height, &nrChannels, 0);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //generates the texture image and the mipmaps
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    //takes the number corisponding to the texture unit we want to bind to. For instance
    //if we wanted to have glActiveTexture(GL_TEXTURE3) called, we would call bind(3); 
    void bind(unsigned int textureUnitNumber) {
        glActiveTexture(GL_TEXTURE0 + textureUnitNumber);
    }

    void unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
};

  

