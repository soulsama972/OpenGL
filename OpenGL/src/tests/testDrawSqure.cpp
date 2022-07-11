#include "testDrawSqure.h"

TestDrawSqure::TestDrawSqure() :color { 255.0f, 255.0f, 255.0f, 255.0f }
{
	float pos[] =
	{
		-0.5f,  0.5f,
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f

	};
	unsigned int indices[] =
	{
		0,1,2,
		0,2,3
	};
	vb = new VertexBuffer(pos, sizeof(float) * 4 * 2);
	va = new VertexArray();
	ib = new IndexBuffer(indices, 6);
	shader = new Shader("res/shaders/testDrawSqure.shader");
	VertexBufferLayout layout;
	layout.Push<float>(2);
	va->AddBuffer(*vb, layout);

	vb->Bind();
	va->Bind();
	shader->Bind();
}

TestDrawSqure::~TestDrawSqure()
{
	delete vb;
	delete va;
	delete ib;
	delete shader;
}

void TestDrawSqure::OnRender()
{
	shader->SetUniform4f("u_Color", color[0], color[1], color[2], color[3]);
	renderer.Draw(*va, *ib, *shader);
}

void TestDrawSqure::OnImGuiRender()
{
	ImGui::ColorEdit4("change Color", color);
}
