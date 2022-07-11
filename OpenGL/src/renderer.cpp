#include "renderer.h"

void GLClearError()
{ 
    while (glGetError() != GL_NO_ERROR); 
}

bool GLLogCall(const char* function, const char* file, const int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "gl error: " << error << ": " << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

}

void Renderer::Clear(float r, float g, float b, float a) const
{
    GLCall(glClearColor(r, g, b, a));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::PrintGLVersion() const
{
    std::cout << glGetString(GL_VERSION) << std::endl;
}
