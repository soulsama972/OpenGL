#pragma once
#include"typing.h"

class IndexBuffer
{
public:
	IndexBuffer(const uint* data, uint count);
	~IndexBuffer();
	void Bind() const;
	void UnBind() const;

	inline uint GetCount() const { return this->m_Count; }


private:
	uint m_rendererID;
	uint m_Count;
};

