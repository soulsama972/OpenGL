#pragma once
#include<iostream>
#include"shader.h"
#include"model.h"

enum POLYGONMODE
{
    POINTS = 0x1B00,
    LINE,
    FILL
};


class Renderer
{
public:
    Renderer() = default;

    template<typename T>
    void Draw(const VertexArray& va, const IndexBuffer& ib, const VertexBuffer<T>& vb, const Shader& shader) const;

    void Clear(float r = 0, float g = 0, float b = 0, float a = 1) const;
    void PrintGLVersion() const;

    static void SetFillMode(POLYGONMODE mode);
    static void EnableZBuffer();
    static void DisableZBuffer();

private:

};


template<typename T>
inline void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const VertexBuffer<T>& vb, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    vb.Bind();
    uint indicesCount = ib.GetCount();
    uint verticesCount = vb.GetCount();
    if (indicesCount && indicesCount != verticesCount)
    {
        GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
    }
    else if(verticesCount)
    {
        GLCall(glDrawArrays(GL_TRIANGLES, 0, verticesCount));
    }
}
