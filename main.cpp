#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
    // #include <OpenGL/gl3ext.h>
#endif

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>


#include "utilities.h"
#include "geometry.h"
#include "shader.h"
#include "texture.h"

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
    Texture texture = Texture("assests/old-gold.png");

    shader.attachTexture("myTexture", 0);
    //bind the texture to the first texture slot. 


    shader.bind();
    texture.bind(0);

    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        //sets clear color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //clears the color buffer 
        glClear(GL_COLOR_BUFFER_BIT);


        geom.draw();

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}