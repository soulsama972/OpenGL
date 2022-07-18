#include "testTextrue.h"

#include<random>
TestTextrue2D::TestTextrue2D() : t1(100, 100, 0), t2(300, 200, 0)
{
	srand(time(0));
	tex = new Texture("res/textures/goku.png");
	tex2 = new Texture("res/textures/goku2.png");
	shader = new Shader("res/shaders/testDrawTextrue.shader");
	index = 0;
	VertexBufferLayout layout;

	layout.Push<float>(2);
	layout.Push<float>(2);
	layout.Push<float>(3);
	layout.Push<float>(1);

	v p[] =
	{
		{{-50.f, -50.0f}, {0.0f, 0.0f},{0,0,0},1}, // 0
		{{ 50.f, -50.0f}, {1.0f, 0.0f},{0,0,0},1}, // 1
		{{ 50.f,  50.0f}, {1.0f, 1.0f},{0,0,0},1}, // 2
		{{-50.f,  50.0f}, {0.0f, 1.0f},{0,0,0},1}, // 3
	};

	uint ii[] =
	{
		0 ,1 ,2 ,
		2 ,3 ,0
	};
	mesh.Init(p, 4, ii, 6, layout, 6, 4, 1, true);



	//mesh.Init(layout, 6,4, 100000);
	//for (uint i = 0; i < 100000; i++)
	//	AddTextrue(glm::vec3(float(rand() % 10000), float(rand() % 10000), rand() % 100 ), rand() % 2);

	int order[] = { 0,1 };
	shader->Bind();
	shader->SetUniform1iv("u_Tex", 2, order);
	proj = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, 0.0f, -1000.0f);
	view = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));

}

TestTextrue2D::~TestTextrue2D()
{
	delete tex;
	delete shader;
}

void TestTextrue2D::OnRender()
{
	renderer.Clear(0.3f, 0.5f, 0.6f, 0.4f);
	shader->Bind();
	tex->Bind();
	tex2->Bind(1);

	shader->SetUniformMat4f("u_MVP", proj * view * glm::translate(glm::mat4(1), t1));
	mesh.Draw();

}

void TestTextrue2D::OnImGuiRender()
{
	ImGui::SliderFloat2("translationA", &t1.x, -1000.0f, 1000.0f);

}

void TestTextrue2D::AddTextrue(glm::vec3 pos, float  i)
{
	v p[] =
	{
		{{-50.f, -50.0f}, {0.0f, 0.0f},{pos.x,pos.y,pos.z},i}, // 0
		{{ 50.f, -50.0f}, {1.0f, 0.0f},{pos.x,pos.y,pos.z},i}, // 1
		{{ 50.f,  50.0f}, {1.0f, 1.0f},{pos.x,pos.y,pos.z},i}, // 2
		{{-50.f,  50.0f}, {0.0f, 1.0f},{pos.x,pos.y,pos.z},i}, // 3
	};

	uint ii[] =
	{
		0 + index,1 + index,2 + index,
		2 + index,3 + index,0 + index
	};

	mesh.Append((v*)&p, 4, ii, 6);
	index += 4;
}

void TestTextrue2D::UpdateTextrue(uint index, glm::vec2 pos)
{

}
