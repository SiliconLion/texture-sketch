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
    //the vertices are in the format x, y, tX, tY
    //x and y are the x and y positions in space. 
    //tX and tY are the texture coordinates
    float* data;
    //number of verticies currently in data
    int vertexCount;
    //number of verticies data can hold without being resized
    int vertexCapacity;
    //the number of floats long a vertex is
    const unsigned int VERTEXLEN = 4;
    //the size in bytes a vertex is
    const unsigned long VERTEXSIZE = sizeof(float) * VERTEXLEN;

    unsigned int * indicies;

    //the vertex array object. Stores 
    unsigned int VAO;
    //the vertex buffer object
    unsigned int VBO;
    //element buffer object
    unsigned int EBO;

    Geometry() {
        vertexCount = 0;
        vertexCapacity = 1000;
        data = (float*)calloc(vertexCapacity, VERTEXSIZE);
        indicies = (unsigned int*)calloc(vertexCapacity, sizeof(unsigned int));


        float firstVerts[12] = {-0.5, -0.5, -0.5, -0.5,
                                 0.0,  0.5,  0.0,  0.5,
                                 0.5, -0.5,  0.5, -0.5};

        memccpy(data, firstVerts, 12, sizeof(float));

        unsigned int firstIndicies[3] = {0,1,2};
        memccpy(indicies, firstIndicies, vertexCount, sizeof(unsigned int));

        //bind the VAO so subsequent calls can be bound with just the VAO
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        errorAtLine_GL();
        //generate and bind the VBO
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, VERTEXSIZE * vertexCount, data, GL_DYNAMIC_DRAW);

        errorAtLine_GL();

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * vertexCount, indicies, GL_DYNAMIC_DRAW);

        errorAtLine_GL();
        //attribute 0 is x and y
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        errorAtLine_GL();
        //attribute 1 is tX and tY
        glVertexAttribPointer(1, 2 , GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)) );
        glEnableVertexAttribArray(1);

        errorAtLine_GL();

        printf("gl errors in geometry intitialization: %x\n", glGetError());

        // unbinds everything
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void addVertex(float x, float y, float tx, float ty) {
        if(vertexCount == vertexCapacity) {
            data = (float*)realloc(data, vertexCapacity * 2 * VERTEXSIZE);
            vertexCapacity *=2;
        }

        // memcpy(data + (vertexCount * VERTEXLEN), vertex, VERTEXLEN);
        data[VERTEXLEN * vertexCount + 1] = x;
        data[VERTEXLEN * vertexCount + 2] = y;
        data[VERTEXLEN * vertexCount + 3] = tx;
        data[VERTEXLEN * vertexCount + 4] = ty;
        vertexCount += 1;



        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, VERTEXSIZE * vertexCount, data, GL_DYNAMIC_DRAW);

        //unbinds everything
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        printf("gl errors in Geometry::addVertex : %x\n", glGetError());
    }

    void draw() {
        glBindVertexArray(VAO);
        errorAtLine_GL();
        // glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // errorAtLine_GL();
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        // errorAtLine_GL();
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        // glDrawElements(GL_TRIANGLE_STRIP, vertexCount, GL_UNSIGNED_INT, )
        printf("gl errors in Geometry::draw : %x\n", glGetError());
    }
};