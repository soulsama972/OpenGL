#include "vertexArray.h"
#include"vertexBufferLayout.h"
#include"renderer.h"
VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_rendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1,&m_rendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned long long offset = 0;
	for (uint i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(),(void*)offset));
		offset += element.count * VertexBufferElement::GetSizeType(element.type);
	}
}

void VertexArray::Bind()const
{
	GLCall(glBindVertexArray(m_rendererID));
}

void VertexArray::UnBind() const
{
	GLCall(glBindVertexArray(0));
}
