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
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

// Screen dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const double PI = 3.14159265358979323846;
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

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplGlfw_InitForOpenGL(window.getGLFWwindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    Texture texture("C:/Users/DELL/Desktop/openglCherno/chernoOpenGl/download.png");
    if (texture.GetWidth() == 0 || texture.GetHeight() == 0) {
        std::cerr << "Texture failed to load!" << std::endl;
    }
    else {
        std::cout << "Texture loaded: " << texture.GetWidth() << "x" << texture.GetHeight() << std::endl;
    }
    texture.Bind(0); // Bind texture to slot 0
	shader2.SetUniform1i("uTexture", 0); // Set the texture uniform in the shader
    

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);




    while (!window.shouldClose())
    {
		// Clear the color buffer
        window.clear();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        window.processInput(window.getWindow());


        float time = static_cast<float>(glfwGetTime());
        float red = (sin(time) + 1.0f) / 2.0f;
        float green = (cos(time) + 1.0f) / 2.0f;
        float blue = (sin(time * 0.5f) + 1.0f) / 2.0f;
        glm::mat4 view = glm::lookAt(
            glm::vec3(0.0f, 0.0f, 3.0f * red), // Camera position
            glm::vec3(0.0f, 0.0f, 0.0f), // Look at origin
            glm::vec3(0.0f, 1.0f, 0.0f)  // Up vector
        );
        // Calculate MVP inside the loop
        glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, time, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around Z-axis
        glm::mat4 mvp = projection * view * model;
        // Draw second triangle with shader2
        // Update color based on time

        // Pass color to shader
        shader2.Bind();
        shader2.SetUniformMat4f("u_MVP", mvp);

        shader2.SetUniform3f("uColor", red, green, blue);
        renderer.Draw(va2, ib2, shader2);

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }




        // Rendering
        ImGui::Render(); 
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Add this line
        //glfwSwapBuffers(window.getWindow());
        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}