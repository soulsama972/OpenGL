#include "indexBuffer.h"
#include"renderer.h"

uint IndexBuffer::bindID = INVALID_ID;

IndexBuffer::IndexBuffer():
count(0), alloctionSize(0), rendererID(0xDEADBF)
{
}

IndexBuffer::IndexBuffer(const uint* data, uint count, uint alloctionSize, bool dynamicDraw)
{
    Init(data, count, alloctionSize, dynamicDraw);
}

IndexBuffer::~IndexBuffer()
{
    if (rendererID != INVALID_ID)
    {
        UnBind();
        GLCall(glDeleteBuffers(1, &rendererID));
    }
}

void IndexBuffer::Init(const uint* data, uint count, uint alloctionSize, bool dynamicDraw)
{
    GLCall(glGenBuffers(1, &rendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, alloctionSize, data, dynamicDraw ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));

    this->count = count;
    this->alloctionSize = alloctionSize;
}


void IndexBuffer::Bind() const
{
    if (bindID != rendererID)
    {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
        bindID = rendererID;
    }
}

void IndexBuffer::UnBind() const
{
    if (bindID == rendererID)
    {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        bindID = INVALID_ID;
    }
}

void IndexBuffer::Append(const uint* data, uint count)
{
    Bind();
    if ((this->count + count) * sizeof(uint) > alloctionSize)
        std::cout << "Error cannot append new indices to indexBuffer out of memroy" << std::endl;

    else
    {
        GLCall(uint* gData = (uint*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
        memcpy(&gData[this->count], data, count * sizeof(uint));
        this->count += count;
        GLCall(glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER));
    }
}

