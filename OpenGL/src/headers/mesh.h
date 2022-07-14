#pragma once
#include"indexBuffer.h"
#include"vertexArray.h"
#include"vertexBuffer.h"


template<typename T>
class Mesh
{
public:

	Mesh() = default;
	Mesh(const VertexBufferLayout& layout, uint indicesPerVertex, uint vertexPerMesh, uint meshCount);
	Mesh(const T* vData, uint vCount, const uint* iData, uint iCount, const VertexBufferLayout& layout, uint indicesPerVertex, uint vertexPerMesh, uint meshCount);
	
	void Init(const VertexBufferLayout& layout, uint indicesPerVertex, uint vertexPerMesh, uint meshCount);
	void Init(const T* vData, uint vCount, const uint* iData,uint iCount, const VertexBufferLayout& layout, uint indicesPerVertex, uint vertexPerMesh, uint meshCount);


	void Bind() const;
	void UnBind() const;

	IndexBuffer& GetIndexBuffer();
	VertexArray& GetVertexArray();
	VertexBuffer<T>& GetVertexBuffer();


private:

	IndexBuffer ib;
	VertexArray va;
	VertexBuffer<T> vb;
};



template<typename T>
inline Mesh<T>::Mesh(const VertexBufferLayout& layout, uint indicesPerVertex, uint vertexPerMesh, uint meshCount)
{
	Init(layout, indicesPerVertex, meshCount);
}

template<typename T>
inline Mesh<T>::Mesh(const T* vData, uint vCount, const uint* iData, uint iCount, const VertexBufferLayout& layout, uint indicesPerVertex, uint vertexPerMesh, uint meshCount)
{
	Init(nullptr, 0, nullptr, 0, layout, indicesPerVertex, vertexPerMesh, meshCount);
}

template<typename T>
inline void Mesh<T>::Init(const VertexBufferLayout& layout, uint indicesPerVertex, uint vertexPerMesh, uint meshCount)
{
	Init(nullptr, 0, nullptr, 0, layout, indicesPerVertex, vertexPerMesh, meshCount);
}

template<typename T>
inline void Mesh<T>::Init(const T* vData, uint vCount, const uint* iData, uint iCount, const VertexBufferLayout& layout, uint indicesPerVertex, uint vertexPerMesh, uint meshCount)
{
	ib.Init(iData, iCount, sizeof(uint) * meshCount * indicesPerVertex, true);
	vb.Init(vData, vCount, sizeof(T) * meshCount * vertexPerMesh, true);
	va.AddBuffer(vb, layout);
}

template<typename T>
inline void Mesh<T>::Bind() const
{
	ib.Bind();
	va.Bind();
}

template<typename T>
inline void Mesh<T>::UnBind() const
{
	ib.UnBind();
	va.UnBind();
}

template<typename T>
inline IndexBuffer& Mesh<T>::GetIndexBuffer()
{
	return ib;
}

template<typename T>
inline VertexArray& Mesh<T>::GetVertexArray()
{
	return va;
}

template<typename T>
inline VertexBuffer<T>& Mesh<T>::GetVertexBuffer()
{
	return vb;
}
