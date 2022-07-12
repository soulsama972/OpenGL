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
	memcpy(temp.pos, pos, sizeof(temp));

	vb = new VertexBuffer<v>(nullptr, 0,sizeof(v) * 100, true);
	va = new VertexArray();
	ib = new IndexBuffer(nullptr, 0, 100 * sizeof(uint), true);
	shader = new Shader("res/shaders/testDrawSqure.shader");
	VertexBufferLayout layout;
	layout.Push<float>(2);
	va->AddBuffer(*vb, layout);
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
	if (ImGui::Button("add Squre", { 100,20 }))
		AddSqure();


	if(ImGui::SliderFloat2("point A", &temp.pos[0], -1.0f, 1.0f))
		UpdateSqure();
	if(ImGui::SliderFloat2("point B", &temp.pos[2], -1.0f, 1.0f))
		UpdateSqure();
	if(ImGui::SliderFloat2("point C", &temp.pos[4], -1.0f, 1.0f))
		UpdateSqure();
	if(ImGui::SliderFloat2("point D", &temp.pos[6], -1.0f, 1.0f))
		UpdateSqure();
}

void TestDrawSqure::AddSqure()
{

	unsigned int indices[] =
	{
		0,1,2,
		0,2,3
	};
	vb->AppendData(&temp, 1);
	ib->Append(indices,6);

}

void TestDrawSqure::UpdateSqure()
{
	vb->UpdateData(&temp, 0, 1);
}
