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
        
    }
};
