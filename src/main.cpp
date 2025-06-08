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

// Screen dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    Window window(SCR_WIDTH, SCR_HEIGHT, "Two Shader Programs");

    
    float vertices2[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    unsigned int indices2[] = {
        0, 1, 2
    };


	//Triangle 2
    VertexArray va2;
    VertexBuffer vb2(vertices2, sizeof(vertices2));
    IndexBuffer ib2(indices2, 3);
    va2.AddBuffer(vb2, 0, 3, 3 * sizeof(float), 0); // Position attribute

    // Shader Program 1 (Dynamic Colors)
    Shader shader1("shaders/Basic.shader");

    // Shader Program 2 (Yellow)
    Shader shader2("shaders/Yellow.shader");

    Renderer renderer;

    while (!window.shouldClose())
    {
        window.clear();
        window.processInput(window.getWindow());

       
        // Draw second triangle with shader2
        // Update color based on time
        float time = glfwGetTime();
        float red = (sin(time) + 1.0f) / 2.0f;
        float green = (cos(time) + 1.0f) / 2.0f;
        float blue = (sin(time * 0.5f) + 1.0f) / 2.0f;

        // Pass color to shader
        shader2.Bind();
        shader2.SetUniform3f("uColor", red, green, blue);
        renderer.Draw(va2, ib2, shader2);

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}