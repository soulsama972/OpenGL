#include "indexBuffer.h"
#include"renderer.h"

IndexBuffer::IndexBuffer(const uint* data, uint count, uint alloctionSize, bool dynamicDraw):
currentIndices(count),alloctionSize(alloctionSize),isBind(false)
{
    GLCall(glGenBuffers(1, &rendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,alloctionSize, data, dynamicDraw ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &rendererID));
}

void IndexBuffer::Bind() const
{
    if(!isBind)
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,rendererID));
    isBind = true;
}

void IndexBuffer::UnBind() const
{
    if(isBind)
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    isBind = false;
}

void IndexBuffer::Append(const uint* data, uint count)
{
    if (currentIndices + count * sizeof(uint) > alloctionSize)
    {
        std::cout << "Error cannot append new indices to indexBuffer out of memroy" << std::endl;
    }
    else
    {
        Bind();
        GLCall(void* gData = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE));
        memcpy(gData, data, count * sizeof(uint));
        currentIndices += count;
        GLCall(glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER));
    }
}
