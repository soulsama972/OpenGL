#include "testDrawModel.h"


TestDrawModel::TestDrawModel() :color{ 255.0f, 255.0f, 255.0f, 255.0f }, t2{ 1,1,1 }
{
	ObjLoader::Obj obj;
	ObjLoader::loadObject("G:/projects/OpenGL/OpenGL/res/models/tt2.obj", obj);
	shader = new Shader("res/shaders/testDrawModel.shader");
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	layout.Push<float>(3);
	
	mesh.Init(layout, 0, obj.vertices.size(), 10);

	mesh.GetVertexBuffer().AppendData(obj.vertices.data(), obj.vertices.size());

	proj = glm::perspectiveFov(glm::radians(90.0f), 1920.0f, 1080.0f, 0.0f, 1000.0f);
	//proj = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, 0.0f, -1000.0f);
	

}

TestDrawModel::~TestDrawModel()
{
	delete shader;
}

void TestDrawModel::OnRender()
{
	mesh.Bind();
	shader->Bind();
	//view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),glm::vec3(0.0f, 0.0f, 0.0f),t2);
	//shader->SetUniformMat4f("u_MVP", proj * view * glm::translate(glm::mat4(1), t1));
	glm::mat4 m = glm::scale(glm::mat4(1), glm::vec3(t2));
	m = glm::translate(m, t1);
	shader->SetUniformMat4f("u_MVP", proj  * m);
	shader->SetUniform4f("u_Color", color[0], color[1], color[2], color[3]);
	renderer.Draw(mesh.GetVertexArray(), mesh.GetIndexBuffer(), mesh.GetVertexBuffer(), *shader);
}

void TestDrawModel::OnImGuiRender()
{
	ImGui::ColorEdit4("change Color", color);
	ImGui::SliderFloat3("translationA", &t1.x, -100.0f, 100.0f);
	ImGui::SliderFloat3("translationB", &t2.x, 0.0f, 4.0f);
}
