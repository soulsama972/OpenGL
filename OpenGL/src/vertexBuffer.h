#pragma once
#include"typing.h"

class VertexBuffer
{
public:
	VertexBuffer(const void* data, uint size);
	~VertexBuffer();
	void Bind() const;
	void UnBind() const;
private:
	uint m_rendererID;
};

