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
void processInput(GLFWwindow *window, Geometry& geometry, Shader& shader, Texture* textures)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (textures[0].bound) {
            textures[0].unbind();
            textures[1].bind(0);
        } else {
            textures[1].unbind();
            textures[0].bind(0);
        }
        
    }
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
    int texture_count = 2;
    Texture textures[] = {Texture("assests/old-gold.png"), Texture("assests/gravel.png")};

    shader.attachTexture("myTexture", 0);
    //bind the texture to the first texture slot. 


    shader.bind();
    textures[0].bind(0);

    int counter = 0;
    while(!glfwWindowShouldClose(window)) {
        processInput(window, geom, shader, textures);
        //sets clear color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //clears the color buffer 
        glClear(GL_COLOR_BUFFER_BIT);


        geom.draw();

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();    

        if (counter == 60) {
            counter = 0;
            errorAtLine_GL();
        } else {
            counter++;
        }
    }

    glfwTerminate();
    return 0;
}