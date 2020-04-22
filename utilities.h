#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#endif


//path is a null terminated string of the file path
//buffsize is the size of the buffer for the file to be read into
char * readFile(const char* path) {
    if(!path) {
        printf("error: attempted to read contents of NULL pointer in readFile");
    }
    FILE * file = fopen(path, "r");
    if (!file) {
        printf("Unable to open file %s", path);
    }
    fseek(file, 0, SEEK_END);
    int size = ftell(file);

    char * outString = (char*)calloc(sizeof(char), size);
    
    fseek(file, 0, 0);
    fread(outString, sizeof(char), size, file); 
    fclose(file);

    // printf("%s", outString);

    return outString;
}

int8_t * readBytes(const char* path) {
    if(!path) {
        printf("error: attempted to read contents of NULL pointer in bytesFile");
    }
    FILE * file = fopen(path, "rb");
    if (!file) {
        printf("Unable to open file %s", path);
    }
    fseek(file, 0, SEEK_END);
    int size = ftell(file);

    int8_t * bytes = (int8_t*)calloc(sizeof(int8_t), size);

    fseek(file, 0, 0);
    fread(bytes, sizeof(int8_t), size, file); 
    fclose(file);

    return bytes;
}

//assumes srand() has been called
// returns a float between -1 and 1
float randFloat() {
    return ( (float)rand()/(float)RAND_MAX ) * 2 - 1; 
}

#define errorAtLine_GL() \
printf("error. %s::%i, %x\n", __FILE__, __LINE__, glGetError())

#ifdef __cplusplus
}
#endif