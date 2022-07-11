#pragma once

#include"tests/test.h"

#include"shader.h"
#include"vertexArray.h"
#include"indexBuffer.h"
#include"vertexBuffer.h"
#include"vertexBufferLayout.h"
class TestDrawSqure : public Test
{
public:
	TestDrawSqure();
	~TestDrawSqure();

	void OnRender() override;
	void OnImGuiRender() override;

private:
	VertexArray *va;
	VertexBuffer *vb;
	IndexBuffer *ib;
	Shader *shader;
	float color[4];
};

