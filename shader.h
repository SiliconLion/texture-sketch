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
        const char * vertSource = readFile(vertSourcePath);
        const char * fragSource = readFile(fragSourcePath);

        int  success;
        char infoLog[512];

        unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertShader, 1, &vertSource, NULL);
        glCompileShader(vertShader);

        //gets info about the shader. we tell it what shader to look at, then what
        //attribute to look at, then where to store that value. 
        //in this case, looking at the compile status of vertexShader, and we want
        //that placed in `success`
        glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);

        if(!success) {
            glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragShader, 1, &fragSource, NULL);
        glCompileShader(fragShader);

        glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        program = glCreateProgram();
        glAttachShader(program, vertShader);
        glAttachShader(program, fragShader);
        glLinkProgram(program);

        //might be worth checking for an error here.

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);

        printf("gl errors in Shader initialization : %x\n", glGetError());
    }

    void bind(){
        glUseProgram(program);
        printf("gl errors in Shader::bind() : %x\n", glGetError());
    }
    void unbind() {
        glUseProgram(0);
        printf("gl errors in Shader::unbind() : %x\n", glGetError());
    }
};
