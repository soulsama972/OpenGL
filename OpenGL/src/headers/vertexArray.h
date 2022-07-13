#pragma once
#include"vertexBuffer.h"
#include"vertexBufferLayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	template<typename T>
	void AddBuffer(const VertexBuffer<T>& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void UnBind() const;
private:
	uint rendererID;
	mutable bool isBind;
};

template<typename T>
inline void VertexArray::AddBuffer(const VertexBuffer<T>& vb, const VertexBufferLayout& layout)
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

