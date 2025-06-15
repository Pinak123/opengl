#include "testTexture2D.h"
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
#include "imgui/imgui.h"
#include <memory> // Include this for std::unique_ptr


// Ensure GL_DEBUG_OUTPUT and GL_DEBUG_OUTPUT_SYNCHRONOUS are defined
#ifndef GL_DEBUG_OUTPUT
#define GL_DEBUG_OUTPUT 0x92E0
#endif

#ifndef GL_DEBUG_OUTPUT_SYNCHRONOUS
#define GL_DEBUG_OUTPUT_SYNCHRONOUS 0x8242
#endif


namespace test
{
    testTexture2D::testTexture2D()
        : m_Projection(glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f)), // Replace ortho with perspective
          m_Translation(0.0f, 0.0f, 0.0f),
          m_CameraDistance(3.0f),
          m_Rotate(false),
          m_CurrentTime(0.0f)
    {
        // Initialize vertex data with larger triangle
        float vertices[] = {
            // positions          // tex coords
            -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,  // bottom left
             1.0f, -1.0f, 0.0f,  1.0f, 0.0f,  // bottom right
             0.0f,  1.0f, 0.0f,  0.5f, 1.0f   // top
        };

        unsigned int indices[] = {
            0, 1, 2  // single triangle
        };

        // Create and set up vertex array
        m_VAO = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 3);

        // Set up vertex attributes
        m_VAO->AddBuffer(*m_VertexBuffer, 0, 3, 5 * sizeof(float), 0);                    // position
        m_VAO->AddBuffer(*m_VertexBuffer, 1, 2, 5 * sizeof(float), 3 * sizeof(float));    // texture coordinates

        // Create shader
        m_Shader = std::make_unique<Shader>("shaders/Yellow.shader");
        
        // Create and check texture
        const std::string texturePath = "C:/Users/DELL/Desktop/openglCherno/chernoOpenGl/download.png";
        std::cout << "Attempting to load texture from: " << texturePath << std::endl;
        
        try {
            m_Texture = std::make_unique<Texture>(texturePath);
            
            // Check if texture loaded successfully
            if (m_Texture->GetWidth() == 0 || m_Texture->GetHeight() == 0) {
                std::cerr << "Error: Texture loaded but has invalid dimensions!" << std::endl;
            } else {
                std::cout << "Texture loaded successfully!" << std::endl;
                std::cout << "Texture dimensions: " << m_Texture->GetWidth() << "x" << m_Texture->GetHeight() << std::endl;
            }
            
            // Initialize texture and shader uniforms
            m_Texture->Bind(0);
            m_Shader->Bind();
            m_Shader->SetUniform1i("uTexture", 0);
        }
        catch (const std::exception& e) {
            std::cerr << "Error loading texture: " << e.what() << std::endl;
        }

        // Enable debug output
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        // Add depth testing
        glEnable(GL_DEPTH_TEST);

        m_Renderer = std::make_unique<Renderer>();
    }

    testTexture2D::~testTexture2D()
    {
    }

    void testTexture2D::OnUpdate(float deltaTime)
    {
        m_CurrentTime = static_cast<float>(glfwGetTime());
    }

    void testTexture2D::OnRender()
    {
        // Clear both color and depth buffer
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Debug print texture state
        GLint current_texture;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &current_texture);
        

        // Calculate color values
        float red = (sin(m_CurrentTime) + 1.0f) / 2.0f;
        float green = (cos(m_CurrentTime) + 1.0f) / 2.0f;
        float blue = (sin(m_CurrentTime * 0.5f) + 1.0f) / 2.0f;

        // Set up view matrix
        glm::mat4 view = glm::lookAt(
            glm::vec3(0.0f, 0.0f, m_CameraDistance),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        // Set up model matrix with translation and optional rotation
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, m_Translation);  // This will now properly handle z-translation
        
        if (m_Rotate) {
            model = glm::rotate(model, m_CurrentTime, glm::vec3(0.0f, 0.0f, 1.0f));
        }

        // Calculate MVP matrix
        glm::mat4 mvp = m_Projection * view * model;

        // Bind shader and set uniforms
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        m_Shader->SetUniform3f("uColor", red, green, blue);

        // Check if texture exists before binding
        if (m_Texture) {
            m_Texture->Bind(0);
            m_Shader->SetUniform1i("uTexture", 0);
            
            // Verify texture binding
            GLint bound_texture;
            glGetIntegerv(GL_TEXTURE_BINDING_2D, &bound_texture);
            if (bound_texture == 0) {
                std::cerr << "Warning: No texture bound before drawing!" << std::endl;
            }
        } else {
            std::cerr << "Warning: Texture not initialized!" << std::endl;
        }

        // Draw using the renderer
        m_Renderer->Draw(*m_VAO, *m_IndexBuffer, *m_Shader);

        // Check for OpenGL errors
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "OpenGL error during render: 0x" << std::hex << err << std::endl;
        }
    }

    void testTexture2D::OnImGuiRender()
    {
        // ImGui controls
        ImGui::SliderFloat("Camera Distance", &m_CameraDistance, -1.0f, 10.0f);
        ImGui::SliderFloat3("Translation", (float*)&m_Translation, -1.0f, 1.0f);
        
        if (ImGui::Button("Toggle Rotation")) {
            m_Rotate = !m_Rotate;
        }
    }
}