#pragma once
#include <memory> 
#include "test.h"
#include "../include/VertexBuffer.h"
#include "../include/VertexArray.h"
#include "../include/IndexBuffer.h"
#include "../include/Shader.h"
#include "../include/Texture.h"
#include "../include/Renderer.h"
#include "glm/glm.hpp"

namespace test {
    class testTexture2D : public Test
    {
    public:
        testTexture2D();
        ~testTexture2D();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;
        std::unique_ptr<Renderer> m_Renderer;

        glm::mat4 m_Projection;
        glm::vec3 m_Translation;
        float m_CameraDistance;
        float m_CurrentTime;
        bool m_Rotate;
    };
}