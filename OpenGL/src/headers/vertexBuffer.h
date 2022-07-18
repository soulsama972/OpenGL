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
		if (rendererID != INVALID_ID)
		{
			UnBind();
			GLCall(glDeleteBuffers(1, &rendererID));
		}
	}
	void Init(const T* data, uint count, uint alloctionSize, bool dymaicDraw);

	void Append(const T* data, uint count);
	void UpdateData(const T* data, uint count, uint index);
	void InsertData(const T* data, uint count, uint index);

	void Bind() const;
	void UnBind() const;

	uint GetCount() const;

private:
	void WriteData(const T* data, uint offset, uint count, bool update);

	uint rendererID;
	uint count;
	uint alloctionSize;
	static uint bindID;
};

template<typename T>
uint  VertexBuffer<T>::bindID = INVALID_ID;

template<typename T>
inline VertexBuffer<T>::VertexBuffer(): 
count(0), alloctionSize(0), rendererID(INVALID_ID)
{
}

template<typename T>
inline void VertexBuffer<T>::Init(const T* data, uint count, uint alloctionSize, bool dynamicDraw)
{
	this->count = count;
	this->alloctionSize = alloctionSize;

	GLCall(glGenBuffers(1, &rendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, alloctionSize, data, dynamicDraw ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));

}

template<typename T>
inline void VertexBuffer<T>::Append(const T* data, uint count)
{
	WriteData(data, count,this->count, false);
}

template<typename T>
void VertexBuffer<T>::InsertData(const T* data, uint count, uint index)
{
	WriteData(data, count,index, false);
}

template<typename T>
void VertexBuffer<T>::UpdateData(const T* data, uint count, uint index)
{
	WriteData(data, count, index, true);
}

template<typename T>
void VertexBuffer<T>::Bind() const
{
	if (rendererID != bindID)
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
		bindID = rendererID;
	}
}

template<typename T>
void VertexBuffer<T>::UnBind() const
{
	if (rendererID == bindID)
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		bindID = INVALID_ID;
	}
}

template<typename T>
inline uint VertexBuffer<T>::GetCount() const
{
	return count;
}


template<typename T>
inline void VertexBuffer<T>::WriteData(const T* data, uint count, uint index, bool update)
{
	Bind();
	GLCall(T* gData = (T*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE));

	if (update)
		memcpy(&gData[index], data, sizeof(T) * count);

	else
	{
		if ((this->count + count) * sizeof(T) > alloctionSize)
			std::cout << "Error trying to append new data to out of bound vertex" << std::endl;

		else
		{
			memcpy(&gData[this->count], data, sizeof(T) * count);
			this->count += count;
		}
	}
	GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
}
