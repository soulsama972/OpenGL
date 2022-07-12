#include "testTextrue.h"



TestTextrue2D::TestTextrue2D() : t1(100, 100, 0), t2(300, 200, 0)
{

	float pos[] =
	{
		-50.f, -50.0f, 0.0f, 0.0f, // 0
		 50.f, -50.0f, 1.0f, 0.0f, // 1
		 50.f,  50.0f, 1.0f, 1.0f, // 2
		-50.f,  50.0f, 0.0f, 1.0f, // 3
	};
	uint indices[] =
	{
		0,1,2,
		2,3,0
	};

	vb = new VertexBuffer<v>((v*)&pos, 1, sizeof(v));
	va = new VertexArray();
	ib = new IndexBuffer(indices, 6, 6 * sizeof(uint));
	tex = new Textrue("res/textures/goku.png");
	shader = new Shader("res/shaders/testDrawTextrue.shader");
	VertexBufferLayout layout;

	layout.Push<float>(2);
	layout.Push<float>(2);

	va->AddBuffer(*vb, layout);
	va->Bind();
	shader->Bind();
	tex->Bind();

	proj = glm::ortho(0.0f, 1600.0f, 0.0f, 900.0f, -1.0f, 1.0f);
	view = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));

}

TestTextrue2D::~TestTextrue2D()
{
	delete tex;
	delete va;
	delete vb;
	delete ib;
	delete shader;
}

void TestTextrue2D::OnRender()
{
	renderer.Clear(0.3f, 0.5f, 0.6f, 0.4f);
	shader->SetUniformMat4f("u_MVP", proj * view * glm::translate(glm::mat4(1), t1));
	renderer.Draw(*va, *ib, *shader);

	shader->SetUniformMat4f("u_MVP", proj * view * glm::translate(glm::mat4(1), t2));
	renderer.Draw(*va, *ib, *shader);
}

void TestTextrue2D::OnImGuiRender()
{
	ImGui::SliderFloat2("translationA", &t1.x, 0.0f, 1600.0f);
	ImGui::SliderFloat2("translationB", &t2.x, 0.0f, 1600.0f);
}
