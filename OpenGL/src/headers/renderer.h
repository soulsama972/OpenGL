#pragma once
#include<iostream>

#include"shader.h"
#include"vertexArray.h"
#include"indexBuffer.h"


class Renderer
{
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear(float r = 0, float g = 0, float b = 0, float a = 1) const;
    void PrintGLVersion() const;
private:

};