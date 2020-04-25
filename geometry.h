#pragma once

#include <stdlib.h> 
#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#endif

#include <cstring>

#include "utilities.h"
using std::memcpy;

class Geometry {
public:
    //number of bytes in a vertex.
    const int VERTEX_SIZE = 4 * sizeof(float);
    //number of bytes in an index. (mostly just for consistency)
    const int INDEX_SIZE = sizeof(unsigned int);
    //number of verticies currently in verticies.
    int vertex_count = 4;
    
    float verticies[16]  = {
            // positions            // texture coords
             0.5f,  0.5f,        1.0,  1.0,
             0.5f, -0.5f,        1.0,  0.0,
            -0.5f, -0.5f,        0.0,  0.0,
            -0.5f,  0.5f,        0.0,  1.0
        }; 
    //the number of indicies currently in indicies
    int indicies_count = 6;
    
    unsigned int indicies[6] = {  
            0, 1, 3,  
            1, 2, 3   
        };


    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    Geometry() {

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertex_count * VERTEX_SIZE, verticies, GL_STATIC_DRAW);

        
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_count * INDEX_SIZE, indicies, GL_STATIC_DRAW);


        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (void*)(2 * sizeof(float)) );
        glEnableVertexAttribArray(1);

        //unbind everything
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void bind() {
        glBindVertexArray(VAO);
    }
    void unbind() {
        glBindVertexArray(0);
    }

    //assumes a shader program has already been bound
    void draw() {
        this->bind();
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        this->unbind();
    }
};



    
    // int vertex_count = 4;
    // float verticies[] = {
    // // positions            // texture coords
    //  0.5f,  0.5f,        1.0,  1.0,
    //  0.5f, -0.5f,        1.0,  0.0,
    // -0.5f, -0.5f,        0.0,  0.0,
    // -0.5f,  0.5f,        0.0,  1.0
    // };
    
    
    // int indicies_len = 6;
    // unsigned int indicies[] = {  
    //     0, 1, 3,  
    //     1, 2, 3   
    // }; 


    // unsigned int VAO;
    // glGenVertexArrays(1, &VAO);
    // glBindVertexArray(VAO);

    // unsigned int VBO;
    // glGenBuffers(1, &VBO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, vertex_count * VERTEX_SIZE, verticies, GL_STATIC_DRAW);

    // unsigned int EBO;
    // glGenBuffers(1, &EBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_len * INDEX_SIZE, indicies, GL_STATIC_DRAW);


    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (void*)0);
    // glEnableVertexAttribArray(0);

    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (void*)(2 * sizeof(float)) );
    // glEnableVertexAttribArray(1);
