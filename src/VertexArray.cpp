// VertexArray.cpp
// VertexArray.cpp
#include "../include/VertexArray.h"
#include <glad/glad.h>
#include "../include/VertexBuffer.h"
#include <cstdint>

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, unsigned int index, unsigned int size, unsigned int stride, unsigned int offset) const {
    Bind();
    vb.Bind();
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (const void*)(uintptr_t)offset);
    glEnableVertexAttribArray(index);
}

void VertexArray::Bind() const {
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}
