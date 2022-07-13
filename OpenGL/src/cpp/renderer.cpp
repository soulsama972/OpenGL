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
