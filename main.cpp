#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
    // #include <OpenGL/gl3ext.h>
#endif

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "utilities.h"
#include "geometry.h"
#include "shader.h"

//updates the glViewport when the window is resized.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

//nothing special, just processes input. its a function to keep things nice.
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{



    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //needed for mac
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, 800, 600);
    glfwMakeContextCurrent(window);

    //adds the callback we defined above to a change in framebuffer size
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    Geometry geom = Geometry();


    Shader shader = Shader("assets/shader.vert", "assets/shader.frag");
    





    const char * texSource = "assests/old-gold.png";
    int width, height;
    //the number of color channels
    int nrChannels;

    stbi_set_flip_vertically_on_load(true);  
    unsigned char* data = stbi_load(texSource, &width, &height, &nrChannels, 0);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);


    shader.bind();
    glUniform1i(glGetUniformLocation(shader.program, "myTexture"), 0);

    std::cout << "got to the main loop" << std::endl;

    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        //sets clear color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //clears the color buffer 
        glClear(GL_COLOR_BUFFER_BIT);

        //bind the texture to the first texture slot. 
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        geom.draw();



        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}