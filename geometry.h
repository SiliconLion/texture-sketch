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
    static const int FLOATS_IN_VERT = 4;
    //number of bytes in a vertex.
    static const int VERTEX_SIZE = FLOATS_IN_VERT * sizeof(float);
    //number of bytes in an index. (mostly just for consistency)
    static const int INDEX_SIZE = sizeof(unsigned int);


    //number of verticies currently in verticies.
    int vertex_count;
    //the number of verticies `verticies` can store without needing to reallocate.
    int vertex_capacity;
    float* verticies;

    //the number of indicies currently in indicies
    int indicies_count;
    //the number of indicies `indicies` can store without needing to reallocate. 
    int indicies_capacity;
    unsigned int* indicies;


    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    //true when the VAO is bound
    bool bound = false; 

    Geometry() {



        float data[16] = {
            // positions            // texture coords
             0.5f,  0.5f,        1.0,  1.0,
             0.5f, -0.5f,        1.0,  0.0,
            -0.5f, -0.5f,        0.0,  0.0,
            -0.5f,  0.5f,        0.0,  1.0
        }; 

        vertex_capacity = 1 << 4;
        verticies = (float*)calloc(vertex_capacity * VERTEX_SIZE, sizeof(float));
        memcpy(verticies, data, 16 * sizeof(float));
        vertex_count = 4;
        
        
        unsigned int index_data[6] = {  
            0, 1, 3,  
            1, 2, 3   
        };

        indicies_capacity = 1 << 6;
        indicies = (unsigned int*)calloc(indicies_capacity * INDEX_SIZE, sizeof(unsigned int));
        memcpy(indicies, index_data, 6 * sizeof(unsigned int));
        indicies_count = 6;


        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertex_count * VERTEX_SIZE, verticies, GL_DYNAMIC_DRAW);

        
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_count * INDEX_SIZE, indicies, GL_DYNAMIC_DRAW);


        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (void*)(2 * sizeof(float)) );
        glEnableVertexAttribArray(1);

        //unbind everything
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        errorAtLine_GL();

        // this->printVerts();
        // this->printIndicies();
    }

    void bind() {
        glBindVertexArray(VAO);
        // printf("VAO: %i\n", VAO);
        bound = true;
    }
    void unbind() {
        glBindVertexArray(0);
        bound = false;
    }

    void addVertex(float x, float y, float tx, float ty) {

        //if adding a vertex goes over capacity, reallocate. 
        if ( vertex_count + 1 >  vertex_capacity) {
            verticies = (float*)realloc(verticies, vertex_capacity * 2 * VERTEX_SIZE);
            vertex_capacity *= 2;
            // printf("vertiecies reallocated\n");
        }
        
        verticies[vertex_count * FLOATS_IN_VERT    ] = x;
        verticies[vertex_count * FLOATS_IN_VERT + 1] = y;
        verticies[vertex_count * FLOATS_IN_VERT + 2] = tx;
        verticies[vertex_count * FLOATS_IN_VERT + 3] = ty;

        vertex_count += 1;

        //we add indicies 3 at a time, so if adding 3 goes over capacity, reallocate. 
        if(indicies_count + 3 > indicies_capacity ) {
            indicies = (unsigned int *)realloc(indicies, indicies_capacity * 3 * INDEX_SIZE);
            indicies_capacity = indicies_capacity * 3;
            // printf("indicies reallocated\n");
        }

        unsigned int last_index = indicies[indicies_count - 1];
        unsigned int second_last_index = indicies[indicies_count - 2];

        indicies[indicies_count] = second_last_index;
        indicies[indicies_count + 1] = last_index;
        indicies[indicies_count + 2] = vertex_count - 1; 

        indicies_count += 3;

        this->bind();
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ARRAY_BUFFER, vertex_count * VERTEX_SIZE, verticies, GL_DYNAMIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_count * INDEX_SIZE, indicies, GL_DYNAMIC_DRAW);

        this->unbind();

        // this->printVerts();
        // this->printIndicies();
    }

    void printVerts() {
        printf("Verticies:\n");
        for(int i = 0; i < vertex_count; i++) {
            printf("( ");
            for(int j = 0; j < FLOATS_IN_VERT; j++){
                printf("%f, ", verticies[i * FLOATS_IN_VERT + j]);
            }
            printf(")\n");
        }
    }

    void printIndicies() {
        printf("indicies:\n");
        for(int i = 0; i < indicies_count; i++) {
            printf("%i, ", indicies[i]);
            if( (i+1) %3 == 0) {
                printf("\n");
            }
        }
    }

    //assumes a shader program has already been bound
    void draw() {
        this->bind();
        // errorAtLine_GL();
        // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        // errorAtLine_GL();
        glDrawElements(GL_TRIANGLES, indicies_count, GL_UNSIGNED_INT, 0);
        // errorAtLine_GL();
        this->unbind();
    }

    ~Geometry() {
        free(verticies);
        free(indicies);

        if(bound) {this->unbind();}

        glDeleteBuffers(1, &EBO);
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
        errorAtLine_GL();
    }
};


