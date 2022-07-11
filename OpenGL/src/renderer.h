#pragma once
#include<GL/glew.h>
#include<iostream>

#include"shader.h"
#include"vertexArray.h"
#include"indexBuffer.h"

#ifdef REL
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
                  x;
#else
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
                  x;\
                  ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#endif

void GLClearError(); 
bool GLLogCall(const char* function, const char* file, const int line);


class Renderer
{
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear(float r = 0, float g = 0, float b = 0, float a = 1) const;
    void PrintGLVersion() const;
private:

};