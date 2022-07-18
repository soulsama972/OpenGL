#include "renderer.h"





void Renderer::Clear(float r, float g, float b, float a) const
{
    GLCall(glClearColor(r, g, b, a));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::PrintGLVersion() const
{
    std::cout << glGetString(GL_VERSION) << std::endl;
}

void Renderer::SetFillMode(POLYGONMODE mode)
{
    GLCall(glPolygonMode(GL_FRONT_AND_BACK, mode));
}

void Renderer::EnableZBuffer()
{
    GLCall(glEnable(GL_DEPTH_TEST));
}

void Renderer::DisableZBuffer()
{
    GLCall(glDisable(GL_DEPTH_TEST));
}
