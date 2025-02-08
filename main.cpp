#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "Shader.h"
#include "Window.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "VertexArray.h"

// Screen dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    Window window(SCR_WIDTH, SCR_HEIGHT, "Two Shader Programs");

    // Vertex data for two triangles
    float vertices1[] = {
        // Positions       // Colors
        -0.9f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // Red
        -0.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Green
        -0.45f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // Blue
    };

    unsigned int indices1[] = {
        0, 1, 2
    };

    float vertices2[] = {
        0.0f, -0.5f, 0.0f,
        0.9f, -0.5f, 0.0f,
        0.45f, 0.5f, 0.0f
    };

    unsigned int indices2[] = {
        0, 1, 2
    };
    //Triangle 1
    VertexArray va1;
    VertexBuffer vb1(vertices1, sizeof(vertices1));
    IndexBuffer ib1(indices1, 3);
    va1.AddBuffer(vb1, 0, 3, 6 * sizeof(float), 0); // Position attribute
    va1.AddBuffer(vb1, 1, 3, 6 * sizeof(float), 3 * sizeof(float)); // Color attribute
	//Triangle 2
    VertexArray va2;
    VertexBuffer vb2(vertices2, sizeof(vertices2));
    IndexBuffer ib2(indices2, 3);
    va2.AddBuffer(vb2, 0, 3, 3 * sizeof(float), 0); // Position attribute

    // Shader Program 1 (Dynamic Colors)
    Shader shader1("res/shaders/Basic.shader");

    // Shader Program 2 (Yellow)
    Shader shader2("res/shaders/Yellow.shader");

    Renderer renderer;

    while (!window.shouldClose())
    {
        window.clear();
        window.processInput(window.getWindow());

        // Draw first triangle with shader1
        renderer.Clear();
        renderer.Draw(va1, ib1, shader1);

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
