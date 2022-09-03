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
	Mesh(const T* vData, uint vCount, const uint* iData, uint iCount, const VertexBufferLayout& layout, uint indicesPerVertex, uint vertexPerMesh, uint meshCount, bool dynamicDraw);
	
	void Init(const VertexBufferLayout& layout, uint indicesPerVertex, uint vertexPerMesh, uint meshCount);
	void Init(const T* vData, uint vCount, const uint* iData,uint iCount, const VertexBufferLayout& layout, uint indicesPerVertex, uint vertexPerMesh, uint meshCount, bool dynamicDraw);

	void Append(const T* vData, uint vCount, const uint* iData, uint iCount);
	void UpdateData(const T* vData, uint vCount, uint index);
	void Draw() const;


	void Bind() const;
	void UnBind() const;

private:
	IndexBuffer ib;
	VertexArray va;
	VertexBuffer<T> vb;

};



template<typename T>
inline Mesh<T>::Mesh(const VertexBufferLayout& layout, uint indicesPerVertex, uint vertexPerMesh, uint meshCount)
{
	Init(layout, indicesPerVertex, meshCount, true);
}

template<typename T>
inline Mesh<T>::Mesh(const T* vData, uint vCount, const uint* iData, uint iCount, const VertexBufferLayout& layout, uint indicesPerVertex, uint vertexPerMesh, uint meshCount, bool dynamicDraw)
{
	Init(vData, vCount, iData, iCount, layout, indicesPerVertex, vertexPerMesh, meshCount, dynamicDraw);
}

template<typename T>
inline void Mesh<T>::Init(const VertexBufferLayout& layout, uint indicesPerVertex, uint vertexPerMesh, uint meshCount)
{
	Init(nullptr, 0, nullptr, 0, layout, indicesPerVertex, vertexPerMesh, meshCount,true);
}

template<typename T>
inline void Mesh<T>::Init(const T* vData, uint vCount, const uint* iData, uint iCount, const VertexBufferLayout& layout, uint indicesPerVertex, uint vertexPerMesh, uint meshCount, bool dynamicDraw)
{
	vb.Init(vData, vCount, sizeof(T) * meshCount * vertexPerMesh, dynamicDraw);
	ib.Init(iData, iCount, sizeof(uint) * meshCount * indicesPerVertex, dynamicDraw);
	va.AddBuffer(vb, layout);
}

template<typename T>
inline void Mesh<T>::Append(const T* vData, uint vCount, const uint* iData, uint iCount)
{
	vb.Append(vData, vCount);
	ib.Append(iData, iCount);
}

template<typename T>
inline void Mesh<T>::UpdateData(const T* vData, uint vCount, uint index)
{
	vb.UpdateData(vData, vCount, index);
}

template<typename T>
inline void Mesh<T>::Draw() const
{
	Bind();
	uint indicesCount = ib.GetCount();
	uint verticesCount = vb.GetCount();
	if (indicesCount && indicesCount != verticesCount)
	{
		GLCall(glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr));
	}
	else if (verticesCount)
	{
		GLCall(glDrawArrays(GL_TRIANGLES, 0, verticesCount));
	}

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

