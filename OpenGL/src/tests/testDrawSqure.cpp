#include "testDrawSqure.h"

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



TestDrawSqure::TestDrawSqure() :color { 255.0f, 255.0f, 255.0f, 255.0f }
{
	memcpy(temp.pos, pos, sizeof(temp));
	index = 0;
	shader = new Shader("res/shaders/testDrawSqure.shader");
	VertexBufferLayout layout;
	layout.Push<float>(2);
	mesh.Init(layout, 6, 4, 10);
	AddSqure();
}

TestDrawSqure::~TestDrawSqure()
{
	delete shader;
}

void TestDrawSqure::OnRender()
{
	mesh.Bind();
	shader->Bind();
	shader->SetUniform4f("u_Color", color[0], color[1], color[2], color[3]);
	renderer.Draw(mesh.GetVertexArray(), mesh.GetIndexBuffer(), mesh.GetVertexBuffer(), *shader);
}

void TestDrawSqure::OnImGuiRender()
{
	ImGui::ColorEdit4("change Color", color);
	if (ImGui::Button("add Squre", { 100,20 }))
	{
		AddSqure();
		index++;
	}


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
	mesh.GetVertexBuffer().AppendData((v*)& pos, 1);
	mesh.GetIndexBuffer().Append(indices, 6);
}

void TestDrawSqure::UpdateSqure()
{
	mesh.GetVertexBuffer().UpdateData(&temp, index, 1);
}
