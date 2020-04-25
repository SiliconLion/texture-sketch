#pragma once

#include <stdlib.h> 
#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#endif

#include <iostream>
#include "utilities.h"

class Shader {
public:
    //the linked shader program
    unsigned int program;

    Shader(const char * vertSourcePath, const char * fragSourcePath) {
        const char * vertexShaderSource = readFile("shaders/shader.vert");
        const char * fragmentShaderSource = readFile("shaders/shader.frag");

        unsigned int vertexShader;
        unsigned int fragmentShader;

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        int  success;
        char infoLog[512];

        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }


        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }


        
        program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void bind() {
        glUseProgram(program);
    }

    void unbind() {
        glUseProgram(0);
    }
};

