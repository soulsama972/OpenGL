#pragma once
#include"typing.h"

class IndexBuffer
{
public:
	IndexBuffer(const uint* data, uint count,uint alloctionSize, bool dynamicDraw = false);
	~IndexBuffer();
	
	void Bind() const;
	void UnBind() const;

	void Append(const uint* data, uint count);

	inline uint GetCount() const { return this->currentIndices; }
private:
	uint rendererID;
	uint currentIndices;
	uint alloctionSize;
	mutable bool isBind;
};

