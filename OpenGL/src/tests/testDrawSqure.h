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
	Mesh<v> mesh;
	Shader *shader;
	float color[4];
	v temp;
	uint index;
};

