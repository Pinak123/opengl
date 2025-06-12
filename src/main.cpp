#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "../include/Shader.h"
#include "../include/Window.h"
#include "../include/VertexBuffer.h"
#include "../include/IndexBuffer.h"
#include "../include/Renderer.h"
#include "../include/VertexArray.h"
#include "../include/Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "main.h"

// Screen dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    Window window(SCR_WIDTH, SCR_HEIGHT, "Two Shader Programs");

    
    float vertices2[] = {
        // positions          // tex coords
        -0.5f, -0.5f, -1.0f,  0.0f, 0.0f, // z = -1.0
         0.5f, -0.5f, -1.0f,  1.0f, 0.0f,
         0.0f,  0.5f, -1.0f,  0.5f, 1.0f
    };
    

    unsigned int indices2[] = {
        0, 1, 2
    };

    // For perspective projection
    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
        (float)SCR_WIDTH / (float)SCR_HEIGHT,
        0.1f, 100.0f);
    //Triangle 2
    VertexArray va2;
    VertexBuffer vb2(vertices2, sizeof(vertices2));
    IndexBuffer ib2(indices2, 3);
    va2.AddBuffer(vb2, 0, 3, 5 * sizeof(float), 0);                  // Position attribute
    va2.AddBuffer(vb2, 1, 2, 5 * sizeof(float), 3 * sizeof(float));  // Texture attribute

    // Shader Program 1 (Dynamic Colors)
    Shader shader1("shaders/Basic.shader");

    // Shader Program 2 (Yellow)
    Shader shader2("shaders/Yellow.shader");

    Renderer renderer;
    Texture texture("C:/Users/DELL/Desktop/openglCherno/chernoOpenGl/download.png");
    if (texture.GetWidth() == 0 || texture.GetHeight() == 0) {
        std::cerr << "Texture failed to load!" << std::endl;
    }
    else {
        std::cout << "Texture loaded: " << texture.GetWidth() << "x" << texture.GetHeight() << std::endl;
    }
    texture.Bind(0); // Bind texture to slot 0
	shader2.SetUniform1i("uTexture", 0); // Set the texture uniform in the shader
    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 3.0f), // Camera position
        glm::vec3(0.0f, 0.0f, 0.0f), // Look at origin
        glm::vec3(0.0f, 1.0f, 0.0f)  // Up vector
    );
    while (!window.shouldClose())
    {
   
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        window.processInput(window.getWindow());

        // Calculate MVP inside the loop
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 mvp = projection * view * model;
        // Draw second triangle with shader2
        // Update color based on time
        float time = static_cast<float>(glfwGetTime());
        float red = (sin(time) + 1.0f) / 2.0f;
        float green = (cos(time) + 1.0f) / 2.0f;
        float blue = (sin(time * 0.5f) + 1.0f) / 2.0f;

        // Pass color to shader
        shader2.Bind();
        shader2.SetUniformMat4f("u_MVP", mvp);

        shader2.SetUniform3f("uColor", red, green, blue);
        renderer.Draw(va2, ib2, shader2);

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
		window.clear();
    }

    glfwTerminate();
    return 0;
}