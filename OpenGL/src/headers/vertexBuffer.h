#pragma once
#include"typing.h"


template<typename T>
class VertexBuffer
{
public:
	VertexBuffer();
	VertexBuffer(const T* data, uint count, uint alloctionSize, bool dynamicDraw)
	{
		Init(data, count, alloctionSize, dynamicDraw);
	}
	~VertexBuffer()
	{
		if (rendererID != 0xDEADBF)
			GLCall(glDeleteBuffers(1, &rendererID));
	}
	void Init(const T* data, uint count, uint alloctionSize, bool dymaicDraw);

	void AppendData(const T* data, uint count);
	void UpdateData(const T* data, uint offset, uint count);
	void InsertData(const T* data, uint offset, uint count);

	void Bind() const;
	void UnBind() const;

	uint GetCount() const;

private:
	void WriteData(const T* data, uint offset, uint count, bool update);

	uint rendererID;
	uint currentCount;
	uint alloctionSize;
	mutable bool isBind;
};

template<typename T>
inline VertexBuffer<T>::VertexBuffer(): 
currentCount(0), alloctionSize(0), 
isBind(false),rendererID(0xDEADBF)
{
}

template<typename T>
inline void VertexBuffer<T>::Init(const T* data, uint count, uint alloctionSize, bool dynamicDraw)
{
	this->currentCount = count;
	this->alloctionSize = alloctionSize;
	this->isBind = false;

	GLCall(glGenBuffers(1, &rendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, alloctionSize, data, dynamicDraw ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));

}

template<typename T>
inline void VertexBuffer<T>::AppendData(const T* data, uint count)
{
	WriteData(data, currentCount, count, false);
}

template<typename T>
void VertexBuffer<T>::InsertData(const T* data, uint offset, uint count)
{
	WriteData(data, offset, count, false);
}

template<typename T>
void VertexBuffer<T>::UpdateData(const T* data, uint offset, uint count)
{
	WriteData(data, offset, count, true);
}

template<typename T>
void VertexBuffer<T>::Bind() const
{
	if (!isBind)
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
		isBind = true;
	}
}

template<typename T>
void VertexBuffer<T>::UnBind() const
{
	if (isBind)
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		isBind = false;
	}
}

template<typename T>
inline uint VertexBuffer<T>::GetCount() const
{
	return currentCount;
}


template<typename T>
inline void VertexBuffer<T>::WriteData(const T* data, uint offset, uint count, bool update)
{
	Bind();
	GLCall(T* gData = (T*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE));

	if (update)
		memcpy(&gData[offset], data, sizeof(T) * count);

	else
	{
		if ((currentCount + count) * sizeof(T) > alloctionSize)
			std::cout << "Error trying to append new data to out of bound vertex" << std::endl;

		else
		{
			memcpy(&gData[currentCount], data, sizeof(T) * count);
			currentCount += count;
		}
	}
	GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
}
