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
	float cam = 3.0f;
    glm::vec3 translation(0.0f, 0.0f, 0.0f);
    
	bool rotate = false;
    while (!window.shouldClose())
    {
        window.clear();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        window.processInput(window.getWindow());

        float time = static_cast<float>(glfwGetTime());
        float red = (sin(time) + 1.0f) / 2.0f;
        float green = (cos(time) + 1.0f) / 2.0f;
        float blue = (sin(time * 0.5f) + 1.0f) / 2.0f;
        glm::mat4 view = glm::lookAt(
            glm::vec3(0.0f, 0.0f,cam ),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        glm::mat4 model = glm::mat4(1.0f);
        // 2. Apply translation to the model matrix
        
        model = glm::translate(model, translation);
        if (rotate) {
            model = glm::rotate(model, time, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around Z-axis
		}
        glm::mat4 mvp = projection * view * model;

        shader2.Bind();
        shader2.SetUniformMat4f("u_MVP", mvp);
        shader2.SetUniform3f("uColor", red, green, blue);
        renderer.Draw(va2, ib2, shader2);

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");

			ImGui::SliderFloat("cam", &cam, -1.0f, 10.0f); // Slider for camera distance
            // 3. Add this line for translation control
            ImGui::SliderFloat3("Triangle Translation", (float*)&translation, -1.0f, 1.0f);

            if (ImGui::Button("Button"))
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
            if (ImGui::Button("rotate"))
				rotate = !rotate; // Toggle rotation on button click
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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