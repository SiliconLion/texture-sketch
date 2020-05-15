
//This is all pretty unsafe. Generally lacking bounds testing and that sort. 
//It's fine for this as everything is tightly controled, but not at all ready to 
//handle the messy world of user input or to be shared with others. 




#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#endif

#include <math.h>

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

//maps an given number from one range to another range.
double mapToRange(double input, double inputMin, double inputMax, double outMin, double outMax) {
    if (input < inputMin || input > inputMax) {
        printf("Error in mapToRange(). input outside of input range.\n");
        goto ADMONISHMENT;
    } else if( inputMax <= inputMin) {
        printf("Error in mapToRange(). input range invalid.\n");
        goto ADMONISHMENT;
    } else if( outMax <= outMin) {
        printf("Error in mapToRange(). output range invalid.\n");
        goto ADMONISHMENT;
    } else {
        goto NOPROBLEM;
    }

    ADMONISHMENT: 
        printf("Also since this error has been triggered you have to actually do a \
        proper error handling job now. \n");
        //does NAN work for floating point numbers? 
        return NAN;

    NOPROBLEM:
        double inputRange = inputMax - inputMin;
        double outRange   = outMax   - outMin  ;
        double scale = outRange / inputRange;

        double output = ( (input - inputMin) * scale) + outMin;
        return output;

}

#ifdef __cplusplus
}
#endif