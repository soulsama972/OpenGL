#pragma once
#include<GL/glew.h>
#include<vector>
#include"renderer.h"

struct VertexBufferElement
{
	uint type;
	uint count;
	bool normalized;

	static uint GetSizeType(uint type)
	{
		switch (type)
		{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(false);
		return 0;
	}

};

class VertexBufferLayout
{
public:
	VertexBufferLayout() :m_Stride(0){};
	~VertexBufferLayout() {};

	template<typename T>
	void Push(uint count)
	{
		static_assert(sizeof(T) == 1);
	}
	template<>
	void Push<float>(uint count)
	{
		m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
		m_Stride += VertexBufferElement::GetSizeType(GL_FLOAT) * count;
	}
	template<>
	void Push<uint>(uint count)
	{

		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeType(GL_UNSIGNED_INT) * count;
	}
	template<>
	void Push<unsigned char>(uint count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += VertexBufferElement::GetSizeType(GL_UNSIGNED_BYTE) * count;
	}

	inline uint GetStride() const { return m_Stride; }
	inline const std::vector< VertexBufferElement>& GetElements() const { return m_Elements; }
private:
	std::vector<VertexBufferElement> m_Elements;
	uint m_Stride;
};

