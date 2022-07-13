#pragma once
#include<iostream>

#include"shader.h"
#include"vertexArray.h"
#include"indexBuffer.h"
#include"mesh.h"

class Renderer
{
public:
    template<typename T>
    void Draw(const VertexArray& va, const IndexBuffer& ib, const VertexBuffer<T>& vb, const Shader& shader) const;
    void Clear(float r = 0, float g = 0, float b = 0, float a = 1) const;
    void PrintGLVersion() const;

private:

};


template<typename T>
inline void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const VertexBuffer<T>& vb, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    uint indicesCount = ib.GetCount();
    if (indicesCount)
    {
        GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
    }
    else
    {
        GLCall(glDrawArrays(GL_TRIANGLES, 0, vb.GetCount()));
    }
}
