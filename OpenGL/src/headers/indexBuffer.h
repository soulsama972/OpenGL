#pragma once
#include"typing.h"

class IndexBuffer
{
public:
	IndexBuffer();
	IndexBuffer(const uint* data, uint count,uint alloctionSize, bool dynamicDraw);
	~IndexBuffer();
	
	void Init(const uint* data, uint count, uint alloctionSize, bool dynamicDraw);
	
	void Bind() const;
	void UnBind() const;

	void Append(const uint* data, uint count);

	inline uint GetCount() const 
	{ 
		return this->currentCount; 
	}


private:
	uint rendererID;
	uint currentCount;
	uint alloctionSize;
	mutable bool isBind;
};

