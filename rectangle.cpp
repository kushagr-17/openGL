//Create rectangle

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

int main(){
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Rectangle", nullptr, nullptr);
    
    if(window==NULL){
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return -1;
    }

    glViewport(0, 0, 800, 800);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float rectangleVertices[] = {
        -0.7f, -0.2f, 0.0f, // Bottom left
         0.7f, -0.2f, 0.0f, // Bottom right
         0.7f,  0.2f, 0.0f, // Top right
        -0.7f,  0.2f, 0.0f  // Top left
    };

    unsigned int rectangleVAO, rectangleVBO, rectangleEBO;
    unsigned int rectangleIndices[] = {
        0, 1, 2, // First triangle
        0, 2, 3  // Second triangle
    };

    glGenVertexArrays(1, &rectangleVAO);
    glGenBuffers(1, &rectangleVBO);
    glGenBuffers(1, &rectangleEBO);

    glBindVertexArray(rectangleVAO);
    glBindBuffer(GL_ARRAY_BUFFER, rectangleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangleEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIndices), rectangleIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(rectangleVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &rectangleVAO);
    glDeleteBuffers(1, &rectangleVBO);
    glDeleteBuffers(1, &rectangleEBO);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
