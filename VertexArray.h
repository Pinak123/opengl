#pragma once
#include "VertexBuffer.h"
class VertexArray {
private:
    unsigned int m_RendererID;
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, unsigned int index, unsigned int size, unsigned int stride, unsigned int offset) const;
    void Bind() const;
    void Unbind() const;
};
