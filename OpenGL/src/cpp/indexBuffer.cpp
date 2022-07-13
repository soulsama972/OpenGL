#include "indexBuffer.h"
#include"renderer.h"

IndexBuffer::IndexBuffer():
currentCount(0), alloctionSize(0), isBind(false), rendererID(0xDEADBF)
{
}

IndexBuffer::IndexBuffer(const uint* data, uint count, uint alloctionSize, bool dynamicDraw)
{
    Init(data, count, alloctionSize, dynamicDraw);
}

IndexBuffer::~IndexBuffer()
{
    if(rendererID != 0xDEADBF)
        GLCall(glDeleteBuffers(1, &rendererID));
}

void IndexBuffer::Init(const uint* data, uint count, uint alloctionSize, bool dynamicDraw)
{
    this->currentCount = count;
    this->alloctionSize = alloctionSize;
    this->isBind = false;

    GLCall(glGenBuffers(1, &rendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, alloctionSize, data, dynamicDraw ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));

}


void IndexBuffer::Bind() const
{
    if (!isBind)
    {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
        isBind = true;
    }
}

void IndexBuffer::UnBind() const
{
    if (isBind)
    {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        isBind = false;
    }
}

void IndexBuffer::Append(const uint* data, uint count)
{
    Bind();
    if ((currentCount + count) * sizeof(uint) > alloctionSize)
        std::cout << "Error cannot append new indices to indexBuffer out of memroy" << std::endl;

    else
    {
        GLCall(uint* gData = (uint*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
        memcpy(&gData[currentCount], data, count * sizeof(uint));
        currentCount += count;
        GLCall(glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER));
    }
}

