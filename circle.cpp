//Implementation of circle using midpoint circle drawing algorithm

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

std::vector<float> midpointCircle(int xc, int yc, int r){
    std::vector<float> points;
    
    int x = 0, y = r;
    int p = 1 - r;

    while(x <= y){
        float px = xc / 400.0f - 1.0f;
        float py = yc / 400.0f - 1.0f;

        //eight point symmetry around center
        points.insert(points.end(), {
            (xc + x) / 400.0f - 1.0f, (yc + y) / 400.0f - 1.0f, 0.0f,
            (xc - x) / 400.0f - 1.0f, (yc + y) / 400.0f - 1.0f, 0.0f,
            (xc + x) / 400.0f - 1.0f, (yc - y) / 400.0f - 1.0f, 0.0f,
            (xc - x) / 400.0f - 1.0f, (yc - y) / 400.0f - 1.0f, 0.0f,
            (xc + y) / 400.0f - 1.0f, (yc + x) / 400.0f - 1.0f, 0.0f,
            (xc - y) / 400.0f - 1.0f, (yc + x) / 400.0f - 1.0f, 0.0f,
            (xc + y) / 400.0f - 1.0f, (yc - x) / 400.0f - 1.0f, 0.0f,
            (xc - y) / 400.0f - 1.0f, (yc - x) / 400.0f - 1.0f, 0.0f
        });

        x++;
        if(p<0){
            p += 2*x+1;
        }
        else{
            y--;
            p += 2*(x-y)+1;
        }
    }

    return points;
}

// Shader sources
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 1.0, 1.0, 1.0); // White color
}
)";

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,800,"Circle", NULL, NULL);
    if(window == NULL){
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 800);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    std::vector<float> circlePoints = midpointCircle(200, 200, 100);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*circlePoints.size(), circlePoints.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glUseProgram(shaderProgram);

        glLineWidth(2.0f);
        glDrawArrays(GL_LINE_STRIP, 0, circlePoints.size()/3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
