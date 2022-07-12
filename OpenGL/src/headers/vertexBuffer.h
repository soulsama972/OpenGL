#pragma once
#include"typing.h"


template<typename T>
class VertexBuffer
{
public:
	VertexBuffer(const T* data, uint count, uint alloctionSize, bool dymaicDraw = false) : currentOffset(count * sizeof(T)), alloctionSize(alloctionSize), isBind(false)
	{
		GLCall(glGenBuffers(1, &rendererID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, alloctionSize, data, dymaicDraw ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
	}
	~VertexBuffer()
	{
		GLCall(glDeleteBuffers(1, &rendererID));
	}

	void AppendData(const T* data, uint count);
	void UpdateData(const T* data, uint offset, uint count);
	void InsertData(const T* data, uint offset, uint count);


	void Bind() const;
	void UnBind() const;

private:
	void WriteData(const T* data, uint offset, uint count, bool update);

	uint rendererID;
	uint currentOffset;
	uint alloctionSize;
	mutable bool isBind;
};

template<typename T>
inline void VertexBuffer<T>::AppendData(const T* data, uint count)
{
	WriteData(data, currentOffset, count, false);
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
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
	isBind = true;
}

template<typename T>
void VertexBuffer<T>::UnBind() const
{
	if (isBind)
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	isBind = false;
}


template<typename T>
inline void VertexBuffer<T>::WriteData(const T* data, uint offset, uint count, bool update)
{
	Bind();
	uint size = sizeof(T) * count;
	GLCall(void * gData = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE));

	if (update)
		memcpy(gData, data, size);

	else
	{
		if (currentOffset + size > alloctionSize)
			std::cout << "Error trying to append new data to out of bound vertex" << std::endl;

		else
		{
			memcpy(gData, data, size);
			currentOffset += size;
		}
	}
	GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
}
