#pragma once

#include"tests/test.h"

class TestDrawSqure : public Test
{
public:
	TestDrawSqure();
	~TestDrawSqure();

	void OnRender() override;
	void OnImGuiRender() override;

private:
	void AddSqure();
	void UpdateSqure();
	struct v
	{
		float pos[8];
	};
	VertexArray *va;
	VertexBuffer<v> *vb;
	IndexBuffer *ib;
	Shader *shader;
	float color[4];
	v temp;
};

